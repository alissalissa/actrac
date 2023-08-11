//Manages identifiers for an activity
//	IDs only need to be unique within a given date, not for all dates

#ifndef ACTRAC_IDGEN_H
#define ACTRAC_IDGEN_H

#include <sstream>
#include <string>
#include <vector>

#define ID_NO_INDEX -1

class ActivityID{
private:

	int index;
	std::string label;

public:

	//Constructors/destructor
	ActivityID(void);
	ActivityID(int,std::string);
	~ActivityID(void)=default;

	//Accessors
	int &Index(void);
	std::string &Label(void);
	std::string str(void);

	//operators
	ActivityID operator=(ActivityID);
	bool operator==(ActivityID);
	bool operator<(ActivityID);
	bool operator<=(ActivityID);
	bool operator>(ActivityID);
	bool operator>=(ActivityID);

};

#endif