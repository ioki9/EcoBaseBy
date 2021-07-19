#pragma once
#include "cMain.h"
#include <chrono>
#include <string>
#include <wx/pdffontmanager.h>
using namespace std::chrono;



cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EcoDataBase", wxDefaultPosition, wxSize(800,600))
{
	wxPdfFontManager::GetFontManager()->RegisterSystemFonts();
	wxPdfFontManager::GetFontManager()->RegisterFontDirectory(wxGetCwd() + wxS("/Fonts"));

	Center();

	mainPanel = new wxPanel(this, -1);
	myList = new wxListCtrl(mainPanel,-1,wxPoint(80,50), wxSize(600,300),wxLC_REPORT| wxLC_HRULES| wxLC_VRULES);
	menuFile = new wxMenu();
	menuAbout = new wxMenu();
	menuFile->Append(ID_MenuFileAdd, "&Add");
	menuFile->Append(wxID_EXIT);
	menuAbout->Append(wxID_ABOUT);

	wxButton *addButton = new wxButton(mainPanel, ID_TEST_BUTTON, wxT("TEST"), wxPoint(400, 450), wxSize(80, 50));

	myList->InsertColumn(ID_LISTCOL_ID, wxS("№"));
	myList->InsertColumn(ID_LISTCOL_MANUFACTURER, wxS("Производитель перевозимых отходов"));
	myList->InsertColumn(ID_LISTCOL_OWNER, wxS("Собственник перевозимых отходов"));
	myList->InsertColumn(ID_LISTCOL_RECEIVER, wxS("Получатель перевозимых отходов"));
	myList->InsertColumn(ID_LISTCOL_TRANSPORT, wxS("Перевозчик перевозимых отходов"));
	myList->InsertColumn(ID_LISTCOL_CODE, wxS("Код отходов"));
	myList->InsertColumn(ID_LISTCOL_REGNUM, wxS("Регистрационный номер"));
	myList->InsertColumn(ID_LISTCOL_AMOUNT, wxS("Количество"));
	myList->InsertColumn(ID_LISTCOL_DATE, wxS("Дата рейса"));


	m_MenuBar = new wxMenuBar();
	m_MenuBar->Append(menuFile, "&File");
	m_MenuBar->Append(menuAbout, "&About");
	this->SetMenuBar(m_MenuBar);

	/*DBMain *db = new DBMain;*/

	/*long count{ 0 };*/
	// creating list from database
	//while (db->NextRow())
	//{

	//	myList->InsertItem(count, db->getIDstring());
	//	myList->SetItem(count, ID_LISTCOL_MANUFACTURER, db->getManufacturer());
	//	myList->SetItem(count, ID_LISTCOL_OWNER, db->getOwner());
	//	myList->SetItem(count, ID_LISTCOL_RECEIVER, db->getReceiver());
	//	myList->SetItem(count, ID_LISTCOL_TRANSPORT, db->getTransporter());
	//	myList->SetItem(count, ID_LISTCOL_DATE,db->getDate() );
	//	myList->SetItem(count, ID_LISTCOL_CODE, db->getCode());
	//	myList->SetItem(count, ID_LISTCOL_REGNUM, db->getRegnum());
	//	myList->SetItem(count, ID_LISTCOL_AMOUNT, db->getAmountstring());
	//	count++;
	//}
	/*delete db;*/
	
	Connect(ID_TEST_BUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::onTestButton));
	Connect(ID_MenuFileAdd,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(cMain::OnMenuFileAdd));
}

cMain::~cMain()
{
	//delete myList;
	//delete menuAbout;
	//delete menuFile;
	//delete mainPanel;

}

void cMain::onTestButton(wxCommandEvent &evt)
{
	auto start = high_resolution_clock::now();
	PDF_Main pdfMain;
	PDF_Pod10 pdf;
	///*wxMessageBox(wxString::Format(wxT("%f"), pdf.GetStringWidth(' ')));*/
	pdfMain.formPod9();
	pdfMain.formJournal();
	pdf.createDoc();
	
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	wxMessageBox(std::to_string(duration.count()));
}

void cMain::OnMenuFileAdd(wxCommandEvent & evt)
{
	cMenuAddDialog *newDialog = new cMenuAddDialog(wxT("Add files"));
	delete newDialog;
	evt.Skip();
}


