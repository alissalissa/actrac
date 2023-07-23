#include "main.h"

IMPLEMENT_APP(AcTrac);

bool AcTrac::OnInit(void){
	main_frame=new MainFrame(NULL);
	main_frame->Show();
	SetTopWindow(main_frame);
	return true;
}