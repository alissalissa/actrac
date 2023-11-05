//Implementation for the DVModel and DVPair classes
#include "dvmodel.h"

void DVModel::GetValueByRow(wxVariant &dest,unsigned int row,unsigned int col) const{
	if(row>=data.size())
		return;
	if(col>=2)
		return;
	std::ostringstream str_value;
	if(col==1)
		str_value<<data[row].second;
	//Debug code
	//std::cout<<"Column being called ="<<col<<std::endl;
	wxString value((col==0)?data[row].first:str_value.str());
	dest=value;
	return;
}

bool DVModel::SetValueByRow(const wxVariant &haystack,unsigned int row,unsigned int col){
	if(row>=data.size() || col>1)
		return false;
	if(col==0){
		data[row].first=haystack.GetString().ToStdString();
		RowChanged(row);
		return true;
	}
	data[row].second=atof(haystack.GetString().ToStdString().c_str());
	RowChanged(row);
	return true;
}

bool DVModel::AddRow(const DVPair<std::string,float> *haystack){
	try{
		//FIXME this can be more efficient with a binary search instead of resorting every time
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

int DVModel::GetRowByItem(const wxDataViewItem item) const {
	for(unsigned int i=0;i<data.size();i++)
		if(this->GetItem(i)==item)
			return i;
	return -1;
}

void DVModel::Rebuild(std::vector<DVPair<std::string,float> > new_set){
	data.clear();
	data=new_set;
	Reset(data.size());
}
