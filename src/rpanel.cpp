//Implementation of the report panel
#include "rpanel.h"

//Constructors/destructor
ReportPanel::ReportPanel(wxWindow *master) : wxPanel(master){
	Bind(wxEVT_PAINT,&ReportPanel::OnPaint,this,wxID_ANY);
}

//Events
void ReportPanel::OnPaint(wxPaintEvent &evt){
	wxClientDC drawer(this);
	this->Render(drawer);
}

void ReportPanel::updateBackend(std::vector<date> haystack){
	data=new ACDateReport(haystack);
}

//Renderer
void ReportPanel::Render(wxClientDC &dc){
	DrawHistogramAxes(dc);
	DrawHistogramLabels(dc);
}

//Drawing
void ReportPanel::DrawHistogramAxes(wxClientDC &dc){
	//Set up the palette
	dc.SetPen(wxPen(*wxBLACK,5));
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
	dc.SetBrush(*wxBLACK_BRUSH);

	//Get dimensions
	wxCoord xwidth=0,ywidth=0;
	dc.GetSize(&xwidth,&ywidth);

	//Draw out the base of the graph
	dc.DrawLine(100,100,100,ywidth-50);
	dc.DrawLine(100,ywidth-50,xwidth-50,ywidth-50);
}

void ReportPanel::DrawHistogramLabels(wxClientDC &dc){
	dc.SetFont(*wxNORMAL_FONT);
	dc.SetTextForeground(*wxBLACK);
	try{
		if(!data->empty()){
			wxString min_label(data->left_label());
			wxString max_label(data->right_label());
			wxCoord xw=0,yw=0;
			dc.GetSize(&xw,&yw);
			dc.DrawText(min_label,100,yw-40);
			dc.DrawText(max_label,xw-70,yw-40);
		}
	}catch(ACReportExcept e){
		std::cout<<"ACReportExcept caught....\n"<<std::endl;
	}
}
