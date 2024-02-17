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

//Renderer
void ReportPanel::Render(wxClientDC &dc){
	dc.SetPen(*wxBLACK_PEN);
	dc.DrawCircle(wxPoint(dc.GetSize().GetWidth()/2,dc.GetSize().GetHeight()/2),20);
}