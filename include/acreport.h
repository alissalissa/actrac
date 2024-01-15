//Class to handle report aggregation for all activities and dates
#pragma once

#include <exception>
#include <map>
#include <vector>

#include "acdate.h"
#include "activity.h"

class ACReportExcept : public std::exception {
private:
	std::string message;
public:
	ACReportExcept(void);
	virtual const char *what(void) const noexcept;
};

class ACBaseReport {
private:
	std::map<std::string,float> process(std::vector<date>);
	bool contains(std::string) const noexcept;
	bool contains(std::map<std::string,float>,std::string);
protected:
	std::map<std::string,float> data;

public:
	//Constructors
	ACBaseReport(void)=default;
	ACBaseReport(std::vector<date>);
	ACBaseReport(const ACBaseReport&);

	//Accessors
	float point(std::string) const;
	std::vector<std::string> labels(void) const;
};