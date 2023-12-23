//Data structure to handle activity Data

#ifndef __ACTRAC_ACTIVITY_H__
#define __ACTRAC_ACTIVITY_H__

//STL includes
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include "idgen.h"

class Activity {
private:

	ActivityID id;
	std::string label;
	std::vector<std::string> tags;
	float hours;
	bool confirmed;
	int recurrences;
	int recurrence_frq; //Measured in days

	//utilities
	int search(std::vector<std::string>,std::string);

public:

	//Constructors/destructor
	Activity(void)=default;
	Activity(ActivityID,std::string,std::vector<std::string>,float=1,bool=true,int=0,int=-1);
	Activity(const Activity&);
	~Activity(void)=default;

	//Accessors and get/set
	ActivityID &ID(void);
	std::string &Label(void);
	std::vector<std::string> &Tags(void);
	float &Hours(void);
	bool is_confirmed(void);
	void confirm(bool);
	int &Recurences(void);
	int &RecurrenceFrequency(void);
	std::string AddTag(std::string);
	void RemoveTag(std::string);

	//Propogates out a list of activities
	std::vector <Activity> propogate(void);

	//operators
	Activity operator=(Activity);
	bool operator==(Activity&) const;
	bool operator!=(Activity&) const;

};

#endif
