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
	data=haystack;
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
	if(!data.empty()){
		ACDateReport rep(data);
		wxString min_label(rep.min().toStdStr());
		dc.DrawLabel(min_label,wxRect(100,110,10,5));																		
	}
}
