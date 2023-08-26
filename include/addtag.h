//Sub-dialog to add a tag to the tag list when adding an activity

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/combobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AddTagDialog
///////////////////////////////////////////////////////////////////////////////
class AddTagDialog : public wxDialog {
private:

	wxComboBox* tag_entry;
	wxButton* ok_btn;
	wxButton* m_button9;

	// Virtual event handlers, override them in your derived class
	virtual void OnOK( wxCommandEvent& event );
	virtual void OnCancel( wxCommandEvent& event );

public:

	AddTagDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Add Tag"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,125 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
	~AddTagDialog();

	//Accessors
	//FIXME this should behave differently if a tag is selected versus entered
	wxString get_tag(void){return tag_entry->GetValue();}

};
