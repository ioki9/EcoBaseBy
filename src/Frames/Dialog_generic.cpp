#include "Dialog_generic.h"
#include "../Utility/Utility.h"
#include "../GUI_parameters.h"

Dialog_generic::Dialog_generic(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
	const wxSize& size,bool drawDarkBg) :wxDialog(parent,id,"",pos,size, wxDEFAULT_DIALOG_STYLE & ~(wxDEFAULT_DIALOG_STYLE)), 
	m_title{title},m_bgNotDrawn{drawDarkBg}
{
	this->SetFont(gui_MainFont);
	m_dlgPanel = new wxPanel(this);
	m_dlgPanel->SetBackgroundColour(*wxWHITE);

	m_headerPanel = new wxPanel(m_dlgPanel, wxID_ANY, wxDefaultPosition);
	m_headerPanel->SetBackgroundColour(gui_MainColour);
	m_headerText = new wxStaticText(m_headerPanel, wxID_ANY, m_title);
	m_headerText->SetForegroundColour(*wxWHITE);
	m_headerText->SetFont(wxFontInfo(13).FaceName("Segoe UI Semibold"));
	m_headerSizer = new wxBoxSizer(wxHORIZONTAL);
	m_headerSizer->Add(m_headerText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
	m_headerPanel->SetSizer(m_headerSizer);
	m_mainPanel = new wxPanel(m_dlgPanel);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainSizer = new wxBoxSizer(wxVERTICAL);
	m_mainSizer->Add(m_headerPanel, m_headerProportion, wxEXPAND);
	m_mainSizer->Add(m_mainPanel, m_mainPanelProportion, wxEXPAND);
	m_dlgPanel->SetSizerAndFit(m_mainSizer);
	CenterOnParent();
	this->Bind(wxEVT_PAINT, &Dialog_generic::onPaint, this);
}

Dialog_generic::~Dialog_generic()
{
}

void Dialog_generic::SetProportions(int headerProp, int mainProp)
{
	m_headerProportion = headerProp;
	m_mainPanelProportion = mainProp;
	m_mainSizer->Remove(1);
	m_mainSizer->Remove(0);
	m_mainSizer->Add(m_headerPanel, m_headerProportion, wxEXPAND);
	m_mainSizer->Add(m_mainPanel, m_mainPanelProportion, wxEXPAND);
}

void Dialog_generic::onPaint(wxPaintEvent& evt)
{
	if (m_bgNotDrawn)
	{
		wxWindowDC* dc = new wxWindowDC(m_parent);
		utility::paintDarkBackground(dc, m_parent);
		m_bgNotDrawn = false;
		delete dc;
	}
}
