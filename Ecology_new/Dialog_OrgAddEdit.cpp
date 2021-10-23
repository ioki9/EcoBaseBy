#include "Dialog_OrgAddEdit.h"
#include <chrono>
#include <wx/datectrl.h>
#include <wx/utils.h>
#include "Utility.h"
#include "MaterialButton.h"
#include "Dialog_ask.h"
#include "GUI_parameters.h"

using namespace std::chrono;

Dialog_OrgAddEdit::Dialog_OrgAddEdit(wxWindow* parent, organization* org, wxWindowID id, const wxString& title, const wxPoint& pos,
	const wxSize& size, long style, const wxString& name) : wxDialog(parent,id,title,pos,size,style,name) , m_parent{parent}
{
	m_db.Backup("db.backup");
	if (org == nullptr)
	{
		m_openedAsEdit = false;
	}
	else
	{
		m_openedAsEdit = true;
		m_org = *org;
	}
	wxString headerStr, unpStr, adressStr, nameStr;
	if (!m_openedAsEdit)
	{
		headerStr = "Добавить организацию";
		unpStr = "";
		adressStr = "";
		nameStr = "";
		m_db.CreateOrgTables(wxString::Format("%i", Settings::getLastAddedOrgID() + 1));
		m_db.SetOrg(Settings::getLastAddedOrgID() + 1);
	}

	else
	{
		headerStr = "Измененить данные организации";
		unpStr = org->unp;
		adressStr = org->address;
		nameStr = org->name;
		m_db.SetOrg(m_org.id);
	}


	this->SetFont(gui_MainFont);
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);

	headerPanel = new wxPanel(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(0, 75));
	headerPanel->SetBackgroundColour(gui_MainColour);
	wxStaticText* headerText = new wxStaticText(headerPanel, wxID_ANY, headerStr);
	headerText->SetForegroundColour(*wxWHITE);
	headerText->SetFont(wxFontInfo(13).FaceName("Segoe UI Semibold"));
	wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
	headerSizer->Add(headerText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
	headerPanel->SetSizer(headerSizer);

	m_1stPage = new wxScrolledWindow(m_mainPanel);
	m_buttonPanel = new wxPanel(m_mainPanel);
	m_mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* staticOrgName = new wxStaticText(m_1stPage, wxID_ANY, wxS("Название организации:"));
	m_orgName = new wxTextCtrl(m_1stPage, wxID_ANY, nameStr);

	wxStaticText* staticOrgAddress = new wxStaticText(m_1stPage, wxID_ANY, wxS("Адрес организации:"));
	m_orgAddress = new wxTextCtrl(m_1stPage, wxID_ANY, adressStr);

	wxStaticText* staticOrgUnp = new wxStaticText(m_1stPage, wxID_ANY, wxS("УНП организации:"));
	m_orgUnp = new wxTextCtrl(m_1stPage, wxID_ANY, unpStr);


	wxStaticText* staticNormList = new wxStaticText(m_1stPage, wxID_ANY, wxS("Нормы образования по видам отходов:"));
	m_wasteNormList = new VirtualCodeList(m_1stPage, &m_db, wxDefaultPosition, wxSize(200, 200));

	MaterialButton* btn_listAdd = new MaterialButton(m_1stPage, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 30));
	btn_listAdd->SetButtonLineColour(gui_MainColour);
	btn_listAdd->SetLabelColour(gui_MainColour);
	btn_listAdd->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listDelete = new MaterialButton(m_1stPage, wxID_ANY, "Удалить", false, wxDefaultPosition, wxSize(80, 30));
	btn_listDelete->SetButtonColour(wxColour(165, 42, 42));
	btn_listDelete->SetLabelColour(*wxWHITE);
	btn_listDelete->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_listChange = new MaterialButton(m_1stPage, wxID_ANY, "Изменить", true, wxDefaultPosition, wxSize(80, 30));
	btn_listChange->SetButtonLineColour(gui_MainColour);
	btn_listChange->SetLabelColour(gui_MainColour);
	btn_listChange->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));

	wxBoxSizer* wasteBtnSizer = new wxBoxSizer(wxVERTICAL);
	wasteBtnSizer->Add(btn_listAdd, 0, wxTOP, 5);
	wasteBtnSizer->Add(btn_listChange, 0, wxTOP, 10);
	wasteBtnSizer->Add(btn_listDelete, 0, wxTOP, 10);

	wxBoxSizer* wasteListSizer = new wxBoxSizer(wxHORIZONTAL);
	wasteListSizer->Add(m_wasteNormList, 1, wxRIGHT, 10);
	wasteListSizer->Add(wasteBtnSizer, 0, wxRIGHT, 50);


	wxStaticText* staticStrgList = new wxStaticText(m_1stPage, wxID_ANY, wxS("Начальные значения хранения отходов:"));
	m_strgList = new VirtualStrgInitList(m_1stPage, &m_db, wxDefaultPosition, wxSize(200, 200));

	MaterialButton* btn_strgListAdd = new MaterialButton(m_1stPage, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 30));
	btn_strgListAdd->SetButtonLineColour(gui_MainColour);
	btn_strgListAdd->SetLabelColour(gui_MainColour);
	btn_strgListAdd->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_strgListDelete = new MaterialButton(m_1stPage, wxID_ANY, "Удалить", false, wxDefaultPosition, wxSize(80, 30));
	btn_strgListDelete->SetButtonColour(wxColour(165, 42, 42));
	btn_strgListDelete->SetLabelColour(*wxWHITE);
	btn_strgListDelete->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_strgListEdit = new MaterialButton(m_1stPage, wxID_ANY, "Изменить", true, wxDefaultPosition, wxSize(80, 30));
	btn_strgListEdit->SetButtonLineColour(gui_MainColour);
	btn_strgListEdit->SetLabelColour(gui_MainColour);
	btn_strgListEdit->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));

	wxBoxSizer* strgBtnSizer = new wxBoxSizer(wxVERTICAL);
	strgBtnSizer->Add(btn_strgListAdd, 0, wxTOP, 5);
	strgBtnSizer->Add(btn_strgListEdit, 0, wxTOP, 10);
	strgBtnSizer->Add(btn_strgListDelete, 0, wxTOP, 10);

	wxBoxSizer* strgListSizer = new wxBoxSizer(wxHORIZONTAL);
	strgListSizer->Add(m_strgList, 1, wxRIGHT, 10);
	strgListSizer->Add(strgBtnSizer, 0, wxRIGHT, 50);

	wxStaticText* staticUnitList = new wxStaticText(m_1stPage, wxID_ANY, wxS("Структурные подразделения организации:"));
	m_unitList = new wxListCtrl(m_1stPage, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxLC_REPORT);
	m_unitList->AppendColumn("Название подразделения", wxLIST_FORMAT_LEFT, 428);
	if (m_openedAsEdit)
	{
		for (size_t i{ 0 }; i < m_org.units.size(); ++i)
		{
			m_unitList->InsertItem(m_unitList->GetItemCount(), m_org.units[i].name);
			m_org.units[i].name;
		}
	}

	MaterialButton* btn_unitListAdd = new MaterialButton(m_1stPage, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 30));
	btn_unitListAdd->SetButtonLineColour(gui_MainColour);
	btn_unitListAdd->SetLabelColour(gui_MainColour);
	btn_unitListAdd->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_unitListDelete = new MaterialButton(m_1stPage, wxID_ANY, "Удалить", false, wxDefaultPosition, wxSize(80, 30));
	btn_unitListDelete->SetButtonColour(wxColour(165, 42, 42));
	btn_unitListDelete->SetLabelColour(*wxWHITE);
	btn_unitListDelete->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	MaterialButton* btn_unitListEdit = new MaterialButton(m_1stPage, wxID_ANY, "Изменить", true, wxDefaultPosition, wxSize(80, 30));
	btn_unitListEdit->SetButtonLineColour(gui_MainColour);
	btn_unitListEdit->SetLabelColour(gui_MainColour);
	btn_unitListEdit->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));

	wxBoxSizer* unitBtnSizer = new wxBoxSizer(wxVERTICAL);
	unitBtnSizer->Add(btn_unitListAdd, 0, wxTOP, 5);
	unitBtnSizer->Add(btn_unitListEdit, 0, wxTOP, 10);
	unitBtnSizer->Add(btn_unitListDelete, 0, wxTOP, 10);

	wxBoxSizer* unitListSizer = new wxBoxSizer(wxHORIZONTAL);
	unitListSizer->Add(m_unitList, 1, wxRIGHT, 10);
	unitListSizer->Add(unitBtnSizer, 0, wxRIGHT, 50);

	wxBoxSizer* firstPageSizer = new wxBoxSizer(wxVERTICAL);
	firstPageSizer->Add(staticOrgName, 0, wxEXPAND | wxTOP, 5);
	firstPageSizer->Add(m_orgName, 0, wxEXPAND | wxRIGHT, 35);
	firstPageSizer->Add(staticOrgAddress, 0, wxEXPAND | wxTOP, 5);
	firstPageSizer->Add(m_orgAddress, 0, wxEXPAND | wxRIGHT, 35);
	firstPageSizer->Add(staticOrgUnp, 0, wxEXPAND | wxTOP, 5);
	firstPageSizer->Add(m_orgUnp, 0, wxEXPAND | wxRIGHT, 35);
	firstPageSizer->Add(staticNormList, 0, wxEXPAND | wxTOP, 15);
	firstPageSizer->Add(wasteListSizer, 0, wxEXPAND);
	firstPageSizer->Add(staticStrgList, 0, wxEXPAND | wxTOP, 15);
	firstPageSizer->Add(strgListSizer, 0, wxEXPAND);
	firstPageSizer->Add(staticUnitList, 0, wxEXPAND | wxTOP, 15);
	firstPageSizer->Add(unitListSizer, 0, wxEXPAND);
	m_1stPage->SetSizerAndFit(firstPageSizer);


	MaterialButton* cancelBtn = new MaterialButton(m_buttonPanel, -1, "ОТМЕНА",
		1, wxDefaultPosition, wxSize(150, 55));
	MaterialButton* applyBtn = new MaterialButton(m_buttonPanel, -1, "ПРИМЕНИТЬ",
		0, wxDefaultPosition, wxSize(150, 55));
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	cancelBtn->SetTextFont(wxFontInfo(10).FaceName("Segoe UI").Bold());
	cancelBtn->SetButtonLineColour(gui_MainColour);
	cancelBtn->SetLabelColour(gui_MainColour);

	applyBtn->SetTextFont(wxFontInfo(10).FaceName("Segoe UI").Bold());
	applyBtn->SetButtonColour(gui_MainColour);
	applyBtn->SetLabelColour(*wxWHITE);

	btnSizer->Add(applyBtn, 0, wxEXPAND | wxLEFT | wxBOTTOM, 20);
	btnSizer->AddStretchSpacer(1);
	btnSizer->Add(cancelBtn, 0, wxEXPAND | wxRIGHT | wxBOTTOM, 20);
	m_buttonPanel->SetSizerAndFit(btnSizer);

	m_mainSizer->Add(headerPanel, 2, wxEXPAND);
	m_mainSizer->Add(m_1stPage, 1, wxEXPAND | wxLEFT, 10);
	m_mainSizer->Add(m_buttonPanel, 0, wxEXPAND);
	m_mainPanel->SetSizerAndFit(m_mainSizer);
	m_1stPage->SetScrollRate(5, 5);
	this->CentreOnScreen();

	this->Bind(wxEVT_PAINT, &Dialog_OrgAddEdit::onPaint, this);
	cancelBtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnCancel, this);
	applyBtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnApply, this);

	btn_listAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnWasteListAdd, this);
	btn_listDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnWasteListDelete, this);
	btn_listChange->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnWasteListEdit, this);

	btn_strgListAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnStorageListAdd, this);
	btn_strgListDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnStorageListDelete, this);
	btn_strgListEdit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnStorageListEdit, this);

	btn_unitListAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnUnitListAdd, this);
	btn_unitListDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnUnitListDelete, this);
	btn_unitListEdit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_OrgAddEdit::OnUnitListEdit, this);



	this->ShowModal();
}

Dialog_OrgAddEdit::~Dialog_OrgAddEdit()
{
	
}

void Dialog_OrgAddEdit::OnCancel(wxCommandEvent& evt)
{
	m_db.SetActiveOrg();
	if (Settings::getLastAddedOrgID() != -1)
	{
		m_db.Restore("db.backup");
		wxRemoveFile(wxGetCwd() + "/db.backup");
		this->Close();
	}
	else
	{
		Dialog_ask* ask = new Dialog_ask(this, "Выход из приложения", "Продолжить без добавления организации невозможно. Желаете выйти?", "Выйти");
		Refresh();
		wxSafeYield(this);
		if (ask->GetReturnCode())
			wxExit();
		ask->Destroy();
	}
	
}

void Dialog_OrgAddEdit::OnApply(wxCommandEvent& evt)
{	
	

	if (m_orgName->GetValue().IsEmpty())
		wxMessageBox("Поле \"Название организации\" не может быть пустым.");
	else if (!m_openedAsEdit)
	{
		wxRemoveFile(wxGetCwd() + "/db.backup");
		m_org.unp = m_orgUnp->GetValue();
		m_org.id = Settings::getLastAddedOrgID() + 1;
		m_org.name = m_orgName->GetValue();
		m_org.address = m_orgAddress->GetValue();
		Settings::addNewOrgAndNotify(m_org, m_parent);

		if (Settings::getActiveOrg() == -1)
		{
			Settings::setActiveOrg(m_org.id,m_parent);
		}
		m_db.SetActiveOrg();
		this->Close();
	}
	else
	{
		m_db.SetActiveOrg();
		wxRemoveFile(wxGetCwd() + "/db.backup");
		m_org.unp = m_orgUnp->GetValue();
		m_org.name = m_orgName->GetValue();
		m_org.address = m_orgAddress->GetValue();
		Settings::editOrgAndNotify(m_org, m_parent);
		this->Close();
	}

}

void Dialog_OrgAddEdit::OnWasteListEdit(wxCommandEvent& evt)
{
	if (m_wasteNormList->GetSelectedItemRef())
	{
		wxDialog dlg(this, wxID_ANY, "Изменить норму образования", wxDefaultPosition, wxSize(300, 230), wxDEFAULT_DIALOG_STYLE);
		wxPanel* main = new wxPanel(&dlg);
		main->SetBackgroundColour(*wxWHITE);
		main->SetFont(gui_MainFont);
		wxStaticText* staticCode = new wxStaticText(main, wxID_ANY, "Код отхода:");
		wxTextCtrl* codeCtrl = new wxTextCtrl(main, wxID_ANY, m_wasteNormList->GetSelectedItemRef()->get()[0]);
		wxStaticText* staticWaste = new wxStaticText(main, wxID_ANY, "Норма образования:");
		wxTextCtrl* wasteCtrl = new wxTextCtrl(main, wxID_ANY, m_wasteNormList->GetSelectedItemRef()->get()[1]);

		MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
		btnNO->SetButtonLineColour(*wxWHITE);
		btnNO->SetLabelColour(wxColour(90, 90, 90));
		btnNO->SetButtonShadow(false);
		btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Применить", true, wxDefaultPosition, wxSize(90, 35));
		btnYES->SetButtonLineColour(*wxWHITE);
		btnYES->SetLabelColour(gui_MainColour);
		btnYES->SetButtonShadow(false);
		btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
		btnSizer->Add(btnYES, 0, wxRIGHT, 15);
		btnSizer->Add(btnNO, 0, wxRIGHT);

		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(staticCode, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(codeCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		mainSizer->Add(staticWaste, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(wasteCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		mainSizer->AddStretchSpacer(1);
		mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
		main->SetSizerAndFit(mainSizer);
		btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
			[&dlg, this, codeCtrl, wasteCtrl](wxCommandEvent& evt) {
				if (codeCtrl->GetValue().IsEmpty())
					wxMessageBox("Код отхода не может быть пустым");
				else
				{
					if (m_wasteNormList->EditSelectedEntry(codeCtrl->GetValue(), wasteCtrl->GetValue()))
						dlg.Close();
					else
						wxMessageBox("Ошибка изменения данных..");
				}});

		btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
		dlg.ShowModal();
	}
}

void Dialog_OrgAddEdit::OnWasteListDelete(wxCommandEvent& evt)
{
	if (m_wasteNormList->GetSelectedItemRef())
	{
		Dialog_ask* dlg = new Dialog_ask(this, "Удаление записи", "Вы уверены, что хотите удалить выбранную запись? Это действие нельзя отменить.");
		Refresh();
		if (dlg->GetReturnCode())
			if (!m_wasteNormList->DeleteSelectedEntry())
			{
				wxMessageBox("Возникла ошибка при удалении");
			}
		dlg->Destroy();
	}
		
}

void Dialog_OrgAddEdit::OnWasteListAdd(wxCommandEvent& evt)
{
	wxDialog dlg(this, wxID_ANY, "Добавить норму образования", wxDefaultPosition, wxSize(300, 230), wxDEFAULT_DIALOG_STYLE);
	wxPanel* main = new wxPanel(&dlg);
	main->SetBackgroundColour(*wxWHITE);
	main->SetFont(gui_MainFont);
	wxStaticText* staticCode = new wxStaticText(main, wxID_ANY, "Код отхода:");
	wxTextCtrl* codeCtrl = new wxTextCtrl(main, wxID_ANY);
	wxStaticText* staticWaste = new wxStaticText(main, wxID_ANY, "Норма образования:");
	wxTextCtrl* wasteCtrl = new wxTextCtrl(main, wxID_ANY);

	MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
	btnNO->SetButtonLineColour(*wxWHITE);
	btnNO->SetLabelColour(wxColour(90, 90, 90));
	btnNO->SetButtonShadow(false);
	btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 35));
	btnYES->SetButtonLineColour(*wxWHITE);
	btnYES->SetLabelColour(gui_MainColour);
	btnYES->SetButtonShadow(false);
	btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	btnSizer->Add(btnYES, 0, wxRIGHT, 15);
	btnSizer->Add(btnNO, 0, wxRIGHT);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(staticCode, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(codeCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mainSizer->Add(staticWaste, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(wasteCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mainSizer->AddStretchSpacer(1);
	mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
	main->SetSizerAndFit(mainSizer);
	btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		[&dlg, this, codeCtrl, wasteCtrl](wxCommandEvent& evt) {
			if (codeCtrl->GetValue().IsEmpty())
				wxMessageBox("Ошибка:код отхода не может быть пустым");
			else if (!m_db.IsCodeExists(codeCtrl->GetValue()))
				wxMessageBox("Ошибка:введенного кода отхода не существует.");
			else
			{
				if (m_wasteNormList->AddNewEntry(codeCtrl->GetValue(), wasteCtrl->GetValue()))
					dlg.Close();

				else
					wxMessageBox("Значение для данного вида отхода уже существует.");
			}});

	btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
	dlg.ShowModal();
}


void Dialog_OrgAddEdit::OnStorageListEdit(wxCommandEvent& evt)
{
	if (m_strgList->GetSelectedItemRef())
	{
		wxDialog dlg(this, wxID_ANY, "Изменить начальные значения хранения", wxDefaultPosition, wxSize(300, 320), wxDEFAULT_DIALOG_STYLE);
		wxPanel* main = new wxPanel(&dlg);
		main->SetBackgroundColour(*wxWHITE);
		main->SetFont(gui_MainFont);
		wxStaticText* staticCode = new wxStaticText(main, wxID_ANY, "Код отхода:");
		wxTextCtrl* codeCtrl = new wxTextCtrl(main, wxID_ANY, m_strgList->GetSelectedItemRef()->get()[1]);
		wxStaticText* staticDate = new wxStaticText(main, wxID_ANY, "Дата:");
		wxDateTime currentDate;
		currentDate.ParseFormat(m_strgList->GetSelectedItemRef()->get()[0], wxS("%Y.%m.%d"));
		wxDatePickerCtrl* dateCtrl = new wxDatePickerCtrl(main, wxID_ANY,currentDate, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
		
		wxDateTime firstDate;
		firstDate.ParseFormat(wxS("2000.01.01"), wxS("%Y.%m.%d"), wxDefaultDateTime);
		wxDateTime lastDate = m_db.getFirstEntryByCodeNoInit(m_strgList->GetSelectedItemRef()->get()[1]);
		dateCtrl->SetRange(firstDate, lastDate);
		wxStaticText* staticStorage = new wxStaticText(main, wxID_ANY, "Хранение:");
		wxTextCtrl* storageCtrl = new wxTextCtrl(main, wxID_ANY, wxEmptyString,
			wxDefaultPosition,wxDefaultSize,0L,utility::GetDoubleValidator(3,wxAtof(m_strgList->GetSelectedItemRef()->get()[2])));
		MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
		btnNO->SetButtonLineColour(*wxWHITE);
		btnNO->SetLabelColour(wxColour(90, 90, 90));
		btnNO->SetButtonShadow(false);
		btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Применить", true, wxDefaultPosition, wxSize(90, 35));
		btnYES->SetButtonLineColour(*wxWHITE);
		btnYES->SetLabelColour(gui_MainColour);
		btnYES->SetButtonShadow(false);
		btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
		btnSizer->Add(btnYES, 0, wxRIGHT, 15);
		btnSizer->Add(btnNO, 0, wxRIGHT);

		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(staticDate, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(dateCtrl, 0, wxLEFT | wxRIGHT, 10);
		mainSizer->Add(staticCode, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(codeCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		mainSizer->Add(staticStorage, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(storageCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		mainSizer->AddStretchSpacer(1);
		mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
		main->SetSizerAndFit(mainSizer);

		btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
			[&dlg, this, codeCtrl, dateCtrl, storageCtrl](wxCommandEvent& evt) {
				if (codeCtrl->GetValue().IsEmpty() || storageCtrl->GetValue().IsEmpty() )
					wxMessageBox("Ошибка:все строки должны быть заполнены.");
				else if(!m_db.IsCodeExists(codeCtrl->GetValue()))
					wxMessageBox("Ошибка:введенного кода отхода не существует.");
				else
				{
					if (m_strgList->EditSelectedEntry(codeCtrl->GetValue(), dateCtrl->GetValue(), storageCtrl->GetValue()))
						dlg.Close();
					else
						wxMessageBox("Ошибка изменения...");
				}});

		btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
		dlg.ShowModal();
	}
}

void Dialog_OrgAddEdit::OnStorageListDelete(wxCommandEvent& evt)
{
	if (m_strgList->GetSelectedItemRef())
	{
		wxSafeYield(this, false);
		Dialog_ask* dlg = new Dialog_ask(this, "Удаление записи", "Вы уверены, что хотите удалить выбранную запись? Это действие нельзя отменить.");
		Refresh();
		if (dlg->GetReturnCode())
			if (!m_strgList->DeleteSelectedEntry())
				wxMessageBox("Возникла ошибка при удалении");

		dlg->Destroy();
	}
}

void Dialog_OrgAddEdit::OnStorageListAdd(wxCommandEvent& evt)
{
	wxDialog dlg(this, wxID_ANY, "Добавить начальные значения хранения", wxDefaultPosition, wxSize(300, 320), wxDEFAULT_DIALOG_STYLE);
	wxPanel* main = new wxPanel(&dlg);
	main->SetBackgroundColour(*wxWHITE);
	main->SetFont(gui_MainFont);
	wxStaticText* staticCode = new wxStaticText(main, wxID_ANY, "Код отхода:");
	wxTextCtrl* codeCtrl = new wxTextCtrl(main, wxID_ANY);
	wxStaticText* staticDate = new wxStaticText(main, wxID_ANY, "Дата:");
	wxDatePickerCtrl* dateCtrl = new wxDatePickerCtrl(main, wxID_ANY, wxDateTime::Today(), wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* staticStorage = new wxStaticText(main, wxID_ANY, "Хранение:");
	wxTextCtrl* storageCtrl = new wxTextCtrl(main, wxID_ANY);


	MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
	btnNO->SetButtonLineColour(*wxWHITE);
	btnNO->SetLabelColour(wxColour(90, 90, 90));
	btnNO->SetButtonShadow(false);
	btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 35));
	btnYES->SetButtonLineColour(*wxWHITE);
	btnYES->SetLabelColour(gui_MainColour);
	btnYES->SetButtonShadow(false);
	btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	btnSizer->Add(btnYES, 0, wxRIGHT, 15);
	btnSizer->Add(btnNO, 0, wxRIGHT);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(staticDate, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(dateCtrl, 0, wxLEFT | wxRIGHT, 10);
	mainSizer->Add(staticCode, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(codeCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mainSizer->Add(staticStorage, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(storageCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mainSizer->AddStretchSpacer(1);
	mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
	main->SetSizerAndFit(mainSizer);

	btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		[&dlg, this, codeCtrl, dateCtrl,storageCtrl](wxCommandEvent& evt) {
			if (codeCtrl->GetValue().IsEmpty() || storageCtrl->GetValue().IsEmpty())
				wxMessageBox("Все строки должны быть заполнены.");
			else if(!m_db.isInitStorageViable(codeCtrl->GetValue(), dateCtrl->GetValue().Format(wxS("%Y.%m.%d") )))
				wxMessageBox("Ошибка: В выбраном или предыдущих месяцах есть внесенные записи.");
			else
			{
				
				if (m_strgList->AddNewEntry(codeCtrl->GetValue(), dateCtrl->GetValue(),storageCtrl->GetValue()))
					dlg.Close();
				else
					wxMessageBox("Значение уже существует.");
			}});

	btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
	dlg.ShowModal();
}


void Dialog_OrgAddEdit::OnUnitListEdit(wxCommandEvent& evt)
{
	if (int selected = m_unitList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED); selected != -1)
	{
		wxDialog dlg(this, wxID_ANY, "Изменить структурное подразделение", wxDefaultPosition, wxSize(370, 180), wxDEFAULT_DIALOG_STYLE);
		wxPanel* main = new wxPanel(&dlg);
		main->SetBackgroundColour(*wxWHITE);
		main->SetFont(gui_MainFont);
		wxStaticText* staticUnit = new wxStaticText(main, wxID_ANY, "Название структурного подразделения:");
		wxTextCtrl* unitCtrl = new wxTextCtrl(main, wxID_ANY,m_unitList->GetItemText(selected));


		MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
		btnNO->SetButtonLineColour(*wxWHITE);
		btnNO->SetLabelColour(wxColour(90, 90, 90));
		btnNO->SetButtonShadow(false);
		btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Изменить", true, wxDefaultPosition, wxSize(80, 35));
		btnYES->SetButtonLineColour(*wxWHITE);
		btnYES->SetLabelColour(gui_MainColour);
		btnYES->SetButtonShadow(false);
		btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
		btnSizer->Add(btnYES, 0, wxRIGHT, 15);
		btnSizer->Add(btnNO, 0, wxRIGHT);

		wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
		mainSizer->Add(staticUnit, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
		mainSizer->Add(unitCtrl, 0, wxLEFT | wxRIGHT | wxEXPAND, 10);
		mainSizer->AddStretchSpacer(1);
		mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
		main->SetSizerAndFit(mainSizer);

		btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
			[&dlg, this, unitCtrl,selected](wxCommandEvent& evt) {
				if (m_unitList->FindItem(-1, unitCtrl->GetValue(), false) > -1 && m_unitList->FindItem(-1, unitCtrl->GetValue(), false) != selected)
					wxMessageBox("Структурное подразделение с таким названием уже существует");
				else if (!m_openedAsEdit)
				{
					m_unitList->SetItem(selected, 0, unitCtrl->GetValue());
					m_org.units[selected].name = unitCtrl->GetValue();
					dlg.Close();
				}
				else
				{
					m_unitList->SetItem(selected, 0, unitCtrl->GetValue());
					m_org.units[selected].name = unitCtrl->GetValue();
					dlg.Close();
				}
			});

		btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
		btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
		dlg.ShowModal();
	}
}

void Dialog_OrgAddEdit::OnUnitListDelete(wxCommandEvent& evt)
{
	if (int selected = m_unitList->GetNextItem(- 1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED); selected != -1)
	{
		if (!m_openedAsEdit)
		{
			wxSafeYield(this, false);
			Dialog_ask* dlg = new Dialog_ask(this, "Удаление структурного подразделения", "Вы уверены, что хотите удалить выбранное подразделение?");
			Refresh();
			if (dlg->GetReturnCode())
			{
				m_unitList->DeleteItem(selected);
				m_org.units.erase(m_org.units.begin() + selected);
			}
			dlg->Destroy();
		}
		else
		{
			wxSafeYield(this, false);
			Dialog_ask* dlg = new Dialog_ask(this, "Удаление структурного подразделения", "Вы уверены, что хотите удалить выбранное подразделение?"
				"Все записи связанные с этим подразделением будут удалены. Это действие нельзя отменить.");
			Refresh();
			if (dlg->GetReturnCode())
			{
				if (!m_unitList->DeleteItem(selected) || !m_db.DeleteAllUnitEntrys(m_org.units[selected].id))
					wxMessageBox("Возникла ошибка при удалении");
				else
					m_org.units.erase(m_org.units.begin() + selected);
			}
			dlg->Destroy();
		}

	}
}

void Dialog_OrgAddEdit::OnUnitListAdd(wxCommandEvent& evt)
{
	wxDialog dlg(this, wxID_ANY, "Добавить структурное подразделение", wxDefaultPosition, wxSize(370, 180), wxDEFAULT_DIALOG_STYLE);
	wxPanel* main = new wxPanel(&dlg);
	main->SetBackgroundColour(*wxWHITE);
	main->SetFont(gui_MainFont);
	wxStaticText* staticUnit = new wxStaticText(main, wxID_ANY, "Название структурного подразделения:");
	wxTextCtrl* unitCtrl = new wxTextCtrl(main, wxID_ANY);
	

	MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, "Отмена", true, wxDefaultPosition, wxSize(70, 35));
	btnNO->SetButtonLineColour(*wxWHITE);
	btnNO->SetLabelColour(wxColour(90, 90, 90));
	btnNO->SetButtonShadow(false);
	btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, "Добавить", true, wxDefaultPosition, wxSize(80, 35));
	btnYES->SetButtonLineColour(*wxWHITE);
	btnYES->SetLabelColour(gui_MainColour);
	btnYES->SetButtonShadow(false);
	btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	btnSizer->Add(btnYES, 0, wxRIGHT, 15);
	btnSizer->Add(btnNO, 0, wxRIGHT);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(staticUnit, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	mainSizer->Add(unitCtrl, 0, wxLEFT | wxRIGHT | wxEXPAND, 10);
	mainSizer->AddStretchSpacer(1);
	mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT, 10);
	main->SetSizerAndFit(mainSizer);

	btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		[&dlg, this, unitCtrl](wxCommandEvent& evt) {
			if (m_unitList->FindItem(-1, unitCtrl->GetValue(), false) > -1)
				wxMessageBox("Структурное подразделение с таким названием уже существует");
			else if(!m_openedAsEdit)
			{
				if (!m_unitList->GetItemCount())
					m_org.units.push_back({ 0,unitCtrl->GetValue() });
				else
					m_org.units.push_back({ m_org.units.back().id + 1,unitCtrl->GetValue() });

				m_unitList->InsertItem(m_unitList->GetItemCount(),unitCtrl->GetValue());
				
				dlg.Close();
			}
			else
			{
				if (!m_unitList->GetItemCount())
					m_org.units.push_back({ 0,unitCtrl->GetValue() });
				else
					m_org.units.push_back({ m_org.units.back().id + 1,unitCtrl->GetValue() });

				m_unitList->InsertItem(m_unitList->GetItemCount(), unitCtrl->GetValue());
				dlg.Close();
			}
		});

	btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
	btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg](wxCommandEvent& evt) { dlg.Close(); });
	dlg.ShowModal();
}


void Dialog_OrgAddEdit::onPaint(wxPaintEvent& evt)
{
	if (!m_isDrawn)
	{
		wxWindowDC* dc = new wxWindowDC(m_parent);
		utility::paintDarkBackground(dc,m_parent);
		m_isDrawn = true;
		delete dc;
	}
		
}

