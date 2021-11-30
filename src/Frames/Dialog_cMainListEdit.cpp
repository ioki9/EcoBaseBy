#include "Dialog_cMainListEdit.h"
#include "../Utility/CustomAutoComplete.h"
#include "../Database/DBColumnEnums.h"
#include "../Utility/CustomCodeValidator.h"
#include "../Utility/Utility.h"
#include "../Settings.h"
#include "../Utility/CustomEvents.h"

Dialog_cMainListEdit::Dialog_cMainListEdit(wxWindow* parent, addPageInfo& info, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
	: wxDialog(parent, id, title, pos, size, style, name), m_record{info}
{
	this->SetBackgroundColour(*wxWHITE);
	m_mainPanel = new wxPanel(this);
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
	horzSizer->Add(vertLftSizer,1,wxEXPAND | wxLEFT,20);
	horzSizer->Add(vertRightSizer,1,wxEXPAND | wxLEFT,20);



	wxStaticText* regnum = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Регистрационный номер:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_regnumCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, info.regnum, wxDefaultPosition, wxSize(250, 30));
	wxStaticText* receiver = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Получатель отхода:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	m_receiverCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, info.receiver, wxDefaultPosition, wxSize(250, 30));
	m_receiverCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_RECEIVER));
	wxStaticText* transport = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Перевозчик отхода:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	m_transporterCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, info.transporter, wxDefaultPosition, wxSize(250, 30));
	m_transporterCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_TRANSPORT));
	wxStaticText* calendar = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Дата рейса:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	wxDateTime currentDate;
	currentDate.ParseFormat(info.date, wxS("%Y.%m.%d"));
	m_date = new wxDatePickerCtrl(m_mainPanel, wxID_ANY, currentDate, wxPoint(600, 230), wxSize(250, 30), wxDP_DROPDOWN);
	wxStaticText* code = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Код отхода:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	wxStaticText* codeDng = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Класс опасности:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	wxArrayString dngLvlStr;
	dngLvlStr.Add(wxString::FromUTF8("н/о"));
	dngLvlStr.Add(wxString::FromUTF8("1-го класса"));
	dngLvlStr.Add(wxString::FromUTF8("2-го класса"));
	dngLvlStr.Add(wxString::FromUTF8("3-го класса"));
	dngLvlStr.Add(wxString::FromUTF8("4-го класса"));
	m_dngLvlCtrl = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), dngLvlStr);
	if(m_dngLvlCtrl->SetStringSelection(m_db.GetDngFromCode(info.code)))
		m_dngLvlCtrl->Enable(0);
	m_codeCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, info.code, wxDefaultPosition, wxSize(250, 30), 0L);
	m_codeCtrl->AutoComplete(new CustomAutoComplete(dbTables::codes, DB_COLUMN_CODE));

	//RIGHT SIDE
	m_owner = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Наименование организации:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	m_owner->Hide();
	m_ownerCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, info.owner, wxDefaultPosition, wxSize(250, 30));
	m_ownerCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_OWNER));
	m_ownerCtrl->Hide();
	wxStaticText* amountStatic = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Количество отхода:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	m_amountReceivedCtrl = new wxTextCtrl(m_mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L);
	wxStaticText* amountRecStatic = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Поступило от/образовалось:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	wxArrayString amRecChoiceStr;
	amRecChoiceStr.Add("-");
	amRecChoiceStr.Add(wxString::FromUTF8("Образовалось"));
	amRecChoiceStr.Add(wxString::FromUTF8("Поступило от физ. лиц."));
	amRecChoiceStr.Add(wxString::FromUTF8("Поступило от др. орг."));
	m_amRecCtrl = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), amRecChoiceStr);
	m_amRecCtrl->SetSelection(1);
	m_unit10Static = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Подразделение, в котором образовался данный вид отхода:"));
	m_structUnit10Ctrl = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), GetUnitChoicesArr());
	wxStaticText* amountTrnsprtStatic = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Движение отхода:"), wxDefaultPosition, wxSize(250, 30), wxALIGN_LEFT);
	wxArrayString amMovmChoiceStr;
	amMovmChoiceStr.Add(wxString::FromUTF8("Использовано"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Обезврежено"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Направлено на хранение"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Захоронено"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Передано на использование"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Передано на обезвреживание"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Передано на хранение"));
	amMovmChoiceStr.Add(wxString::FromUTF8("Передано на захоронение"));
	m_amMovmCtrl = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), amMovmChoiceStr);
	m_orgTransRadio = new wxRadioButton(m_mainPanel, wxID_ANY, wxString::FromUTF8("Передано организации:"), wxDefaultPosition, wxSize(250, 30), wxRB_GROUP);
	m_orgTransRadio->Enable(0);
	wxStaticText* orgTransText = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Организация:"));
	m_selfTransRadio = new wxRadioButton(m_mainPanel, wxID_ANY, wxString::FromUTF8("Передано своему подразделению:"));
	m_selfTransRadio->Enable(0);
	wxStaticText* selfTransText = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Подразделение:"));
	m_structUnit9Ctrl = new wxTextCtrl(m_mainPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 30));
	m_structUnit9Ctrl->Enable(0);
	wxStaticText* unit9GoalText = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("Цель:"));
	m_structUnitChoice = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), GetUnitChoicesArr());
	m_structUnitChoice->Enable(0);
	m_amMovmStructCtrl = new wxChoice(m_mainPanel, wxID_ANY, wxDefaultPosition, wxSize(250, 30), amMovmChoiceStr);
	m_amMovmStructCtrl->Enable(0);
	m_recievedPhysText = new wxStaticText(m_mainPanel, wxID_ANY, wxString::FromUTF8("ФИО физ лица:"));
	m_recievedPhysText->Hide();


	

	//RIGHT SIZER 
	vertRightSizer->Add(amountStatic, 0);
	vertRightSizer->Add(m_amountReceivedCtrl, 0);
	vertRightSizer->Add(amountRecStatic, 0);
	vertRightSizer->Add(m_amRecCtrl, 0);
	vertRightSizer->Add(m_unit10Static, 0);
	vertRightSizer->Add(m_structUnit10Ctrl, 0);
	vertRightSizer->Add(amountTrnsprtStatic, 0);
	vertRightSizer->Add(m_amMovmCtrl, 0);
	vertRightSizer->Add(m_orgTransRadio, 0);
	vertRightSizer->Add(orgTransText, 0);
	vertRightSizer->Add(m_structUnit9Ctrl, 0);
	vertRightSizer->Add(m_selfTransRadio, 0);
	vertRightSizer->Add(selfTransText, 0);
	vertRightSizer->Add(m_structUnitChoice, 0);
	vertRightSizer->Add(unit9GoalText, 0);
	vertRightSizer->Add(m_amMovmStructCtrl,0);

	//LEFT SIZER
	vertLftSizer->Add(calendar, 0);
	vertLftSizer->Add(m_date, 0);
	vertLftSizer->Add(code, 0);
	vertLftSizer->Add(m_codeCtrl, 0);
	vertLftSizer->Add(codeDng, 0);
	vertLftSizer->Add(m_dngLvlCtrl, 0);
	vertLftSizer->Add(regnum, 0);
	vertLftSizer->Add(m_regnumCtrl, 0);
	vertLftSizer->Add(receiver, 0);
	vertLftSizer->Add(m_receiverCtrl, 0);
	vertLftSizer->Add(transport, 0);
	vertLftSizer->Add(m_transporterCtrl, 0);

	

	MaterialButton* cancelBtn = new MaterialButton(m_buttonPanel, -1, wxString::FromUTF8("ОТМЕНА"),
		1, wxDefaultPosition, wxSize(150, 55));
	MaterialButton* applyBtn = new MaterialButton(m_buttonPanel, -1, wxString::FromUTF8("ПРИМЕНИТЬ"),
		0, wxDefaultPosition, wxSize(150, 55));
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	cancelBtn->SetTextFont(wxFontInfo(10).FaceName("Segoe UI").Bold());
	cancelBtn->SetButtonLineColour(gui_MainColour);
	cancelBtn->SetLabelColour(gui_MainColour);

	applyBtn->SetTextFont(wxFontInfo(10).FaceName("Segoe UI").Bold());
	applyBtn->SetButtonColour(gui_MainColour);
	applyBtn->SetLabelColour(*wxWHITE);

	btnSizer->Add(applyBtn, 0, wxEXPAND | wxLEFT | wxBOTTOM , 20);
	btnSizer->AddStretchSpacer(1);
	btnSizer->Add(cancelBtn, 0, wxEXPAND | wxRIGHT | wxBOTTOM , 20);

	m_buttonPanel->SetSizer(btnSizer);
	m_mainPanel->SetSizer(horzSizer);
	horzSizer->Layout();
	m_mainPanel->Layout();
	cancelBtn->Bind(wxEVT_LEFT_UP, &Dialog_cMainListEdit::OnCancel, this);
	applyBtn->Bind(wxEVT_LEFT_UP, &Dialog_cMainListEdit::OnApply, this);
	m_structUnit10Ctrl->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt)
		{
			wxString temp = m_structUnitChoice->GetStringSelection();
			m_structUnitChoice->Set(GetUnitChoicesArr(evt.GetString()));
			m_structUnitChoice->SetStringSelection(temp);
		});
	m_amRecCtrl->Bind(wxEVT_CHOICE, [&, vertRightSizer](wxCommandEvent& evt)
		{
			if (m_amRecCtrl->GetSelection() == 0)
			{
				m_receiverCtrl->Clear();
				m_receiverCtrl->Enable(0);
				m_transporterCtrl->Clear();
				m_transporterCtrl->Enable(0);
				m_regnumCtrl->Clear();
				m_regnumCtrl->Enable(0);
				m_ownerCtrl->Clear();
				m_ownerCtrl->Hide();
				m_owner->Hide();
				m_unit10Static->Hide();
				m_structUnit10Ctrl->Hide();
				m_recievedPhysText->Hide();
				m_structUnitChoice->SetSelection(-1);
				m_amMovmStructCtrl->SetSelection(-1);
				vertRightSizer->Detach(4); 
				vertRightSizer->Detach(4);
				vertRightSizer->InsertStretchSpacer(4, 0);
				vertRightSizer->InsertStretchSpacer(5, 0);
				vertRightSizer->Layout();
				wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
				wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
	

			}
			else if (m_amRecCtrl->GetSelection() == 1)
			{
				if (vertRightSizer->GetItem(4)->GetWindow() == m_unit10Static)
					return;
				m_transporterCtrl->Enable(1);
				m_receiverCtrl->Enable(1);
				m_regnumCtrl->Enable(1);
				m_ownerCtrl->Clear();
				m_ownerCtrl->Hide();
				m_owner->Hide();
				m_recievedPhysText->Hide();
				vertRightSizer->Detach(4);
				vertRightSizer->Detach(4);
				vertRightSizer->Insert(4, m_unit10Static);
				vertRightSizer->Insert(5, m_structUnit10Ctrl);
				m_unit10Static->Show();
				m_structUnit10Ctrl->Show();
				vertRightSizer->Layout();
				wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
				wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
			}
			else if (m_amRecCtrl->GetSelection() == 2)
			{
				if (vertRightSizer->GetItem(4)->GetWindow() == m_recievedPhysText)
					return;
				m_transporterCtrl->Enable(1);
				m_receiverCtrl->Enable(1);
				m_regnumCtrl->Enable(1);
				m_structUnit10Ctrl->Hide();
				m_unit10Static->Hide();
				m_owner->Hide();
				vertRightSizer->Detach(4);
				vertRightSizer->Insert(4, m_recievedPhysText);
				if (vertRightSizer->GetItem(5)->GetWindow() != m_ownerCtrl)
				{
					vertRightSizer->Detach(5);
					vertRightSizer->Insert(5, m_ownerCtrl);
				}
				m_recievedPhysText->Show();
				m_ownerCtrl->Show();
				vertRightSizer->Layout();
				wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
				wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
			}
			else
			{
				if (vertRightSizer->GetItem(9)->GetWindow() == m_owner)
					return;
				m_transporterCtrl->Enable(1);
				m_receiverCtrl->Enable(1);
				m_regnumCtrl->Enable(1);
				m_recievedPhysText->Hide();
				m_structUnit10Ctrl->Hide();
				m_unit10Static->Hide();
				vertRightSizer->Detach(4);
				vertRightSizer->Insert(4, m_owner);
				if (vertRightSizer->GetItem(5)->GetWindow() != m_ownerCtrl)
				{
					vertRightSizer->Detach(5);
					vertRightSizer->Insert(5, m_ownerCtrl);
				}
				m_owner->Show();
				m_ownerCtrl->Show();
				vertRightSizer->Layout();
				wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
				wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
			}
		});
	m_amMovmCtrl->Bind(wxEVT_CHOICE, &Dialog_cMainListEdit::OnAmMovmSelect, this);
	m_dngLvlCtrl->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt) {
		if (m_dngLvlCtrl->GetSelection() > 2)
			m_amountReceivedCtrl->SetValidator(utility::GetDoubleValidator(3, wxAtof(m_amountReceivedCtrl->GetValue())));
		else
		{
			wxString temp = m_amountReceivedCtrl->GetValue();
			if (temp.After('.').size() > 2)
				temp.RemoveLast();
			m_amountReceivedCtrl->Clear();
			m_amountReceivedCtrl->SetValue(temp);
			m_amountReceivedCtrl->SetValidator(utility::GetDoubleValidator(2, wxAtof(temp)));
		}
		
		});
	m_orgTransRadio->Bind(wxEVT_RADIOBUTTON, &Dialog_cMainListEdit::OnRadioButton, this);
	m_selfTransRadio->Bind(wxEVT_RADIOBUTTON, &Dialog_cMainListEdit::OnRadioButton, this);

	SetValues();
	m_amountReceivedCtrl->SetValidator(utility::GetDoubleValidator(3, m_amountRecVal));
	this->SetSizer(mainSizer);
	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();

}

Dialog_cMainListEdit::~Dialog_cMainListEdit()
{
}

wxArrayString Dialog_cMainListEdit::GetUnitChoicesArr(const wxString& exclusion)
{
	wxArrayString arr;
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		if (it.id == Settings::getActiveOrg())
		{
			for (const auto& unit : it.units)
			{
				if (unit.name == exclusion)
					continue;
				arr.push_back(unit.name);
			}
		}
	}
	return arr;
}

bool Dialog_cMainListEdit::VerifyValues()
{
	DBMain db;
	if (!db.IsCodeExists(m_codeCtrl->GetValue()))
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: введенное значение в поле \"Код отходов\" не существует"));
		return false;
	}
	if (m_codeCtrl->GetValue().IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Код отходов\" должно быть заполнено"));
		return false;
	}
	if (m_dngLvlCtrl->GetSelection() == -1)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Класс опосности\" должно быть заполнено"));
		return false;
	}
	if (m_amountReceivedCtrl->GetValue().IsEmpty())
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Количество отходов\" должно быть заполнено"));
		return false;
	}
	if (m_amRecCtrl->GetSelection() == -1)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Поступло от/образовалось\" должно быть заполнено"));
		return false;
	}
	if (m_amRecCtrl->GetSelection() == 1 && m_structUnit10Ctrl->GetSelection() == -1)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Подразделение, в котором образовался данный вид отхода\" должно быть заполнено"));
		return false;
	}
	if (m_amMovmCtrl->GetSelection() == -1)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Движение отхода\" должно быть заполнено"));
		return false;
	}
	if (m_amMovmCtrl->GetSelection() > 3 && m_selfTransRadio->GetValue())
	{
		if (m_amMovmStructCtrl->GetSelection() == -1)
		{
			wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Цель\" должно быть заполнено"));
			return false;
		}
		if (m_structUnitChoice->GetSelection() == -1)
		{
			wxMessageBox(wxString::FromUTF8("Ошибка: поле \"Передано своему подразделению\" должно быть заполнено"));
			return false;
		}
	}
	if (m_amRecCtrl->GetSelection() == 0 && m_amMovmCtrl->GetSelection() == 2)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка: выбранная комбинация полей \"Поступило от/образовалось\" и \"Движение отхода\" невозможна."));
		return false;
	}
	if (m_structUnitChoice->GetStringSelection() == m_structUnit10Ctrl->GetStringSelection() && m_structUnitChoice->GetSelection() != -1)
	{
		wxMessageBox(wxString::FromUTF8("Ошибка:невозможно передать отход в подразделение в котором он образовался."));
		return false;
	}
	return true;
}
void Dialog_cMainListEdit::OnApply(wxMouseEvent& evt)
{
	if (!VerifyValues())
		return;

	addPageInfo info;
	DBMain db;
	info.wasteNorm = db.GetWasteNormByCode(m_codeCtrl->GetValue());
	info.activeUnitID = wxString::Format("%i", Settings::getActiveUnitID());
	info.date = m_date->GetValue().Format((wxS("%Y.%m.%d")));
	info.code = m_codeCtrl->GetValue();
	info.codeDngLvl = m_dngLvlCtrl->GetStringSelection();
	info.regnum = m_regnumCtrl->GetValue();
	info.owner = m_ownerCtrl->GetValue();
	info.storageId = m_record.storageId;
	info.receiver = m_receiverCtrl->GetValue();
	info.oldStructUnit10 = m_record.structUnit10;
	info.transporter = m_transporterCtrl->GetValue();
	switch (m_amRecCtrl->GetSelection())
	{
	case 1:
	{
		info.amountFormed = m_amountReceivedCtrl->GetValue();
		info.owner = m_structUnit10Ctrl->GetStringSelection();
		info.structUnit10 = m_structUnit10Ctrl->GetStringSelection();
		for (const auto& it : *Settings::GetOrgArrayPtr())
		{
			if (it.id == Settings::getActiveOrg())
			{
				for (const auto& unit : it.units)
					if (unit.name == m_structUnit10Ctrl->GetStringSelection())
					{
						info.activeUnitID = wxString::Format("%i", unit.id);
						break;;
					}
			}
		}
		break;
	}
	case 2:
	{
		info.amountReceivedPhys = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 3:
	{
		info.amountReceivedOrg = m_amountReceivedCtrl->GetValue();
		break;
	}
	}

	switch (m_amMovmCtrl->GetSelection())
	{
	case 0:
	{
		info.amountUsed = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 1:
	{
		info.amountDefused = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 2:
	{
		info.amountStorage = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 3:
	{
		info.amountBurial = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 4:
	{
		info.tamountUsed = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 5:
	{
		info.tamountDefused = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 6:
	{
		info.tamountStorage = m_amountReceivedCtrl->GetValue();
		break;
	}
	case 7:
	{
		info.tamountBurial = m_amountReceivedCtrl->GetValue();
		break;
	}
	}

	if (m_amMovmCtrl->GetSelection() > 3)
	{
		if (m_orgTransRadio->GetValue())
			info.structUnit9 = m_structUnit9Ctrl->GetValue();
		else
		{
			info.structUnit9 = m_structUnitChoice->GetStringSelection();
			//getting unit id
			for (const auto& it : *Settings::GetOrgArrayPtr())
			{
				if (it.id == Settings::getActiveOrg())
				{
					for (const auto& unit : it.units)
						if (unit.name == m_structUnitChoice->GetStringSelection())
						{
							info.actveRecieverUnitID = wxString::Format("%i", unit.id);
							break;;
						}
				}
			}

			switch (m_amMovmStructCtrl->GetSelection())
			{
			case 0:
			{
				info.amountUsedUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 1:
			{
				info.amountDefusedUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 2:
			{
				info.amountStorageUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 3:
			{
				info.amountBurialUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 4:
			{
				info.tamountUsed = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 5:
			{
				info.tamountDefusedUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 6:
			{
				info.tamountStorageUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			case 7:
			{
				info.tamountBurialUnit = m_amountReceivedCtrl->GetValue();
				break;
			}
			}
		}
	}

	wxPostEvent(GetParent(), wxCommandEvent(EVT_DATABASE_CHANGED));
	info.oldDate = m_record.date;
	info.oldCode = m_record.code;
	info.dependency = m_record.dependency;
	info.id = m_record.id;
	if (m_amMovmCtrl->GetSelection() > 3 && m_selfTransRadio->GetValue())
	{
		db.editEntry(info,true);
	}
	else
	{
		db.editEntry(info, false);
	}

	this -> Close();
}

void Dialog_cMainListEdit::OnCancel(wxMouseEvent& evt)
{
	this->Close();
}



void Dialog_cMainListEdit::UnitChoiceChange(wxCommandEvent& evt)
{
	m_structUnitChoice->Set(GetUnitChoicesArr());
	m_structUnit10Ctrl->Set(GetUnitChoicesArr());
}


void Dialog_cMainListEdit::OnAmMovmSelect(wxCommandEvent& evt)
{

	if (m_amMovmCtrl->GetSelection() > 3)
	{
		if (m_amRecCtrl->GetSelection() == 0)
		{
			m_orgTransRadio->SetValue(1);
			m_orgTransRadio->Enable(0);
			m_selfTransRadio->Enable(0);
			m_structUnit9Ctrl->Clear();
			m_structUnit9Ctrl->Enable(0);
			
			return;
		}
		if (m_orgTransRadio->IsEnabled() || m_selfTransRadio->IsEnabled())
			return;
		m_orgTransRadio->Enable(1);
		m_selfTransRadio->Enable(1);
		m_structUnit9Ctrl->Enable(1);
		m_amMovmStructCtrl->Enable(0);
		m_structUnitChoice->Enable(0);

	}
	else
	{
		m_orgTransRadio->SetValue(1);
		m_orgTransRadio->Enable(0);
		m_selfTransRadio->Enable(0);
		m_structUnit9Ctrl->Clear();
		m_structUnit9Ctrl->Enable(0);
		m_amMovmStructCtrl->Enable(0);
		m_amMovmStructCtrl ->SetSelection(-1);
		m_structUnitChoice->Enable(0);
		m_structUnitChoice->SetSelection(-1);
	}
}

void Dialog_cMainListEdit::OnRadioButton(wxCommandEvent& evt)
{
	if (m_amMovmCtrl->GetSelection() < 3)
	{
		m_structUnit9Ctrl->Clear();
		m_structUnit9Ctrl->Enable(0);
		m_amMovmStructCtrl->Enable(0);
		m_structUnitChoice->Enable(0);
		return;
	}
	if (m_orgTransRadio->GetValue())
	{
		m_structUnit9Ctrl->Enable(1);
		m_amMovmStructCtrl->Enable(0);
		m_structUnitChoice->Enable(0);
	}
	else if (m_selfTransRadio->GetValue())
	{
		m_structUnit9Ctrl->Clear();
		m_structUnit9Ctrl->Enable(0);
		m_amMovmStructCtrl->Enable(1);
		m_structUnitChoice->Enable(1);
	}

}

void Dialog_cMainListEdit::OnEnteredCodeExists(wxCommandEvent& evt)
{
	if (evt.GetString().find('*') != wxNOT_FOUND || evt.GetString() == "")
	{
		m_dngLvlCtrl->SetSelection(wxNOT_FOUND);
		m_dngLvlCtrl->Enable();
		wxPostEvent(m_dngLvlCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
	else
	{
		m_dngLvlCtrl->SetStringSelection(evt.GetString());
		m_dngLvlCtrl->Enable(false);
		wxPostEvent(m_dngLvlCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
}

void Dialog_cMainListEdit::SetValues()
{

	if (m_record.amountFormed != "")
	{
		m_amRecCtrl->SetSelection(1);
		m_structUnit10Ctrl->SetStringSelection(m_record.structUnit10);
		wxPostEvent(m_amRecCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
	else if (m_record.amountReceivedOrg != "")
	{
		m_amRecCtrl->SetSelection(3);
		wxPostEvent(m_amRecCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
	else if (m_record.amountReceivedPhys != "")
	{
		m_amRecCtrl->SetSelection(2);
		wxPostEvent(m_amRecCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
	else if (m_record.amountFormed == "" && m_record.amountReceivedOrg == "" && m_record.amountReceivedPhys == "")
	{
		m_amRecCtrl->SetSelection(0);
		wxPostEvent(m_amRecCtrl, wxCommandEvent(wxEVT_CHOICE));
	}
	m_amMovmCtrl->SetStringSelection(GetMovementStringAndSetAmount());
	wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));

	if (m_structUnitChoice->SetStringSelection(m_record.structUnit9))
	{
		m_selfTransRadio->SetValue(1);
		wxPostEvent(m_selfTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
		m_amMovmStructCtrl->SetStringSelection(m_db.GetMovmStringFromDepend(m_record.dependency));
	}
	else
	{
		m_structUnit9Ctrl->SetValue(m_record.structUnit9);
	}
}

wxString Dialog_cMainListEdit::GetMovementStringAndSetAmount()
{
	if (m_record.amountBurial != "")
	{
		m_amountRecVal = wxAtof(m_record.amountBurial);
		return wxString::FromUTF8("Захоронено");
	}
		
	if (m_record.amountDefused != "")
	{
		m_amountRecVal = wxAtof(m_record.amountDefused);
		return wxString::FromUTF8("Обезврежено");
	}
		
	if (m_record.amountStorage != "")
	{
		m_amountRecVal = wxAtof(m_record.amountStorage);
		return wxString::FromUTF8("Направлено на хранение");
	}
	
	if (m_record.amountUsed != "")
	{
		m_amountRecVal = wxAtof(m_record.amountUsed);
		return wxString::FromUTF8("Использовано");
	}
		
	if (m_record.tamountBurial != "")
	{
		m_amountRecVal = wxAtof(m_record.tamountBurial);
		return wxString::FromUTF8("Передано на захоронение");
	}
		
	if (m_record.tamountDefused != "")
	{
		m_amountRecVal=wxAtof(m_record.tamountDefused);
		return wxString::FromUTF8("Передано на обезвреживание");
	}
	
	if (m_record.tamountStorage != "")
	{
		m_amountRecVal = wxAtof(m_record.tamountStorage);
		return wxString::FromUTF8("Передано на хранение");
	}
	
	if (m_record.tamountUsed != "")
	{
		m_amountRecVal = wxAtof(m_record.tamountUsed);
		return wxString::FromUTF8("Передано на использование");
	}

	return wxString();
}
