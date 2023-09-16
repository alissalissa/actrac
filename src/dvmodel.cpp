//Implementation for the DVModel and DVPair classes
#include "dvmodel.h"

int DVModel::search(const DVPair<std::string,float> haystack) const {
	for(int i=0;i<data.size();i++)
		if(data[i]==haystack)
			return i;
	return -1;
}

void DVModel::GetValueByRow(wxVariant &dest,unsigned int row,unsigned int col) const{
	if(row>=data.size())
		return;
	if(col>=2)
		return;
	std::ostringstream str_value;
	if(col==1)
		str_value<<data[row].second;
	wxString value((col==0)?data[row].first:str_value.str());
	dest=value;
	return;
}

bool DVModel::SetValueByRow(const wxVariant &haystack,unsigned int row,unsigned int col){
	if(row>=data.size() || col>1)
		return false;
	if(col==0){
		data[row].first=haystack.GetString().ToStdString();
		return true;
	}
	data[row].second=atof(haystack.GetString().ToStdString().c_str());
	RowChanged(row);
	return true;
}

bool DVModel::AddRow(const DVPair<std::string,float> *haystack){
	try{
		data.push_back(*haystack);
		std::sort(data.begin(),data.end());
		Reset(data.size());
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		return false;
	}
	return true;
}

bool DVModel::DeleteRow(const unsigned int row){
	try{
		if(row==0){
			data.erase(data.begin());
		}else{
			std::vector<DVPair<std::string,float> >::iterator it=data.begin();
			for(int i=1;i<=row;i++)
				++it;
			data.erase(it);
		}
		RowDeleted(row);
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		return false;
	}
	return true;
}
