#include "Dialog_ListColumnSelect.h"
#include "../Utility/CustomEvents.h"
#include <map>

Dialog_ListColumnSelect::Dialog_ListColumnSelect(wxWindow* parent, const std::map<Grid_label, wxString>& grid_labels,uint32_t activeColFlags, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxDialog(parent, id, title, pos, size, style, name), dlg_activeColFlags{activeColFlags}, m_gridLabels{grid_labels}
{

	for (size_t k{ 0 }; k < static_cast<size_t>(Grid_label::grid_max_labels); ++k)
	{
		m_gridLabels[static_cast<Grid_label>(k)].Replace('\n', wxEmptyString);
	}
	wxFont colFont(wxFontInfo(12).FaceName("Segoe UI"));
	checkBoxPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 600));
	checkBoxPanel->SetBackgroundColour(*wxWHITE);
	MaterialButton* cancelBtn = new MaterialButton(checkBoxPanel, wxID_CANCEL, "������", 
													1, wxPoint(GetSize().x-140, 510), wxSize(100, 40));
	MaterialButton* applyBtn = new MaterialButton(checkBoxPanel, wxID_CANCEL, "���������", 
													0, wxPoint(25, 510), wxSize(100, 40));
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	cancelBtn->SetTextFont(wxFont(wxFontInfo(10).FaceName("Segoe UI").Bold()));
	cancelBtn->SetButtonLineColour(wxColour(20, 148, 20));
	cancelBtn->SetLabelColour(wxColour(20, 148, 20));

	applyBtn->SetTextFont(wxFont(wxFontInfo(10).FaceName("Segoe UI").Bold()));
	applyBtn->SetButtonColour(wxColour(20, 148, 20));
	applyBtn->SetLabelColour(*wxWHITE);


	checkBoxPanel->SetSizer(btnSizer);
	checkBoxes = new CustomCheckBox * [20];
	checkText = new wxStaticText * [20];
	for (size_t i{ 0 }; i < 20; ++i)
	{
		checkBoxes[i] = new CustomCheckBox(checkBoxPanel, 3567 + i, "", wxPoint(40, 30 + i * 21));
		if (activeColFlags & (1ul << i))
			checkBoxes[i]->SetCheckBoxActive();
		checkText[i] = new wxStaticText(checkBoxPanel, 3567 + i, m_gridLabels[static_cast<Grid_label> (i)], wxPoint(70, 26 + i * 21));
		checkText[i]->SetFont(colFont);
		checkText[i]->SetForegroundColour(*wxBLACK);
	}

	cancelBtn->Bind(wxEVT_LEFT_UP, &Dialog_ListColumnSelect::OnCancel, this);
	applyBtn->Bind(wxEVT_LEFT_UP, &Dialog_ListColumnSelect::OnApply, this);
	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();
	
}



Dialog_ListColumnSelect::~Dialog_ListColumnSelect()
{
	delete[] checkBoxes;
	delete[] checkText;
}


//void Dialog_ListColumnSelect::initLabels()
//{
//	m_labels.reserve(20);
//	m_labels.push_back( "��������������� �����");
//	m_labels.push_back("����");
//	m_labels.push_back("��������� �� ���.");
//	m_labels.push_back("���������� �������");
//	m_labels.push_back("���������� �������");
//	m_labels.push_back("��� �������");
//	m_labels.push_back("������������, �.(��.)");
//	m_labels.push_back("��������� �� ���. ���, �.(��.)");
//	m_labels.push_back("��������� �� ��. ���., �.(��.)");
//	m_labels.push_back("������������, �.(��.)");
//	m_labels.push_back("�����������, �.(��.)");
//	m_labels.push_back("���������� �� ��������, �.(��.)");
//	m_labels.push_back("����������, �.(��.)");
//	m_labels.push_back("�������� �� �������������, �.(��.)");
//	m_labels.push_back("�������� �� ��������������, �.(��.)");
//	m_labels.push_back("�������� �� ��������, �.(��.)");
//	m_labels.push_back("�������� �� �����������, �.(��.)");
//	m_labels.push_back("�������� ��������, �.(��.)");
//	m_labels.push_back("����������� ������������� (��� 10)");
//	m_labels.push_back("����������� ������������� (��� 9)");
//}

void Dialog_ListColumnSelect::OnCancel(wxMouseEvent& evt)
{
	this->Close();
}


void Dialog_ListColumnSelect::OnApply(wxMouseEvent& evt)
{
	for (size_t i{ 0 }; i < 20; ++i)
	{
		if (checkBoxes[i]->status & checkBoxes[i]->flag_active)
		{
			dlg_activeColFlags |= (1ul << i);
		}
		else
		{
			dlg_activeColFlags &= ~(1ul << i);
		}
	}
	if (dlg_activeColFlags == 0x000000000)
	{
		wxMessageBox("������: ���� �� 1 ������� ������ ���� ��������.");
		return;
	}
	wxCommandEvent sndEvet(EVT_GRID_ACTIVE_COL_CHANGE);
	sndEvet.SetInt(dlg_activeColFlags);
	wxPostEvent(GetParent(), sndEvet);
	this->Close();
}