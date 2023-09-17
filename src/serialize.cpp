#include "serialize.h"

bool write_to_file(std::string filename,std::vector<date> dates,std::vector<std::string> tags){
	std::ofstream output(filename.c_str(),std::ios_base::out | std::ios_base::binary);
	if(!output.is_open()){
		std::cout<<"Unable to open file for writing...."<<std::endl;
		return false;
	}
	//Write the magic number to get started
	try{
		output.write(reinterpret_cast<const char*>(&ACSERIALIZE_MAGIC_NUMBER),sizeof(int32_t));
		//Calculate the size of the next section
		//	We start with the number of tag seperators, INCLUDING the end of section magic number
		int32_t tag_section_size=tags.size();
		for_each(tags.begin(),tags.end(),[&](std::string tag){
			tag_section_size+=tag.length();
		});

		//write the tag section to the file
		output.write(reinterpret_cast<char*>(&tag_section_size),sizeof(int32_t));
		for_each(tags.begin(),tags.end(),[&](std::string tag){
			output.write(tag.c_str(),tag.length());
			const int32_t seperator=(tag==(*tags.end()))?0x0d:0x0a;
			output.write(reinterpret_cast<const char*>(&seperator),sizeof(int32_t));
		});

		//Create a string to encapsulate the date section
		//	The length of the section will be prepended after
		std::ostringstream date_info;
		for_each(dates.begin(),dates.end(),[&](date d){
			date_info<<d.toStdStr("%mm%dd%yyyy");
			for_each(d.Activities().begin(),d.Activities().end(),[&](Activity ac){
				date_info<<(char)0x0c;
				date_info<<ac.ID().str();
				date_info<<(char)0x0e;
				date_info<<ac.Tags().size();
				for_each(ac.Tags().begin(),ac.Tags().end(),[&](std::string t){
					date_info<<t;
					if(t!=(*ac.Tags().end()))
						date_info<<0x0b;
				});
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
			});
			if(d!=(*dates.end()))
				date_info<<0x0d;
		});
		std::string date_info_buffer=date_info.str();
		std::ostringstream date_info_length;
		date_info_length<<date_info_buffer.length();
		std::string date_info_str=date_info_length.str()+date_info_buffer;
		output.write(date_info_str.c_str(),date_info_str.length());
		output.write(reinterpret_cast<const char*>(ACSERIALIZE_MAGIC_NUMBER),sizeof(int32_t));
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		output.close();
		return false;
	}
	
	output.close();
	return true;
}
