#include "cMain.h"
#include <chrono>
#include <wx/pdfdoc.h>
#include <wx/pdffontmanager.h>
#include <wx/utils.h>
#include <wx/wxsqlite3.h>
#include <wx/busyinfo.h>
#include <wx/listctrl.h>
#include <optional>
#include "MyBusyInfo.h"
#include "../PDF/PDF_Main.h"
#include "Dialog_cMainListEdit.h"
#include "Dialog_ask.h"
#include "Dialog_OrgAddEdit.h"
#include "../Controls/VirtualCodeList.h"
#include "../Settings.h"
#include "../GUI_parameters.h"
#include "../Structs.h"
#include "../Utility/CustomEvents.h"
#include "../Utility/CustomAutoComplete.h"
#include "../Controls/VirtualEntryDateList.h"
#include "../Frames/Dialog_generic.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EcoBaseBy", wxDefaultPosition, wxSize(1024,600))
{
	SetIcons(wxIconBundle(wxGetCwd() + "/EcoIcon.ico"));
	Settings::LoadState();
	if (Settings::getLastAddedOrgID() == -1)
	{
		Dialog_OrgAddEdit* dlg = new Dialog_OrgAddEdit(this, nullptr, wxID_ANY, "", wxDefaultPosition, wxSize(600, 600));
		Refresh();
		if (dlg->GetReturnCode() == 0)
		{
			dlg->Destroy();
			this->Close();
			return;
		}
		dlg->Destroy();
	}
	wxPdfFontManager::GetFontManager()->RegisterFontDirectory(wxGetCwd() + "/Fonts");
	this->SetMinClientSize(wxSize(660, 480));
	Center();
	this->initListPanel();
	this->initAddPanel();
	this->initFormPDFPage();
	this->initMainMenu();
	this->initSettingsPage();
	m_activePanel = m_listPanel;
	setActiveMenuButton(m_menuButtonList);
	m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(m_mainSizer);
	m_mainSizer->Add(m_mainMenu, 0, wxEXPAND | wxBOTTOM);
	m_mainSizer->Add(m_listPanel, 1, wxEXPAND);

	this->Bind(EVT_ACTIVE_ORG_CHANGED, &cMain::PostOrgEvents, this);
	this->Bind(EVT_ACTIVE_UNIT_CHANGED, &cMain::PostOrgEvents, this);
	this->Bind(EVT_ORGANIZATION_CHANGED, &cMain::PostOrgEvents, this);
	this->Bind(EVT_ORGANIZATION_CHANGED, &cMain::OnOrgChanged,this);
	this->Bind(wxEVT_SIZE, &cMain::OnSize, this);
	this->Bind(EVT_DATABASE_CHANGED, &cMain::OnDbChange, this);
	this->Bind(wxEVT_CLOSE_WINDOW, [&](wxCloseEvent& evt)
		{
			Dialog_ask* ask = new Dialog_ask(this, wxString::FromUTF8("Сохранение базы данных"), 
				wxString::FromUTF8("Желаете сохранить копию базы данных?"), wxString::FromUTF8("Сохранить"), gui_MainColour, wxString::FromUTF8("Нет")
				,wxDefaultPosition,wxSize(400,150));
			Refresh();
			if (ask->GetReturnCode())
			{
				wxDirDialog* dirDlg = new wxDirDialog(this, wxString::FromUTF8("Путь сохранения базы данных"), wxGetCwd(),
					wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
				dirDlg->ShowModal();
				wxCopyFile(wxGetCwd() + "/passport_data.db", dirDlg->GetPath() + "/passport_data.db");
				dirDlg->Destroy();
			}
			ask->Destroy();
			evt.Skip();

		});
	
}

cMain::~cMain()
{
	delete m_dataBase;
	utility::ClearVars();
	Settings::SaveState();

}

void cMain::initListPanel()
{
	m_listPanel = new wxPanel(this, ID_LIST_PANEL, wxDefaultPosition, wxDefaultSize);
	m_listPanel->SetBackgroundColour(wxColor(255, 255, 255));
	m_listPanel->SetFont(gui_MainFont);
	m_listMainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);


	MaterialButton* editButton = new MaterialButton(m_listPanel, wxID_ANY, wxString::FromUTF8("ИЗМЕНИТЬ"), true,wxDefaultPosition, wxSize(100, 35));
	editButton->SetButtonLineColour(gui_MainColour);
	editButton->SetLabelColour(gui_MainColour);

	m_deleteButton = new MaterialButton(m_listPanel, wxID_ANY, wxString::FromUTF8("УДАЛИТЬ"), false,wxDefaultPosition,wxSize(100, 35));
	m_deleteButton->SetButtonColour(wxColour(165, 42, 42));
	m_deleteButton->SetLabelColour(*wxWHITE);
	buttonSizer->AddStretchSpacer(1);
	buttonSizer->Add(editButton, 0, wxRIGHT, 5);
	buttonSizer->Add(m_deleteButton, 0,  wxRIGHT, 20);

	
	m_grid = new myGridTable(m_listPanel, wxID_ANY, wxPoint(0, 0),wxSize(this->GetSize().GetWidth() - m_mainMenuWidth, m_listPanel->GetSize().GetY()));

	

	m_listMainSizer->AddSpacer(50);
	m_listMainSizer->Add(buttonSizer,0,wxALIGN_RIGHT);
	m_listMainSizer->Add(m_grid,1,wxEXPAND | wxTOP,3);
	m_listPanel->SetSizerAndFit(m_listMainSizer);
	editButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnListEditButton, this);
	m_deleteButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnListDeleteButton, this);

}

void cMain::initAddPanel()
{
	m_addPanel = new Add_panel(this);
	m_addPanel->SetBackgroundColour(wxColor(255, 255, 255));
	m_addPanel->Hide();
}

void cMain::initSettingsPage()
{
	m_settingsPage = new Settings_page(this,m_orgChoice);
	
	m_settingsPage->Hide();
}

void cMain::initMainMenu()
{
	
	m_mainMenu = new wxPanel(this, ID_MAINMENU_PANEL, wxDefaultPosition, wxSize(m_mainMenuWidth, 200));
	m_mainMenu->SetDoubleBuffered(true);
	m_mainMenu->SetBackgroundColour(gui_MainColour);
	m_mainMenu->SetFont(wxFontInfo(10.5).FaceName("Segoe UI"));

	m_menuButtonList = new MainMenuTabButton(m_mainMenu, wxString::FromUTF8("Таблица"), ID_MAINMENU_LIST_BUTTON,false,wxSize(m_mainMenuWidth,50),wxPoint(0,150));
	m_menuButtonList->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonList);

	m_menuButtonAdd = new MainMenuTabButton(m_mainMenu, wxString::FromUTF8("Добавить запись"), ID_MAINMENU_ADD_BUTTON,false, wxSize(m_mainMenuWidth, 50), wxPoint(0, 200));
	m_menuButtonAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonAdd);

	m_menuButtonForm = new MainMenuTabButton(m_mainMenu, wxString::FromUTF8("Сформировать"), ID_MAINMENU_FORM_BUTTON,false, wxSize(m_mainMenuWidth, 50), wxPoint(0, 250));
	m_menuButtonForm->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonForm);

	m_menuButtonSetting = new MainMenuTabButton(m_mainMenu, wxString::FromUTF8("Настройки"), ID_MAINMENU_SETTINGS_BUTTON, false, wxSize(m_mainMenuWidth, 50), wxPoint(0, 300));
	m_menuButtonSetting->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_menuButtonSetting->setDropArrowtSize(wxSize(14, 30));
	m_allMenuButtons.push_back(m_menuButtonSetting);
	
	wxArrayString orgNames;
	wxString activeOrg;
	wxArrayString unitNames;
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		orgNames.Add(it.name);
		if (it.id == Settings::getActiveOrg())
		{
			activeOrg = it.name;
			for (const auto& unit : it.units)
				unitNames.Add(unit.name);
		}

	}
	m_orgChoice = new wxChoice(m_mainMenu, -1, wxPoint(120, 42), wxSize(140, 30), orgNames);
	m_orgChoice->SetStringSelection(activeOrg);
	m_orgChoice->SetFont(wxFontInfo(10).FaceName("Segoe UI"));
	m_orgText = new wxStaticText(m_mainMenu, -1, wxString::FromUTF8("Организация:"), wxPoint(8, 42));
	m_orgText->SetForegroundColour(*wxWHITE);
	m_unitText = new wxStaticText(m_mainMenu, -1, wxString::FromUTF8("Подразделение:"), wxPoint(8, 82));
	m_unitText->SetForegroundColour(*wxWHITE);
	m_unitChoice = new wxChoice(m_mainMenu, -1, wxPoint(120, 82), wxSize(140, 30), unitNames);


	if (Settings::getActiveUnitID() > -1)
		m_unitChoice->SetStringSelection(Settings::getActiveUnitString());

	else
		m_unitChoice->SetSelection(0);
	
	m_unitChoice->SetFont(wxFontInfo(10).FaceName("Segoe UI"));
	m_orgChoice->Bind(wxEVT_CHOICE, &cMain::OnOrgSelect, this);
	m_unitChoice->Bind(wxEVT_CHOICE, &cMain::OnUnitSelect, this);


}

void cMain::setActiveMenuButton(MainMenuTabButton* activeBtn)
{
	this->setAllMenuBtnInactive();
	activeBtn->setSelected(true);
}

void  cMain::initFormPDFPage()
{
	m_formPDFPanel = new wxScrolledWindow(this,wxID_ANY,wxPoint(0,0),wxSize(600,600));
	m_formPDFPanel->Hide();
	m_formPDFPanel->SetBackgroundColour(*wxWHITE);
	m_formPDFPanel->SetFont(wxFontInfo(14).FaceName("Segoe UI"));
	m_formPDFPanel->SetDoubleBuffered(true);

	m_firstDate = m_dataBase->getFirstEntryDate();
	m_lastDate = m_dataBase->getLastEntryDate();
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// _____________POD9_____________
	wxStaticText* labelPOD9 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("ПОД 9"));
	labelPOD9->SetForegroundColour(*wxBLACK);
	labelPOD9->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDatePod9 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("Сформировать с:"));
	txtFirstDatePod9->SetForegroundColour(*wxBLACK);
	m_date1_pod9 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate,wxPoint(300,200),wxDefaultSize,wxDP_DROPDOWN);
	wxStaticText* txtSecondDatePod9 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("По:"));
	txtSecondDatePod9->SetForegroundColour(*wxBLACK);
	m_date2_pod9 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerPod9Row1 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod9Row1->Add(txtFirstDatePod9,0,wxLEFT,20);
	sizerPod9Row1->Add(m_date1_pod9,0, wxLEFT, 15);
	sizerPod9Row1->Add(txtSecondDatePod9, 0, wxLEFT, 50);
	sizerPod9Row1->Add(m_date2_pod9, 0, wxLEFT, 15);
	MaterialButton* btnFormPOD9 = new MaterialButton(m_formPDFPanel, ID_FORMPDF_POD9_BUTTON, wxString::FromUTF8("СФОРМИРОВАТЬ"), true, wxDefaultPosition, wxSize(155, 40));
	btnFormPOD9->SetButtonLineColour(gui_MainColour);
	btnFormPOD9->SetButtonFillColour(*wxWHITE);
	btnFormPOD9->SetLabelColour(gui_MainColour);
	m_date1_pod9->SetRange(m_firstDate, m_lastDate);
	m_date2_pod9->SetRange(m_firstDate, m_lastDate);

	//______________POD10_____________
	wxStaticText* labelPOD10 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("ПОД 10"));
	labelPOD10->SetForegroundColour(*wxBLACK);
	labelPOD10->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDatePod10 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("Сформировать с:"));
	txtFirstDatePod10->SetForegroundColour(*wxBLACK);
	m_date1_pod10 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate, wxPoint(300, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* txtSecondDatePod10 = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("По:"));
	txtSecondDatePod10->SetForegroundColour(*wxBLACK);
	m_date2_pod10 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerPod10Row1 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod10Row1->Add(txtFirstDatePod10, 0, wxLEFT, 20);
	sizerPod10Row1->Add(m_date1_pod10, 0, wxLEFT, 15);
	sizerPod10Row1->Add(txtSecondDatePod10, 0, wxLEFT, 50);
	sizerPod10Row1->Add(m_date2_pod10, 0, wxLEFT, 15);

	MaterialButton* btnFormPOD10 = new MaterialButton(m_formPDFPanel, ID_FORMPDF_POD10_BUTTON, wxString::FromUTF8("СФОРМИРОВАТЬ"), true, wxDefaultPosition, wxSize(155, 40));
	btnFormPOD10->SetButtonLineColour(gui_MainColour);
	btnFormPOD10->SetButtonFillColour(*wxWHITE);
	btnFormPOD10->SetLabelColour(gui_MainColour);
	MaterialButton* btnSetEntryDates = new MaterialButton(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("ДАТЫ ВНЕСЕНИЯ"), 
		true,wxDefaultPosition,wxSize(162,40));
	btnSetEntryDates->SetButtonLineColour(gui_MainColour);
	btnSetEntryDates->SetLabelColour(gui_MainColour);
	btnSetEntryDates->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
	wxBoxSizer* pod10BtnSizer = new wxBoxSizer(wxHORIZONTAL);
	pod10BtnSizer->Add(btnFormPOD10, 0);
	pod10BtnSizer->Add(btnSetEntryDates, 0,wxLEFT,40);


	m_date1_pod10->SetRange(m_firstDate, m_lastDate);
	m_date2_pod10->SetRange(m_firstDate, m_lastDate);
	//______________JOURNAL_____________
	wxStaticText* labelJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("ЖУРНАЛ"));
	labelJournal->SetForegroundColour(*wxBLACK);
	labelJournal->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDateJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("Сформировать с:"));
	txtFirstDateJournal->SetForegroundColour(*wxBLACK);
	m_date1_journal = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate, wxPoint(300, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* txtSecondDateJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, wxString::FromUTF8("По:"));
	txtSecondDateJournal->SetForegroundColour(*wxBLACK);
	m_date2_journal = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerJournalRow1 = new wxBoxSizer(wxHORIZONTAL);

	sizerJournalRow1->Add(txtFirstDateJournal, 0, wxLEFT, 20);
	sizerJournalRow1->Add(m_date1_journal, 0, wxLEFT, 15);
	sizerJournalRow1->Add(txtSecondDateJournal, 0, wxLEFT, 50);
	sizerJournalRow1->Add(m_date2_journal, 0, wxLEFT, 15);
	MaterialButton* btnFormJournal = new MaterialButton(m_formPDFPanel, ID_FORMPDF_JOURNAL_BUTTON, wxString::FromUTF8("СФОРМИРОВАТЬ"), true, wxDefaultPosition, wxSize(155, 40));
	btnFormJournal->SetButtonLineColour(gui_MainColour);
	btnFormJournal->SetButtonFillColour(*wxWHITE);
	btnFormJournal->SetLabelColour(gui_MainColour);

	m_date2_journal->SetRange(m_firstDate, m_lastDate);
	m_date1_journal->SetRange(m_firstDate, m_lastDate);


	mainSizer->Add(labelPOD9, 0, wxEXPAND | wxLEFT | wxTOP, 20);
	mainSizer->Add(sizerPod9Row1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(btnFormPOD9, 0, wxLEFT , 40);
	mainSizer->AddSpacer(30);
	mainSizer->Add(labelPOD10, 0, wxEXPAND | wxLEFT | wxTOP, 20);
	mainSizer->Add(sizerPod10Row1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(pod10BtnSizer, 0, wxLEFT, 40);
	mainSizer->AddSpacer(30);
	mainSizer->Add(labelJournal, 0, wxEXPAND | wxLEFT | wxTOP, 20);
	mainSizer->Add(sizerJournalRow1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(btnFormJournal, 0, wxLEFT, 40);

	btnFormPOD9->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFormPDFButton, this);
	btnFormPOD10->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFormPDFButton, this);
	btnFormJournal->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFormPDFButton, this);
	btnSetEntryDates->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnPOD10EntryDateButton, this);
	m_formPDFPanel->SetSizerAndFit(mainSizer);
	m_formPDFPanel->SetScrollRate(5, 5);

}

void cMain::setAllMenuBtnInactive()
{
	if (!m_allMenuButtons.empty())
	{
		for (auto it : m_allMenuButtons)
		{
			it->setSelected(false);
		}
	}
}

void cMain::changeActivePage( wxWindow* newPage)
{
	if (!newPage)
		return;
	m_mainSizer->Detach(1);
	m_activePanel->Hide();
	m_activePanel = newPage;
	m_mainSizer->Add(newPage, 1, wxEXPAND);
	newPage->Show();
}

void cMain::OnSize(wxSizeEvent& evt)
{
	
	if (GetClientSize().GetWidth() < 800)
	{
		m_mainMenu->Hide();
	}
	else if (GetClientSize().GetWidth() > 800)
	{
		m_mainMenu->Show();
	}
	evt.Skip();
}




void cMain::OnFormPDFButton(wxCommandEvent& evt)
{
	PDF_Main pdf;
	wxString activeOrg{ Settings::getActiveOrgName() };
	for (size_t i{ 0 }; i < wxFileName::GetForbiddenChars().size(); ++i)
		activeOrg.Replace(wxFileName::GetForbiddenChars()[i], "");
	switch (evt.GetId())
	{
		
		case ID_FORMPDF_POD9_BUTTON:
		{
			wxWindowDisabler* disabler = new wxWindowDisabler(true);
			
			MyBusyInfo wait(this,wxString::FromUTF8("Пожалуйста, подождите... это может занять несколько минут."));
			int temp{ Settings::getActiveUnitID() };
			for (const auto& it : *Settings::GetOrgArrayPtr())
			{
				if (it.id == Settings::getActiveOrg())
				{
					
					for (const auto& unit : it.units)
					{
						Settings::setActiveUnit(unit.id, this);
						pdf.formPod9(m_date1_pod9->GetValue(), m_date2_pod9->GetValue(), 
							activeOrg, unit.name,wxString::Format("%i",unit.id));
					}
					break;
				}
			}
			Settings::setActiveUnit(temp, this);
			wxTheApp->Yield();
			wxMilliSleep(200);
			delete disabler;
			Refresh();
			Update();
			break;
		}
		case ID_FORMPDF_POD10_BUTTON:
		{
			if (!m_dataBase->AskToEnterAllEntryDates(m_date1_pod10->GetValue().Format("%Y.%m.%d"), m_date2_pod10->GetValue().Format("%Y.%m.%d")))
			{
				wxMessageBox(wxString::FromUTF8("ПОД 10 не может быть сформирован без \"даты внесения\""));
				return;
			}

			pdf.formPod10(m_date1_pod10->GetValue(), m_date2_pod10->GetValue(), activeOrg);
			break;
		}
		case ID_FORMPDF_JOURNAL_BUTTON:
		{
			pdf.formJournal(m_date1_journal->GetValue(), m_date2_journal->GetValue(), activeOrg);
			break;
		}

		default:
			break;
	}
	
	
}

void cMain::OnPOD10EntryDateButton(wxCommandEvent& evt)
{
	Dialog_generic dlg(this, wxID_ANY, wxString::FromUTF8("Изменить дату внесения записи в ПОД10"),wxDefaultPosition,wxSize(450,400));
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	dlg.SetProportions(1,5);
	VirtualEntryDateList* list = new VirtualEntryDateList(dlg.GetMain(), m_dataBase, wxDefaultPosition, wxSize(300, 240));
	MaterialButton* btn_listChange = new MaterialButton(dlg.GetMain(), wxID_ANY, wxString::FromUTF8("Изменить"), true, wxDefaultPosition, wxSize(80, 30));
	btn_listChange->SetButtonLineColour(gui_MainColour);
	btn_listChange->SetLabelColour(gui_MainColour);
	btn_listChange->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);
	listSizer->Add(list, 1, wxRIGHT, 10);
	listSizer->Add(btn_listChange, 0);
	MaterialButton* acceptButton = new MaterialButton(dlg.GetMain(), wxID_ANY, wxString::FromUTF8("ЗАКРЫТЬ"), false, wxDefaultPosition, wxSize(120, 40));
	acceptButton->SetLabelColour(*wxWHITE);
	acceptButton->SetButtonColour(gui_MainColour);
	sizer->Add(listSizer,1,wxTOP | wxLEFT | wxBOTTOM,15);
	sizer->Add(acceptButton, 0, wxALIGN_RIGHT | wxBOTTOM | wxRIGHT,15 );
	dlg.GetMain()->SetSizer(sizer);
	acceptButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&](wxCommandEvent& evt) { 
		dlg.Close();
		this->Refresh();
		});
	btn_listChange->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&](wxCommandEvent& evt) {
		if (list->GetSelectedItemRef() != std::nullopt)
		{
			Dialog_generic dateDlg(&dlg, wxID_ANY, wxString::FromUTF8("Введите дату внесения записи"), wxDefaultPosition, wxSize(300, 150), true);
			dateDlg.SetProportions(1,3);
			wxStaticText* staticDate = new wxStaticText(dateDlg.GetMain(), wxID_ANY, wxString::FromUTF8("Дата внесения:"));
			staticDate->SetForegroundColour(*wxBLACK);
			wxDateTime currentDate = wxDateTime::Now();
			if (list->GetSelectedItemRef()->get()[1] != "")
				currentDate.ParseFormat(list->GetSelectedItemRef()->get()[1], wxS("%d.%m.%Y"));
			wxDatePickerCtrl* dateCtrl = new wxDatePickerCtrl(dateDlg.GetMain(), wxID_ANY, currentDate, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
			wxBoxSizer* dateSizer = new wxBoxSizer(wxHORIZONTAL);
			dateSizer->Add(staticDate,0,wxLEFT,15);
			dateSizer->Add(dateCtrl, 0,wxLEFT,15);

			MaterialButton* btnNO = new MaterialButton(dateDlg.GetMain(), wxID_ANY, wxString::FromUTF8("Отмена"), true, wxDefaultPosition, wxSize(70, 35));
			btnNO->SetButtonLineColour(*wxWHITE);
			btnNO->SetLabelColour(wxColour(90, 90, 90));
			btnNO->SetButtonShadow(false);
			btnNO->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
			MaterialButton* btnYES = new MaterialButton(dateDlg.GetMain(), wxID_ANY, wxString::FromUTF8("Применить"), true, wxDefaultPosition, wxSize(95, 35));
			btnYES->SetButtonLineColour(*wxWHITE);
			btnYES->SetLabelColour(gui_MainColour);
			btnYES->SetButtonShadow(false);
			btnYES->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
			wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

			btnSizer->Add(btnYES, 0, wxRIGHT, 15);
			btnSizer->Add(btnNO, 0, wxRIGHT);

			wxBoxSizer* mSizer = new wxBoxSizer(wxVERTICAL);
			mSizer->AddSpacer(20);
			mSizer->Add(dateSizer);
			mSizer->AddSpacer(10);
			mSizer->Add(btnSizer,0,wxALIGN_RIGHT | wxRIGHT,5);
			dateDlg.GetMain()->SetSizer(mSizer);

			btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&](wxCommandEvent& evt) {dateDlg.Close(); dlg.Refresh(); });
			btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&](wxCommandEvent& evt) {
				list->EditSelectedEntryDate(dateCtrl->GetValue().Format(wxS("%Y.%m.%d")));
				dateDlg.Close(); 
				dlg.Refresh();
					});
			btnNO->Bind(wxEVT_MOTION, [this](wxMouseEvent& evt) { SetCursor(wxCURSOR_HAND); });
			btnNO->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent& evt) { SetCursor(wxCURSOR_DEFAULT); });
			btnYES->Bind(wxEVT_MOTION, [this](wxMouseEvent& evt) { SetCursor(wxCURSOR_HAND); });
			btnYES->Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent& evt) { SetCursor(wxCURSOR_DEFAULT); });
			dateDlg.ShowModal();
		}
		});
	dlg.ShowModal();

}

void cMain::initNewOrgPage()
{

}

void cMain::OnTabSwitch(wxCommandEvent& evt)
{

	switch (evt.GetId())
	{
	case ID_MAINMENU_ADD_BUTTON:
	{
		if (!m_addPanel->IsShown())
		{
			changeActivePage(m_addPanel);
			setActiveMenuButton(m_menuButtonAdd);
			this->Refresh();
		}
		break;
	}

	case ID_MAINMENU_LIST_BUTTON:
	{
		if (!m_listPanel->IsShown())
		{
			changeActivePage(m_listPanel);
			setActiveMenuButton(m_menuButtonList);
			this->Refresh();
		}
		break;
	}
	case ID_MAINMENU_FORM_BUTTON:
	{
		if (!m_formPDFPanel->IsShown())
		{
			m_firstDate = m_dataBase->getFirstEntryDate();
			m_lastDate = m_dataBase->getLastEntryDate();
			m_date1_pod9->SetRange(m_firstDate, m_lastDate);
			m_date2_pod9->SetRange(m_firstDate, m_lastDate);
			m_date1_pod10->SetRange(m_firstDate, m_lastDate);
			m_date2_pod10->SetRange(m_firstDate, m_lastDate);
			m_date1_journal->SetRange(m_firstDate, m_lastDate);
			m_date2_journal->SetRange(m_firstDate, m_lastDate);
			changeActivePage(m_formPDFPanel);
			setActiveMenuButton(m_menuButtonForm);
			this->Refresh();
		}
		break;
	case ID_MAINMENU_SETTINGS_BUTTON:
	{
		if (!m_settingsPage->IsShown())
		{
			changeActivePage(m_settingsPage);
			setActiveMenuButton(m_menuButtonSetting);
			this->Refresh();
		}
		break;
	}
	}
	default:
		break;
	}
	m_mainSizer->Layout();
	evt.Skip();
}

void cMain::OnListEditButton(wxCommandEvent& evt)
{
	if (m_grid->isRowSelected())
	{
		addPageInfo info;
		m_grid->getSelectedRowData(info);
		Dialog_cMainListEdit* dialog = new Dialog_cMainListEdit(this,info);
		dialog->Destroy();
		m_grid->updateGrid();
	}
}

void cMain::OnListDeleteButton(wxCommandEvent& evt)
{
	if (m_grid->isRowSelected())
	{
		wxSafeYield(this, false);
		Dialog_ask* askDlg = new Dialog_ask(this, wxString::FromUTF8("Удаление записи"),
		 wxString::FromUTF8("Вы уверены, что хотите удалить выбранную запись? Это действие нельзя отменить."));
		if (askDlg->GetReturnCode())
		{
			addPageInfo m_record;
			m_grid->getSelectedRowData(m_record);
			m_dataBase->deleteEntry(m_record);
		}
		askDlg->Destroy();
		m_grid->updateGrid();
		Refresh();
	}
}

void cMain::OnOrgChanged(wxCommandEvent& evt)
{
	this->UpdateOrgChoices();
	evt.Skip();
}

void cMain::UpdateOrgChoices()
{
	wxArrayString orgNames;
	wxString activeOrg;
	wxArrayString unitNames;
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		orgNames.Add(it.name);
		if (it.id == Settings::getActiveOrg())
		{
			activeOrg = it.name;
			for (const auto& unit : it.units)
				unitNames.Add(unit.name);
			
		}
	}
	m_orgChoice->Set(orgNames);
	m_unitChoice->Set(unitNames);
	m_orgChoice->SetStringSelection(activeOrg);
	m_unitChoice->SetStringSelection(unitNames[0]);
}

void cMain::OnOrgSelect(wxCommandEvent& evt)
{
	wxArrayString unitNames;
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		if (it.name == evt.GetString())
		{
		
			Settings::setActiveOrg(it.id, this);
			Settings::setActiveUnit(it.units[0].id, this);
			for (const auto& unit : it.units)
				unitNames.Add(unit.name);
			break;
		}
	}
	m_unitChoice->Set(unitNames);
	m_unitChoice->SetStringSelection(unitNames[0]);
	m_grid->updateGrid();
}

void cMain::OnUnitSelect(wxCommandEvent& evt)
{
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		if (it.id == Settings::getActiveOrg())
		{
			for (const auto& unit : it.units)
				if (unit.name == evt.GetString())
				{
					Settings::setActiveUnit(unit.id, this);
					return;
				}	
		}
	}
	m_grid->updateGrid();
}

void cMain::PostOrgEvents(wxCommandEvent& evt)
{
	m_grid->updateGrid();
	m_grid->Refresh();
	wxPostEvent(m_addPanel, evt);
	evt.Skip();
}

void cMain::OnDbChange(wxCommandEvent& evt)
{
	m_grid->updateGrid();
	m_firstDate = m_dataBase->getFirstEntryDate();
	m_lastDate = m_dataBase->getLastEntryDate();
}
