#ifndef __ACTRAC_MAINFRAME_H__
#define __ACTRAC_MAINFRAME_H__

//#include <algorithm>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>

#include <wx/string.h>
#include <wx/dataview.h>
#include <wx/datetime.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/tglbtn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/calctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/radiobox.h>

#include <wx/wx.h>

#include "aediag.h"
#include "acdate.h"
#include "activity.h"
#include "acutil.h"
#include "dvmodel.h"
#include "idgen.h"
#include "rpanel.h"
#include "serialize.h"

///////////////////////////////////////////////////////////////////////////
class MFException : std::exception {
public:
	const char *what(void) const noexcept;
};

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame {
private:

	wxDataViewCtrl* otd_activities;
	wxDataViewColumn* activity_name;
	wxDataViewColumn* activity_time;
	wxNotebook* view_selector;
	wxPanel* tracker_panel;
	wxPanel *report_panel;
	wxRadioBox *report_radio;
	wxButton* add_evt_btn;
	wxButton* delete_event_btn;
	wxButton* edit_event_btn;
	wxCalendarCtrl* date_selector;
	wxButton *today_button;
	ReportPanel* drawer_panel;
	wxMenuBar* menu_bar;
	wxMenu* file_menu;
	DVModel *activity_model;

	void OnQuit( wxCommandEvent& );
	void OnAddEvent(wxCommandEvent&);
	void OnEditEvent(wxCommandEvent&);
	void OnRemoveEvent(wxCommandEvent &evt);
	void OnSave(wxCommandEvent&);
	void OnLoad(wxCommandEvent&);
	void OnSelectActivity(wxDataViewEvent&);
	void OnSelectDate(wxCalendarEvent&);
	void OnToday(wxCommandEvent&);
	void OnPageSelect(wxNotebookEvent&);

	//Intternal model/view
	std::vector <date> utilized_dates;
	std::vector <std::string> tags_cache;
	int selected_row;
	//void update_view(void);

	void add_to_tags_cache(std::string);
	void add_date(wxDateTime);
	bool date_exists(wxDateTime);

	std::vector<Activity> activities_from_selected_date(wxDateTime);

public:

	MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL|wxVSCROLL );

	virtual ~MainFrame();

};

#endif
