//
// Created by alissa on 8/9/24.
//

#include "ardiag.h"

AddRecurrenceDialog::AddRecurrenceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Enter Frequency: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer4->Add( m_staticText8, 0, wxALL, 5 );
	
	wxString frq_selectionChoices[] = { wxT("Daily"), wxT("Weekly"), wxT("Monthly") };
	int frq_selectionNChoices = sizeof( frq_selectionChoices ) / sizeof( wxString );
	frq_selection = new wxRadioBox( this, wxID_ANY, wxT("Select One:"), wxDefaultPosition, wxDefaultSize, frq_selectionNChoices, frq_selectionChoices, 1, wxRA_SPECIFY_COLS );
	frq_selection->SetSelection( 0 );
	fgSizer4->Add( frq_selection, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("End Date:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer4->Add( m_staticText9, 0, wxALL, 5 );
	
	date_selection = new wxCalendarCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	fgSizer4->Add( date_selection, 0, wxALL, 5 );
	
	ok_btn = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	
	ok_btn->SetDefault();
	fgSizer4->Add( ok_btn, 0, wxALL, 5 );
	
	cancel_btn = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( cancel_btn, 0, wxALL, 5 );
	
	
	this->SetSizer( fgSizer4 );
	this->Layout();
	fgSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	ok_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddRecurrenceDialog::OnOK ), NULL, this );
	cancel_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddRecurrenceDialog::OnCancel ), NULL, this );
}

AddRecurrenceDialog::~AddRecurrenceDialog(void){
	// Disconnect Events
	ok_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddRecurrenceDialog::OnOK ), NULL, this );
	cancel_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddRecurrenceDialog::OnCancel ), NULL, this );
	
}

//events
void AddRecurrenceDialog::OnOK(wxCommandEvent &event){
	this->EndModal(wxOK);
}

void AddRecurrenceDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxCANCEL);
}
