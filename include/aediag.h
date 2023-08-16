//Diaog to add an event to a date
#pragma once

#include <wx/artprov.h>
#include <wx/event.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AddEventDialog
///////////////////////////////////////////////////////////////////////////////
//TODO flesh out events
//TODO integrate into the mainframe classs
class AddEventDialog : public wxDialog{
private:

	wxStaticText* m_staticText2;
	wxTextCtrl* ac_label_entry;
	wxStaticText* m_staticText21;
	wxSpinCtrlDouble* hour_entry;
	wxStaticText* m_staticText3;
	wxListBox* tag_entry;
	wxButton* ok_btn;
	wxButton* cancel_btn;

	// Virtual event handlers, override them in your derived class
	virtual void ValidateHourEntry( wxCommandEvent& event ) { event.Skip(); }
	virtual void OnOK( wxCommandEvent& event );
    virtual void OnCancel( wxCommandEvent& event );

public:

	AddEventDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add New Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,390 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
	~AddEventDialog();

};

