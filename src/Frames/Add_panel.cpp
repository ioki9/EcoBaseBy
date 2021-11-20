#include "Add_panel.h"
#include <wx/pdfdoc.h>
#include <wx/valnum.h>
#include <wx/validate.h>
#include <wx/radiobut.h>
#include <wx/textcompleter.h>
#include <wx/graphics.h>
#include "../Database/DBMain.h"
#include "../GUI_parameters.h"
#include "../Controls/VirtualListCtrl.h"
#include "../Controls/CustomCheckBox.h"
#include "../Utility/Utility.h"
#include "../Settings.h"
#include "../Utility/CustomEvents.h"
#include "../Utility/CustomAutoComplete.h"
#include "../Utility/CustomCodeValidator.h"

Add_panel::Add_panel(wxWindow* parent)
	:wxPanel(parent,wxID_ANY)
{
	SetDoubleBuffered(true);
	this->initPage1();

	m_mainSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(m_mainSizer);
	m_mainSizer->Add(m_page1, 1, wxEXPAND);
	this->Bind(EVT_ORGANIZATION_CHANGED, &Add_panel::UnitChoiceChange, this);
	this->Bind(EVT_ACTIVE_ORG_CHANGED, &Add_panel::UnitChoiceChange, this);
	this->Bind(EVT_ACTIVE_UNIT_CHANGED, &Add_panel::UnitChoiceChange, this);
	this->Bind(EVT_ENTERED_CODE_EXISTS, &Add_panel::OnEnteredCodeExists, this);
}

Add_panel::~Add_panel()
{
	
}




wxArrayString Add_panel::GetUnitChoicesArr(const wxString& exclusion)
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


void Add_panel::initPage1()
{

	m_page1 = new wxPanel(this);
	m_page1->SetFont(gui_MainFont);

	wxBoxSizer* midVertSizerLeft = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* midVertSizerRight = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* mainMidSiz = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* leftMidPanel = new wxPanel(m_page1);
	wxPanel* rightMidPanel = new wxPanel(m_page1);
	mainMidSiz->Add(leftMidPanel, 1, wxEXPAND | wxLEFT,20);
	mainMidSiz->Add(rightMidPanel, 1, wxEXPAND);
	
	wxStaticText* label = new wxStaticText(m_page1, wxID_ANY, "ВНЕСЕНИЕ ЗАПИСИ", wxPoint(30, 30), wxDefaultSize, wxALIGN_LEFT);
	label->SetFont(wxFontInfo(18).FaceName("Segoe UI Semibold"));

	//LEFT SIDE
	wxStaticText* regnum = new wxStaticText(leftMidPanel, wxID_ANY, "Регистрационный номер:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_regnumCtrl = new wxTextCtrl(leftMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120, 30));
	wxStaticText* receiver = new wxStaticText(leftMidPanel, wxID_ANY, "Получатель отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_receiverCtrl = new wxTextCtrl(leftMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, txtCtrlSize);
	m_receiverCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_RECEIVER));
	wxStaticText* transport = new wxStaticText(leftMidPanel, wxID_ANY, "Перевозчик отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_transporterCtrl = new wxTextCtrl(leftMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, txtCtrlSize);
	m_transporterCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_TRANSPORT));
	wxStaticText* calendar = new wxStaticText(leftMidPanel, wxID_ANY, "Дата рейса:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_date = new wxDatePickerCtrl(leftMidPanel, wxID_ANY, wxDateTime::Today(), wxPoint(600, 230), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* code = new wxStaticText(leftMidPanel, wxID_ANY, "Код отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* codeDng = new wxStaticText(leftMidPanel, wxID_ANY, "Класс опасности:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxArrayString dngLvlStr;
	dngLvlStr.Add("н/о");
	dngLvlStr.Add("1-го класса");
	dngLvlStr.Add("2-го класса");
	dngLvlStr.Add("3-го класса");
	dngLvlStr.Add("4-го класса");
	m_dngLvlCtrl = new wxChoice(leftMidPanel, wxID_ANY, wxDefaultPosition, wxSize(120, 30), dngLvlStr);
	m_dngLvlCtrl->Enable(0);
	m_codeCtrl = new wxTextCtrl(leftMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(120, 30), 0L, CustomCodeValidator());
	m_codeCtrl->AutoComplete(new CustomAutoComplete(dbTables::codes, DB_COLUMN_CODE));

	//RIGHT SIDE
	m_owner = new wxStaticText(rightMidPanel, wxID_ANY, "Наименование организации:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_owner->Hide();
	m_ownerCtrl = new wxTextCtrl(rightMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, txtCtrlSize);
	m_ownerCtrl->AutoComplete(new CustomAutoComplete(dbTables::passport, DB_COLUMN_OWNER));
	m_ownerCtrl->Hide();
	wxStaticText* amountStatic = new wxStaticText(rightMidPanel, wxID_ANY, "Количество отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amountReceivedCtrl = new wxTextCtrl(rightMidPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 30),0L,utility::GetDoubleValidator(3));
	wxStaticText* amountRecStatic = new wxStaticText(rightMidPanel, wxID_ANY, "Поступило от/образовалось:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxArrayString amRecChoiceStr;
	amRecChoiceStr.Add("-");
	amRecChoiceStr.Add("Образовалось");
	amRecChoiceStr.Add("Поступило от физ. лиц.");
	amRecChoiceStr.Add("Поступило от др. орг.");
	m_amRecCtrl = new wxChoice(rightMidPanel,wxID_ANY, wxDefaultPosition, txtCtrlSize, amRecChoiceStr);
	m_amRecCtrl->SetSelection(1);
	m_unit10Static = new wxStaticText(rightMidPanel, wxID_ANY, "Подразделение, в котором образовался данный вид отхода:");
	m_structUnit10Ctrl = new wxChoice(rightMidPanel, wxID_ANY, wxDefaultPosition, txtCtrlSize, GetUnitChoicesArr());
	wxStaticText* amountTrnsprtStatic = new wxStaticText(rightMidPanel, wxID_ANY, "Движение отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxArrayString amMovmChoiceStr;
	amMovmChoiceStr.Add("Использовано");
	amMovmChoiceStr.Add("Обезврежено");
	amMovmChoiceStr.Add("Направлено на хранение");
	amMovmChoiceStr.Add("Захоронено");
	amMovmChoiceStr.Add("Передано на использование");
	amMovmChoiceStr.Add("Передано на обезвреживание");
	amMovmChoiceStr.Add("Передано на хранение");
	amMovmChoiceStr.Add("Передано на захоронение");
	m_amMovmCtrl = new wxChoice(rightMidPanel, wxID_ANY, wxDefaultPosition, txtCtrlSize, amMovmChoiceStr);
	m_orgTransRadio = new wxRadioButton(rightMidPanel, ID_RADIO_ORG_TRANSPORT,"Передано организации:",wxDefaultPosition,wxDefaultSize, wxRB_GROUP);
	m_orgTransRadio->Enable(0);
	wxStaticText* orgTransText = new wxStaticText(rightMidPanel, wxID_ANY, "Организация:");
	m_selfTransRadio = new wxRadioButton(rightMidPanel, ID_RADIO_SELF_TRANSPORT, "Передано своему подразделению:");
	m_selfTransRadio->Enable(0);
	wxStaticText* selfTransText= new wxStaticText(rightMidPanel, wxID_ANY, "Подразделение:");
	m_structUnit9Ctrl = new wxTextCtrl(rightMidPanel, wxID_ANY,wxEmptyString, wxDefaultPosition, txtCtrlSize);
	m_structUnit9Ctrl->Enable(0);
	wxStaticText* unit9GoalText = new wxStaticText(rightMidPanel, wxID_ANY, "Цель:");
	m_structUnitChoice = new wxChoice(rightMidPanel, wxID_ANY, wxDefaultPosition, txtCtrlSize, GetUnitChoicesArr());
	m_structUnitChoice->Enable(0);
	m_amMovmStructCtrl = new wxChoice(rightMidPanel, wxID_ANY, wxDefaultPosition, txtCtrlSize, amMovmChoiceStr);
	m_amMovmStructCtrl->Enable(0);
	m_recievedPhysText = new wxStaticText(rightMidPanel, wxID_ANY, "ФИО физ лица:");
	m_recievedPhysText->Hide();


	wxPanel* btnPanel = new wxPanel(m_page1);
	m_applyButton = new MaterialButton(btnPanel, wxID_ANY, wxS("ВНЕСТИ ЗАПИСЬ"),false,wxDefaultPosition,wxSize(200,55));
	m_applyButton->SetButtonColour(gui_MainColour);
	m_applyButton->SetLabelColour(*wxWHITE);
	wxBoxSizer* btnSzr = new wxBoxSizer(wxHORIZONTAL);
	btnSzr->AddStretchSpacer(1);
	btnSzr->Add(m_applyButton, 0, wxLEFT | wxBOTTOM, 10);
	btnPanel->SetSizerAndFit(btnSzr);

	wxBoxSizer* newMainSzr = new wxBoxSizer(wxVERTICAL);
	newMainSzr->Add(label, 0, wxLEFT, 20);
	newMainSzr->Add(mainMidSiz, 1);
	newMainSzr->Add(btnPanel,0,wxEXPAND | wxRIGHT | wxBOTTOM, 30);

	midVertSizerLeft->Add(calendar, 0,wxFIXED_MINSIZE | wxRIGHT,120);
	midVertSizerLeft->Add(m_date, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(code, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(m_codeCtrl, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(codeDng, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(m_dngLvlCtrl, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(regnum, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(m_regnumCtrl, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(receiver, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(m_receiverCtrl, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(transport, 0, wxFIXED_MINSIZE | wxRIGHT, 120);
	midVertSizerLeft->Add(m_transporterCtrl, 0, wxFIXED_MINSIZE | wxRIGHT, 120);

	midVertSizerRight->Add(amountStatic, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_amountReceivedCtrl, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(amountRecStatic, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_amRecCtrl, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_unit10Static, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_structUnit10Ctrl, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(amountTrnsprtStatic, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_amMovmCtrl, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_orgTransRadio, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(orgTransText, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_structUnit9Ctrl, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_selfTransRadio, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(selfTransText, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_structUnitChoice, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(unit9GoalText, 0, wxFIXED_MINSIZE);
	midVertSizerRight->Add(m_amMovmStructCtrl, 0, wxFIXED_MINSIZE);


	leftMidPanel->SetSizerAndFit(midVertSizerLeft);
	rightMidPanel->SetSizerAndFit(midVertSizerRight);
	m_page1->SetSizerAndFit(newMainSzr);
	

	m_structUnit10Ctrl->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt) 
		{
			wxString temp = m_structUnitChoice->GetStringSelection();
			m_structUnitChoice->Set(GetUnitChoicesArr(evt.GetString()));
			m_structUnitChoice->SetStringSelection(temp);		
		});
	m_amRecCtrl->Bind(wxEVT_CHOICE, [&, midVertSizerRight](wxCommandEvent& evt)
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
			midVertSizerRight->Detach(4);
			midVertSizerRight->Detach(4);
			midVertSizerRight->InsertStretchSpacer(4,0);
			midVertSizerRight->InsertStretchSpacer(5,0);
			midVertSizerRight->Layout();
			wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
			wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));

		}
		else if (m_amRecCtrl->GetSelection() == 1)
		{
			if (midVertSizerRight->GetItem(4)->GetWindow() == m_unit10Static)
				return;
			m_transporterCtrl->Enable(1);
			m_receiverCtrl->Enable(1);
			m_regnumCtrl->Enable(1);
			m_ownerCtrl->Clear();
			m_ownerCtrl->Hide();
			m_owner->Hide();
			m_recievedPhysText->Hide();
			midVertSizerRight->Detach(4);
			midVertSizerRight->Detach(4);
			midVertSizerRight->Insert(4, m_unit10Static);
			midVertSizerRight->Insert(5, m_structUnit10Ctrl);
			m_unit10Static->Show();
			m_structUnit10Ctrl->Show();
			midVertSizerRight->Layout();
			wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
			wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
		}
		else if (m_amRecCtrl->GetSelection() == 2)
		{
			if (midVertSizerRight->GetItem(4)->GetWindow() == m_recievedPhysText)
				return;
			m_transporterCtrl->Enable(1);
			m_receiverCtrl->Enable(1);
			m_regnumCtrl->Enable(1);
			m_structUnit10Ctrl->Hide();
			m_unit10Static->Hide();
			m_owner->Hide();
			midVertSizerRight->Detach(4);
			midVertSizerRight->Insert(4, m_recievedPhysText);
			if (midVertSizerRight->GetItem(5)->GetWindow() != m_ownerCtrl)
			{
				midVertSizerRight->Detach(5);
				midVertSizerRight->Insert(5, m_ownerCtrl);
			}
			m_recievedPhysText->Show();
			m_ownerCtrl->Show();
			midVertSizerRight->Layout();
			wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
			wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
		}
		else
		{
			if (midVertSizerRight->GetItem(9)->GetWindow() == m_owner)
				return;
			m_transporterCtrl->Enable(1);
			m_receiverCtrl->Enable(1);
			m_regnumCtrl->Enable(1);
			m_recievedPhysText->Hide();
			m_structUnit10Ctrl->Hide();
			m_unit10Static->Hide();
			midVertSizerRight->Detach(4);
			midVertSizerRight->Insert(4, m_owner);
			if (midVertSizerRight->GetItem(5)->GetWindow() != m_ownerCtrl)
			{
				midVertSizerRight->Detach(5);
				midVertSizerRight->Insert(5, m_ownerCtrl);
			}
			m_owner->Show();
			m_ownerCtrl->Show();
			midVertSizerRight->Layout();
			wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));
			wxPostEvent(m_orgTransRadio, wxCommandEvent(wxEVT_RADIOBUTTON));
		}
	});
	m_amMovmCtrl->Bind(wxEVT_CHOICE, &Add_panel::OnAmMovmSelect, this);
	m_orgTransRadio->Bind(wxEVT_RADIOBUTTON, &Add_panel::OnRadioButton, this);
	m_dngLvlCtrl->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt) 
	{
		if (m_dngLvlCtrl->GetSelection() > 2)
			m_amountReceivedCtrl->SetValidator(utility::GetDoubleValidator(3, wxAtof(m_amountReceivedCtrl->GetValue())));
		else
		{
			wxString temp = m_amountReceivedCtrl->GetValue();
			if (temp.After('.').size() > 2)
				temp.RemoveLast();
			m_amountReceivedCtrl->SetValue(temp);
			m_amountReceivedCtrl->SetValidator(utility::GetDoubleValidator(2, wxAtof(temp)));
		}
	});
	m_selfTransRadio->Bind(wxEVT_RADIOBUTTON, &Add_panel::OnRadioButton, this);
	m_applyButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Add_panel::OnButtonApply, this);
}


void Add_panel::UnitChoiceChange(wxCommandEvent& evt)
{
	m_structUnitChoice->Set(GetUnitChoicesArr());
	m_structUnit10Ctrl->Set(GetUnitChoicesArr());
}


void Add_panel::OnAmMovmSelect(wxCommandEvent& evt)
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
	}
}

void Add_panel::OnRadioButton(wxCommandEvent& evt)
{
	if (m_amMovmCtrl->GetSelection() < 3)
	{
		m_structUnit9Ctrl->Clear();
		m_structUnit9Ctrl->Enable(0);
		m_amMovmStructCtrl->SetSelection(-1);
		m_amMovmStructCtrl->Enable(0);
		m_structUnitChoice->SetSelection(-1);
		m_structUnitChoice->Enable(0);
		return;
	}
	if (m_orgTransRadio->GetValue())
	{
		m_structUnit9Ctrl->Enable(1);
		m_amMovmStructCtrl->Enable(0);
		m_structUnitChoice->Enable(0);
	}
	else if(m_selfTransRadio->GetValue() && m_structUnit10Ctrl->GetCount() > 1)
	{
		m_structUnit9Ctrl->Clear();
		m_structUnit9Ctrl->Enable(0);
		m_amMovmStructCtrl->Enable(1);
		m_structUnitChoice->Enable(1);
	}
	else if(m_selfTransRadio->GetValue() && m_structUnit10Ctrl->GetCount() < 2)
	{
		wxMessageBox("невозможно передать в другое подразделение, количество существующих подразделений меньше 2.");
		m_orgTransRadio->SetValue(1);
		return;
	}
}

bool Add_panel::VerifyValues()
{
	DBMain db;
	if (!db.IsCodeExists(m_codeCtrl->GetValue()))
	{
		wxMessageBox("Ошибка: введенное значение в поле \"Код отходов\" не существует");
		return false;
	}
	if (m_codeCtrl->GetValue().IsEmpty())
	{
		wxMessageBox("Ошибка: поле \"Код отходов\" должно быть заполнено");
		return false;
	}
	if (m_dngLvlCtrl->GetSelection() == -1)
	{
		wxMessageBox("Ошибка: поле \"Класс опосности\" должно быть заполнено");
		return false;
	}
	if (m_amountReceivedCtrl->GetValue().IsEmpty())
	{
		wxMessageBox("Ошибка: поле \"Количество отходов\" должно быть заполнено");
		return false;
	}
	if (m_amRecCtrl->GetSelection() == -1)
	{
		wxMessageBox("Ошибка: поле \"Поступло от/образовалось\" должно быть заполнено");
		return false;
	}
	if (m_amRecCtrl->GetSelection() == 1 && m_structUnit10Ctrl->GetSelection() == -1)
	{
		if (m_structUnit10Ctrl->GetCount() != 1)
		{
			wxMessageBox("Ошибка: поле \"Подразделение, в котором образовался данный вид отхода\" должно быть заполнено");
			return false;
		}
		else
		{
			if (m_structUnit10Ctrl->GetString(0) == "")
				m_structUnit10Ctrl->SetSelection(0);
		}

	}
	if (m_amMovmCtrl->GetSelection() == -1)
	{
		wxMessageBox("Ошибка: поле \"Движение отхода\" должно быть заполнено");
		return false;
	}
	if (m_amMovmCtrl->GetSelection() > 3 && m_selfTransRadio->GetValue())
	{
		if (m_amMovmStructCtrl->GetSelection() == -1)
		{
			wxMessageBox("Ошибка: поле \"Цель\" должно быть заполнено");
			return false;
		}
		if (m_structUnitChoice->GetSelection() == -1)
		{
			if (m_structUnitChoice->GetCount() != 1)
			{
				wxMessageBox("Ошибка: поле \"Подразделение\" должно быть заполнено");
				return false;
			}
			else
			{
				if (m_structUnitChoice->GetString(0) == "")
					m_structUnitChoice->SetSelection(0);
			}

		}
	}
	if (m_amRecCtrl->GetSelection() == 0 && m_amMovmCtrl->GetSelection() == 2)
	{
		wxMessageBox("Ошибка: выбранная комбинация полей \"Поступило от/образовалось\" и \"Движение отхода\" невозможна.");
		return false;
	}
	return true;
}

void Add_panel::OnButtonApply(wxCommandEvent& evt)
{
	if (!VerifyValues())
		return;
	addPageInfo info;
	DBMain db;
	info.wasteNorm = db.GetWasteNormByCode(m_codeCtrl->GetValue());
	info.activeUnitID = wxString::Format("%i",Settings::getActiveUnitID());
	info.date = m_date->GetValue().Format((wxS("%Y.%m.%d")));
	info.code = m_codeCtrl->GetValue();
	info.codeDngLvl = m_dngLvlCtrl->GetStringSelection();
	info.regnum = m_regnumCtrl->GetValue();
	info.owner = m_ownerCtrl->GetValue();
	info.receiver = m_receiverCtrl->GetValue();
	info.transporter = m_transporterCtrl->GetValue();
	switch (m_amRecCtrl->GetSelection())
	{
		case 1:
		{
			info.amountFormed = m_amountReceivedCtrl->GetValue();
			info.owner = m_structUnit10Ctrl->GetStringSelection();
			info.structUnit10 = m_structUnit10Ctrl->GetStringSelection();
			if(m_amMovmCtrl->GetSelection() == 2 || m_amMovmCtrl->GetSelection() == 3)
				info.structUnit9 = m_structUnit10Ctrl->GetStringSelection();
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
			info.structUnit9 = m_receiverCtrl->GetValue();
			break;
		}
		case 3:
		{
			info.amountReceivedOrg = m_amountReceivedCtrl->GetValue();
			info.structUnit9 = m_receiverCtrl->GetValue();
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

	if (m_amMovmCtrl->GetSelection() > 3 )
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
							info.actveRecieverUnitID = wxString::Format("%i",unit.id);
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
	if (m_amMovmCtrl->GetSelection() > 3 && m_selfTransRadio->GetValue())
	{
		db.insertNewDoubleEntry(info);
	}
	else
	{

		db.insertNewEntry(info);
	}
	wxCommandEvent cmdEvt(EVT_DATABASE_CHANGED);
	wxPostEvent(GetParent(), cmdEvt);
	ClearControls();
}


void Add_panel::OnEnteredCodeExists(wxCommandEvent& evt)
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
		wxPostEvent(m_dngLvlCtrl,wxCommandEvent(wxEVT_CHOICE));
	}
}

void Add_panel::ClearControls()
{
	m_transporterCtrl->Clear();
	m_ownerCtrl->Clear();
	m_receiverCtrl->Clear();
	m_regnumCtrl->Clear();
	m_codeCtrl->Clear();
	m_amountReceivedCtrl->Clear();
	m_dngLvlCtrl->SetSelection(-1);
	m_structUnit10Ctrl->Clear();
	m_amRecCtrl->SetSelection(1);
	wxPostEvent(m_amRecCtrl, wxCommandEvent(wxEVT_CHOICE));
	m_amMovmCtrl->SetSelection(-1);
	wxPostEvent(m_amMovmCtrl, wxCommandEvent(wxEVT_CHOICE));

}