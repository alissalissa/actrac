//date class compatible with the enums in wxDateTime
//	Tracks activities for a given date

#ifndef __ACTRAC_ACDATE_H__
#define __ACTRAC_ACDATE_H__

#include <algorithm>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <wx/datetime.h>

#include "activity.h"
#include "idgen.h"

typedef enum Month{
	JAN=1,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC,
	INV
}month_t;

class date{
private:
	month_t month;
	short day;
	short year;

	std::vector <Activity> activities;

	//utilities
	std::vector<std::string> split(std::string,std::string) const;

public:
	//Constructors/destructors
	date(void)=default;
	date(short,month_t,short);
	date(const wxDateTime&);
	date(const date&);
	~date(void)=default;

	//Accessors/converters
	short &Day(void);
	month_t &Month(void);
	short &Year(void);
	std::string toStdStr(std::string="%mm%dd%yy") const;
	std::vector<Activity> &Activities(void);

	//Container management
	void AddActivity(Activity);
	void AddActivity(std::string,std::vector<std::string>,float=1,bool=true,int=0,int=-1);
	void RemoveActivity(ActivityID);

	//operators
	bool operator==(date);
	bool operator!=(date);
	bool operator==(wxDateTime);
	bool operator!=(wxDateTime);
	date operator=(date);
	bool operator<(date) const;
	
};

ActivityID gen_ac_id(std::vector<Activity>,std::string);
date create_date(wxDateTime);

#endif