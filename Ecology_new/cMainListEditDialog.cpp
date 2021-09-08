#include "cMainListEditDialog.h"



cMainListEditDialog::cMainListEditDialog(wxWindow* parent, addPageInfo& info,const std::map<Grid_label,wxString>& gridLabels, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name), m_record{info}
{
	unsigned int labelSize{ static_cast<int>(Grid_label::grid_max_labels) };
	this->SetBackgroundColour(*wxWHITE);
	m_mainPanel = new wxScrolledWindow(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainPanel->SetFont(wxFontInfo(12).FaceName("Segoe UI"));
	m_buttonPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	m_buttonPanel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_mainPanel, 1, wxEXPAND);
	mainSizer->Add(m_buttonPanel, 0, wxEXPAND |wxTOP | wxLEFT |wxRIGHT,15);
	wxBoxSizer* horzSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vertLftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vertRightSizer = new wxBoxSizer(wxVERTICAL);
	horzSizer->Add(vertLftSizer,1,wxEXPAND | wxLEFT,10);
	horzSizer->Add(vertRightSizer,1,wxEXPAND | wxLEFT,10);

	//LEFT COLUMN
	wxStaticText *staticRegnum = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at( Grid_label::grid_regnum ), wxDefaultPosition, wxSize(250, 30));
	m_valueRegnum = new wxTextCtrl(m_mainPanel, wxID_ANY, info.regnum,wxDefaultPosition,wxSize(250,30));
	wxStaticText* staticCode = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_code), wxDefaultPosition, wxSize(250, 30));
	m_valueCode = new wxTextCtrl(m_mainPanel, wxID_ANY, info.code, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticReceiver = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_receiver), wxDefaultPosition, wxSize(250, 30));
	m_valueReceiver = new wxTextCtrl(m_mainPanel, wxID_ANY, info.receiver, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountFormed = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_formed), wxDefaultPosition, wxSize(250, 30));
	m_valueAmount_formed = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountFormed, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountReceivedOrg = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_received_org), wxDefaultPosition, wxSize(250, 30));
	m_valueamount_received_org = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountReceivedOrg, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountDefused = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_defused), wxDefaultPosition, wxSize(250, 30));
	m_valueamount_defused = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountDefused, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountStorage = new wxStaticText(m_mainPanel, wxID_ANY, "Направлено на хранение", wxDefaultPosition, wxSize(250, 30));
	m_valueamount_storage = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountStorage, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountTrDefused = new wxStaticText(m_mainPanel, wxID_ANY, "Передано на обезвреживание", wxDefaultPosition, wxSize(250, 30));
	m_valueamount_tDefused = new wxTextCtrl(m_mainPanel, wxID_ANY, info.tamountDefused, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticAmountTrStorage = new wxStaticText(m_mainPanel, wxID_ANY, "Передано на хранение", wxDefaultPosition, wxSize(250, 30));
	m_valueamount_tStorage = new wxTextCtrl(m_mainPanel, wxID_ANY, info.tamountStorage, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticStructUnitPOD9 = new wxStaticText(m_mainPanel, wxID_ANY, "Структурное подразд. ПОД9", wxDefaultPosition, wxSize(250, 30));
	m_valuestruct_unitPOD9 = new wxTextCtrl(m_mainPanel, wxID_ANY, info.structUnit9, wxDefaultPosition, wxSize(250, 30));


	//RIGHT COLUMN
	wxDateTime dt;
	dt.ParseFormat(info.date, wxS("%Y.%m.%d"));
	wxStaticText* staticDate = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_date), wxDefaultPosition, wxSize(250, 30));
	m_valueDate = new wxDatePickerCtrl(m_mainPanel, wxID_ANY, dt, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* staticOwner = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_owner), wxDefaultPosition, wxSize(250, 30));
	m_valueOwner = new wxTextCtrl(m_mainPanel, wxID_ANY, info.owner, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticTransporter = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_transporter), wxDefaultPosition, wxSize(250, 30));
	m_valueTransporter = new wxTextCtrl(m_mainPanel, wxID_ANY, info.transporter, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticamount_received_phys = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_received_phys), wxDefaultPosition, wxSize(250, 30));
	m_valueamount_received_phys = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountReceivedPhys, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticamount_used = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_used), wxDefaultPosition, wxSize(250, 30));
	m_valueamount_used = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountUsed, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticamount_burial = new wxStaticText(m_mainPanel, wxID_ANY, gridLabels.at(Grid_label::grid_amount_burial), wxDefaultPosition, wxSize(250, 30));
	m_valueamount_burial = new wxTextCtrl(m_mainPanel, wxID_ANY, info.amountBurial, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticamount_tUsed = new wxStaticText(m_mainPanel, wxID_ANY, "Передано на использование", wxDefaultPosition, wxSize(250, 30));
	m_valueamount_tUsed = new wxTextCtrl(m_mainPanel, wxID_ANY, info.tamountUsed, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticamount_tBurial = new wxStaticText(m_mainPanel, wxID_ANY, "Передано на захоронение", wxDefaultPosition, wxSize(250, 30));
	m_valueamount_tBurial = new wxTextCtrl(m_mainPanel, wxID_ANY, info.tamountBurial, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticstruct_unitPOD10 = new wxStaticText(m_mainPanel, wxID_ANY, "Структурное подразд. ПОД10", wxDefaultPosition, wxSize(250, 30));
	m_valuestruct_unitPOD10 = new wxTextCtrl(m_mainPanel, wxID_ANY, info.structUnit10, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* staticWasteNorm = new wxStaticText(m_mainPanel, wxID_ANY, "Норматив образования отхода", wxDefaultPosition, wxSize(250, 30));
	m_valuewaste_norm = new wxTextCtrl(m_mainPanel, wxID_ANY, info.wasteNorm, wxDefaultPosition, wxSize(250, 30));
	

	//RIGHT SIZER 
	vertRightSizer->Add(staticDate);
	vertRightSizer->Add(m_valueDate);
	vertRightSizer->Add(staticOwner);
	vertRightSizer->Add(m_valueOwner);
	vertRightSizer->Add(staticTransporter);
	vertRightSizer->Add(m_valueTransporter);
	vertRightSizer->Add(staticamount_received_phys);
	vertRightSizer->Add(m_valueamount_received_phys);
	vertRightSizer->Add(staticamount_used);
	vertRightSizer->Add(m_valueamount_used);
	vertRightSizer->Add(staticamount_burial);
	vertRightSizer->Add(m_valueamount_burial);
	vertRightSizer->Add(staticamount_tUsed);
	vertRightSizer->Add(m_valueamount_tUsed);
	vertRightSizer->Add(staticamount_tBurial);
	vertRightSizer->Add(m_valueamount_tBurial);
	vertRightSizer->Add(staticstruct_unitPOD10);
	vertRightSizer->Add(m_valuestruct_unitPOD10);
	vertRightSizer->Add(staticWasteNorm);
	vertRightSizer->Add(m_valuewaste_norm);

	//LEFT SIZER
	vertLftSizer->Add(staticRegnum);
	vertLftSizer->Add(m_valueRegnum);
	vertLftSizer->Add(staticCode);
	vertLftSizer->Add(m_valueCode);
	vertLftSizer->Add(staticReceiver);
	vertLftSizer->Add(m_valueReceiver);
	vertLftSizer->Add(staticAmountFormed);
	vertLftSizer->Add(m_valueAmount_formed);
	vertLftSizer->Add(staticAmountReceivedOrg);
	vertLftSizer->Add(m_valueamount_received_org);
	vertLftSizer->Add(staticAmountDefused);
	vertLftSizer->Add(m_valueamount_defused);
	vertLftSizer->Add(staticAmountStorage);
	vertLftSizer->Add(m_valueamount_storage);
	vertLftSizer->Add(staticAmountTrDefused);
	vertLftSizer->Add(m_valueamount_tDefused);
	vertLftSizer->Add(staticAmountTrStorage);
	vertLftSizer->Add(m_valueamount_tStorage);
	vertLftSizer->Add(staticStructUnitPOD9);
	vertLftSizer->Add(m_valuestruct_unitPOD9);

	

	MaterialButton* cancelBtn = new MaterialButton(m_buttonPanel, wxID_CANCEL, "ОТМЕНА",
		1, wxDefaultPosition, wxSize(150, 55));
	MaterialButton* applyBtn = new MaterialButton(m_buttonPanel, wxID_CANCEL, "ПРИМЕНИТЬ",
		0, wxDefaultPosition, wxSize(150, 55));
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	cancelBtn->SetTextFont(wxFont(wxFontInfo(10).FaceName("Segoe UI").Bold()));
	cancelBtn->SetButtonLineColour(wxColour(20, 148, 20));
	cancelBtn->SetLabelColour(wxColour(20, 148, 20));

	applyBtn->SetTextFont(wxFont(wxFontInfo(10).FaceName("Segoe UI").Bold()));
	applyBtn->SetButtonColour(wxColour(20, 148, 20));
	applyBtn->SetLabelColour(*wxWHITE);

	btnSizer->Add(applyBtn, 0, wxEXPAND | wxLEFT | wxBOTTOM, 20);
	btnSizer->AddStretchSpacer(1);
	btnSizer->Add(cancelBtn, 0, wxEXPAND | wxRIGHT | wxBOTTOM, 20);

	m_buttonPanel->SetSizer(btnSizer);
	m_mainPanel->SetSizer(horzSizer);
	horzSizer->Layout();
	m_mainPanel->Layout();
	m_mainPanel->SetScrollRate(5, 5);
	cancelBtn->Bind(wxEVT_LEFT_UP, &cMainListEditDialog::OnCancel, this);
	applyBtn->Bind(wxEVT_LEFT_UP, &cMainListEditDialog::OnApply, this);
	this->SetSizer(mainSizer);
	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();

}

cMainListEditDialog::~cMainListEditDialog()
{
}

void cMainListEditDialog::OnApply(wxMouseEvent& evt)
{
	m_record.regnum = m_valueRegnum->GetValue();
	m_record.oldDate = m_record.date;
	m_record.date = m_valueDate->GetValue().Format(wxS("%Y.%m.%d"));
	m_record.owner = m_valueOwner->GetValue();
	m_record.receiver = m_valueReceiver->GetValue();
	m_record.transporter = m_valueTransporter->GetValue();
	m_record.oldCode = m_record.code;
	m_record.code = m_valueCode->GetValue();
	m_record.amountFormed = m_valueAmount_formed->GetValue();
	m_record.amountReceivedPhys = m_valueamount_received_phys->GetValue();
	m_record.amountReceivedOrg = m_valueamount_received_org->GetValue();
	m_record.amountUsed = m_valueamount_used->GetValue();
	m_record.amountDefused = m_valueamount_defused->GetValue();
	m_record.amountStorage = m_valueamount_storage->GetValue();
	m_record.amountBurial = m_valueamount_burial->GetValue();
	m_record.tamountUsed = m_valueamount_tUsed->GetValue();
	m_record.tamountDefused = m_valueamount_tDefused->GetValue();
	m_record.tamountStorage = m_valueamount_tStorage->GetValue();
	m_record.tamountBurial = m_valueamount_tBurial->GetValue();
	m_record.wasteNorm = m_valuewaste_norm->GetValue();
	m_record.structUnit9 = m_valuestruct_unitPOD9->GetValue();
	m_record.structUnit10 = m_valuestruct_unitPOD10->GetValue();
	DBMain* db = new DBMain;
	db->editEntry(m_record);
	delete db;
	this -> Close();
}

void cMainListEditDialog::OnCancel(wxMouseEvent& evt)
{
	this->Close();
}

void cMainListEditDialog::setNewItem()
{
	
}

