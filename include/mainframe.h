#ifndef __ACTRAC_MAINFRAME_H__
#define __ACTRAC_MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>

#include <wx/string.h>
#include <wx/dataview.h>
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

#include <wx/wx.h>

///////////////////////////////////////////////////////////////////////////


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
	wxToggleButton* add_event;
	wxButton* delete_event_btn;
	wxButton* edit_event_btn;
	wxCalendarCtrl* m_calendar1;
	wxPanel* report_panel;
	wxMenuBar* menu_bar;
	wxMenu* file_menu;
	// Virtual event handlers, override them in your derived class
	//virtual void OnEditEvent( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnQuit( wxCommandEvent& );

public:

	MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,700 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL|wxVSCROLL );

	virtual ~MainFrame()=default;

};

#endif