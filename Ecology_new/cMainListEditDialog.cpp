#include "cMainListEditDialog.h"



cMainListEditDialog::cMainListEditDialog(wxWindow* parent, std::vector<wxString>& item,const std::vector<wxString>& labels, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name),m_item{item}
{
	unsigned int labelSize{ labels.size() };
	this->SetBackgroundColour(*wxWHITE);
	m_mainPanel = new wxScrolledWindow(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainPanel->SetFont(wxFontInfo(12).FaceName("Segoe UI"));
	m_buttonPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	m_buttonPanel->SetBackgroundColour(*wxWHITE);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_mainPanel, 1, wxEXPAND);
	mainSizer->Add(m_buttonPanel, 0, wxEXPAND |wxTOP | wxLEFT |wxRIGHT,15);
	wxGridSizer *gridSizer = new wxFlexGridSizer(2, wxSize(30, 0));
	m_staticText = new wxStaticText* [labelSize];
	m_textCtrl = new wxTextCtrl* [labelSize];
	for (size_t i{ 0 }; i < labelSize; ++i)
	{
		m_staticText[i] = new wxStaticText(m_mainPanel, wxID_ANY, labels[i], wxDefaultPosition, wxSize(250, 30));
		m_textCtrl[i] = new wxTextCtrl(m_mainPanel, wxID_ANY, m_item[i],wxDefaultPosition,wxSize(250,30));
	}

	for (size_t k{ 0 }; k < labelSize ; k+=2)
	{
		gridSizer->Add(m_staticText[k], 0,wxLEFT| wxTOP, 20);
		gridSizer->Add(m_staticText[k+1], 0, wxTOP, 20);
		gridSizer->Add(m_textCtrl[k], 0, wxLEFT| wxFIXED_MINSIZE, 20);
		gridSizer->Add(m_textCtrl[k+1], 0, wxEXPAND| wxFIXED_MINSIZE);
			
	}
	

	MaterialButton* cancelBtn = new MaterialButton(m_buttonPanel, wxID_CANCEL, "ÎÒÌÅÍÀ",
		1, wxDefaultPosition, wxSize(150, 55));
	MaterialButton* applyBtn = new MaterialButton(m_buttonPanel, wxID_CANCEL, "ÏÐÈÌÅÍÈÒÜ",
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
	m_mainPanel->SetSizer(gridSizer);
	gridSizer->Layout();
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
	delete[] m_textCtrl;
	delete[] m_staticText;
}

void cMainListEditDialog::OnApply(wxMouseEvent& evt)
{
	m_record.regnum = m_textCtrl[0]->GetValue();
	m_record.date = m_textCtrl[1]->GetValue();
	m_record.oldDate = m_item[1];
	m_record.owner = m_textCtrl[2]->GetValue();
	m_record.receiver = m_textCtrl[3]->GetValue();
	m_record.transporter = m_textCtrl[4]->GetValue();
	m_record.code = m_textCtrl[5]->GetValue();
	m_record.oldCode = m_item[5];
	m_record.amountFormed = m_textCtrl[6]->GetValue();
	m_record.amountReceivedPhys = m_textCtrl[7]->GetValue();
	m_record.amountReceivedOrg = m_textCtrl[8]->GetValue();
	m_record.amountUsed = m_textCtrl[9]->GetValue();
	m_record.amountDefused = m_textCtrl[10]->GetValue();
	m_record.amountStorage = m_textCtrl[11]->GetValue();
	m_record.amountBurial = m_textCtrl[12]->GetValue();
	m_record.tamountUsed = m_textCtrl[13]->GetValue();
	m_record.tamountDefused = m_textCtrl[14]->GetValue();
	m_record.tamountStorage = m_textCtrl[15]->GetValue();
	m_record.tamountBurial = m_textCtrl[16]->GetValue();
	m_record.wasteNorm = m_textCtrl[18]->GetValue();
	m_record.structUnit9 = m_textCtrl[19]->GetValue();
	m_record.id = m_item.back();
	this->setNewItem();
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
	m_item[0] = m_record.regnum;
	m_item[1] = m_record.date;
	m_item[2] = m_record.owner;
	m_item[3] = m_record.receiver;
	m_item[4] = m_record.transporter;
	m_item[5] = m_record.code;
	m_item[6] = m_record.amountFormed;
	m_item[7] = m_record.amountReceivedPhys;
	m_item[8] = m_record.amountReceivedOrg;
	m_item[9] = m_record.amountUsed;
	m_item[10] = m_record.amountDefused;
	m_item[11] = m_record.amountBurial;
	m_item[12] = m_record.amountStorage;
	m_item[13] = m_record.tamountUsed;
	m_item[14] = m_record.tamountDefused;
	m_item[15] = m_record.tamountStorage;
	m_item[16] = m_record.tamountBurial;
	m_item[17] = m_record.amountStrgFull;
	m_item[18] = m_record.wasteNorm;
	m_item[19] = m_record.structUnit10;
	
}

