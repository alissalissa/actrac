//Class to handle report aggregation for all activities and dates
#pragma once

#include <algorithm>
#include <exception>
#include <map>
#include <string>
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
	virtual std::map<std::string,float> process(std::vector<date>);
	virtual bool contains(std::string) const noexcept;
	virtual bool contains(std::map<std::string,float>,std::string);
protected:
	std::map<std::string,float> data;

public:
	//Constructors
	ACBaseReport(void)=default;
	ACBaseReport(std::vector<date>);
	ACBaseReport(const ACBaseReport&);

	//Accessors
	virtual float point(std::string) const;
	virtual std::vector<std::string> labels(void) const;
	virtual std::vector<std::string> trim_labels(void) const;
	virtual date min(void) const = 0;
	virtual date max(void) const = 0;
	virtual std::string left_label(void) const = 0;
	virtual std::string right_label(void) const = 0;

	//Checkers
	virtual bool empty(void);
	virtual size_t size(void);
};

class ACDateReport : public ACBaseReport {
private:
	std::map<date,float> db_data; //date_based data
	bool contains_date(std::map<date,float>,date) const;
protected:
	virtual std::map<date,float> date_process(std::vector<date>);
public:
	ACDateReport(void)=default;
	ACDateReport(std::vector<date>);

	//Accessors
	virtual float date_point(date) const;
	virtual std::vector<date> sorted_dates(void) const;
	virtual date min(void) const;
	virtual date max(void) const;
	virtual std::string left_label(void) const;
	virtual std::string right_label(void) const;
	[[nodiscard]] std::vector<std::string> labels(void) const override;
	[[nodiscard]] std::vector<std::string> trim_labels(void) const override;
};