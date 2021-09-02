#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/gdicmn.h> 
#include "GUI_parameters.h"

class MainMenuTabButton : public wxPanel
{
public:
	MainMenuTabButton(wxWindow* parent, const wxString& text, wxWindowID id = wxID_ANY , bool droppable = false,
		const wxSize& size = wxDefaultSize, const wxPoint& pos = wxDefaultPosition);
	~MainMenuTabButton();
	uint8_t status = 0x00;
	enum conditionFlags : char
	{
		None = 0x00,
		flag_motionIN = 1 << 0,
		flag_motionOUT = 1 << 1,
		flag_leftKeyDown = 1 << 2,
		flag_isSelected = 1 << 3,
		flag_isDroppable = 1 << 4
	};

	void setSelected(bool selected);

private:
	wxString m_text;
	wxSize m_size;
	void OnPaint(wxPaintEvent& evt);
	
	void OnLeftDown(wxMouseEvent& evt);
	void OnLeftUp(wxMouseEvent& evt);
	void OnMotionIN(wxMouseEvent& evt);
	void OnMotionOUT(wxMouseEvent& evt);

};

