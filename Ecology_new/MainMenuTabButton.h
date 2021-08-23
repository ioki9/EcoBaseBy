#pragma once
#include <wx/wx.h>


class MainMenuTabButton : public wxPanel
{
	MainMenuTabButton(wxWindow* parent, const wxString& text, wxWindowID id = wxID_ANY , 
		const wxSize& size = wxDefaultSize, const wxPoint& pos = wxDefaultPosition);
	~MainMenuTabButton();


};

