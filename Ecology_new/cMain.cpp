#pragma once
#include "cMain.h"


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EcoDataBase", wxDefaultPosition, wxSize(1024,600))
{
	
	
	this->SetMinClientSize(wxSize(660, 480));
	wxPdfFontManager::GetFontManager()->RegisterSystemFonts();
	wxPdfFontManager::GetFontManager()->RegisterFontDirectory(wxGetCwd() + wxS("/Fonts"));

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

	

	this->Bind(wxEVT_SIZE, &cMain::OnSize, this);
}

cMain::~cMain()
{
	delete m_dataBase;
	//delete myList;
	//delete menuAbout;
	//delete menuFile;
	//delete mainPanel;

}

void cMain::initListPanel()
{
	m_listPanel = new wxPanel(this, ID_LIST_PANEL, wxDefaultPosition, wxSize(800, 600));
	m_listPanel->SetBackgroundColour(wxColor(255, 255, 255));
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	MaterialButton* editButton = new MaterialButton(m_listPanel, wxID_ANY, "ИЗМЕНИТЬ", true,wxDefaultPosition, wxSize(100, 35));
	editButton->SetButtonLineColour(gui_MainColour);
	editButton->SetLabelColour(gui_MainColour);

	m_deleteButton = new MaterialButton(m_listPanel, wxID_ANY, "УДАЛИТЬ", false,wxDefaultPosition,wxSize(100, 35));
	m_deleteButton->SetButtonColour(wxColour(165, 42, 42));
	m_deleteButton->SetLabelColour(*wxWHITE);
	buttonSizer->AddStretchSpacer(1);
	buttonSizer->Add(editButton, 0, wxRIGHT, 5);
	buttonSizer->Add(m_deleteButton, 0,  wxRIGHT, 20);

	
	m_grid = new myGridTable(m_listPanel, wxID_ANY, wxPoint(0, 0),wxSize(m_listPanel->GetSize().GetX(), m_listPanel->GetSize().GetY()));

	


	mainSizer->AddSpacer(50);
	mainSizer->Add(buttonSizer,0,wxALIGN_RIGHT);
	mainSizer->Add(m_grid,1,wxEXPAND | wxTOP,3);
	m_listPanel->SetSizerAndFit(mainSizer);
	editButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnListEditButton, this);
	m_deleteButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnListDeleteButton, this);
}

void cMain::initAddPanel()
{

	m_addPanel = new wxPanel(this, ID_LIST_PANEL, wxDefaultPosition, wxSize(800, 600));
	m_addPanel->SetBackgroundColour(wxColor(255, 255, 255));
	Add_panel* AddPanel = new Add_panel(m_addPanel);
	wxBoxSizer* mainAddsizer = new wxBoxSizer(wxVERTICAL);
	mainAddsizer->Add(AddPanel,1,wxEXPAND);
	m_addPanel->SetSizerAndFit(mainAddsizer);
	m_addPanel->Hide();
}

void cMain::initSettingsPage()
{
	m_settingsPage = new Settings_page(this);
	
	m_settingsPage->Hide();
}

void cMain::initMainMenu()
{

	m_mainMenu = new wxPanel(this, ID_MAINMENU_PANEL, wxDefaultPosition, wxSize(m_mainMenuWidth, 200));
	m_mainMenu->SetBackgroundColour(gui_MainColour);

	m_menuButtonList = new MainMenuTabButton(m_mainMenu, "Таблица", ID_MAINMENU_LIST_BUTTON,false,wxSize(m_mainMenuWidth,50),wxPoint(0,150));
	m_menuButtonList->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonList);

	m_menuButtonAdd = new MainMenuTabButton(m_mainMenu, "Добавить запись", ID_MAINMENU_ADD_BUTTON,false, wxSize(m_mainMenuWidth, 50), wxPoint(0, 200));
	m_menuButtonAdd->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonAdd);

	m_menuButtonForm = new MainMenuTabButton(m_mainMenu, "Сформировать", ID_MAINMENU_FORM_BUTTON,false, wxSize(m_mainMenuWidth, 50), wxPoint(0, 250));
	m_menuButtonForm->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_allMenuButtons.push_back(m_menuButtonForm);

	m_menuButtonSetting = new MainMenuTabButton(m_mainMenu, "Настройки", ID_MAINMENU_SETTINGS_BUTTON, true, wxSize(m_mainMenuWidth, 50), wxPoint(0, 300));
	m_menuButtonSetting->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTabSwitch, this);
	m_menuButtonSetting->seDropArrowtSize(wxSize(14, 30));
	m_allMenuButtons.push_back(m_menuButtonSetting);
	
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
	m_formPDFPanel->SetFont(wxFontInfo(14).FaceName("Segoe UI").Bold(false));
	
	m_firstDate = m_dataBase->getFirstEntryDate();
	m_lastDate = m_dataBase->getLastEntryDate();
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// _____________POD9_____________
	wxStaticText* labelPOD9 = new wxStaticText(m_formPDFPanel, wxID_ANY, "ПОД 9");
	labelPOD9->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDatePod9 = new wxStaticText(m_formPDFPanel, wxID_ANY, "Сформировать с:");
	m_date1_pod9 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate,wxPoint(300,200),wxDefaultSize,wxDP_DROPDOWN);
	wxStaticText* txtSecondDatePod9 = new wxStaticText(m_formPDFPanel, wxID_ANY, "По:");
	m_date2_pod9 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerPod9Row1 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod9Row1->Add(txtFirstDatePod9,0,wxLEFT,20);
	sizerPod9Row1->Add(m_date1_pod9,0, wxLEFT, 15);
	sizerPod9Row1->Add(txtSecondDatePod9, 0, wxLEFT, 130);
	sizerPod9Row1->Add(m_date2_pod9, 0, wxLEFT, 15);
	wxStaticText* txtDirPod9 = new wxStaticText(m_formPDFPanel, wxID_ANY, "Путь:");
	m_dir_pod9 = new myDirPicker(m_formPDFPanel, wxID_ANY, wxGetCwd(), "Папка для сохранения документов", wxDefaultPosition, wxSize(460, 30));
	wxBoxSizer* sizerPod9Row2 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod9Row2->Add(txtDirPod9, 0, wxLEFT, 20);
	sizerPod9Row2->Add(m_dir_pod9, 0, wxLEFT, 15);
	MaterialButton* btnFormPOD9 = new MaterialButton(m_formPDFPanel, ID_FORMPDF_POD9_BUTTON, "СФОРМИРОВАТЬ", true, wxDefaultPosition, wxSize(155, 40));
	btnFormPOD9->SetButtonLineColour(gui_MainColour);
	btnFormPOD9->SetButtonFillColour(*wxWHITE);
	btnFormPOD9->SetLabelColour(gui_MainColour);
	m_date1_pod9->SetRange(m_firstDate, m_lastDate);
	m_date2_pod9->SetRange(m_firstDate, m_lastDate);

	//______________POD10_____________
	wxStaticText* labelPOD10 = new wxStaticText(m_formPDFPanel, wxID_ANY, "ПОД 10");
	labelPOD10->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDatePod10 = new wxStaticText(m_formPDFPanel, wxID_ANY, "Сформировать с:");
	m_date1_pod10 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate, wxPoint(300, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* txtSecondDatePod10 = new wxStaticText(m_formPDFPanel, wxID_ANY, "По:");
	m_date2_pod10 = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerPod10Row1 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod10Row1->Add(txtFirstDatePod10, 0, wxLEFT, 20);
	sizerPod10Row1->Add(m_date1_pod10, 0, wxLEFT, 15);
	sizerPod10Row1->Add(txtSecondDatePod10, 0, wxLEFT, 130);
	sizerPod10Row1->Add(m_date2_pod10, 0, wxLEFT, 15);
	wxStaticText* txtDirPod10 = new wxStaticText(m_formPDFPanel, wxID_ANY, "Путь:");
	m_dir_pod10 = new myDirPicker(m_formPDFPanel, wxID_ANY, wxGetCwd(), "Папка для сохранения документов", wxDefaultPosition, wxSize(460, 30));
	wxBoxSizer* sizerPod10Row2 = new wxBoxSizer(wxHORIZONTAL);
	sizerPod10Row2->Add(txtDirPod10, 0, wxLEFT, 20);
	sizerPod10Row2->Add(m_dir_pod10, 0, wxLEFT, 15);
	MaterialButton* btnFormPOD10 = new MaterialButton(m_formPDFPanel, ID_FORMPDF_POD10_BUTTON, "СФОРМИРОВАТЬ", true, wxDefaultPosition, wxSize(155, 40));
	btnFormPOD10->SetButtonLineColour(gui_MainColour);
	btnFormPOD10->SetButtonFillColour(*wxWHITE);
	btnFormPOD10->SetLabelColour(gui_MainColour);

	m_date1_pod10->SetRange(m_firstDate, m_lastDate);
	m_date2_pod10->SetRange(m_firstDate, m_lastDate);
	//______________JOURNAL_____________
	wxStaticText* labelJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, "ЖУРНАЛ");
	labelJournal->SetFont(wxFontInfo(20).FaceName("Segoe UI").Bold());
	wxStaticText* txtFirstDateJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, "Сформировать с:");
	m_date1_journal = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, m_firstDate, wxPoint(300, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* txtSecondDateJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, "По:");
	m_date2_journal = new wxDatePickerCtrl(m_formPDFPanel, wxID_ANY, wxDateTime::Today(), wxPoint(400, 200), wxDefaultSize, wxDP_DROPDOWN);
	wxBoxSizer* sizerJournalRow1 = new wxBoxSizer(wxHORIZONTAL);

	sizerJournalRow1->Add(txtFirstDateJournal, 0, wxLEFT, 20);
	sizerJournalRow1->Add(m_date1_journal, 0, wxLEFT, 15);
	sizerJournalRow1->Add(txtSecondDateJournal, 0, wxLEFT, 130);
	sizerJournalRow1->Add(m_date2_journal, 0, wxLEFT, 15);
	wxStaticText* txtDirJournal = new wxStaticText(m_formPDFPanel, wxID_ANY, "Путь:");
	m_dir_journal = new myDirPicker(m_formPDFPanel, wxID_ANY, wxGetCwd(), "Папка для сохранения документов", wxDefaultPosition, wxSize(460, 30));
	wxBoxSizer* sizerJournalRow2 = new wxBoxSizer(wxHORIZONTAL);
	sizerJournalRow2->Add(txtDirJournal, 0, wxLEFT, 20);
	sizerJournalRow2->Add(m_dir_journal, 0, wxLEFT, 15);
	MaterialButton* btnFormJournal = new MaterialButton(m_formPDFPanel, ID_FORMPDF_JOURNAL_BUTTON, "СФОРМИРОВАТЬ", true, wxDefaultPosition, wxSize(155, 40));
	btnFormJournal->SetButtonLineColour(gui_MainColour);
	btnFormJournal->SetButtonFillColour(*wxWHITE);
	btnFormJournal->SetLabelColour(gui_MainColour);
	m_date2_journal->SetRange(m_firstDate, m_lastDate);
	m_date1_journal->SetRange(m_firstDate, m_lastDate);

	mainSizer->Add(labelPOD9, 0, wxEXPAND | wxLEFT | wxTOP ,20);
	mainSizer->AddSpacer(5);
	mainSizer->Add(sizerPod9Row1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(sizerPod9Row2, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(30);
	mainSizer->Add(btnFormPOD9, 0, wxLEFT , 40);
	mainSizer->AddSpacer(40);
	mainSizer->Add(labelPOD10, 0, wxEXPAND | wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(5);
	mainSizer->Add(sizerPod10Row1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(sizerPod10Row2, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(30);
	mainSizer->Add(btnFormPOD10, 0, wxLEFT, 40);
	mainSizer->AddSpacer(40);
	mainSizer->Add(labelJournal, 0, wxEXPAND | wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(5);
	mainSizer->Add(sizerJournalRow1, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(10);
	mainSizer->Add(sizerJournalRow2, 0, wxLEFT | wxTOP, 20);
	mainSizer->AddSpacer(30);
	mainSizer->Add(btnFormJournal, 0, wxLEFT, 40);

	btnFormPOD9->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFromPDFButton, this);
	btnFormPOD10->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFromPDFButton, this);
	btnFormJournal->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnFromPDFButton, this);
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

void cMain::OnFromPDFButton(wxCommandEvent& evt)
{
	PDF_Main pdf;
	switch (evt.GetId())
	{
		case ID_FORMPDF_POD9_BUTTON:
		{
			pdf.formPod9(m_date1_pod9->GetValue(), m_date2_pod9->GetValue());
			break;
		}
		case ID_FORMPDF_POD10_BUTTON:
		{
			pdf.formPod10(m_date1_pod10->GetValue(), m_date2_pod10->GetValue());
			break;
		}
		case ID_FORMPDF_JOURNAL_BUTTON:
		{
			pdf.formJournal(m_date1_journal->GetValue(), m_date2_journal->GetValue());
			break;
		}

		default:
			break;
	}

	
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
		Dialog_cMainListEdit* dialog = new Dialog_cMainListEdit(this,info,m_grid->getGridLabels());
		dialog->Destroy();
	}
}

void cMain::OnListDeleteButton(wxCommandEvent& evt)
{
	if (m_grid->isRowSelected())
	{
		addPageInfo m_record;
		m_grid->getSelectedRowData(m_record);
		wxSafeYield(this, false);
		Dialog_askDeleteEntry* askDlg = new Dialog_askDeleteEntry(this, m_record);
		askDlg->Destroy();
		this->Refresh();
	}
}



