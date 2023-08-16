#include "aediag.h"

///////////////////////////////////////////////////////////////////////////

AddEventDialog::AddEventDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 4, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Activity Label:"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALL, 5 );

	ac_label_entry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), wxTE_DONTWRAP|wxTE_NO_VSCROLL );
	fgSizer1->Add( ac_label_entry, 0, wxALL, 5 );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Hours:"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	m_staticText21->Wrap( -1 );
	fgSizer1->Add( m_staticText21, 0, wxALL, 5 );

	hour_entry = new wxSpinCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 300,-1 ), wxSP_ARROW_KEYS, 0, 24, 0 );
	fgSizer1->Add(hour_entry, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Tags"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALL, 5 );

	tag_entry = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 300,200 ), 0, NULL, 0 );
	fgSizer1->Add( tag_entry, 0, wxALL, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	ok_btn = new wxButton( this, wxID_ANY, wxT("Submit!"), wxDefaultPosition, wxDefaultSize, 0 );

	ok_btn->SetDefault();
	bSizer7->Add( ok_btn, 0, wxALL, 5 );

	cancel_btn = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( cancel_btn, 0, wxALL, 5 );


	fgSizer1->Add( bSizer7, 1, wxEXPAND, 5 );


	this->SetSizer( fgSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	hour_entry->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AddEventDialog::ValidateHourEntry ), NULL, this );
	ok_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnOK ), NULL, this );
	cancel_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnCancel ), NULL, this );
}

AddEventDialog::~AddEventDialog()
{
	// Disconnect Events
	hour_entry->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( AddEventDialog::ValidateHourEntry ), NULL, this );
	ok_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnOK ), NULL, this );
	cancel_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnCancel ), NULL, this );

}

//Event management
void AddEventDialog::OnOK(wxCommandEvent &event){
    this->EndModal(wxOK);
}

void AddEventDialog::OnCancel(wxCommandEvent &event){
    this->EndModal(wxCANCEL);
}