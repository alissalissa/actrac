//The panel to draw report data
#pragma once

#include <wx/wx.h>

#include "acreport.h"

class ReportPanel : public wxPanel {
public:
	ReportPanel(wxWindow*);
	~ReportPanel(void)=default;

	//Events
	void OnPaint(wxPaintEvent&);

	//Rendered
	void Render(wxClientDC&);
};