#include "mainframe.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer( wxVERTICAL );

	view_selector = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0|wxBORDER_RAISED|wxVSCROLL, wxT("Activities") );
	tracker_panel = new wxPanel( view_selector, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	otd_activities = new wxDataViewCtrl( tracker_panel, wxID_ANY, wxDefaultPosition, wxSize( 700,500 ), 0 );
	activity_name = otd_activities->AppendTextColumn( wxT("Activity"), 0, wxDATAVIEW_CELL_INERT, 400, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	activity_time = otd_activities->AppendTextColumn( wxT("Hours"), 1, wxDATAVIEW_CELL_INERT, 300, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
	activity_model=new DVModel();
	otd_activities->AssociateModel(activity_model);
	bSizer4->Add( otd_activities, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	add_evt_btn = new wxButton( tracker_panel, wxID_ANY, wxT("Add Event"), wxDefaultPosition, wxDefaultSize, 0 );
	add_evt_btn->SetDefault();
	bSizer41->Add( add_evt_btn, 0, wxALL, 5 );

	delete_event_btn = new wxButton( tracker_panel, wxID_ANY, wxT("Delete Event"), wxDefaultPosition, wxDefaultSize, 0 );
	delete_event_btn->Enable( false );

	bSizer41->Add( delete_event_btn, 0, wxALL, 5 );

	edit_event_btn = new wxButton( tracker_panel, wxID_ANY, wxT("Edit Event"), wxDefaultPosition, wxDefaultSize, 0 );
	edit_event_btn->Enable( false );

	bSizer41->Add( edit_event_btn, 0, wxALL, 5 );


	bSizer4->Add( bSizer41, 1, wxEXPAND, 5 );


	bSizer2->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	date_selector = new wxCalendarCtrl( tracker_panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	bSizer5->Add( date_selector, 0, wxALL|wxALIGN_RIGHT, 5 );


	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );


	tracker_panel->SetSizer( bSizer2 );
	tracker_panel->Layout();
	bSizer2->Fit( tracker_panel );
	view_selector->AddPage( tracker_panel, wxT("Activities"), true );
	report_panel = new wxPanel( view_selector, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED|wxTAB_TRAVERSAL, wxT("Reports") );
	view_selector->AddPage( report_panel, wxT("Reports"), false );

	main_sizer->Add( view_selector, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( main_sizer );
	this->Layout();
	menu_bar = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* save_menu_item = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("CTRL-s"), wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( save_menu_item );
	wxMenuItem* file_menu_quit = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( file_menu_quit );

	menu_bar->Append( file_menu, wxT("File") );

	this->SetMenuBar( menu_bar );


	this->Centre( wxBOTH );

	selected_row=-1;

	// Connect Events
	edit_event_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnQuit ), this, file_menu_quit->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSave ), this, save_menu_item->GetId());
	add_evt_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );
	otd_activities->Connect(wxEVT_DATAVIEW_SELECTION_CHANGED,wxDataViewEventHandler(MainFrame::OnSelectActivity),NULL,this);
	date_selector->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnSelectDate ), NULL, this );

}

MainFrame::~MainFrame(void) {
	// Disconnect Events
	add_evt_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );
	otd_activities->Disconnect(wxEVT_DATAVIEW_SELECTION_CHANGED,wxDataViewEventHandler(MainFrame::OnSelectActivity),NULL,this);
	edit_event_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );
	date_selector->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnSelectDate ), NULL, this );

}

//Internal Model
//Binary search and insert
void MainFrame::add_to_tags_cache(std::string new_entry){
	if(tags_cache.size()==0){
		tags_cache.push_back(new_entry);
		return;
	}else if(tags_cache.size()==1){
		if(new_entry<tags_cache[0]) tags_cache.insert(tags_cache.begin(),new_entry);
		else tags_cache.push_back(new_entry);
		return;
	}else{
		int insertion_point=binary_search<std::string>(tags_cache,new_entry);
		std::vector<std::string>::iterator insert_it=tags_cache.begin();
		for(int i=1;i<=insertion_point;i++) ++insert_it;
		tags_cache.insert(insert_it,new_entry);
	}
	return;
}

void MainFrame::add_date(wxDateTime haystack){
	//Does this date already exist in the list?
	if(date_exists(haystack))
		return;
	//Not already in the list
	date to_add(haystack);
	int insert_index=binary_search<date>(utilized_dates,to_add);
	std::vector<date>::iterator it=utilized_dates.begin();
	for(int i=1;i<=insert_index;i++) it++;
	utilized_dates.insert(it,to_add);
}

bool MainFrame::date_exists(wxDateTime comparator){
	//binary search is meant to give us an insertion point
	//	consequently, the index is spits out has to be adjusted when searching
	//	to see if something exists or not
	if(utilized_dates.size()>1){
		int index=binary_search<date>(utilized_dates,create_date(comparator));
		if(index>=utilized_dates.size())
			return false;
		if(utilized_dates[index]==comparator)
			return true;
	}else if(utilized_dates.size()==1){
		if(utilized_dates[0]==comparator)
			return true;
	}
	return false;
}

//Events
void MainFrame::OnQuit(wxCommandEvent &evt){
	wxExit();
}

void MainFrame::OnSave(wxCommandEvent &evt){
	wxFileDialog selector_diag(this,wxT("Save events to file"),wxT(""),wxT(""),wxT(".dat"),wxFD_SAVE);
	if(selector_diag.ShowModal()==wxID_OK){
		std::cout<<selector_diag.GetPath().ToStdString()<<std::endl;
		if(!write_to_file(selector_diag.GetPath().ToStdString(),this->utilized_dates,tags_cache))
			std::cout<<"Error writing file..."<<std::endl;
	}
}

void MainFrame::OnAddEvent(wxCommandEvent &evt){
	AddEventDialog *diag=new AddEventDialog(this,tags_cache);
	if(diag->ShowModal()==wxOK){
		wxDateTime cd=date_selector->GetDate();
		int index=binary_search<date>(utilized_dates,create_date(cd));
		if(utilized_dates.size()==0){
			date d(cd);
			std::cout<<"Adding date "<<d.toStdStr()<<" to the list...."<<std::endl;
			utilized_dates.push_back(d);
		}else if(utilized_dates[index]!=create_date(cd)){
			date d(cd);
			std::vector<date>::iterator it=utilized_dates.begin();
			for(int i=1;i<=index;i++)
				it++;
			utilized_dates.insert(it,d);
		}

		ActivityID id_to_add=gen_ac_id(utilized_dates[index].Activities(),diag->get_activity_label());
		Activity ac_to_add(diag->get_generated_activity(id_to_add));
		for(auto t : ac_to_add.Tags())
			this->add_to_tags_cache(t);
		
		utilized_dates[index].AddActivity(ac_to_add);
		std::cout<<"Added activity "<<ac_to_add.ID().str()<<std::endl;
		DVPair <std::string,float> *to_add=new DVPair<std::string,float>(ac_to_add.Label(),ac_to_add.Hours());
		activity_model->AddRow(to_add);
		delete to_add;
	}
}

void MainFrame::OnEditEvent(wxCommandEvent &evt){
	std::cout<<"Edit event!"<<std::endl;
}

void MainFrame::OnRemoveEvent(wxCommandEvent &evt){
	evt.Skip();
}

void MainFrame::OnSelectActivity(wxDataViewEvent &evt){
	selected_row=activity_model->GetRowByItem(evt.GetItem());
	if(selected_row<0){
		MFException except;
		throw except;
	}
	std::cout<<"Row = "<<selected_row<<std::endl;
}

void MainFrame::OnSelectDate(wxCalendarEvent &evt){
	std::vector<DVPair<std::string,float> > acs;
	if(date_exists(evt.GetDate())){
		date selected_date(evt.GetDate());
		std::cout<<"Selected date "<<selected_date.toStdStr()<<" exists!"<<std::endl;
		int index=binary_search<date>(utilized_dates,create_date(evt.GetDate()));
		//FIXME this conditional tree does not adequately address all cases
		if(index==utilized_dates.size() && utilized_dates.size()!=0){
			if(utilized_dates[index-1]==evt.GetDate()){
				for(auto ac : utilized_dates[index-1].Activities()){
					DVPair<std::string,float> a(ac.Label(),ac.Hours());
					acs.push_back(a);
				}
			}
		}else if(utilized_dates.size()>index){
			if(index==0){
				if(utilized_dates[index]==evt.GetDate()){
					for(auto ac : utilized_dates[index].Activities()){
						DVPair<std::string,float> a(ac.Label(),ac.Hours());
						acs.push_back(a);
					}
				}
			}else if(index>0){
				for(auto ac : utilized_dates[index].Activities()){
					DVPair<std::string,float> a(ac.Label(),ac.Hours());
					acs.push_back(a);
				}
			}
		}
	}
	activity_model->Rebuild(acs);
	Refresh();
}

//MFException stuff
const char *MFException::what(void) const noexcept {
	const std::string message="Exception thrown within the MainFrame class.";
	return message.c_str();
}