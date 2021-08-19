//#pragma once
//#include "cMenuAddDialog.h"
//#include "PDF_Pod9.h"
//#include "Global variables.h"
//#include "DMColumnEnums.h"
//
//enum Control_IDs
//{
//	ID_BUTTON_ADD,
//	ID_BUTTON_CANCEL,
//};
//
//
//cMenuAddDialog::cMenuAddDialog(const wxString &title) : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(800, 600),
//																wxRESIZE_BORDER|wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX)
//{
//
//	wxFloatingPointValidator<float> valid(3, &m_value, wxNUM_VAL_ZERO_AS_BLANK);
//	wxPanel *panel = new wxPanel(this, -1);
//
//	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
//
//	wxButton *addButton = new wxButton(this, ID_BUTTON_ADD, wxT("Добавить"), wxDefaultPosition, wxSize(80, 50));
//	wxButton *cancelButton = new wxButton(this, ID_BUTTON_CANCEL, wxT("Отмена"), wxDefaultPosition, wxSize(80, 50));
//
//	
//	
//
//	wxStaticText *txtManufStatic = new wxStaticText(this, wxID_ANY, wxS("Производитель перевозимых отходов"), wxPoint(40, 20));
//	txtNameManufCtrl = new wxTextCtrl(this, DB_COLUMN_MANUFACTURER, wxEmptyString, wxPoint(40, 40), wxSize(300, 20));
//	
//	wxStaticText *txtOwnerStatic = new wxStaticText(this, wxID_ANY, wxS("Собственник перевозимых отходов"), wxPoint(40, 60));
//	txtNameOwnerCtrl = new wxTextCtrl(this, DB_COLUMN_OWNER, wxEmptyString, wxPoint(40, 80), wxSize(300, 20));
//	
//	wxStaticText *txtReceiverStatic = new wxStaticText(this, wxID_ANY, wxS("Получатель перевозимых отходов"), wxPoint(40, 100));
//	txtNameReceiverCtrl = new wxTextCtrl(this, DB_COLUMN_RECEIVER, wxEmptyString, wxPoint(40, 120), wxSize(300, 20));
//	
//	wxStaticText *txtTransportStatic = new wxStaticText(this, wxID_ANY, wxS("Перевозчик перевозимых отходов"), wxPoint(40, 140));
//	txtNameTransportCtrl = new wxTextCtrl(this, DB_COLUMN_TRANSPORT, wxEmptyString, wxPoint(40, 160), wxSize(300, 20));
//	
//	
//	wxStaticText *txtDateStatic = new wxStaticText(this, wxID_ANY, wxS("Дата рейса"), wxPoint(400, 20));
//	txtDateCtrl = new wxDatePickerCtrl(this, DB_COLUMN_DATE,wxDefaultDateTime,wxPoint(400,40),wxSize(100,20));
//
//
//
//	wxStaticText *txtCodeStatic = new wxStaticText(this, wxID_ANY, wxS("Код отходов"), wxPoint(400, 60));
//	txtCodeCtrl = new wxTextCtrl(this, DB_COLUMN_CODE, wxEmptyString, wxPoint(400, 80), wxSize(100, 20));
//	
//	wxStaticText *txtRegNumStatic = new wxStaticText(this, wxID_ANY, wxS("Регистрационный номер"), wxPoint(400, 100));
//	txtRegNumCtrl = new wxTextCtrl(this, DB_COLUMN_REGNUM, wxEmptyString, wxPoint(400, 120), wxSize(100, 20));
//	
//	wxStaticText *txtAmountStatic = new wxStaticText(this, wxID_ANY, wxS("Количество"), wxPoint(400, 140));
//	txtAmountCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT, wxEmptyString, wxPoint(400, 160), wxSize(100, 20),0L,valid);
//
//	wxStaticText *txtAmountFormedStatic = new wxStaticText(this, wxID_ANY, wxS("Образовалось"), wxPoint(400, 180));
//	txtAmountFormedCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_FORMED, wxEmptyString, wxPoint(400, 200), wxSize(100, 20));
//
//	wxStaticText *txtAmountReceivedOrgStatic = new wxStaticText(this, wxID_ANY, wxS("получено от др. орг"), wxPoint(400, 220));
//	txtAmountReceivedOrgCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_RECEIVED_ORG, wxEmptyString, wxPoint(400, 240), wxSize(100, 20));
//
//	wxStaticText *txtAmountReceivedPhysStatic = new wxStaticText(this, wxID_ANY, wxS("получено от физ. лиц"), wxPoint(400, 260));
//	txtAmountReceivedPhysCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_RECEIVED_PHYS, wxEmptyString, wxPoint(400, 280), wxSize(100, 20));
//
//	wxStaticText *txtAmountUsedStatic = new wxStaticText(this, wxID_ANY, wxS("использовано"), wxPoint(400, 300));
//	txtAmountUsedCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_USED, wxEmptyString, wxPoint(400, 320), wxSize(100, 20));
//
//	wxStaticText *txtAmountDefusedStatic = new wxStaticText(this, wxID_ANY, wxS("обезврежено"), wxPoint(400, 340));
//	txtAmountDefusedCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_DEFUSED, wxEmptyString, wxPoint(400, 360), wxSize(100, 20));
//
//	wxStaticText *txtAmountSelfstorageStatic = new wxStaticText(this, wxID_ANY, wxS("хранение"), wxPoint(400, 380));
//	txtAmountSelfstorageCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_SELFSTORAGE, wxEmptyString, wxPoint(400, 400), wxSize(100, 20));
//
//	wxStaticText *txtAmountBurialStatic = new wxStaticText(this, wxID_ANY, wxS("захоронение"), wxPoint(400, 420));
//	txtAmountBurialCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_BURIAL, wxEmptyString, wxPoint(400, 440), wxSize(100, 20));
//
//	wxStaticText *txtAmountTransferPurposeStatic = new wxStaticText(this, wxID_ANY, wxS("передано цель"), wxPoint(40, 180));
//	txtAmountTransferPurposeCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_TRANSFER_PURPOSE, wxEmptyString, wxPoint(40, 200), wxSize(100, 20));
//
//	wxStaticText *txtAmountTransferUsedStatic = new wxStaticText(this, wxID_ANY, wxS("передано исп."), wxPoint(40, 220));
//	txtAmountTransferUsedCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_TRANSFER_USED, wxEmptyString, wxPoint(40, 240), wxSize(100, 20));
//
//	wxStaticText *txtAmountTransferDefusedStatic = new wxStaticText(this, wxID_ANY, wxS("передано обезвр"), wxPoint(40, 260));
//	txtAmountTransferDefusedCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_TRANSFER_DEFUSED, wxEmptyString, wxPoint(40, 280), wxSize(100, 20));
//
//	wxStaticText *txtAmountTransferStorageStatic = new wxStaticText(this, wxID_ANY, wxS("передано хранение"), wxPoint(40, 300));
//	txtAmountTransferStorageCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_TRANSFER_STORAGE, wxEmptyString, wxPoint(40, 320), wxSize(100, 20));
//
//	wxStaticText *txtAmountTransferBuriaStatic = new wxStaticText(this, wxID_ANY, wxS("передано захоронение"), wxPoint(40, 340));
//	txtAmountTransferBurialCtrl = new wxTextCtrl(this, DB_COLUMN_AMOUNT_TRANSFER_BURIAL, wxEmptyString, wxPoint(40, 360), wxSize(100, 20));
//
//	wxStaticText *txtWasteNormStatic = new wxStaticText(this, wxID_ANY, wxS("Норматив образования отходов"), wxPoint(40, 380));
//	txtWasteNormCtrl = new wxTextCtrl(this, DB_COLUMN_WASTE_NORM, wxEmptyString, wxPoint(40, 400), wxSize(100, 20));
//
//	wxStaticText *txtStructUnitStatic = new wxStaticText(this, wxID_ANY, wxS("Структурное подразделения, где образовался отход"), wxPoint(40, 420));
//	txtStructUnitCtrl = new wxTextCtrl(this, DB_COLUMN_STRUCTURAL_UNIT, wxEmptyString, wxPoint(40, 440), wxSize(100, 20));
//
//	hbox->Add(addButton, 1, wxRIGHT, 200);
//	hbox->Add(cancelButton, 1,wxLEFT, 200);
//	
//
//	vbox->Add(panel, 1);
//	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
//	SetSizer(vbox);
//
//	Connect(ID_BUTTON_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMenuAddDialog::onAddButton));
//	Connect(ID_BUTTON_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMenuAddDialog::onCancelButton));
//
//	ShowModal();
//	Centre();
//	Destroy();
//}
//cMenuAddDialog::~cMenuAddDialog()
//{
//	delete txtNameOwnerCtrl;
//	delete txtNameManufCtrl;
//	delete txtNameReceiverCtrl;
//	delete txtNameTransportCtrl;
//	delete txtDateCtrl;
//	delete txtCodeCtrl;
//	delete txtRegNumCtrl;
//	delete txtAmountCtrl;
//
//}
//
//void cMenuAddDialog::onCancelButton(wxCommandEvent &evt)
//{
//	Close();
//}
//
//void cMenuAddDialog::onAddButton(wxCommandEvent &evt)
//{
//	wxArrayString sArray;
//
//	getDialogValues(sArray);
//
//	DBMain *db = new DBMain;
//	db->updateDBPassport(sArray);
//	db->setMonthlyResult(sArray[DB_COLUMN_CODE], txtDateCtrl->GetValue());
//
//	delete db;
//	Close();
//	evt.Skip();
//
//}
//
////Populate string array with values from dialog
//void cMenuAddDialog::getDialogValues(wxArrayString &sArray)
//{
//	wxDateTime dateFormat;
//	dateFormat = txtDateCtrl->GetValue();
//	m_myDate = dateFormat.Format(wxS("%Y.%m.%d"));
//	sArray.SetCount(DB_COLUMN_MAXIDS);
//	sArray[DB_COLUMN_MANUFACTURER] = txtNameManufCtrl->GetValue();
//	sArray[DB_COLUMN_TRANSPORT] = txtNameTransportCtrl->GetValue();
//	sArray[DB_COLUMN_DATE] = m_myDate;
//	sArray[DB_COLUMN_CODE] = txtCodeCtrl->GetValue();
//	sArray[DB_COLUMN_REGNUM] = txtRegNumCtrl->GetValue();
//	sArray[DB_COLUMN_OWNER] = txtNameOwnerCtrl->GetValue();
//	sArray[DB_COLUMN_RECEIVER] = txtNameReceiverCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT] = txtAmountCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_FORMED] = txtAmountFormedCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_RECEIVED_ORG] = txtAmountReceivedOrgCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = txtAmountReceivedPhysCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_USED] = txtAmountUsedCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_DEFUSED] = txtAmountDefusedCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_SELFSTORAGE] = txtAmountSelfstorageCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_BURIAL] = txtAmountBurialCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_TRANSFER_PURPOSE] = txtAmountTransferPurposeCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_TRANSFER_USED] = txtAmountTransferUsedCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = txtAmountTransferDefusedCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = txtAmountTransferStorageCtrl->GetValue();
//	sArray[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = txtAmountTransferBurialCtrl->GetValue();
//	sArray[DB_COLUMN_WASTE_NORM] = txtWasteNormCtrl->GetValue();
//	sArray[DB_COLUMN_STRUCTURAL_UNIT] = txtStructUnitCtrl->GetValue();
//}
//
//void cMenuAddDialog::getDialogValues(std::map<int, wxString> &map)
//{
//	wxDateTime dateFormat;
//	dateFormat = txtDateCtrl->GetValue();
//	m_myDate = dateFormat.Format(wxS("%Y.%m"));
//	map[DB_COLUMN_DATE] = m_myDate;
//	map[DB_COLUMN_CODE] = txtCodeCtrl->GetValue();
//
//	if (txtAmountFormedCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_FORMED] = txtAmountFormedCtrl->GetValue();
//	if (txtAmountReceivedOrgCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_RECEIVED_ORG] = txtAmountReceivedOrgCtrl->GetValue();
//	if (txtAmountReceivedPhysCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = txtAmountReceivedPhysCtrl->GetValue();
//	if (txtAmountUsedCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_USED] = txtAmountUsedCtrl->GetValue();
//	if (txtAmountDefusedCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_DEFUSED] = txtAmountDefusedCtrl->GetValue();
//	if (txtAmountSelfstorageCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_SELFSTORAGE] = txtAmountSelfstorageCtrl->GetValue();
//	if (txtAmountBurialCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_BURIAL] = txtAmountBurialCtrl->GetValue();
//	if (txtAmountTransferUsedCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_TRANSFER_USED] = txtAmountTransferUsedCtrl->GetValue();
//	if (txtAmountTransferDefusedCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = txtAmountTransferDefusedCtrl->GetValue();
//	if (txtAmountTransferStorageCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = txtAmountTransferStorageCtrl->GetValue();
//	if (txtAmountTransferBurialCtrl->GetValue() != "")
//		map[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = txtAmountTransferBurialCtrl->GetValue();
//}
//
//
