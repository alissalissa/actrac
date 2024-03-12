//Utility functions for use elsewhere in the project
#pragma once

#include <vector>

template <class T> int binary_search(std::vector<T> haystack,T delimiter){
	if(haystack.size()==0)
		return 0;
	if(haystack.size()==1){
		if(delimiter==haystack[0])
			return 0;
		else
			return delimiter<haystack[0]?0:1;
	}
	//haystack size>=2
	if(delimiter<haystack[haystack.size()/2]){
		std::vector<T> next_haystack;
		for(int i=0;i<(haystack.size()/2);i++)
			next_haystack.push_back(haystack[i]);
		return binary_search<T>(next_haystack,delimiter);
	}else if(haystack[haystack.size()/2]<delimiter){
		std::vector<T> next_haystack;
		for(int i=(haystack.size()/2);i<haystack.size();i++)
			next_haystack.push_back(haystack[i]);
		return binary_search<T>(next_haystack,delimiter)+next_haystack.size();
	}
	return haystack.size()/2;
}