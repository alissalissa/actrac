#include "acreport.h"

//Exceptions
ACReportExcept::ACReportExcept(void) : std::exception() {
	message="Exception reached in generating report....";
}
const char *ACReportExcept::what(void) const noexcept {
	return message.c_str();
}

//Constructors
ACBaseReport::ACBaseReport(std::vector<date> haystack){
	data=this->process(haystack);
}

ACBaseReport::ACBaseReport(const ACBaseReport &haystack){
	for(auto label : haystack.labels())
		if(this->contains(label))
			data[label]+=haystack.point(label);
		else
			data[label]=haystack.point(label);
}

//Private
bool ACBaseReport::contains(std::string label) const noexcept{
	for(auto p : data)
		if(p.first==label)
			return true;
	return false;
}

bool ACBaseReport::contains(std::map<std::string,float> haystack,std::string delimiter){
	for(auto p : haystack)
		if(p.first==delimiter)
			return true;
	return false;
}

std::map<std::string,float> ACBaseReport::process(std::vector<date> haystack){
	std::map<std::string,float> ret;
	if(haystack.empty())
		return ret;
	for(date current_date : haystack){
		for(auto ac : current_date.Activities()){
			//TODO We need a way to tell if a map contains a key
			if(this->contains(ret,ac.Label()))
				ret[ac.Label()]+=ac.Hours();
			else
				ret[ac.Label()]=ac.Hours();
		}
	}
	return ret;
}

//Accessors
float ACBaseReport::point(std::string label) const {
	if(!contains(label))
		throw ACReportExcept();
	return data.at(label);
}

std::vector<std::string> ACBaseReport::labels(void) const {
	std::vector<std::string> ret;
	for(auto p : data)
		ret.push_back(p.first);
	return ret;
}
