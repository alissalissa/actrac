#include "addtag.h"

///////////////////////////////////////////////////////////////////////////

AddTagDialog::AddTagDialog( wxWindow* parent, std::vector<std::string> tc,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	cache=tc;
	tag_entry = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	if(cache.size()>0)
		for_each(cache.begin(),cache.end(),[&](std::string t){
			wxString wt(t);
			tag_entry->Append(wt);
		});
	tag_entry->SetMinSize( wxSize( 300,-1 ) );

	bSizer7->Add(tag_entry, 0, wxALL, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	ok_btn = new wxButton( this, wxID_ANY, wxT("Add Label!"), wxDefaultPosition, wxDefaultSize, 0 );

	ok_btn->SetDefault();
	bSizer8->Add( ok_btn, 0, wxALL, 5 );

	m_button9 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_button9, 0, wxALL, 5 );
	
	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );

	this->SetSizer( bSizer7 );
	this->Layout();

	this->Centre( wxBOTH );
	this->Fit();
	
	// Connect Events
	ok_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddTagDialog::OnOK ), NULL, this );
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddTagDialog::OnCancel ), NULL, this );
}

AddTagDialog::~AddTagDialog()
{
	// Disconnect Events
	ok_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddTagDialog::OnOK ), NULL, this );
	m_button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddTagDialog::OnCancel ), NULL, this );
}

//Events
void AddTagDialog::OnOK(wxCommandEvent &event){
	this->EndModal(wxOK);
}

void AddTagDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxCANCEL);
}
