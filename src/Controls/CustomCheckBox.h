#pragma once

#include <wx/wx.h>


class CustomCheckBox : public wxPanel
{
public:
	CustomCheckBox(wxPanel* parent, wxWindowID id, const wxString &label,const wxPoint &pos);
	~CustomCheckBox();
	uint8_t status = 0x00;
	enum conditionFlags : char
	{
		None = 0x00,
		flag_active = 1 << 0,
		flag_motionIN = 1 << 1,
		flag_motionOUT = 1 << 2,
		flag_leftKeyDown = 1 << 3
	};
private:
	
	wxRect m_rect{ 0 ,0 , this->GetSize().x, this->GetSize().y };
	wxColour m_checkBoxColour = wxColour(20, 148, 20);
	wxString m_text;

protected:
	void OnPaint(wxPaintEvent& evt);
	void OnMotion(wxMouseEvent& evt);
	void OnLeave(wxMouseEvent& evt);
	void OnClick(wxMouseEvent& evt);
	void OnKeyDown(wxMouseEvent& evt);;
public:
	void SetCheckBoxActive();
	void setCheckBoxColour(const wxColour& colour);

};

