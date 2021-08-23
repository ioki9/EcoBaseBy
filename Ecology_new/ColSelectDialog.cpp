#include "ColSelectDialog.h"

ColSelectDialog::ColSelectDialog(wxWindow* parent,uint32_t activeColFlags, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxDialog(parent, id, title, pos, size, style, name), dlg_activeColFlags{activeColFlags}
{
	initLabels();
	
	wxFont colFont(wxFontInfo(12).FaceName("Segoe UI"));
	checkBoxPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 600));
	checkBoxPanel->SetBackgroundColour(*wxWHITE);
	MaterialButton* cancelBtn = new MaterialButton(checkBoxPanel, wxID_CANCEL, "ОТМЕНА", 
													1, wxPoint(GetSize().x-140, 510), wxSize(100, 40));
	MaterialButton* applyBtn = new MaterialButton(checkBoxPanel, wxID_CANCEL, "ПРИМЕНИТЬ", 
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
		checkText[i] = new wxStaticText(checkBoxPanel, 3567 + i, m_labels[i], wxPoint(70, 26 + i * 21));
		checkText[i]->SetFont(colFont);
		checkText[i]->SetForegroundColour(*wxBLACK);
	}

	cancelBtn->Bind(wxEVT_LEFT_UP, &ColSelectDialog::OnCancel, this);
	applyBtn->Bind(wxEVT_LEFT_UP, &ColSelectDialog::OnApply, this);
	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();
	
}



ColSelectDialog::~ColSelectDialog()
{
	delete[] checkBoxes;
	delete[] checkText;
	m_labels.clear();
}


void ColSelectDialog::initLabels()
{
	m_labels.reserve(20);
	m_labels.push_back( "Регистрационный номер");
	m_labels.push_back("Дата");
	m_labels.push_back("Поступило от орг.");
	m_labels.push_back("Получатель отходов");
	m_labels.push_back("Перевозчик отходов");
	m_labels.push_back("Код отходов");
	m_labels.push_back("Образовалось, т.(шт.)");
	m_labels.push_back("Поступило от физ. лиц, т.(шт.)");
	m_labels.push_back("Поступило от др. орг., т.(шт.)");
	m_labels.push_back("Использовано, т.(шт.)");
	m_labels.push_back("Обезврежено, т.(шт.)");
	m_labels.push_back("Направлено на хранение, т.(шт.)");
	m_labels.push_back("Захоронено, т.(шт.)");
	m_labels.push_back("Передано на использование, т.(шт.)");
	m_labels.push_back("Передано на обезвреживание, т.(шт.)");
	m_labels.push_back("Передано на хранение, т.(шт.)");
	m_labels.push_back("Передано на захоронение, т.(шт.)");
	m_labels.push_back("Хранится суммарно, т.(шт.)");
	m_labels.push_back("Структурные подразделения (ПОД 10)");
	m_labels.push_back("Структурные подразделения (ПОД 9)");
}

void ColSelectDialog::OnCancel(wxMouseEvent& evt)
{
	this->Close();
}


void ColSelectDialog::OnApply(wxMouseEvent& evt)
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
	
	this->Close();
}