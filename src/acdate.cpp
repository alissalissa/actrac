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

date::date(const wxDateTime &haystack){
	day=haystack.GetDay();
	month=static_cast<month_t>(static_cast<int>(haystack.GetMonth())+1);
	year=haystack.GetYear();
}

date::date(const date &haystack){
	day=haystack.day;
	month=haystack.month;
	year=haystack.year;
	for(auto ac : haystack.activities)
		this->activities.push_back(ac);
}
/*****************END CONSTRUCTOR****************/

//Accessors / converters
short &date::Day(void){return day;}
month_t &date::Month(void){return month;}
short &date::Year(void){return year;}
std::vector<Activity> &date::Activities(void){return activities;}

std::string date::toStdStr(std::string format){
	std::ostringstream output;
	std::vector<std::string> components=split(format,"%");
	if(components.size()!=4)
		throw -2;
	components.erase(components.begin());
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
bool date::operator==(date haystack){
	if(month==haystack.Month() && day==haystack.Day() && year==haystack.Year())
		return true;
	return false;
}

bool date::operator!=(date haystack){
	return (this->operator==(haystack))?false:true;
}

bool date::operator==(wxDateTime haystack){
	date comparator(haystack);
	try{
		std::cout<<"Comparing "<<this->toStdStr()<<" with "<<comparator.toStdStr()<<std::endl;
	}catch(int e){
		std::cout<<"Caught exception code "<<e<<std::endl;
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
	}
	return this->operator==(comparator);
}

bool date::operator!=(wxDateTime haystack){
	return !(this->operator==(haystack));
}

date date::operator=(date haystack){
	day=haystack.Day();
	month=haystack.Month();
	year=haystack.Year();
	for(auto ac : haystack.activities)
		this->activities.push_back(ac);
	return haystack;
}

bool date::operator<(date h)const{
	date haystack(h);
	if(year<haystack.Year()) return true;
	if(month>=1 && month<haystack.Month()) return true;
	if(day<haystack.Day()) return true;
	return false;
}

/************************END OPERATORS****************/

//Container Management
void date::AddActivity(Activity a){
	activities.push_back(a);
}

void date::AddActivity(std::string l,std::vector<std::string> t,float h,bool c,int r,int rf){
	Activity ac(gen_ac_id(activities,l),l,t,h,c,r,rf);
	activities.push_back(ac);
}

void date::RemoveActivity(ActivityID idtr){
	if(activities.size()==1){
		if(activities[0].ID()==idtr)
			activities.erase(activities.begin());
	}else if(activities.size()>1){
		for(std::vector<Activity>::iterator it=activities.begin();it!=activities.end();it++){
			if((*it).ID()==idtr){
				activities.erase(it);
				break;
			}
		}
	}
}

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

ActivityID gen_ac_id(std::vector<Activity> existing,std::string new_label){
	int max=0;
	for_each(existing.begin(),existing.end(),[&](Activity ac){
		if(ac.Label()==new_label)
			max=(ac.ID().Index()>max)?ac.ID().Index():max;
	});
	ActivityID id(max+1,new_label);
	return id;
}

date create_date(wxDateTime haystack){
	date ret(haystack);
	return ret;
}