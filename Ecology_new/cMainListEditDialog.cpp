#include "cMainListEditDialog.h"



cMainListEditDialog::cMainListEditDialog(wxWindow* parent, std::vector<wxString>& item,const std::vector<wxString>& labels, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name),m_item{item}
{
	unsigned int labelSize{ labels.size() };
	m_mainPanel = new wxScrolledWindow(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainPanel->SetFont(wxFontInfo(12).FaceName("Segoe UI"));
	m_buttonPanel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_mainPanel, 1, wxEXPAND);
	mainSizer->Add(m_buttonPanel, 0, wxEXPAND |wxTOP,50);
	wxGridSizer *gridSizer = new wxFlexGridSizer(2, wxSize(30, 0));
	m_staticText = new wxStaticText* [labelSize];
	m_textCtrl = new wxTextCtrl* [labelSize];
	for (size_t i{ 0 }; i < labelSize; ++i)
	{
		m_staticText[i] = new wxStaticText(m_mainPanel, wxID_ANY, labels[i], wxDefaultPosition, wxSize(250, 30));
		m_textCtrl[i] = new wxTextCtrl(m_mainPanel, wxID_ANY, m_item[i],wxDefaultPosition,wxSize(250,30));
	}

	//if (labelSize % 2)
	//{
		for (size_t k{ 0 }; k < labelSize ; k+=2)
		{
			gridSizer->Add(m_staticText[k], 0,wxLEFT| wxTOP, 20);
			gridSizer->Add(m_staticText[k+1], 0, wxTOP, 20);
			gridSizer->Add(m_textCtrl[k], 0, wxLEFT| wxFIXED_MINSIZE, 20);
			gridSizer->Add(m_textCtrl[k+1], 0, wxEXPAND| wxFIXED_MINSIZE);
			
		}
	
	m_mainPanel->SetSizer(gridSizer);
	gridSizer->Layout();
	m_mainPanel->Layout();
	m_mainPanel->SetScrollRate(5, 5);
	this->SetSizer(mainSizer);
	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();
}

cMainListEditDialog::~cMainListEditDialog()
{
	delete[] m_textCtrl;
	delete[] m_staticText;
}
