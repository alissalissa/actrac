//
// Created by alissa on 8/9/24.
//

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobox.h>
#include <wx/calctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AddRecurrenceDialog
///////////////////////////////////////////////////////////////////////////////
class AddRecurrenceDialog : public wxDialog {
private:
	
	wxStaticText* m_staticText8;
	wxRadioBox* frq_selection;
	wxStaticText* m_staticText9;
	wxCalendarCtrl* date_selection;
	wxButton* ok_btn;
	wxButton* cancel_btn;
	
	// Virtual event handlers, override them in your derived class
	void OnOK( wxCommandEvent& event );
	void OnCancel( wxCommandEvent& event );


public:
	
	AddRecurrenceDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Recurrence"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
	
	~AddRecurrenceDialog(void);
	
};


