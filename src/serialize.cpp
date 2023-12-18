#include "serialize.h"

bool write_to_file(std::string filename,std::vector<date> dates,std::vector<std::string> tags){
	std::fstream output(filename.c_str(),std::ios_base::out | std::ios_base::binary);
	if(!output.is_open()){
		std::cout<<"Unable to open file for writing...."<<std::endl;
		return false;
	}
	//Write the magic number to get started
	try{
		output.put(ACSERIALIZE_MAGIC_NUMBER);
		//Calculate the size of the next section
		//	We start with the number of tag seperators, INCLUDING the end of section magic number
		int32_t tag_section_size=tags.size();
		for(auto tag : tags)
			tag_section_size+=tag.length();

		//write the tag section to the file
		output.write(reinterpret_cast<char*>(&tag_section_size),sizeof(int32_t));
		for(auto tag : tags){
			output.write(tag.c_str(),tag.length());
			const char seperator=(tag==tags[tags.size()-1])?0x0d:0x0a;
			output.put(seperator);
		}

		//Date Section
		const size_t number_of_dates=dates.size();
		output.write(reinterpret_cast<const char*>(&number_of_dates),sizeof(size_t));
		for(auto d : dates){
			output.write(d.toStdStr("%mm%dd%yyyy").c_str(),d.toStdStr("%mm%dd%yyyy").length());
			for(auto ac : d.Activities()){
				output.put(0x0c);
				const int index=ac.ID().Index();
				output.write(reinterpret_cast<const char*>(&index),sizeof(int));
				size_t lab_length=ac.Label().length();
				output.write(reinterpret_cast<char*>(&lab_length),sizeof(size_t));
				output.write(ac.Label().c_str(),ac.Label().length());
				const size_t n_of_tags=ac.Tags().size();
				output.write(reinterpret_cast<const char*>(&n_of_tags),sizeof(size_t));
				for(auto tag : ac.Tags()){
					output.write(tag.c_str(),tag.length());
					output.put(0x0b);
				}
				output.write(reinterpret_cast<char*>(&ac.Hours()),sizeof(float));
				output.put((ac.is_confirmed())?0x01:0x00);
				//recurrences
				output.write(reinterpret_cast<char*>(&ac.Recurences()),sizeof(int));
				output.write(reinterpret_cast<char*>(&ac.RecurrenceFrequency()),sizeof(int));
				//Ending byte
				if(ac!=d.Activities()[d.Activities().size()-1])
					output.put(0x0c);
			}
			if(d!=dates[dates.size()-1])
				output.put(0x0d);
		}
		output.put(ACSERIALIZE_MAGIC_NUMBER);
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		output.close();
		return false;
	}
	
	output.close();
	return true;
}

bool read_from_file(std::string filename,std::vector<date> &dates,std::vector<std::string> &tags_cache){
	std::fstream handle(filename.c_str(),std::ios_base::in | std::ios_base::binary);
	if(!handle.is_open())
		return false;
	try{
		char first_byte='\0';
		handle.get(first_byte);
		if(first_byte!=ACSERIALIZE_MAGIC_NUMBER){
			std::cout<<"File corrupted!"<<std::endl;
			handle.close();
			return false;
		}

		//Reconstruct the tag cache
		int32_t tag_section_size=0;
		handle.read(reinterpret_cast<char*>(&tag_section_size),sizeof(int32_t));
		char *tag_stream_buffer=(char*)calloc(tag_section_size,sizeof(char));
		handle.read(tag_stream_buffer,tag_section_size);
		std::string tag_stream(tag_stream_buffer);
		std::vector<std::string> tags_cache_buffer=split_str(tag_stream,0x0a);
		int tcb_end=tags_cache_buffer.size()-1;
		if(tags_cache_buffer[tcb_end][tags_cache_buffer[tcb_end].length()-1]!=0x0d){
			std::cout<<"Tags section corrupted!"<<std::endl;
			handle.close();
			return false;
		}
		tags_cache_buffer[tcb_end]=tags_cache_buffer[tcb_end].substr(0,tags_cache_buffer[tcb_end].length()-1);
		for(auto tag : tags_cache_buffer)
			tags_cache.push_back(tag);
		
		//Get the stream of date info
		size_t date_section_size=0;
		handle.read(reinterpret_cast<char*>(&date_section_size),sizeof(size_t));
		for(size_t i=0;i<date_section_size;i++){
			//First we read in the date
			char *date_string_buffer=(char*)calloc(11,sizeof(char));
			handle.read(date_string_buffer,10);
			date_string_buffer[10]='\0';
			std::string date_string(date_string_buffer);
			free(date_string_buffer);
			std::vector<std::string> date_fields=split_str(date_string,'/');
			if(date_fields.size()!=3)
				throw sfexception();
			date date_buffer(std::stoi(date_fields[1]),static_cast<month_t>(std::stoi(date_fields[0])),std::stoi(date_fields[2]));
			
			//Next we read all the activities into this date object
			char placeholder='\0';
			handle.get(placeholder);
			while(placeholder==0x0c){
				int idn=-1;
				handle.read(reinterpret_cast<char*>(&idn),sizeof(int));

				size_t label_length=-1;
				handle.read(reinterpret_cast<char*>(&label_length),sizeof(size_t));
				char *label_buffer=static_cast<char*>(calloc(label_length+1,sizeof(char)));
				handle.read(label_buffer,label_length);
				label_buffer[label_length]='\0';
				std::string label(label_buffer);
				free(label_buffer);

				size_t n_of_tags=-1;
				handle.read(reinterpret_cast<char*>(&n_of_tags),sizeof(size_t));
				std::vector<std::string> ac_tags;
				for(size_t j=0;j<n_of_tags;j++){
					std::string t="";
					char b='\0';
					handle.get(b);
					while(b!=0x0b){
						t+=b;
						handle.get(b);
					}
					ac_tags.push_back(t);
				}

				float hours=0.0;
				handle.read(reinterpret_cast<char*>(&hours),sizeof(float));

				char confirmed_buffer=0x00;
				handle.get(confirmed_buffer);
				bool confirmed=(confirmed_buffer)?true:false;

				int32_t recurrences=0;
				handle.read(reinterpret_cast<char*>(&recurrences),sizeof(int32_t));
				int32_t recurrence_frq=0;
				handle.read(reinterpret_cast<char*>(&recurrence_frq),sizeof(int32_t));
				
				ActivityID new_id(idn,label);
				if(ac_tags.size()>0)
					ac_tags.push_back("\0");
				Activity ac(new_id,label,ac_tags.data(),hours,confirmed,recurrences,recurrence_frq);
				date_buffer.AddActivity(ac);

				handle.get(placeholder);
			}
			dates.push_back(date_buffer);
			//TODO what do we do to cleanup after we add the dates?
			//	Are there formatting checks we should be making against the file here?
			if(i<date_section_size-1 && placeholder!=0x0d)
				throw sfexception();
			if(i==date_section_size-1 && placeholder!=ACSERIALIZE_MAGIC_NUMBER)
				throw sfexception();
		}
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		handle.close();
		return false;
	}

	handle.close();
	return true;
}

std::vector<std::string> split_str(std::string haystack,char delimiter){
	std::vector<std::string> ret;
	if(delimiter=='\0'){
		for(int i=0;i<haystack.length();i++)
			ret.push_back(haystack.substr(i,1));
		return ret;
	}
	while(haystack.find(delimiter)!=std::string::npos){
		ret.push_back(haystack.substr(0,haystack.find(delimiter)));
		haystack=haystack.substr(haystack.find(delimiter)+1,std::string::npos);
	}
	ret.push_back(haystack);
	return ret;
}

//Exception information
sfexception::sfexception(void) : std::exception() {
	message="File is corrupted!";
}

const char *sfexception::what(void) const noexcept {
	return message.c_str();
}
