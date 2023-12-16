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
		int32_t date_section_size=0;
		handle.read(reinterpret_cast<char*>(&date_section_size),sizeof(int32_t));

		if(date_section_size>0){
			char *date_section_buffer=(char*)calloc(date_section_size+1,sizeof(char));
			handle.read(date_section_buffer,date_section_size);
			date_section_buffer[date_section_size]='\0';
			std::string date_section_stream(date_section_buffer);
			//Get the actual date streams
			std::vector<std::string> date_streams=split_str(date_section_stream,0x0d);

			//Process each date stream
			for(auto ds : date_streams){
				if(ds.find(0x0c)==std::string::npos){
					std::cout<<"throw 4"<<std::endl;
					sfexception ex;
					throw ex;
				}

				std::string date_string=ds.substr(0,ds.find(0x0c));
				std::vector<std::string> date_fields=split_str(date_string,'/');
				//FIXME this is where the exception is coming from
				date d(std::stoi(date_fields[1]),static_cast<month_t>(std::stoi(date_fields[0])),std::stoi(date_fields[2]));
				std::vector<std::string> activities=split_str(ds,0x0c);
				if(activities[0][0]!=0x0c || activities[0].length()!=1){
					std::cout<<"throw 0"<<std::endl;
					sfexception ex;
					throw ex;
				}

				activities.erase(activities.begin());
				std::vector<Activity> acs;
				for(auto ac_stream : activities){
					std::vector<std::string> fields=split_str(ac_stream,0x0e);
					if(fields.size()!=8){ //The number of expected fields
						std::cout<<"throw 1"<<std::endl;
						sfexception sf;
						throw sf;
					}
					std::vector<std::string> tag_fields_buffer=split_str(fields[3],0x0b);
					std::string tag_fields[tag_fields_buffer.size()+1];
					for(int i=0;i<tag_fields_buffer.size();i++)
						tag_fields[i]=tag_fields_buffer[i];
					tag_fields[tag_fields_buffer.size()]="\0";
					ActivityID id(std::stoi(fields[0]),fields[1]);
					Activity ac(id,fields[2],tag_fields,std::stof(fields[4]),std::stoi(fields[5]),std::stoi(fields[6]),std::stoi(fields[7]));
					d.AddActivity(ac);
				}
				dates.push_back(d);
			}
		}
		char final_byte='\0';
		handle.get(final_byte);
		if(final_byte!=ACSERIALIZE_MAGIC_NUMBER){
			std::cout<<"throw 2"<<std::endl;
			sfexception ex;
			throw ex;
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
