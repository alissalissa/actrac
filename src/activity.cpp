#include "activity.h"

//Constructors
Activity::Activity(ActivityID i,std::string l,std::vector<std::string> t,float h,bool c,int r,int rf){
	id=i;
	label=l;
	for(auto nt : t)
		tags.push_back(nt);
	hours=h;
	confirmed=c;
	recurrences=r;
	recurrence_frq=rf;
}

Activity::Activity(const Activity &haystack){
	label=haystack.label;
	tags=haystack.tags;
	hours=haystack.hours;
	confirmed=haystack.confirmed;
	recurrences=haystack.recurrences;
	recurrence_frq=haystack.recurrence_frq;
}

/******************END CONSTRUCTORS*******************/

//Accessors and get/set
ActivityID &Activity::ID(void){return id;}
std::string &Activity::Label(void){return label;}
std::vector<std::string> &Activity::Tags(void){return tags;}
float &Activity::Hours(void){return hours;}
bool Activity::is_confirmed(void){return confirmed;}
void Activity::confirm(bool c){confirmed=c;}
int &Activity::Recurences(void){return recurrences;}
int &Activity::RecurrenceFrequency(void){return recurrence_frq;}

std::string Activity::AddTag(std::string t){
	tags.push_back(t);
	return t;
}

void Activity::RemoveTag(std::string tbr){
	int index=search(tags,tbr);
	while(index!=-1){
		std::vector<std::string>::iterator it=tags.begin();
		for(int i=0;i<index && it!=tags.end();i++)
			++it;
		tags.erase(it);
		index=search(tags,tbr);
	}
}

/******************END ACCESSORS******************/

//Propogation
std::vector <Activity> Activity::propogate(void){
	std::vector<Activity> ret;
	if(recurrences==0){
		return ret;
	}else{
		for(int i=1;i<=recurrences;i++){
			ActivityID nid(id.Index()+i,id.Label());
			Activity ac(nid,label,tags,hours,false,recurrences-i,recurrence_frq);
			ret.push_back(ac);
		}
	}
	return ret;
}

//Operators
Activity Activity::operator=(Activity haystack){
	label=haystack.Label();
	tags=haystack.Tags();
	hours=haystack.Hours();
	confirmed=haystack.is_confirmed();
	recurrences=haystack.Recurences();
	recurrence_frq=haystack.RecurrenceFrequency();
	return haystack;
}

bool Activity::operator==(Activity &haystack) const {
	if(haystack.Label()!=label)
		return false;
	if(haystack.Tags().size()!=tags.size())
		return false;
	for(int i=0;i<tags.size();i++)
		if(tags[i]!=haystack.Tags()[i])
			return false;
	if(haystack.Hours()!=hours)
		return false;
	if(haystack.is_confirmed()!=confirmed)
		return false;
	if(haystack.Recurences()!=recurrences)
		return false;
	if(haystack.RecurrenceFrequency()!=recurrence_frq)
		return false;
	return true;
}

bool Activity::operator!=(Activity &haystack) const {
	return !(this->operator==(haystack));
}

//Utilities
int Activity::search(std::vector<std::string> cont,std::string delimiter){
	for(int i=0;i<cont.size();i++)
		if(cont[i]==delimiter)
			return i;
	return -1;
}
