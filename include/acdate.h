//Slimmed down date class compatible with the enums in wxDateTime
//	Yes, wxDateTime exists, but we don't need all that for what we're doing.

#ifndef __ACTRAC_ACDATE_H__
#define __ACTRAC_ACDATE_H__

#include <cstdarg>
#include <sstream>
#include <string>
#include <vector>

#include <wx/datetime.h>

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

	//utilities
	std::vector<std::string> split(std::string,std::string);

public:
	//Constructors/destructors
	date(void)=default;
	date(short,month_t,short);
	date(const wxDateTime);
	date(date&);
	~date(void)=default;

	//Accessors/converters
	short &Day(void);
	month_t &Month(void);
	short &Year(void);
	std::string toStdStr(std::string="%mm%dd%yy");

	//operators
	bool operator==(date&);
	date &operator=(date&);
};

#endif