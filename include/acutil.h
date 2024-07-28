//Utility functions for use elsewhere in the project
#pragma once

#include <vector>

#define END_INDEX -1

template <class T> int binary_search(std::vector<T> haystack,T delimiter){
	if(haystack.size()==0)
		return 0;
	if(haystack.size()==1){
		if(delimiter==haystack[0])
			return 0;
		else if(delimiter<haystack[0])
			return 0;
		else
			return END_INDEX;
	}
	//haystack size>=2
	if(delimiter<haystack[haystack.size()/2]){
		std::vector<T> next_haystack;
		for(int i=0;i<(haystack.size()/2);i++)
			next_haystack.push_back(haystack[i]);
		int ind=binary_search<T>(next_haystack,delimiter);
		return (ind==END_INDEX)?haystack.size()/2:ind;
	}else if(haystack[haystack.size()/2]<delimiter){
		std::vector<T> next_haystack;
		for(int i=(haystack.size()/2);i<haystack.size();i++)
			next_haystack.push_back(haystack[i]);
		int ind=binary_search<T>(next_haystack,delimiter);
		ind+=(ind==END_INDEX)?0:(haystack.size()/2);
		return ind;
	}
	return haystack.size()/2;
}
