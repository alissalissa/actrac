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

	today_button = new wxButton( tracker_panel, wxID_ANY, wxT("Today!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( today_button, 0, wxALIGN_RIGHT|wxALL, 5 );

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
	wxMenuItem* load_menu_item = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Load From File") ) + wxT('\t') + wxT("ctrl-o"), wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( load_menu_item );
	wxMenuItem* file_menu_quit = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( file_menu_quit );

	menu_bar->Append( file_menu, wxT("File") );

	this->SetMenuBar( menu_bar );
	this->Centre( wxBOTH );
	selected_row=-1;

	// Connect Events
	edit_event_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );
	delete_event_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainFrame::OnRemoveEvent),NULL,this);
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnQuit ), this, file_menu_quit->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnSave ), this, save_menu_item->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnLoad ), this, load_menu_item->GetId());
	add_evt_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );
	otd_activities->Connect(wxEVT_DATAVIEW_SELECTION_CHANGED,wxDataViewEventHandler(MainFrame::OnSelectActivity),NULL,this);
	date_selector->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnSelectDate ), NULL, this );
	today_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToday ), NULL, this );
}

MainFrame::~MainFrame(void) {
	// Disconnect Events
	add_evt_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );
	otd_activities->Disconnect(wxEVT_DATAVIEW_SELECTION_CHANGED,wxDataViewEventHandler(MainFrame::OnSelectActivity),NULL,this);
	edit_event_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );
	date_selector->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( MainFrame::OnSelectDate ), NULL, this );
	delete_event_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainFrame::OnRemoveEvent),NULL,this);
	today_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnToday ), NULL, this );
}

//Internal Model
//Binary search and insert
void MainFrame::add_to_tags_cache(std::string new_entry){
	if(tags_cache.size()==0){
		tags_cache.push_back(new_entry);
		return;
	}else if(tags_cache.size()==1){
		if(new_entry<tags_cache[0])
			tags_cache.insert(tags_cache.begin(),new_entry);
		else if(new_entry!=tags_cache[0])
			tags_cache.push_back(new_entry);
		return;
	}else{
		int insertion_point=binary_search<std::string>(tags_cache,new_entry);
		if(tags_cache[insertion_point]==new_entry)
			return;
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
	wxFileDialog selector_diag(this,wxT("Save events to file"),wxT(""),wxT(""),wxT("*.dat"),wxFD_SAVE);
	if(selector_diag.ShowModal()==wxID_OK){
		std::cout<<selector_diag.GetPath().ToStdString()<<std::endl;
		if(!write_to_file(selector_diag.GetPath().ToStdString(),this->utilized_dates,tags_cache))
			std::cout<<"Error writing file..."<<std::endl;
	}
}

void MainFrame::OnLoad(wxCommandEvent &evt){
	wxFileDialog *selector_diag=new wxFileDialog(this,wxT("Load events from file"),wxT(""),wxT(""),wxT("*.dat"),wxFD_OPEN);
	if(selector_diag->ShowModal()==wxID_OK){
		std::cout<<"Loading events from "<<selector_diag->GetPath().ToStdString()<<std::endl;
		utilized_dates.clear();
		tags_cache.clear();
		//FIXME unhandled exception is occurring
		if(!read_from_file(selector_diag->GetPath().ToStdString(),utilized_dates,tags_cache)){
			std::cout<<"Error reading activity file!"<<std::endl;
			delete selector_diag;
			throw MFException();
		}
	}
	delete selector_diag;
}

void MainFrame::OnAddEvent(wxCommandEvent &evt){
	AddEventDialog *diag=new AddEventDialog(this,tags_cache);
	if(diag->ShowModal()==wxOK){
		//In order to generate a new activity,
		//	we first need to generate an ID.
		//	In order to do that, we need to establish a date object
		ActivityID new_id;
		try{
			if(date_exists(date_selector->GetDate())){
				//Yes, we have an established date, so let's get the ID.
				int index=binary_search<date>(utilized_dates,create_date(date_selector->GetDate()));
				if(utilized_dates.size()==1){
					//There's only one date, and we know it's our's because the date exists
					new_id=gen_ac_id(utilized_dates[0].Activities(),diag->get_activity_label());
					utilized_dates[0].AddActivity(diag->get_generated_activity(new_id));
				}else{
					//We know size>1 because if size==0, date_exists would return false
					//We know index<size, because otherwise exists would have returned false
					new_id=gen_ac_id(utilized_dates[index].Activities(),diag->get_activity_label());
					utilized_dates[index].AddActivity(diag->get_generated_activity(new_id));
				}
				std::vector<DVPair<std::string,float> > new_model;
				for(auto ac : utilized_dates[index].Activities()){
					DVPair<std::string,float> *pair_buffer=new DVPair<std::string,float>(ac.Label(),ac.Hours());
					new_model.push_back(*pair_buffer);
					delete pair_buffer;
				}
				activity_model->Rebuild(new_model);
			}else{
				//We need to create a new date
				date new_date(date_selector->GetDate());
				//Get our insertion point
				int insertion_point=binary_search<date>(utilized_dates,new_date);
				std::vector<date>::iterator insertion_iterator=utilized_dates.begin();
				for(int i=1;i<=insertion_point;i++) insertion_iterator++;
				utilized_dates.insert(insertion_iterator,new_date);
				//Now we know for sure the date exissts
				int index=binary_search<date>(utilized_dates,new_date);
				new_id=gen_ac_id(new_date.Activities(),diag->get_activity_label());
				utilized_dates[index].AddActivity(diag->get_generated_activity(new_id));
				std::vector<DVPair<std::string,float> > new_model;
				for(auto ac : utilized_dates[index].Activities()){
					DVPair<std::string,float> *pair_buffer=new DVPair<std::string,float>(ac.Label(),ac.Hours());
					new_model.push_back(*pair_buffer);
					delete pair_buffer;
				}
				activity_model->Rebuild(new_model);
			}
		}catch(std::exception e){
			std::cout<<e.what()<<std::endl;
			wxExit();
		}catch(int e){
			std::cout<<"caught code "<<e<<std::endl;
			wxExit();
		}
		std::vector<std::string> new_tags=diag->get_generated_activity(new_id).Tags();
		for(auto nt : new_tags)
			add_to_tags_cache(nt);
	}
	Refresh();
}

void MainFrame::OnEditEvent(wxCommandEvent &evt){
	//std::cout<<"Edit event!"<<std::endl;
	//Get the list of activities for the selected date
	std::vector<Activity> current_activities=this->activities_from_selected_date(date_selector->GetDate());
	Activity current_activity=current_activities[selected_row];
	AddEventDialog *diag=new AddEventDialog(this,tags_cache);
	diag->populate(current_activity.Label(),current_activity.Hours(),current_activity.Tags());
	if(diag->ShowModal()==wxOK){
		std::cout<<"Updating activity to be written...."<<std::endl;
		//Okay, so we need to update the current event
		ActivityID new_id=gen_ac_id(current_activities,diag->get_activity_label());
		current_activities[selected_row]=diag->get_generated_activity(new_id);
		std::vector<DVPair<std::string,float> > new_model_context;
		for(auto ac : current_activities){
			DVPair<std::string,float> *p=new DVPair<std::string,float>(ac.Label(),ac.Hours());
			new_model_context.push_back(*p);
			delete p;
		}
		activity_model->Rebuild(new_model_context);
		//The display model has been rebuilt, now update the vector of Activities
		//We know the date has to exist, and we know it has to be populated
		//	We know this because a date and activity were selected to get to this point
		int match_index=binary_search<date>(utilized_dates,create_date(date_selector->GetDate()));
		utilized_dates[match_index].Activities()=current_activities;
		Refresh();
	}
	delete diag;
}

void MainFrame::OnRemoveEvent(wxCommandEvent &evt){
	try{
		//Start by getting the date we're on.
		//	We can assume the date exists, since an activity has to be selected to access this event
		int date_index=binary_search<date>(utilized_dates,create_date(date_selector->GetDate()));
		//That should give us an exact date index
		//Next we need the ID of the activity to delete
		ActivityID id_to_delete=utilized_dates[date_index].Activities()[selected_row].ID();
		utilized_dates[date_index].RemoveActivity(id_to_delete);
		//Now we need to purge from the DV model
		std::vector<DVPair<std::string,float> > acs;
		for(auto ac : utilized_dates[date_index].Activities()){
			DVPair<std::string,float> a(ac.Label(),ac.Hours());
			acs.push_back(a);
		}
		activity_model->Rebuild(acs);
		//Clear out the selection
		selected_row=-1;
		delete_event_btn->Enable(false);
		edit_event_btn->Enable(false);
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		wxExit();
	}catch(int e_code){
		std::cout<<"caught exception code "<<e_code<<std::endl;
		wxExit();
	}
	Refresh();
}

void MainFrame::OnSelectActivity(wxDataViewEvent &evt){
	selected_row=activity_model->GetRowByItem(evt.GetItem());
	if(selected_row<0){
		MFException except;
		throw except;
	}
	std::cout<<"Row = "<<selected_row<<std::endl;
	edit_event_btn->Enable(true);
	delete_event_btn->Enable(true);
}

void MainFrame::OnToday(wxCommandEvent &evt){
	std::vector<DVPair<std::string,float> > acs;
	wxDateTime wx_today(time(NULL));
	std::vector<Activity> selected_date_activities=this->activities_from_selected_date(wx_today);
	for(auto activity : selected_date_activities){
		DVPair <std::string,float> p(activity.Label(),activity.Hours());
		acs.push_back(p);
	}
	activity_model->Rebuild(acs);
	date_selector->SetDate(wx_today);
	Refresh();
}

void MainFrame::OnSelectDate(wxCalendarEvent &evt){
	std::vector<DVPair<std::string,float> > acs;
	std::vector<Activity> selected_date_activities=this->activities_from_selected_date(evt.GetDate());
	for(auto activity : selected_date_activities){
		DVPair <std::string,float> p(activity.Label(),activity.Hours());
		acs.push_back(p);
	}
	activity_model->Rebuild(acs);
	Refresh();
}

std::vector<Activity> MainFrame::activities_from_selected_date(wxDateTime wx_selected){
	date selected(wx_selected);
	std::vector<Activity> ret;
	try{
		if(utilized_dates.empty())
			return ret;
		//We know there's at least one date
		int date_match_index=binary_search<date>(utilized_dates,selected);
		if(date_match_index==utilized_dates.size()){
			//We know the date doesn't exist, since the search is punting to the end of the vector
			return ret;
		}
		if(utilized_dates[date_match_index]!=selected){
			//The date doesn't exist
			return ret;
		}
		//The date exists, and we've selected it
		for(auto ac : utilized_dates[date_match_index].Activities())
			ret.push_back(ac);
	}catch(std::exception e){
		std::cout<<e.what()<<std::endl;
		wxExit();
	}catch(int e_code){
		std::cout<<"Caught error code "<<e_code<<std::endl;
		wxExit();
	}
	return ret;
}

//MFException stuff
const char *MFException::what(void) const noexcept {
	const std::string message="Exception thrown within the MainFrame class.";
	return message.c_str();
}