//Backend model for the mainframe data view

#ifndef __ACTRAC_DVM_H__
#define __ACTRAC_DVM_H__

#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <wx/dataview.h>
#include <wx/wx.h>

template <class T1,class T2> class DVPair {
public:
	T1 first;
	T2 second;

	//So it can be contained in a std::vector
	DVPair(const DVPair<T1,T2> &haystack){
		this->first=haystack.first;
		this->second=haystack.second;
	}
	//Just a general purpose constructor set
	DVPair(void)=default;
	DVPair(T1 f,T2 s){
		this->first=f;
		this->second=s;
	}

	~DVPair(void)=default;
	
	//So it can be sorted
	bool operator<(const DVPair<T1,T2> haystack) const{
		if(this->first < haystack.first)
			return true;
		if(this->first > haystack.first)
			return false;
		if(this->second<haystack.second)
			return true;
		return false;
	}

	//So it can be searched
	bool operator==(const DVPair<T1,T2> haystack) const {
		if(this->first!=haystack.first)
			return false;
		if(this->second!=haystack.second)
			return false;
		return true;
	}

};

class DVModel : public wxDataViewVirtualListModel {
private:

	std::vector<DVPair<std::string,float> > data;

public:

	//Constructors/Destructors
	DVModel(void)=default;
	~DVModel(void)=default;

	//Accessors / modifiers
	void GetValueByRow(wxVariant&,unsigned int,unsigned int) const wxOVERRIDE;
	bool SetValueByRow(const wxVariant&,unsigned int,unsigned int) wxOVERRIDE;
	bool AddRow(const DVPair<std::string,float>*);
	bool DeleteRow(const unsigned int);
	int GetRowByItem(const wxDataViewItem) const;

	void Rebuild(std::vector<DVPair<std::string,float> >);

};

#endif