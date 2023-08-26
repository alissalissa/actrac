//Diaog to add an event to a date
#pragma once

//#include <iostream>

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
#include <wx/menu.h>

#include "addtag.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AddEventDialog
///////////////////////////////////////////////////////////////////////////////
//TODO How do we edit tags?
class AddEventDialog : public wxDialog{
private:

	wxStaticText* m_staticText2;
	wxTextCtrl* ac_label_entry;
	wxStaticText* m_staticText21;
	wxSpinCtrlDouble* hour_entry;
	wxStaticText* m_staticText3;
	wxListBox* tag_entry;
	wxMenu* tag_entry_context_menu;
	wxButton* ok_btn;
	wxButton* cancel_btn;

	// Virtual event handlers, override them in your derived class
	virtual void OnAddTag( wxCommandEvent& event );
	virtual void OnContextClick(wxContextMenuEvent &event);
	virtual void OnOK( wxCommandEvent& event );
    virtual void OnCancel( wxCommandEvent& event );

public:

	AddEventDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add New Event"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,390 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
	~AddEventDialog();

};

