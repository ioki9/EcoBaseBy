#pragma once
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/graphics.h>
#include <wx/toplevel.h>
class TransparentPanel : public wxTopLevelWindow
{
public:
	TransparentPanel(wxWindow* parent);
private:
	wxSize m_wndwSize;
	wxPoint m_wndwPos;
	void OnPaint(wxEraseEvent& evt);
};

