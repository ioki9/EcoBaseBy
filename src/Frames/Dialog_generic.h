#pragma once
#include <wx/wx.h>

class Dialog_generic : public wxDialog
{
public:
	Dialog_generic(wxWindow* parent, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 220),bool drawDarkBg = true);
	~Dialog_generic();
	void SetProportions(int headerProp, int mainProp);
	wxPanel* GetMain() { return m_mainPanel; }
	int GetMainPanelProp(){ return m_mainPanelProportion; }
	int GetHeaderPanelProp() { return m_headerProportion; }
private:
	wxPanel* m_dlgPanel = nullptr;
	wxPanel* m_headerPanel = nullptr;
	wxPanel* m_mainPanel = nullptr;
	wxString m_title;
	wxStaticText* m_headerText = nullptr;
	wxBoxSizer* m_headerSizer = nullptr;
	wxBoxSizer* m_mainSizer = nullptr;
	int m_headerProportion{ 1 };
	int m_mainPanelProportion{ 3 };
	bool m_bgNotDrawn;
	void onPaint(wxPaintEvent& evt);
};