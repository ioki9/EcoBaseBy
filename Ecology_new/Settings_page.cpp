#include "Settings_page.h"
#include "GUI_parameters.h"
#include "MaterialButton.h"
#include "Dialog_OrgAddEdit.h"
#include "Dialog_ask.h"
#include "DBMain.h"
#include "Settings.h"
#include "CustomEvents.h"

Settings_page::Settings_page(wxWindow* parent, wxChoice* orgChoice) : wxPanel(parent), m_mainOrgChoice{ orgChoice }, m_parent{ parent }
{
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer* mainWindowSizer = new wxBoxSizer(wxVERTICAL);
	mainWindowSizer->Add(m_mainPanel,1,wxEXPAND);
	this->SetSizerAndFit(mainWindowSizer);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainSizerH = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* listTitle = new wxStaticText(m_mainPanel, wxID_ANY, "�����������:");
	listTitle->SetFont(gui_MainFont);

	m_orgList = new VirtualOrgList(m_mainPanel, wxID_ANY,wxDefaultPosition,wxSize(350,150));
	MaterialButton* btn_listAdd = new MaterialButton(m_mainPanel, wxID_ANY, "��������", true, wxDefaultPosition, wxSize(80, 30));
	btn_listAdd->SetButtonLineColour(gui_MainColour);
	btn_listAdd->SetLabelColour(gui_MainColour);
	btn_listAdd->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listDelete = new MaterialButton(m_mainPanel, wxID_ANY, "�������", false,wxDefaultPosition, wxSize(80, 30));
	btn_listDelete->SetButtonColour(wxColour(165, 42, 42));
	btn_listDelete->SetLabelColour(*wxWHITE);
	btn_listDelete->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listChange = new MaterialButton(m_mainPanel, wxID_ANY, "��������", true, wxDefaultPosition, wxSize(80,30));
	btn_listChange->SetButtonLineColour(gui_MainColour);
	btn_listChange->SetLabelColour(gui_MainColour);
	btn_listChange->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));

	wxStaticText* dirPickerLabel = new wxStaticText(m_mainPanel, wxID_ANY, "���� ���������� ����������:");
	m_dir = new myDirPicker(m_mainPanel , wxID_ANY, Settings::GetPdfSavePath(), "����� ��� ���������� ����������", wxDefaultPosition, wxSize(460, 30));
	dirPickerLabel->SetFont(gui_MainFont);

	wxBoxSizer* btnSizer = new wxBoxSizer(wxVERTICAL);
	btnSizer->Add(btn_listAdd,0,wxTOP,5);
	btnSizer->Add(btn_listChange, 0, wxTOP, 10);
	btnSizer->Add(btn_listDelete, 0, wxTOP, 10);

	wxBoxSizer* listBtnSizer = new wxBoxSizer(wxHORIZONTAL);
	listBtnSizer->Add(m_orgList,1 );
	listBtnSizer->Add(btnSizer, 0, wxLEFT, 10);

	mainSizer->Add(listTitle, 0, wxEXPAND | wxTOP,30);
	mainSizer->Add(listBtnSizer, 0,  wxTOP, 5);
	mainSizer->Add(dirPickerLabel, 0, wxEXPAND | wxTOP, 30);
	mainSizer->Add(m_dir, 0, wxTOP, 5);
	mainSizerH->Add(mainSizer, 1, wxEXPAND | wxLEFT, 20);
	m_mainPanel->SetSizerAndFit(mainSizerH);

	btn_listChange->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Settings_page::OnListEditBtn, this);
	btn_listAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Settings_page::OnListAddBtn, this);
	btn_listDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Settings_page::OnListDeleteBtn, this);
	this->Bind(EVT_DIR_CHANGED, &Settings_page::OnDirChange, this);
}

Settings_page::~Settings_page()
{
}

void Settings_page::OnListEditBtn(wxCommandEvent& evt)
{
	if (m_orgList->GetSelectedItemRef())
	{
		wxSafeYield(this, false);
		Dialog_OrgAddEdit* dlg = new Dialog_OrgAddEdit(m_parent, &m_orgList->GetSelectedItemRef()->get(), wxID_ANY, "", wxDefaultPosition, wxSize(600, 600));
		m_parent->Refresh();
		dlg->Destroy();
	}

}

void Settings_page::OnListAddBtn(wxCommandEvent& evt)
{
	wxSafeYield(this, false);
	Dialog_OrgAddEdit* dlg = new Dialog_OrgAddEdit(m_parent, nullptr, wxID_ANY, "", wxDefaultPosition, wxSize(600, 600));
	m_parent->Refresh();
	m_orgList->UpdateAfterEdit();
	dlg->Destroy();
}

void Settings_page::OnListDeleteBtn(wxCommandEvent& evt)
{
	if (m_orgList->GetSelectedItemRef())
	{
		if (m_orgList->GetItemCount() < 2)
			wxMessageBox("������: � ����������� ������ ���� ���� �� ���� �����������.");
		else
		{
			wxSafeYield(this, false);
			Dialog_ask* ask = new Dialog_ask(m_parent, "�������� �����������", "�� �������, ��� ������ ������� ��������� �����������? ��� ������ ��������� � ���� ������������ ����� �������.");
			m_parent->Refresh();
			if (ask->GetReturnCode())
			{
				int id = m_orgList->GetSelectedItemRef()->get().id;
				DBMain db;
				db.DeleteOrgTables(id);
				Settings::deleteOrgAndNotify(m_orgList->GetSelectedItemRef()->get(), m_parent);
				if (id == Settings::getActiveOrg())
					Settings::setActiveOrg(Settings::GetOrgArrayPtr()->at(0).id, m_parent);
				m_orgList->UpdateAfterEdit();
			}
			ask->Destroy();
		}
	}
}

void Settings_page::OnDirChange(wxCommandEvent& evt)
{
	Settings::SetPdfSavePath(m_dir->getDirectory());
}
