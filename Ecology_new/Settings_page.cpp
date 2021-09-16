#include "Settings_page.h"

Settings_page::Settings_page(wxWindow* parent) : wxPanel(parent)
{
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer* mainWindowSizer = new wxBoxSizer(wxVERTICAL);
	mainWindowSizer->Add(m_mainPanel,1,wxEXPAND);
	this->SetSizerAndFit(mainWindowSizer);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainSizerH = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* listTitle = new wxStaticText(m_mainPanel, wxID_ANY, "Организации:");
	listTitle->SetFont(gui_MainFont);

	m_orgList = new wxListBox(m_mainPanel, wxID_ANY,wxDefaultPosition,wxSize(350,150));
	MaterialButton* btn_listAdd = new MaterialButton(m_mainPanel, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 30));
	btn_listAdd->SetButtonLineColour(gui_MainColour);
	btn_listAdd->SetLabelColour(gui_MainColour);
	btn_listAdd->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listDelete = new MaterialButton(m_mainPanel, wxID_ANY, "Удалить", false,wxDefaultPosition, wxSize(80, 30));
	btn_listDelete->SetButtonColour(wxColour(165, 42, 42));
	btn_listDelete->SetLabelColour(*wxWHITE);
	btn_listDelete->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listChange = new MaterialButton(m_mainPanel, wxID_ANY, "Изменить", true, wxDefaultPosition, wxSize(80,30));
	btn_listChange->SetButtonLineColour(gui_MainColour);
	btn_listChange->SetLabelColour(gui_MainColour);
	btn_listChange->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));

	wxBoxSizer* btnSizer = new wxBoxSizer(wxVERTICAL);
	btnSizer->Add(btn_listAdd,0,wxTOP,5);
	btnSizer->Add(btn_listChange, 0, wxTOP, 10);
	btnSizer->Add(btn_listDelete, 0, wxTOP, 10);

	wxBoxSizer* listBtnSizer = new wxBoxSizer(wxHORIZONTAL);
	listBtnSizer->Add(m_orgList );
	listBtnSizer->Add(btnSizer, 0, wxLEFT, 10);

	mainSizer->Add(listTitle, 0, wxEXPAND | wxTOP,30);
	mainSizer->Add(listBtnSizer, 0,  wxTOP, 5);
	mainSizerH->Add(mainSizer, 1, wxEXPAND | wxLEFT, 20);
	m_mainPanel->SetSizerAndFit(mainSizerH);

	this->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Settings_page::OnListEditBtn, this);
}

Settings_page::~Settings_page()
{
}

void Settings_page::OnListEditBtn(wxCommandEvent& evt)
{
	wxSafeYield(this, false);
	Dialog_OrgAddEdit* dlg = new Dialog_OrgAddEdit(this->GetParent(),true,wxID_ANY,"",wxDefaultPosition,wxSize(600,600));
	dlg->Destroy();
}
