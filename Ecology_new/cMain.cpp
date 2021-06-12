#pragma once
#include "cMain.h"






cMain::cMain() : wxFrame(nullptr, wxID_ANY, "EcoDataBase", wxDefaultPosition, wxSize(800,600))
{

	Center();

	wxPanel *mainPanel = new wxPanel(this, -1);
	wxListCtrl *myList = new wxListCtrl(mainPanel,-1,wxPoint(80,50), wxSize(600,300),wxLC_REPORT| wxLC_HRULES| wxLC_VRULES);
	wxMenu *menuFile = new wxMenu();
	wxMenu *menuAbout = new wxMenu();
	menuFile->Append(ID_MenuFileAdd, "&Add");
	menuFile->Append(wxID_EXIT);
	menuAbout->Append(wxID_ABOUT);

	wxButton *addButton = new wxButton(mainPanel, ID_TEST_BUTTON, wxT("TEST"), wxPoint(400, 450), wxSize(80, 50));

	myList->InsertColumn(ID_LISTCOL_ID, wxS("�"));
	myList->InsertColumn(ID_LISTCOL_MANUFACTURER, wxS("������������� ����������� �������"));
	myList->InsertColumn(ID_LISTCOL_OWNER, wxS("����������� ����������� �������"));
	myList->InsertColumn(ID_LISTCOL_RECEIVER, wxS("���������� ����������� �������"));
	myList->InsertColumn(ID_LISTCOL_TRANSPORT, wxS("���������� ����������� �������"));
	myList->InsertColumn(ID_LISTCOL_CODE, wxS("��� �������"));
	myList->InsertColumn(ID_LISTCOL_REGNUM, wxS("��������������� �����"));
	myList->InsertColumn(ID_LISTCOL_AMOUNT, wxS("����������"));
	myList->InsertColumn(ID_LISTCOL_DATE, wxS("���� �����"));


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
}

void cMain::onTestButton(wxCommandEvent &evt)
{
	PDF_Pod10 pdf;
	//PDF_Main pdf9;
	///*wxMessageBox(wxString::Format(wxT("%f"), pdf.GetStringWidth(' ')));*/
	//pdf9.formPod9();
	pdf.createDoc();
	
	utility::draw();
}

void cMain::OnMenuFileAdd(wxCommandEvent & evt)
{
	cMenuAddDialog *newDialog = new cMenuAddDialog(wxT("Add files"));
	delete newDialog;
	evt.Skip();
}


