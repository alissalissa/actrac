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
	wxString value((col==0)?data[row].first:str_value.str());
	dest=value;
	return;
}

bool DVModel::SetValueByRow(const wxVariant &haystack,unsigned int one,unsigned int two){
	return true;
}