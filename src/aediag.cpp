#include "../include/aediag.h"

///////////////////////////////////////////////////////////////////////////

AddEventDialog::AddEventDialog(wxWindow* parent, std::vector<std::string> tc, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	cache=tc;

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 5, 2, 0, 0 );
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

	hour_entry = new wxSpinCtrlDouble( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 300,-1 ), wxSP_ARROW_KEYS, 0, 24, 0.000000, 0.25 );
	hour_entry->SetDigits( 2 );
	fgSizer1->Add( hour_entry, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Tags"), wxDefaultPosition, wxSize( 125,-1 ), 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALL, 5 );

	tag_entry = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 300,200 ), 0, NULL, 0 );
	
	tag_entry_context_menu = new wxMenu();
	add_tag = new wxMenuItem( tag_entry_context_menu, wxID_ANY, wxString( wxT("Add Tag") ) , wxT("Add a new tag to the list"), wxITEM_NORMAL );
	tag_entry_context_menu->Append( add_tag );
	delete_tag = new wxMenuItem( tag_entry_context_menu, wxID_ANY, wxString( wxT("Remove Tag") ) , wxEmptyString, wxITEM_NORMAL );
	tag_entry_context_menu->Append( delete_tag );
	edit_tag = new wxMenuItem( tag_entry_context_menu, wxID_ANY, wxString( wxT("Edit Tag") ) , wxEmptyString, wxITEM_NORMAL );
	tag_entry_context_menu->Append( edit_tag );
	edit_tag->Enable( false );
	delete_tag->Enable(false);

	tag_entry->Connect(wxEVT_CONTEXT_MENU,wxContextMenuEventHandler(AddEventDialog::OnContextClick),NULL,this);
	
	fgSizer1->Add( tag_entry, 0, wxALL, 5 );
	
	tag_entry_context_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(AddEventDialog::OnAddTag), this, add_tag->GetId());
	tag_entry_context_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( AddEventDialog::OnRemoveTag ), this, delete_tag->GetId());
	tag_entry_context_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( AddEventDialog::OnEditTag ), this, edit_tag->GetId());
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Make this a recurring event?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL, 5 );
	
	recurring_check = new wxCheckBox( this, wxID_ANY, wxT("Recurring Event"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( recurring_check, 0, wxALL, 5 );
	
	ok_btn = new wxButton( this, wxID_ANY, wxT("Submit!"), wxDefaultPosition, wxDefaultSize, 0 );

	ok_btn->SetDefault();
	fgSizer1->Add( ok_btn, 0, wxALL, 5 );

	cancel_btn = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( cancel_btn, 0, wxALL, 5 );

	ok_btn->Enable(false);
	cancel_btn->Enable(true);
	
	this->SetSizer( fgSizer1 );
	this->Layout();
	this->Fit();

	this->Centre( wxBOTH );

	// Connect Events
	tag_entry->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddEventDialog::OnSelect ), NULL, this );
	ac_label_entry->Connect(wxEVT_TEXT,wxCommandEventHandler(AddEventDialog::OnFieldChanged),NULL,this);
	hour_entry->Connect(wxEVT_TEXT,wxCommandEventHandler(AddEventDialog::OnFieldChanged),NULL,this);
	ok_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnOK ), NULL, this );
	cancel_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnCancel ), NULL, this );
	recurring_check->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AddEventDialog::OnMakeRecurring ), NULL, this );
}

AddEventDialog::~AddEventDialog(void){
	// Disconnect Events
	ok_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnOK ), NULL, this );
	cancel_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AddEventDialog::OnCancel ), NULL, this );
	ac_label_entry->Disconnect(wxEVT_TEXT,wxCommandEventHandler(AddEventDialog::OnFieldChanged),NULL,this);
	hour_entry->Disconnect(wxEVT_TEXT,wxCommandEventHandler(AddEventDialog::OnFieldChanged),NULL,this);
	tag_entry->Disconnect(wxEVT_CONTEXT_MENU,wxContextMenuEventHandler(AddEventDialog::OnContextClick),NULL,this);
	tag_entry->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( AddEventDialog::OnSelect ), NULL, this );
	recurring_check->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AddEventDialog::OnMakeRecurring ), NULL, this );
}

//Event management
void AddEventDialog::OnOK(wxCommandEvent &event){
	this->EndModal(wxOK);
}

void AddEventDialog::OnCancel(wxCommandEvent &event){
    this->EndModal(wxCANCEL);
}

void AddEventDialog::OnContextClick(wxContextMenuEvent &event){
	PopupMenu(tag_entry_context_menu);
	//std::cout<<"X="<<event.GetPosition().x<<std::endl;
	//std::cout<<"Y="<<event.GetPosition().y<<std::endl;
}

void AddEventDialog::OnSelect(wxCommandEvent &event){
	edit_tag->Enable(true);
	delete_tag->Enable(true);
}

void AddEventDialog::OnAddTag( wxCommandEvent& event ){
	AddTagDialog *diag=new AddTagDialog(this,cache);
	if(diag->ShowModal()==wxOK){
		wxString temp_tag=diag->get_tag();
		//std::cout<<"tag="<<temp_tag.ToStdString()<<std::endl;
		tag_entry->InsertItems(1,&temp_tag,0);
		tag_entry->Refresh();
		this->Refresh();
	}
}

void AddEventDialog::OnRemoveTag(wxCommandEvent &event){
	int selected=tag_entry->GetSelection();
	if(selected!=wxNOT_FOUND){
		std::string tag_to_remove=tag_entry->GetString(selected).ToStdString();
		for(int i=0;i<cache.size();i++){
			if(cache[i]==tag_to_remove){
				std::vector<std::string>::iterator it=cache.begin();
				if(i>0){
					for(int j=1;j<=i;j++)
						it++;
				}
				cache.erase(it);
			}
		}
		tag_entry->Delete(selected);
		this->Refresh();
	}
	delete_tag->Enable(false);
	edit_tag->Enable(false);
	return;
}

void AddEventDialog::OnEditTag(wxCommandEvent &event){
	AddTagDialog diag(this,cache);
	if(diag.ShowModal()==wxOK){
		wxString temp_tag=diag.get_tag();
		int index=tag_entry->GetSelection();
		tag_entry->Delete(index);
		edit_tag->Enable(false);
		tag_entry->InsertItems(1,&temp_tag,index);
		tag_entry->Refresh();
		this->Refresh();
	}
}

void AddEventDialog::OnFieldChanged(wxCommandEvent &evt){
	std::string label=ac_label_entry->GetValue().ToStdString();
	float t=static_cast<float>(hour_entry->GetValue());
	if(label.length()>0 && t>0)
		ok_btn->Enable(true);
	else
		ok_btn->Enable(false);
}

[[maybe_unused]] void AddEventDialog::OnMakeRecurring(wxCommandEvent &event) {
	if(recurring_check->IsChecked()){
		AddRecurrenceDialog *diag=new AddRecurrenceDialog(this);
		if(diag->ShowModal()==wxOK){
			std::cout<<"Make recurrence OK!"<<std::endl;
		}else{
			std::cout<<"Make recurrence cancelled!"<<std::endl;
		}
	}
}

//Accessors
Activity AddEventDialog::get_generated_activity(ActivityID id_to_add){
	std::vector<std::string> ts;
	if(tag_entry->GetCount()>0){
		for(int i=0;i<tag_entry->GetCount();i++)
			ts.push_back(tag_entry->GetString(i).ToStdString());
		ts.push_back("\0");
	}
	Activity ac(id_to_add,get_activity_label(),ts,static_cast<float>(hour_entry->GetValue()),true,0,-1);
	return ac;
}

//Event editing
void AddEventDialog::populate(std::string label,float hours,std::vector<std::string> tags){
	wxString wxs_label(label);
	ac_label_entry->SetValue(wxs_label);
	hour_entry->SetValue(static_cast<double>(hours));
	if(!tags.empty()){
		wxArrayString wxs_tags;
		for(auto t : tags){
			wxString wxs_tag(t);
			wxs_tags.Add(wxs_tag);
		}
		tag_entry->InsertItems(wxs_tags,0);
	}
}
