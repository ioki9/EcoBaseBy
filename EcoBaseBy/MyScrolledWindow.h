#pragma once
#include <wx/wx.h>

class MyScrolledWindow : public wxScrolledWindow
{
public:
	MyScrolledWindow(wxWindow * parent);
private:
	void OnSize(wxSizeEvent& Event);
};

