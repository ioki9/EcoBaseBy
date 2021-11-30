#include "cApp.h"
#include <wx/pdfdoc.h>
#include <wx/pdffontmanager.h>
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
#include "../Settings.h"
#include "../Utility/Utility.h"
#include <wx/wfstream.h>
wxIMPLEMENT_APP(cApp);


cApp::cApp()
{


}


cApp::~cApp()
{

}

bool cApp::OnInit()
{
	wxInitAllImageHandlers();
	wxLocale loc(wxLANGUAGE_RUSSIAN);
	m_frame1 = new cMain();
	m_frame1->Show();
	return true;
}