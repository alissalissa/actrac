#include "idgen.h"

//Constructors
ActivityID::ActivityID(void){
	index=ID_NO_INDEX;
	label="";
}

ActivityID::ActivityID(int i,std::string l){
	index=i;
	label=l;
}

//Accessors
int &ActivityID::Index(void){return index;}
std::string &ActivityID::Label(void){return label;}
std::string ActivityID::str(void){
	std::ostringstream str;
	str<<index;
	str<<label;
	return str.str();
}

//Operators
ActivityID &ActivityID::operator=(ActivityID &haystack){
	index=haystack.Index();
	label=haystack.Label();
	return haystack;
}

bool ActivityID::operator==(ActivityID haystack){
	return (haystack.Index()==index && haystack.Label()==label);
}

bool ActivityID::operator<(ActivityID haystack){
	return (index<haystack.Index());
}

bool ActivityID::operator<=(ActivityID haystack){
	return (index<=haystack.Index());
}

bool ActivityID::operator>(ActivityID haystack){
	return (index>haystack.Index());
}

bool ActivityID::operator>=(ActivityID haystack){
	return (index>=haystack.Index());
}