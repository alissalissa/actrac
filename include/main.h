#ifndef __ACTRAC_MAIN_H__
#define __ACTRAC_MAIN_H__

#include <wx/wx.h>

#include "mainframe.h"

class AcTrac : public wxApp {
private:

	MainFrame *main_frame;

public:

	bool OnInit(void);

	virtual ~AcTrac()=default;

};

#endif