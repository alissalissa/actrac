#include "main.h"

IMPLEMENT_APP(AcTrac);

bool AcTrac::OnInit(void){
	main_frame=new MainFrame(NULL,wxID_ANY,wxT("AcTrac"));
	main_frame->Show();
	SetTopWindow(main_frame);
	return true;
}