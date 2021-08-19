#pragma once
#include "cMain.h"


using namespace std::chrono;




cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EcoDataBase", wxDefaultPosition, wxSize(1024,600))
{
	
	this->SetMinClientSize(wxSize(660, 480));
	wxPdfFontManager::GetFontManager()->RegisterSystemFonts();
	wxPdfFontManager::GetFontManager()->RegisterFontDirectory(wxGetCwd() + wxS("/Fonts"));


	Center();
	this->initListPanel();
	this->initAddPanel();
	this->initMainMenu();

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
	m_listTopPanel = new wxPanel(m_listPanel, -1, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer* topButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vtopButtonSizer = new wxBoxSizer(wxVERTICAL);
	MaterialButton* editButton = new MaterialButton(m_listTopPanel, wxID_ANY, "ÈÇÌÅÍÈÒÜ", true,wxDefaultPosition, wxSize(100, 40));
	editButton->SetButtonLineColour(wxColour(34, 139, 34));
	editButton->SetLabelColour(wxColour(34, 139, 34));
	editButton->SetButtonRadius(0);
	MaterialButton* deleteButton = new MaterialButton(m_listTopPanel, wxID_ANY, "ÓÄÀËÈÒÜ", false,wxDefaultPosition,wxSize(100,40));
	deleteButton->SetButtonColour(wxColour(165, 42, 42));
	deleteButton->SetLabelColour(*wxWHITE);
	deleteButton->SetButtonRadius(0);

	topButtonSizer->Add(editButton, 0, wxRIGHT | wxALIGN_BOTTOM , 10);
	topButtonSizer->Add(deleteButton, 0, wxRIGHT | wxALIGN_BOTTOM , 17);
	vtopButtonSizer->AddStretchSpacer();
	vtopButtonSizer->Add(topButtonSizer, 0, wxALIGN_RIGHT| wxBOTTOM,5);

	deleteButton->Bind(wxEVT_LEFT_UP, &cMain::OnListDeleteButton, this);
	editButton->Bind(wxEVT_LEFT_UP, &cMain::OnListEditButton, this);


	m_listBottomPanel = new wxPanel(m_listPanel, -1);
	m_myList = new VirtualListCtrl(m_listBottomPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxColour grey(39, 39, 39);
	m_myList->SetTextColour(grey);
	m_dataBase->getListItemData(m_myList->m_items);
	m_myList->SetHeaderFont(wxFontInfo(11).FaceName("Segoe UI"));
	m_myList->RefrestAfterUpdate();
	wxBoxSizer* mainPanelSizer = new wxBoxSizer(wxVERTICAL);
	mainPanelSizer->Add(m_listTopPanel, 1, wxEXPAND | wxRIGHT);
	mainPanelSizer->Add(m_listBottomPanel, 3, wxEXPAND | wxRIGHT | wxBOTTOM);
	m_listPanel->SetSizerAndFit(mainPanelSizer);
	wxBoxSizer* mainBotPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	mainBotPanelSizer->Add(m_myList, 1, wxEXPAND);
	m_listBottomPanel->SetSizerAndFit(mainBotPanelSizer);
	m_listTopPanel->SetSizerAndFit(vtopButtonSizer);
}
void cMain::initAddPanel()
{

	m_addPanel = new wxPanel(this, ID_LIST_PANEL, wxDefaultPosition, wxSize(800, 600));
	m_addPanel->SetBackgroundColour(wxColor(255, 255, 255));
	Add_panel* AddPanel = new Add_panel(m_addPanel, -1, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer* mainAddsizer = new wxBoxSizer(wxVERTICAL);
	mainAddsizer->Add(AddPanel,1,wxEXPAND);
	m_addPanel->SetSizerAndFit(mainAddsizer);
	m_addPanel->Hide();
}

void cMain::initMainMenu()
{

	m_mainMenu = new wxPanel(this, ID_MAINMENU_PANEL, wxDefaultPosition, wxSize(270, 200));
	m_mainMenu->SetBackgroundColour(wxColour(34, 139, 34));

	//================================= DATA BUTTON====================================================
	m_dataMenuTab = new wxPanel(m_mainMenu, ID_MAINMENU_LIST_BUTTON, wxPoint(0, 150), wxSize(200, 50));
	m_dataMenuText = new wxStaticText(m_dataMenuTab, ID_MAINMENU_LIST_BUTTON, wxS("Òàáëèöà"),
		wxDefaultPosition, wxSize(150, 30), wxALIGN_LEFT);
	m_dataMenuText->CentreOnParent();
	m_dataMenuText->SetFont(m_myFont);
	m_dataMenuText->SetForegroundColour(wxColour(*wxWHITE));
	m_dataMenuTab->SetBackgroundColour(wxColour(34, 139, 34));
	m_dataMenuTab->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);
	m_dataMenuText->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);

	//================================= ADD BUTTON====================================================
	wxPanel* addMenuTab = new wxPanel(m_mainMenu, ID_MAINMENU_ADD_BUTTON, wxPoint(0, 200), wxSize(200, 50));
	wxStaticText* addMenuText = new wxStaticText(addMenuTab, ID_MAINMENU_ADD_BUTTON, wxS("Äîáàâèòü çàïèñü"),
		wxDefaultPosition, wxSize(150, 30), wxALIGN_LEFT);
	addMenuText->CentreOnParent();
	addMenuText->SetFont(m_myFont);
	addMenuText->SetForegroundColour(wxColour(*wxWHITE));
	addMenuTab->SetBackgroundColour(wxColour(34, 139, 34));
	addMenuTab->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);
	addMenuText->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);

	//================================= TEST BUTTON====================================================
	wxPanel* testMenuTab = new wxPanel(m_mainMenu, 779, wxPoint(0, 250), wxSize(200, 50));
	wxStaticText* testMenuText = new wxStaticText(testMenuTab, 779, wxS("Òåñò"), wxDefaultPosition, wxSize(150, 30), wxALIGN_LEFT);
	testMenuText->CentreOnParent();
	testMenuText->SetFont(m_myFont);
	testMenuText->SetForegroundColour(wxColour(*wxWHITE));
	testMenuTab->SetBackgroundColour(wxColour(34, 139, 34));
	testMenuTab->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);
	testMenuText->Bind(wxEVT_LEFT_UP, &cMain::OnTabSwitch, this);
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

void cMain::OnTabSwitch(wxMouseEvent& evt)
{
	m_mainSizer->Detach(1);
	switch (evt.GetId())
	{
	case ID_MAINMENU_ADD_BUTTON:
	{
		m_listPanel->Hide();
		m_mainSizer->Add(m_addPanel, 1, wxEXPAND);
		m_addPanel->Show();
		break;
	}

	case ID_MAINMENU_LIST_BUTTON:
	{
		m_addPanel->Hide();
		m_mainSizer->Add(m_listPanel, 1, wxEXPAND);
		m_listPanel->Show();

		break;
	}

	default:
		break;
	}
	m_mainSizer->Layout();
	evt.Skip();
}

void cMain::OnListEditButton(wxMouseEvent& evt)
{

	cMainListEditDialog* dialog = new cMainListEditDialog(this, m_myList->GetSelectedItemRef(),m_myList->GetColumnLabels());
	dialog->Destroy();

}

void cMain::OnListDeleteButton(wxMouseEvent& evt)
{

}

void cMain::onTestButton(wxCommandEvent &evt)
{
	//auto start = high_resolution_clock::now();
	//PDF_Main pdfMain;
	//PDF_Pod10 pdf;
	////pdfMain.formPod9();
	////pdfMain.formJournal();
	//pdf.createDoc();
	//
	////DBMain db;
	////db.fillRandomData();
	//auto end = high_resolution_clock::now();
	//auto duration = duration_cast<milliseconds>(end - start);
	//wxMessageBox(std::to_string(duration.count()));
	//evt.Skip();
}

void cMain::OnMenuFileAdd(wxCommandEvent & evt)
{
	//cMenuAddDialog *newDialog = new cMenuAddDialog(wxT("Add files"));

}


