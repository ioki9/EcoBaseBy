#pragma once
#include "cApp.h"
#include <wx/pdffontmanager.h>
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
wxIMPLEMENT_APP(cApp);


cApp::cApp()
{
	wxInitAllImageHandlers();
	wxLocale(wxLANGUAGE_RUSSIAN);
	
}


cApp::~cApp()
{
	
}

bool cApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}