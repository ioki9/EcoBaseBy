#pragma once
#include <wx/wx.h>

class MyBusyInfo : public wxObject
{
public:
	MyBusyInfo(wxWindow* parent,const wxString& message);
	~MyBusyInfo();
private:
	wxWindow* m_parent;
	wxFrame* m_InfoFrame;
	void OnPaint(wxPaintEvent& evt);
};

