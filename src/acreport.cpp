#include "acreport.h"
#include "../include/acreport.h"


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
	std::sort(ret.begin(),ret.end());
	return ret;
}

std::vector<std::string> ACBaseReport::trim_labels(void) const {
	std::vector<std::string> ret=this->labels();
	auto it= ret.begin();
	ret.erase(it);
	it=ret.begin();
	for(size_t i=0;i<ret.size();i++) ++it;
	ret.erase(it);
	return ret;
}

//Checkers
bool ACBaseReport::empty(void){
	return data.empty();
}

size_t ACBaseReport::size(void){
	return data.size();
}

//ACDateReport
//private
bool ACDateReport::contains_date(std::map<date,float> haystack,date delimiter)const{
	if(haystack.empty())
		return false;
	for(auto p : haystack)
		if(delimiter==p.first)
			return true;
	return false;
}

//protected
std::map<date,float> ACDateReport::date_process(std::vector<date> haystack){
	std::sort(haystack.begin(),haystack.end());
	std::map<date,float> ret;
	for(date d : haystack){
		float total=0;
		for(auto ac : d.Activities())
			total+=ac.Hours();
		if(contains_date(ret,d))
			ret[d]+=total;
		else
			ret[d]=total;
	}
	return ret;
}

ACDateReport::ACDateReport(std::vector<date> haystack) : ACBaseReport(haystack) {
	db_data=date_process(haystack);
}

//Accessors
float ACDateReport::date_point(date delimiter) const {
	if(!contains_date(db_data,delimiter))
		throw ACReportExcept();
	return db_data.at(delimiter);
}

std::vector<date> ACDateReport::sorted_dates(void) const {
	std::vector<date> ret;
	if(db_data.empty())
		return ret;
	for(auto p : db_data)
		ret.push_back(p.first);
	std::sort(ret.begin(),ret.end());
	return ret;
}

date ACDateReport::min(void) const {
	if(db_data.empty())
		throw ACReportExcept();
	std::vector<date> ds=this->sorted_dates();
	return ds[0];
}

date ACDateReport::max(void) const {
	if(db_data.empty())
		throw ACReportExcept();
	std::vector<date> ds=this->sorted_dates();
	return ds[ds.size()-1];
}

std::string ACDateReport::left_label(void) const {
	try{
		return this->min().toStdStr();
	}catch(ACReportExcept e){
		throw e;
	}
}

std::string ACDateReport::right_label(void) const {
	try{
		return this->max().toStdStr();
	}catch(ACReportExcept e){
		throw e;
	}
}
