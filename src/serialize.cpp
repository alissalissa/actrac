#include "serialize.h"

bool write_to_file(std::string filename,std::vector<date> dates,std::vector<std::string> tags){
	std::ofstream output(filename.c_str(),std::ios_base::out | std::ios_base::binary);
	if(!output.is_open()){
		std::cout<<"Unable to open file for writing...."<<std::endl;
		return false;
	}
	//Write the magic number to get started
	try{
		output.write(&ACSERIALIZE_MAGIC_NUMBER,sizeof(char));
		//Calculate the size of the next section
		//	We start with the number of tag seperators, INCLUDING the end of section magic number
		int32_t tag_section_size=tags.size();
		for(auto tag : tags)
			tag_section_size+=tag.length();

		//write the tag section to the file
		output.write(reinterpret_cast<char*>(&tag_section_size),sizeof(int32_t));
		for(auto tag : tags){
			output.write(tag.c_str(),tag.length());
			const int32_t seperator=(tag==tags[tags.size()-1])?0x0d:0x0a;
			output.write(reinterpret_cast<const char*>(&seperator),sizeof(int32_t));
		}

		//Create a string to encapsulate the date section
		//	The length of the section will be prepended after
		std::ostringstream date_info;
		for(auto d : dates){
			date_info<<d.toStdStr("%mm%dd%yyyy");
			for(auto ac : d.Activities()){
				date_info<<(char)0x0c;
				date_info<<ac.ID().Index();
				date_info<<(char)0x0e;
				date_info<<ac.ID().Label();
				date_info<<(char)0x0e;
				date_info<<ac.Tags().size();
				date_info<<0x0e;
				for(auto t : ac.Tags()){
					date_info<<t;
					if(t!=ac.Tags()[ac.Tags().size()-1])
						date_info<<0x0b;
				}
				date_info<<0x0e;
				date_info<<ac.Hours();
				date_info<<0x0e;
				if(ac.is_confirmed())
					date_info<<0x01;
				else
					date_info<<0x00;
				date_info<<0x0e;
				date_info<<ac.Recurences();
				date_info<<0x0e;
				date_info<<ac.RecurrenceFrequency();
				if(ac!=(*d.Activities().end()))
					date_info<<0x0c;
			}
			if(d!=dates[dates.size()-1])
				date_info<<0x0d;
		};
		std::string date_info_buffer=date_info.str();
		std::ostringstream date_info_length;
		date_info_length<<date_info_buffer.length()<<date_info_buffer;
		output.write(date_info_length.str().c_str(),date_info_length.str().length());
		output.write(&ACSERIALIZE_MAGIC_NUMBER,sizeof(char));
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
		if(handle.get()!=ACSERIALIZE_MAGIC_NUMBER){
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
		for_each(tags_cache_buffer.begin(),tags_cache_buffer.end(),[&](std::string tag){
			tags_cache.push_back(tag);
		});

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
			for_each(date_streams.begin(),date_streams.end(),[&](std::string ds){
				if(ds.find(0x0c)==std::string::npos){
					sfexception ex;
					throw ex;
				}

				std::string date_string=ds.substr(0,ds.find(0x0c));
				std::vector<std::string> date_fields=split_str(date_string,'/');
				date d(std::stoi(date_fields[1]),static_cast<month_t>(std::stoi(date_fields[0])),std::stoi(date_fields[2]));
				std::vector<std::string> activities=split_str(ds,0x0c);
				if(activities[0][0]!=0x0c || activities[0].length()!=1){
					sfexception ex;
					throw ex;
				}

				activities.erase(activities.begin());
				std::vector<Activity> acs;
				for_each(activities.begin(),activities.end(),[&](std::string ac_stream){
					std::vector<std::string> fields=split_str(ac_stream,0x0e);
					if(fields.size()!=8){ //The number of expected fields
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
				});
				dates.push_back(d);
			});
		}
		if(handle.get()!=ACSERIALIZE_MAGIC_NUMBER){
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
