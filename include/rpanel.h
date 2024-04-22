//The panel to draw report data
#pragma once

#include <iostream>
#include <vector>

#include <wx/wx.h>

#include "acdate.h"
#include "acreport.h"

//TODO how do we want to store data for this panel?
class ReportPanel : public wxPanel {
private:

	ACBaseReport *data;

	void DrawHistogramAxes(wxClientDC&);
	void DrawHistogramLabels(wxClientDC&);

public:
	ReportPanel(wxWindow*);
	~ReportPanel(void)=default;

	//Events
	void OnPaint(wxPaintEvent&);
	void updateBackend(std::vector<date>);

	//Rendered
	void Render(wxClientDC&);
};