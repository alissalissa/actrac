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

	m_calendar1 = new wxCalendarCtrl( tracker_panel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	bSizer5->Add( m_calendar1, 0, wxALL|wxALIGN_RIGHT, 5 );


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

//Events
void MainFrame::OnQuit(wxCommandEvent &evt){
	wxExit();
}

void MainFrame::OnAddEvent(wxCommandEvent &evt){
	AddEventDialog *diag=new AddEventDialog(this);
	diag->ShowModal();
}
