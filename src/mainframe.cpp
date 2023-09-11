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
	activity_time = otd_activities->AppendTextColumn( wxT("Hours"), 0, wxDATAVIEW_CELL_INERT, 300, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE );
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
	wxMenuItem* file_menu_quit;
	file_menu_quit = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( file_menu_quit );

	menu_bar->Append( file_menu, wxT("File") );

	this->SetMenuBar( menu_bar );


	this->Centre( wxBOTH );

	// Connect Events
	//edit_event_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnQuit ), this, file_menu_quit->GetId());
	add_evt_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );

}

MainFrame::~MainFrame()
{
	// Disconnect Events
	add_evt_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnAddEvent ), NULL, this );
	//edit_event_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnEditEvent ), NULL, this );

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
		//TODO flesh this out
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
	//FIXME this conditional can be optimized out
	if(insert_index==0)
		utilized_dates.insert(utilized_dates.begin(),to_add);
	else{
		std::vector<date>::iterator insert_it=utilized_dates.begin();
		for(int i=1;i<=insert_index;i++)
			insert_it++;
		utilized_dates.insert(insert_it,to_add);
	}
}

bool MainFrame::date_exists(wxDateTime comparator){
	int index=binary_search<date>(utilized_dates,create_date(comparator));
	if(utilized_dates[index]==comparator)
		return true;
	return false;
}

//Events
void MainFrame::OnQuit(wxCommandEvent &evt){
	wxExit();
}

//Internal model/view
void MainFrame::update_view(void){
	
}

//TODO flesh out the backend of this
void MainFrame::OnAddEvent(wxCommandEvent &evt){
	AddEventDialog *diag=new AddEventDialog(this);
	if(diag->ShowModal()==wxOK){
		wxDateTime cd=date_selector->GetDate();
		int index=binary_search<date>(utilized_dates,create_date(cd));
		if(utilized_dates.size()==0){
			date d(cd);
			std::vector<date>::iterator it=utilized_dates.begin();
			//FIXME this conditional block can be optimized better by switching order
			utilized_dates.insert(it,d);
		}else if(utilized_dates[index]!=create_date(cd)){
			date d(cd);
			std::vector<date>::iterator it=utilized_dates.begin();
			//FIXME this conditional block can be optimized better by switching order
			if(index==0)
				utilized_dates.insert(it,d);
			else{
				for(int i=1;i<=index;i++)
					it++;
				utilized_dates.insert(it,d);
			}
		}

		ActivityID id_to_add=gen_ac_id(utilized_dates[index].Activities(),diag->get_activity_label());
		Activity ac_to_add(diag->get_generated_activity(id_to_add));
		//FIXME insert the code to add the new tags to the cache
		utilized_dates[index].AddActivity(ac_to_add);
	}
	//TODO update the display maybe?
}

template <class T> int binary_search(std::vector<T> haystack,T delimiter){
	if(haystack.size()==0)
		return 0;
	if(haystack.size()==1)
		return delimiter<haystack[0]?0:1;
	//haystack size>=2
	if(delimiter<haystack[haystack.size()/2]){
		std::vector<T> next_haystack;
		for(int i=0;i<(haystack.size()/2);i++)
			next_haystack.push_back(haystack[i]);
		return binary_search<T>(next_haystack,delimiter);
	}else if(haystack[haystack.size()/2]<delimiter){
		std::vector<T> next_haystack;
		for(int i=(haystack.size()/2);i<haystack.size();i++)
			next_haystack.push_back(haystack[i]);
		return binary_search<T>(next_haystack,delimiter)+next_haystack.size();
	}
	return haystack.size()/2;
}
