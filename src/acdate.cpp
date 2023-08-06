//Implementation for date
#include "acdate.h"

//Constructor
date::date(short d,month_t m,short y){
	//error checking
	if(m<1 || m>12) throw -1;
	if(d<1 || d>31) throw -1;
	day=d;
	month=m;
	year=y;
}

date::date(const wxDateTime haystack){
	day=haystack.GetDay();
	month=static_cast<month_t>(haystack.GetMonth());
	year=haystack.GetYear();
}

date::date(date &haystack){
	day=haystack.Day();
	month=haystack.Month();
	year=haystack.Year();
}
/*****************END CONSTRUCTOR****************/

//Accessors / converters
short &date::Day(void){return day;}
month_t &date::Month(void){return month;}
short &date::Year(void){return year;}

std::string date::toStdStr(std::string format){
	std::ostringstream output;
	std::vector<std::string> components=split(format,"%");
	if(components.size()!=3)
		throw -2;
	for(int i=0;i<3;i++){
		switch(components[i][0]){
			case 'm':
				{
				if(components[i].length()!=2)
					throw -4;
				if(month<10)
					output<<0;
				output<<month<<'/';
				break;
				}
			case 'd':
				{
				if(components[i].length()!=2)
					throw -4;
				if(day<10)
					output<<0;
				output<<day<<'/';
				break;
				}
			case 'y':
				{
				if(components[i].length()!=2 && components[i].length()!=4)
					throw -4;
				//Get the year string
				std::ostringstream year_stream;
				year_stream<<year;
				std::string year_string=year_stream.str();
				if(components[i].length()==2)
					output<<year_string.substr(2,std::string::npos);
				else
					output<<year;
				output<<'/';
				break;
				}
			default:
				throw -3;
				break;
		}
	}
	std::string ret=output.str();
	return ret.substr(0,ret.length()-1); //get rid of that last '/'
}

/***************END ACCESSORS****************/

//Operators
//Comparator
bool date::operator==(date &haystack){
	if(month==haystack.Month() && day==haystack.Day() && year==haystack.Year())
		return true;
	return false;
}

date &date::operator=(date &haystack){
	day=haystack.Day();
	month=haystack.Month();
	year=haystack.Year();
	return haystack;
}

/************************END OPERATORS****************/

//Utilities
std::vector<std::string> date::split(std::string h,std::string delimiter){
	std::string haystack(h);
	std::vector<std::string> ret;
	while(haystack.find(delimiter)!=std::string::npos){
		ret.push_back(haystack.substr(0,haystack.find(delimiter)));
		haystack=haystack.substr(haystack.find(delimiter)+delimiter.length(),std::string::npos);
	}
	ret.push_back(haystack);
	return ret;
}
