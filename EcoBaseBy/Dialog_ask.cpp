#include "Dialog_ask.h"

Dialog_ask::Dialog_ask(wxWindow* parent, const wxString& title,const wxString& text,const wxString& acptBtnLabel, const wxPoint& pos, 
	const wxSize& size, long style, const wxString& name) : wxDialog(parent, -1, "", pos,size, style, name), m_parent{parent}
{
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainPanel->SetFont(gui_MainFont);
	wxPanel* topGreenPanel = new wxPanel(m_mainPanel);
	topGreenPanel->SetBackgroundColour(gui_MainColour);
	wxStaticText *topText = new wxStaticText(topGreenPanel, wxID_ANY,title ,wxDefaultPosition,wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	topText->SetForegroundColour(*wxWHITE);
	topText->SetFont(wxFontInfo(14).FaceName("Segoe UI Semibold"));
	wxBoxSizer* topTextSizer = new wxBoxSizer(wxHORIZONTAL);
	topTextSizer->Add(topText,0,wxALIGN_CENTER_VERTICAL | wxLEFT , 10);
	topGreenPanel->SetSizerAndFit(topTextSizer);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* mainText = new wxStaticText(m_mainPanel, wxID_ANY, text, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_VERTICAL);
	wxBoxSizer* mainTextSizer = new wxBoxSizer(wxHORIZONTAL);
	mainTextSizer->Add(mainText, 1,wxEXPAND | wxTOP | wxLEFT, 10);
	
	m_btnNO = new MaterialButton(m_mainPanel, wxID_ANY, "Отмена",true,wxDefaultPosition,wxSize(70, 35));
	m_btnNO->SetButtonLineColour(*wxWHITE);
	m_btnNO->SetLabelColour(wxColour(90, 90, 90));
	m_btnNO->SetButtonShadow(false);
	m_btnNO->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
	m_btnYES = new MaterialButton(m_mainPanel, wxID_ANY, acptBtnLabel, true, wxDefaultPosition, wxSize(70, 35));
	m_btnYES->SetButtonLineColour(*wxWHITE);
	m_btnYES->SetLabelColour(wxColour(165, 42, 42));
	m_btnYES->SetButtonShadow(false);
	m_btnYES->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	btnSizer->Add(m_btnYES,0,wxRIGHT,15);
	btnSizer->Add(m_btnNO, 0, wxRIGHT);
	
	mainSizer->Add(topGreenPanel, 1, wxEXPAND);
	mainSizer->Add(mainTextSizer,2,wxEXPAND);
	mainSizer->Add(btnSizer,0,wxBOTTOM|wxRIGHT | wxALIGN_RIGHT,20);
	m_mainPanel->SetSizerAndFit(mainSizer);
	m_btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_ask::OnNoButton, this);
	m_btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_ask::OnYesButton, this);
	m_btnNO->Bind(wxEVT_MOTION, &Dialog_ask::OnButtonMotion, this);
	m_btnNO->Bind(wxEVT_LEAVE_WINDOW, &Dialog_ask::OnButtonMotionOUT, this);
	m_btnYES->Bind(wxEVT_MOTION, &Dialog_ask::OnButtonMotion, this);
	m_btnYES->Bind(wxEVT_LEAVE_WINDOW, &Dialog_ask::OnButtonMotionOUT, this);
	this->Bind(wxEVT_PAINT, &Dialog_ask::OnPaint, this);


	this->CentreOnScreen();

	this->ShowModal();
	if (m_isYesPressed)
		SetReturnCode(1);
	else
		SetReturnCode(0);
}

Dialog_ask::~Dialog_ask()
{
}

void Dialog_ask::OnNoButton(wxCommandEvent& evt)
{
	m_isYesPressed = false;
	this->Close();
}

void Dialog_ask::OnYesButton(wxCommandEvent& evt)
{
	m_isYesPressed = true;
	this->Close();
}

void Dialog_ask::OnButtonMotion(wxMouseEvent& evt)
{
	SetCursor(wxCURSOR_HAND);
}

void Dialog_ask::OnButtonMotionOUT(wxMouseEvent& evt)
{
	SetCursor(wxCURSOR_DEFAULT);
}

void Dialog_ask::OnPaint(wxPaintEvent& evt)
{
	wxWindowDC* dc = new wxWindowDC(m_parent);
	utility::paintDarkBackground(dc, m_parent);
	delete dc;
}
