#pragma once
#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <cstdint>

class MaterialButton : public wxPanel
{
public:
	MaterialButton(wxWindow* parent, wxWindowID id, const wxString& text,bool isOutlined = 0, const wxPoint& pos=wxDefaultPosition,
		const wxSize& size = wxDefaultSize);
	~MaterialButton();

	void SetTextFont(const wxFont& font);
	void SetButtonFillColour(const wxColour& colour);
	void SetButtonLineColour(const wxColour& colour);
	void SetLabelColour(const wxColour& colour);
	void SetButtonColour(const wxColour& colour);
	void SetButtonShadow(bool isDrawn);
	void disableButton(bool disable = true);
	//if set might end badly
	bool SetLineWidth(uint8_t width);

	bool SetButtonRadius(uint8_t radius);
private:
	struct rectInfo 
	{
		uint8_t LineWidth : 4;
		uint8_t Radius : 4;
	};
	struct rectInfo rectInfo = { 1, 4 };
	const wxSize m_size;

	std::string m_text;

	wxColour m_colourText = *wxBLACK;
	wxColour m_colourBtnBrush = *wxWHITE;
	wxColour m_colourBtnPen = *wxBLACK;
	wxFont m_txtFont = wxFontInfo(12).FaceName("Segoe UI").Bold();
	
	void OnPaint(wxPaintEvent& evt);
	void OnLeftDown(wxMouseEvent& evt);
	void OnLeftUp(wxMouseEvent& evt);
	void OnMotionIN(wxMouseEvent& evt);
	void OnMotionOUT(wxMouseEvent& evt);
	wxSize DoGetBestSize() const wxOVERRIDE;

	uint8_t status = 0x00;
	enum conditionFlags : char
	{
		None = 0x00,
		flag_outlined = 1 << 0,
		flag_motionIN = 1 << 1,
		flag_motionOUT = 1 << 2,
		flag_leftKeyDown = 1 << 3,
		flag_shadowDrawn = 1 << 4,
		flag_isDisabled = 1 << 5


	};
};

