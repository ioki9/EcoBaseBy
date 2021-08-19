#include "Add_panel.h"


Add_panel::Add_panel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size)
	:wxPanel(parent,winid,pos,size)
{
	SetDoubleBuffered(true);
	this->initPage1();
	this->initPage2();
	m_page2->Hide();
	this->initPage3();
	m_page3->Hide();
	m_amFullStrgCtrl->HideNativeCaret();

	//m_resultPage = new wxPanel(this, wxID_ANY);
	//m_resultPage->Hide();

	mainSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainSizer);
	mainSizer->Add(m_page1, 1, wxEXPAND);

	p1_buttonNext->Bind(wxEVT_LEFT_UP, &Add_panel::OnP1_ButtonNext, this);
	p2_buttonNext->Bind(wxEVT_LEFT_UP, &Add_panel::OnP2_ButtonNext, this);
	p2_buttonPrevious->Bind(wxEVT_LEFT_UP, &Add_panel::OnP2_ButtonPrev, this);
	p3_buttonNext->Bind(wxEVT_LEFT_UP, &Add_panel::OnP3_ButtonNext, this);
	p3_buttonPrevious->Bind(wxEVT_LEFT_UP, &Add_panel::OnP3_ButtonPrev, this);
	p3_strgCheck->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Add_panel::OnP3_CheckBoxUp, this);

}

Add_panel::~Add_panel()
{

}

void Add_panel::initPage1()
{
	wxFloatingPointValidator<float> floatValidator(3, &m_validatorValue, wxNUM_VAL_ZERO_AS_BLANK);

	m_page1 = new wxPanel(this, ID_PAGE1, wxDefaultPosition, wxDefaultSize);

	wxPanel *botPanel = new wxPanel(m_page1);
	wxPanel *topPanel = new wxPanel(m_page1, wxID_ANY,wxDefaultPosition, wxDefaultSize);
	wxPanel *middlePanel = new wxPanel(m_page1, wxID_ANY);
	wxPanel *midLeftPanel = new wxPanel(middlePanel, wxID_ANY);
	wxPanel* midRightPanel = new wxPanel(middlePanel, wxID_ANY);
	wxPanel* midRightSizPanel = new wxPanel(midRightPanel);

	wxBoxSizer *p1_mainSizer = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* middleSizer = new wxGridSizer(1,2,wxSize(80,0));
	wxBoxSizer* midLeftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* midRightMainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* midRightSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *buttonSizer = new wxBoxSizer(wxVERTICAL);
	midRightMainSizer->Add(midRightSizPanel, 1);
	
	midRightSizPanel->SetFont(m_textFont);
	midLeftPanel->SetFont(m_textFont);
	wxStaticText* label = new wxStaticText(topPanel, wxID_ANY, "КАКОЙ-ТО ЗАГОЛОВОК", wxPoint(30, 30),wxDefaultSize, wxALIGN_LEFT);
	label->SetFont(wxFontInfo(18).FaceName("Segoe UI Semibold"));
	wxStaticText* regnum = new wxStaticText(midLeftPanel, wxID_ANY, "Регистрационный номер:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_regnumCtrl = new wxTextCtrl(midLeftPanel, ID_PAGE1_REGNUMTXT, wxEmptyString, wxDefaultPosition, wxSize(100,30));
	wxStaticText* owner = new wxStaticText(midLeftPanel, wxID_ANY, "Поступило от организации:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_ownerCtrl = new wxTextCtrl(midLeftPanel, ID_PAGE1_OWNERTXT, wxEmptyString, wxDefaultPosition, txtCtrlSize);
	wxStaticText* receiver = new wxStaticText(midLeftPanel, wxID_ANY, "Получатель отходов:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_receiverCtrl = new wxTextCtrl(midLeftPanel, ID_PAGE1_RECEIVERTXT, wxEmptyString, wxDefaultPosition, txtCtrlSize);
	wxStaticText* transport = new wxStaticText(midLeftPanel, wxID_ANY, "Перевозчик отходов:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_transporterCtrl = new wxTextCtrl(midLeftPanel, ID_PAGE1_TRANSPORTERTXT, wxEmptyString, wxDefaultPosition, txtCtrlSize);

	wxStaticText* calendar = new wxStaticText(midRightSizPanel, wxID_ANY, "Дата рейса:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_date = new wxDatePickerCtrl(midRightSizPanel, ID_PAGE1_CALENDAR_DATE, wxDateTime::Today(),
		wxPoint(600, 230), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* code = new wxStaticText(midRightSizPanel, wxID_ANY, "Код отходов:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_codeCtrl = new wxTextCtrl(midRightSizPanel, ID_PAGE1_CODETXT, wxEmptyString, wxDefaultPosition, wxSize(100, 30));

	wxStaticText* amount = new wxStaticText(midRightSizPanel, wxID_ANY, "Количество отходов:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amountReceivedCtrl = new wxTextCtrl(midRightSizPanel, ID_PAGE1_AMOUNTTXT, wxEmptyString, wxDefaultPosition, wxSize(100, 30),0L, floatValidator);
	amountFromedRadio = new wxRadioButton(midRightSizPanel, ID_PAGE1_AMOUNTRADIO, "Образовалось", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	amountReceivedPhysRadio = new wxRadioButton(midRightSizPanel, ID_PAGE1_AMOUNTRADIO, "Поступило от физ. лиц.", wxDefaultPosition, wxDefaultSize);
	amountReceivedOrgRadio = new wxRadioButton(midRightSizPanel, ID_PAGE1_AMOUNTRADIO, "Поступило от др. орг.", wxDefaultPosition, wxDefaultSize);

	p1_buttonNext = new MaterialButton(botPanel, ID_PAGE1_BUTTON_NEXT, wxS("ДАЛЕЕ"),true,wxDefaultPosition,wxSize(200,55));
	p1_buttonNext->SetButtonLineColour(wxColour(34, 139, 34));
	p1_buttonNext->SetLabelColour(wxColour(34, 139, 34));
	buttonSizer->Add(p1_buttonNext, 1, wxALIGN_RIGHT | wxRIGHT, 50);

	//____________MAIN_______________________________
	p1_mainSizer->Add(topPanel, 0, wxEXPAND|wxLEFT,20);
	p1_mainSizer->Add(middlePanel,1, wxEXPAND);
	p1_mainSizer->Add(botPanel, 0, wxEXPAND | wxBOTTOM,30);
	middleSizer->Add(midLeftPanel, 1, wxEXPAND | wxTOP | wxBOTTOM| wxLEFT, 50);
	middleSizer->Add(midRightPanel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 50);

	//____________MIDDLE LEFT________________________
	midLeftSizer->Add(regnum, 0, wxBOTTOM, 10);
	midLeftSizer->Add(m_regnumCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midLeftSizer->Add(owner, 0, wxBOTTOM, 10);
	midLeftSizer->Add(m_ownerCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midLeftSizer->Add(receiver, 0, wxBOTTOM, 10);
	midLeftSizer->Add(m_receiverCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midLeftSizer->Add(transport, 0, wxEXPAND | wxBOTTOM, 10);
	midLeftSizer->Add(m_transporterCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);

	//____________MIDDLE RIGHT________________________

	midRightSizer->Add(calendar, 0, wxEXPAND | wxBOTTOM ,10);
	midRightSizer->Add(m_date, 0, wxFIXED_MINSIZE | wxBOTTOM , 20);
	midRightSizer->Add(code, 0, wxEXPAND | wxBOTTOM, 10);
	midRightSizer->Add(m_codeCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midRightSizer->Add(amount, 0, wxEXPAND | wxBOTTOM, 10);
	midRightSizer->Add(m_amountReceivedCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midRightSizer->Add(amountFromedRadio, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midRightSizer->Add(amountReceivedPhysRadio, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	midRightSizer->Add(amountReceivedOrgRadio, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);

	m_page1->SetSizer(p1_mainSizer);
	middlePanel->SetSizerAndFit(middleSizer);
	botPanel->SetSizerAndFit(buttonSizer);


	midRightPanel->SetSizerAndFit(midRightMainSizer);
	midRightSizPanel->SetSizerAndFit(midRightSizer);
	midLeftPanel->SetSizerAndFit(midLeftSizer);
	buttonSizer->Layout();
	middleSizer->Layout();


}

void Add_panel::initPage2()
{
	wxFloatingPointValidator<float> floatValidator(3, &m_validatorValue, wxNUM_VAL_ZERO_AS_BLANK);
	
	m_page2 = new wxPanel(this, ID_PAGE2, wxDefaultPosition, wxDefaultSize);
	

	wxPanel* p2_topPanel = new wxPanel(m_page2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxPanel* p2_middlePanel = new wxPanel(m_page2, wxID_ANY);
	wxPanel* p2_midLeftPanel = new wxPanel(p2_middlePanel, wxID_ANY);
	wxPanel* p2_midRightPanel = new wxPanel(p2_middlePanel, wxID_ANY);
	wxPanel* p2_botPanel = new wxPanel(m_page2, wxID_ANY);
	wxPanel* p2_midRightSizPanel = new wxPanel(p2_midRightPanel);

	wxBoxSizer* p2_mainSizer = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* p2_middleSizer = new wxGridSizer(1, 2, wxSize(50, 0));
	wxBoxSizer* p2_midLeftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* p2_midRightSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* p2_buttonSizerH = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* p2_midRightMainSizer = new wxBoxSizer(wxVERTICAL);

	p2_midRightMainSizer->Add(p2_midRightSizPanel, 1, wxALIGN_CENTER_HORIZONTAL);


	p2_midRightSizPanel->SetFont(m_textFont);
	p2_midLeftPanel->SetFont(m_textFont);
	wxStaticText* label = new wxStaticText(p2_topPanel, wxID_ANY, "КАКОЙ-ТО ЗАГОЛОВОК2", wxPoint(30, 30), wxDefaultSize, wxALIGN_LEFT);
	label->SetFont(wxFontInfo(18).FaceName("Segoe UI Semibold"));

	wxStaticText* amUsed = new wxStaticText(p2_midLeftPanel, wxID_ANY, "Использовано:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amUsedCtrl = new wxTextCtrl(p2_midLeftPanel, ID_PAGE1_REGNUMTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* defused = new wxStaticText(p2_midLeftPanel, wxID_ANY, "Обезврежено:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amDefusedCtrl = new wxTextCtrl(p2_midLeftPanel, ID_PAGE1_OWNERTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* storage = new wxStaticText(p2_midLeftPanel, wxID_ANY, "Направлено на хранение:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amStorageCtrl = new wxTextCtrl(p2_midLeftPanel, ID_PAGE1_RECEIVERTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* burial = new wxStaticText(p2_midLeftPanel, wxID_ANY, "Захоронено:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amBurialCtrl = new wxTextCtrl(p2_midLeftPanel, ID_PAGE1_TRANSPORTERTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);

	wxStaticText* tUsed = new wxStaticText(p2_midRightSizPanel, wxID_ANY, "Передано на использование:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_tamUsedCtrl = new wxTextCtrl(p2_midRightSizPanel, ID_PAGE1_TRANSPORTERTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* tDefused = new wxStaticText(p2_midRightSizPanel, wxID_ANY, "Передано на обозвреживание:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_tamDefusedCtrl = new wxTextCtrl(p2_midRightSizPanel, ID_PAGE1_CODETXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* tStorage = new wxStaticText(p2_midRightSizPanel, wxID_ANY, "Передано на хранение:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_tamStorageCtrl = new wxTextCtrl(p2_midRightSizPanel, ID_PAGE1_AMOUNTTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* tBurial = new wxStaticText(p2_midRightSizPanel, wxID_ANY, "Передано на захоронение:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_tamBurialCtrl = new wxTextCtrl(p2_midRightSizPanel, ID_PAGE1_AMOUNTTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);

	p2_buttonNext = new MaterialButton(p2_botPanel, ID_PAGE1_BUTTON_NEXT, wxS("ДАЛЕЕ"),true, wxDefaultPosition, wxSize(200, 55));
	p2_buttonNext->SetButtonLineColour(wxColour(34, 139, 34));
	p2_buttonNext->SetLabelColour(wxColour(34, 139, 34));
	p2_buttonPrevious = new MaterialButton(p2_botPanel, ID_PAGE1_BUTTON_NEXT, wxS("НАЗАД"), true, wxDefaultPosition, wxSize(200, 55));
	p2_buttonPrevious->SetButtonLineColour(wxColour(34, 139, 34));
	p2_buttonPrevious->SetLabelColour(wxColour(34, 139, 34));

	p2_buttonSizerH->Add(p2_buttonPrevious,0,wxLEFT,50);
	p2_buttonSizerH->AddStretchSpacer();
	p2_buttonSizerH->Add(p2_buttonNext,0,wxRIGHT,50);


	//____________MAIN_______________________________
	p2_mainSizer->Add(p2_topPanel, 0, wxEXPAND | wxLEFT, 20);
	p2_mainSizer->Add(p2_middlePanel, 1, wxEXPAND);
	p2_mainSizer->Add(p2_botPanel, 0, wxEXPAND | wxBOTTOM, 30);
	p2_middleSizer->Add(p2_midLeftPanel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 50);
	p2_middleSizer->Add(p2_midRightPanel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 50);


	//____________MIDDLE LEFT________________________
	p2_midLeftSizer->Add(amUsed, 0, wxBOTTOM, 10);
	p2_midLeftSizer->Add(m_amUsedCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midLeftSizer->Add(defused, 0, wxBOTTOM, 10);
	p2_midLeftSizer->Add(m_amDefusedCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midLeftSizer->Add(storage, 0, wxBOTTOM, 10);
	p2_midLeftSizer->Add(m_amStorageCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midLeftSizer->Add(burial, 0, wxEXPAND | wxBOTTOM, 10);
	p2_midLeftSizer->Add(m_amBurialCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);

	//____________MIDDLE RIGHT________________________

	p2_midRightSizer->Add(tUsed, 0, wxEXPAND | wxBOTTOM, 10);
	p2_midRightSizer->Add(m_tamUsedCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midRightSizer->Add(tDefused, 0, wxEXPAND | wxBOTTOM, 10);
	p2_midRightSizer->Add(m_tamDefusedCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midRightSizer->Add(tStorage, 0, wxEXPAND | wxBOTTOM, 10);
	p2_midRightSizer->Add(m_tamStorageCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p2_midRightSizer->Add(tBurial, 0, wxFIXED_MINSIZE | wxBOTTOM, 10);
	p2_midRightSizer->Add(m_tamBurialCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);


	p2_middlePanel->SetSizer(p2_middleSizer);

	m_page2->SetSizer(p2_mainSizer);
	p2_botPanel->SetSizerAndFit(p2_buttonSizerH);
	p2_midRightPanel->SetSizerAndFit(p2_midRightMainSizer);
	p2_midRightSizPanel->SetSizerAndFit(p2_midRightSizer);
	p2_midLeftPanel->SetSizerAndFit(p2_midLeftSizer);
	p2_buttonSizerH->Layout();
	p2_middleSizer->Layout();

	//m_page2->FitInside(); // ask the sizer about the needed size
	//m_page2->SetScrollRate(5, 5);
}

void Add_panel::initPage3()
{
	wxFloatingPointValidator<float> floatValidator(3, &m_validatorValue, wxNUM_VAL_ZERO_AS_BLANK);

	m_page3 = new wxPanel(this, ID_PAGE3, wxDefaultPosition, wxDefaultSize);
	

	wxPanel* p3_topPanel = new wxPanel(m_page3, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxPanel* p3_middlePanel = new wxPanel(m_page3, wxID_ANY);
	wxPanel* p3_midLeftPanel = new wxPanel(p3_middlePanel, wxID_ANY);
	wxPanel* p3_midRightPanel = new wxPanel(p3_middlePanel, wxID_ANY);
	wxPanel* p3_botPanel = new wxPanel(m_page3, wxID_ANY);
	wxPanel* p3_midRightSizPanel = new wxPanel(p3_midRightPanel);
	

	wxBoxSizer* p3_mainSizer = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* p3_middleSizer = new wxGridSizer(1, 2, wxSize(80, 0));
	wxBoxSizer* p3_midLeftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* p3_midRightSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* p3_midRightMainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* p3_buttonSizerH = new wxBoxSizer(wxHORIZONTAL);

	p3_midRightMainSizer->Add(p3_midRightSizPanel, 1, wxALIGN_CENTER_HORIZONTAL | wxTOP,22);


	p3_midRightSizPanel->SetFont(m_textFont);
	p3_midLeftPanel->SetFont(m_textFont);
	wxStaticText* label = new wxStaticText(p3_topPanel, wxID_ANY, "КАКОЙ-ТО ЗАГОЛОВОК3", wxPoint(30, 30), wxDefaultSize, wxALIGN_LEFT);
	label->SetFont(wxFontInfo(18).FaceName("Segoe UI Semibold"));
	wxStaticText* structUnit10 = new wxStaticText(p3_midLeftPanel, wxID_ANY, "Структурное подразделение в которых образовался данный вид отхода (ПОД 10):", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_structUnit10Ctrl = new wxTextCtrl(p3_midLeftPanel, ID_PAGE1_REGNUMTXT, wxEmptyString, wxDefaultPosition, txtCtrlSize, 0L);
	structUnit10->Wrap(400);
	wxStaticText* structUnit9 = new wxStaticText(p3_midLeftPanel, wxID_ANY, "Передано организации, структурному подразделению (ПОД 9):", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_structUnit9Ctrl = new wxTextCtrl(p3_midLeftPanel, ID_PAGE1_REGNUMTXT, wxEmptyString, wxDefaultPosition, txtCtrlSize, 0L);
	structUnit9->Wrap(400);


	wxStaticText* entryDate = new wxStaticText(p3_midRightSizPanel, wxID_ANY, "Дата внесения уч. записи (ПОД 10):", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_entryDate = new wxDatePickerCtrl(p3_midRightSizPanel, ID_PAGE1_CALENDAR_DATE, wxDateTime::Today(),
		wxPoint(600, 230), wxDefaultSize, wxDP_DROPDOWN);
	wxStaticText* wasteNorm = new wxStaticText(p3_midRightSizPanel, wxID_ANY, "Норма образования отхода:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_wasteNormCtrl = new wxTextCtrl(p3_midRightSizPanel, ID_PAGE1_OWNERTXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	wxStaticText* fullStrg = new wxStaticText(p3_midRightSizPanel, wxID_ANY, "*Всего на хранении: ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	m_amFullStrgCtrl = new wxTextCtrl(p3_midRightSizPanel, ID_PAGE1_CODETXT, wxEmptyString, wxDefaultPosition, wxSize(250, 30), 0L, floatValidator);
	m_amFullStrgCtrl->SetEditable(0);
	

	p3_strgCheck = new CustomCheckBox(p3_midRightSizPanel, wxID_ANY, "",wxDefaultPosition);
	wxBoxSizer *fullStrgSizer = new wxBoxSizer(wxHORIZONTAL);
	fullStrgSizer->Add(m_amFullStrgCtrl);
	fullStrgSizer->Add(p3_strgCheck,0,wxALIGN_CENTER_VERTICAL| wxLEFT,10);
	


	p3_buttonNext = new MaterialButton(p3_botPanel, ID_PAGE1_BUTTON_NEXT, wxS("ДАЛЕЕ"),true, wxDefaultPosition, wxSize(200, 55));
	p3_buttonNext->SetButtonLineColour(wxColour(34, 139, 34));
	p3_buttonNext->SetLabelColour(wxColour(34, 139, 34));
	p3_buttonPrevious = new MaterialButton(p3_botPanel, ID_PAGE1_BUTTON_NEXT, wxS("НАЗАД"), true, wxDefaultPosition, wxSize(200, 55));
	p3_buttonPrevious->SetButtonLineColour(wxColour(34, 139, 34));
	p3_buttonPrevious->SetLabelColour(wxColour(34, 139, 34));

	p3_buttonSizerH->Add(p3_buttonPrevious, 0, wxLEFT, 50);
	p3_buttonSizerH->AddStretchSpacer(1);
	p3_buttonSizerH->Add(p3_buttonNext, 0, wxRIGHT, 50);


	//____________MAIN_______________________________
	p3_mainSizer->Add(p3_topPanel, 0, wxEXPAND | wxLEFT, 20);
	p3_mainSizer->Add(p3_middlePanel, 1, wxEXPAND);
	p3_mainSizer->Add(p3_botPanel, 0, wxEXPAND | wxBOTTOM, 30);
	p3_middleSizer->Add(p3_midLeftPanel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxLEFT, 50);
	p3_middleSizer->Add(p3_midRightPanel, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 50);

	//____________MIDDLE LEFT________________________
	p3_midLeftSizer->Add(structUnit10, 0, wxBOTTOM, 10);
	p3_midLeftSizer->Add(m_structUnit10Ctrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p3_midLeftSizer->Add(structUnit9, 0, wxBOTTOM, 10);
	p3_midLeftSizer->Add(m_structUnit9Ctrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);


	//____________MIDDLE RIGHT________________________
	p3_midRightSizer->Add(entryDate, 0, wxEXPAND | wxBOTTOM, 10);
	p3_midRightSizer->Add(m_entryDate, 0, wxFIXED_MINSIZE | wxBOTTOM, 44);
	p3_midRightSizer->Add(wasteNorm, 0, wxBOTTOM, 10);
	p3_midRightSizer->Add(m_wasteNormCtrl, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);
	p3_midRightSizer->Add(fullStrg, 0, wxEXPAND | wxBOTTOM, 10);
	p3_midRightSizer->Add(fullStrgSizer, 0, wxFIXED_MINSIZE | wxBOTTOM, 20);



	p3_middlePanel->SetSizerAndFit(p3_middleSizer);

	m_page3->SetSizer(p3_mainSizer);
	p3_botPanel->SetSizer(p3_buttonSizerH);
	p3_midRightPanel->SetSizer(p3_midRightMainSizer);
	p3_midRightSizPanel->SetSizer(p3_midRightSizer);
	p3_midLeftPanel->SetSizer(p3_midLeftSizer);
	p3_buttonSizerH->Layout();
	p3_middleSizer->Layout();

}

void Add_panel::initResultPage()
{
	
	m_resultPage = new wxPanel(this, wxID_ANY);
	
	m_resultPage->SetFont(m_textFont);
	pr_mainPanel = new wxScrolledWindow(m_resultPage);

	wxString amountStr ,valAmountStr;

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(pr_mainPanel, 1, wxEXPAND);
	 

	wxBoxSizer* lhMainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* lsRow1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow3 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow4 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow5 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow6 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow7 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow8 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow9 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow10 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow11 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow12 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow13 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow14 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow15 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow16 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow17 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow18 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow19 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* lsRow20 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	 
	if (amountFromedRadio->GetValue())
	{
		amountStr = "Количество отходов (образовалось): ";
		valAmountStr = m_record.amountFormed;

	}
		 
	else if (amountReceivedPhysRadio->GetValue())
	{
		valAmountStr = m_record.amountReceivedPhys;
	amountStr = "Количество отходов (поступило от физ. лиц): ";
	}
		 
	else
	{
		amountStr = "Количество отходов(поступило от др. орг.): ";
		valAmountStr = m_record.amountReceivedOrg;
	}
		 

	wxStaticText* label = new wxStaticText(pr_mainPanel, wxID_ANY, "ИТОГОВЫЙ ЗАГЛОВОК");
	label->SetFont(wxFontInfo(20).FaceName("Segoe UI Semibold"));
	wxStaticText* regnum = new wxStaticText(pr_mainPanel, wxID_ANY, "Регистрационный номер: ");
	wxStaticText* valRegnum = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.regnum,wxDefaultPosition,wxDefaultSize,wxALIGN_LEFT);
	valRegnum->SetFont(m_textFont.Bold());
	wxStaticText* owner = new wxStaticText(pr_mainPanel, wxID_ANY, "Поступило от организации: ");
	wxStaticText* valOwner = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.owner, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	valOwner->SetFont(m_textFont.Bold());
	wxStaticText* receiver = new wxStaticText(pr_mainPanel, wxID_ANY, "Получатель отходов: ");
	wxStaticText* valReceiver = new wxStaticText(pr_mainPanel, wxID_ANY,m_record.receiver, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	valReceiver->SetFont(m_textFont.Bold());
	wxStaticText* transporter = new wxStaticText(pr_mainPanel, wxID_ANY, "Перевозчик отходов: ");
	wxStaticText* valTransporter = new wxStaticText(pr_mainPanel, wxID_ANY,m_record.transporter, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	valTransporter->SetFont(m_textFont.Bold());
	wxStaticText* date = new wxStaticText(pr_mainPanel, wxID_ANY, "Дата рейса: " );
	wxStaticText* valDate = new wxStaticText(pr_mainPanel, wxID_ANY,utility::convertDate(m_record.date), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	valDate->SetFont(m_textFont.Bold());
	wxStaticText* code = new wxStaticText(pr_mainPanel, wxID_ANY, "Код отхода: ");
	wxStaticText* valCode = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.code, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	valCode->SetFont(m_textFont.Bold());


	wxStaticText* amount = new wxStaticText(pr_mainPanel, wxID_ANY, amountStr);
	wxStaticText* valAmount = new wxStaticText(pr_mainPanel, wxID_ANY, valAmountStr);
	valAmount->SetFont(m_textFont.Bold());
	wxStaticText* amUsed = new wxStaticText(pr_mainPanel, wxID_ANY, "Использовано: ");
	wxStaticText* valAmUsed = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.amountUsed);
	valAmUsed->SetFont(m_textFont.Bold());
	wxStaticText* amDefused = new wxStaticText(pr_mainPanel, wxID_ANY, "Обезврежено: " );
	wxStaticText* valAmDefused = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.amountDefused);
	valAmDefused->SetFont(m_textFont.Bold());
	wxStaticText* amStorage = new wxStaticText(pr_mainPanel, wxID_ANY, "Направлено на хранение: ");
	wxStaticText* valAmStorage = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.amountStorage);
	valAmStorage->SetFont(m_textFont.Bold());
	wxStaticText* amBurial = new wxStaticText(pr_mainPanel, wxID_ANY, "Захоронено: " );
	wxStaticText* valAmBurial = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.amountBurial);
	valAmBurial->SetFont(m_textFont.Bold());
	wxStaticText* tamUsed = new wxStaticText(pr_mainPanel, wxID_ANY, "Передано на использование: " );
	wxStaticText* valTamUsed = new wxStaticText(pr_mainPanel, wxID_ANY,  m_record.tamountUsed);
	valTamUsed->SetFont(m_textFont.Bold());
	wxStaticText* tamDefused = new wxStaticText(pr_mainPanel, wxID_ANY, "Передано на обезвреживание: ");
	wxStaticText* valTamDefused = new wxStaticText(pr_mainPanel, wxID_ANY,  m_record.tamountDefused);
	valTamDefused->SetFont(m_textFont.Bold());
	wxStaticText* tamStorage = new wxStaticText(pr_mainPanel, wxID_ANY, "Передано на хранение: " );
	wxStaticText* valTamStorage = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.tamountStorage);
	valTamStorage->SetFont(m_textFont.Bold());
	wxStaticText* tamBurial = new wxStaticText(pr_mainPanel, wxID_ANY, "Передано на захоронение: " );
	wxStaticText* valTamBurial = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.tamountBurial);
	valTamBurial->SetFont(m_textFont.Bold());

	wxStaticText* structUnit9 = new wxStaticText(pr_mainPanel, wxID_ANY, "Передано организации,\n структурному подразделению (ПОД 9): ");
	wxStaticText* valStructUnit9 = new wxStaticText(pr_mainPanel, wxID_ANY, "\n" + m_record.structUnit9);
	valStructUnit9->SetFont(m_textFont.Bold());
	wxStaticText* structUnit10 = new wxStaticText(pr_mainPanel, wxID_ANY, "Структурное подразделение в которых\n образовался данный вид отхода (ПОД 10): " );
	wxStaticText* valStructUnit10 = new wxStaticText(pr_mainPanel, wxID_ANY,"\n" + m_record.structUnit10);
	valStructUnit10->SetFont(m_textFont.Bold());
	wxStaticText* wasteNorm = new wxStaticText(pr_mainPanel, wxID_ANY, "Норма образования отхода: ");
	wxStaticText* valWasteNorm = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.wasteNorm);
	valWasteNorm->SetFont(m_textFont.Bold());
	wxStaticText* entryDate = new wxStaticText(pr_mainPanel, wxID_ANY, "Дата внесения уч. записи (ПОД 10): ");
	wxStaticText* valEntryDate = new wxStaticText(pr_mainPanel, wxID_ANY, utility::convertDate(m_record.entryDate));
	valEntryDate->SetFont(m_textFont.Bold());
	wxStaticText* strgFull = new wxStaticText(pr_mainPanel, wxID_ANY, "Всего на хранении: " );
	wxStaticText* valStrgFull = new wxStaticText(pr_mainPanel, wxID_ANY, m_record.amountStrgFull);
	valStrgFull->SetFont(m_textFont.Bold());



	
	m_rButtonPanel = new wxPanel(m_resultPage, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	mainSizer->Add(m_rButtonPanel, 0, wxEXPAND | wxBOTTOM | wxTOP, 30);
	pr_buttonPrevious = new MaterialButton(m_rButtonPanel, wxID_ANY, "НАЗАД", true, wxDefaultPosition, wxSize(200, 55));
	pr_buttonPrevious->SetButtonLineColour(wxColour(34, 139, 34));
	pr_buttonPrevious->SetLabelColour(wxColour(34, 139, 34));
	pr_buttonApply = new MaterialButton(m_rButtonPanel, wxID_ANY, "ДОБАВИТЬ", false, wxDefaultPosition, wxSize(200, 55));
	pr_buttonApply->SetButtonColour(wxColour(34, 139, 34));
	pr_buttonApply->SetLabelColour(*wxWHITE);
	buttonSizer->Add(pr_buttonPrevious, 0, wxEXPAND | wxLEFT, 50);
	buttonSizer->AddStretchSpacer(1);
	buttonSizer->Add(pr_buttonApply, 0, wxEXPAND | wxRIGHT, 50);
	pr_buttonApply->Bind(wxEVT_LEFT_UP, &Add_panel::OnPR_ButtonApply, this);
	pr_buttonPrevious->Bind(wxEVT_LEFT_UP, &Add_panel::OnPR_ButtonPrevious, this);
	


	lhMainSizer->Add(label, 0, wxLEFT | wxTOP | wxALIGN_LEFT, 20);

	lsRow1->Add(regnum, 0, wxALIGN_LEFT | wxLEFT, 40);
	lsRow1->Add(valRegnum, 1, wxALIGN_LEFT |wxEXPAND);
	lsRow2->Add(date, 0,  wxLEFT,40);
	lsRow2->Add(valDate, 1, wxALIGN_LEFT | wxLEFT);
	lsRow3->Add(owner, 0,  wxLEFT, 40);
	lsRow3->Add(valOwner, 0, wxALIGN_LEFT | wxEXPAND);
	lsRow4->Add(receiver, 0, wxALIGN_LEFT | wxLEFT,40);
	lsRow4->Add(valReceiver, 0, wxALIGN_LEFT | wxLEFT);
	lsRow5->Add(transporter, 0, wxLEFT, 40);
	lsRow5->Add(valTransporter, 1, wxALIGN_LEFT | wxEXPAND);
	lsRow6->Add(amount, 0, wxLEFT, 40);
	lsRow6->Add(valAmount, 1, wxLEFT);
	lsRow7->Add(code, 0, wxLEFT, 40);
	lsRow7->Add(valCode, 1, wxLEFT);
	lsRow8->Add(amUsed, 0, wxLEFT, 40);
	lsRow8->Add(valAmUsed, 1, wxALIGN_LEFT | wxEXPAND);
	lsRow9->Add(amDefused, 0, wxLEFT,40);
	lsRow9->Add(valAmDefused, 1, wxLEFT);
	lsRow10->Add(amStorage, 0, wxLEFT, 40);
	lsRow10->Add(valAmStorage, 1, wxALIGN_LEFT | wxEXPAND);
	lsRow11->Add(amBurial, 0, wxLEFT,40);
	lsRow11->Add(valAmBurial, 1, wxLEFT);
	lsRow12->Add(tamUsed, 0, wxLEFT, 40);
	lsRow12->Add(valTamUsed, 1, wxLEFT);
	lsRow13->Add(tamStorage, 0, wxLEFT,40);
	lsRow13->Add(valTamStorage, 1, wxLEFT);
	lsRow14->Add(tamDefused, 0, wxLEFT, 40);
	lsRow14->Add(valTamDefused, 1, wxLEFT);
	lsRow15->Add(tamBurial, 0, wxLEFT, 40);
	lsRow15->Add(valTamBurial, 1, wxLEFT);
	lsRow16->Add(structUnit10, 0, wxLEFT, 40);
	lsRow16->Add(valStructUnit10, 1, wxLEFT);
	lsRow17->Add(entryDate, 0, wxLEFT, 40);
	lsRow17->Add(valEntryDate, 1, wxLEFT);
	lsRow18->Add(structUnit9, 0, wxLEFT, 40);
	lsRow18->Add(valStructUnit9, 1, wxLEFT);
	lsRow19->Add(wasteNorm, 0, wxLEFT, 40);
	lsRow19->Add(valWasteNorm, 1, wxLEFT);
	lsRow20->Add(strgFull, 0, wxLEFT, 40);
	lsRow20->Add(valStrgFull, 1, wxLEFT);
	lhMainSizer->Add(lsRow1, 0, wxEXPAND | wxTOP ,20);
	lhMainSizer->Add(lsRow2, 0, wxEXPAND | wxTOP, 5 );
	lhMainSizer->Add(lsRow3, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow4, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow5, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow6, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow7, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow8, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow9, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow10, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow11, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow12, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow13, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow14, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow15, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow16, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow17, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow18, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow19, 0, wxEXPAND | wxTOP, 5);
	lhMainSizer->Add(lsRow20, 0, wxEXPAND | wxTOP, 5);



	m_rButtonPanel->SetSizer(buttonSizer);

	pr_mainPanel->SetSizer(lhMainSizer);
	m_resultPage->SetSizer(mainSizer);
	m_rButtonPanel->Layout();
	m_rButtonPanel->Fit();
	pr_mainPanel->Fit();
	pr_mainPanel->Layout();
	m_resultPage->Fit();
	m_resultPage->Layout();
	pr_mainPanel->SetScrollRate(5, 5);

}

void Add_panel::OnPaint(wxPaintEvent &evt)
{

}


void Add_panel::OnP1_ButtonNext(wxMouseEvent& evt)
{

	m_record.date = m_date->GetValue().Format((wxS("%Y.%m.%d")));
	m_record.code = m_codeCtrl->GetValue();
	m_record.regnum = m_regnumCtrl->GetValue();
	m_record.owner = m_ownerCtrl->GetValue();
	m_record.transporter = m_transporterCtrl->GetValue();
	m_record.receiver = m_receiverCtrl->GetValue();
	m_record.amountGet = m_amountReceivedCtrl->GetValue();
	if (amountFromedRadio->GetValue())
		m_record.amountFormed = m_amountReceivedCtrl->GetValue();
	else if(amountReceivedPhysRadio->GetValue())
		m_record.amountReceivedPhys = m_amountReceivedCtrl->GetValue();
	else
		m_record.amountReceivedOrg = m_amountReceivedCtrl->GetValue();
	

	mainSizer->Detach(0);
	m_page1->Hide();
	mainSizer->Add(m_page2, 1, wxEXPAND);
	m_page2->Show();
	mainSizer->Layout();
	evt.Skip();
}


void Add_panel::OnP2_ButtonNext(wxMouseEvent& evt)
{
	m_record.amountBurial = m_amBurialCtrl->GetValue();
	m_record.amountStorage = m_amStorageCtrl->GetValue();
	m_record.amountUsed = m_amUsedCtrl->GetValue();
	m_record.amountDefused = m_amDefusedCtrl->GetValue();
	m_record.tamountBurial = m_tamBurialCtrl->GetValue();
	m_record.tamountStorage = m_tamStorageCtrl->GetValue();
	m_record.tamountUsed = m_tamUsedCtrl->GetValue();
	m_record.tamountDefused = m_tamDefusedCtrl->GetValue();

	mainSizer->Detach(0);
	m_page2->Hide();
	mainSizer->Add(m_page3, 1, wxEXPAND);
	m_page3->Show();
	mainSizer->Layout();

	evt.Skip();
}

void Add_panel::OnP2_ButtonPrev(wxMouseEvent& evt)
{
	mainSizer->Detach(0);
	m_page2->Hide();
	mainSizer->Add(m_page1, 1, wxEXPAND);
	m_page1->Show();
	mainSizer->Layout();

	evt.Skip();
}

void Add_panel::OnP3_ButtonNext(wxMouseEvent& evt)
{
	m_record.wasteNorm = m_wasteNormCtrl->GetValue();
	m_record.structUnit10 = m_structUnit10Ctrl->GetValue();
	m_record.structUnit9 = m_structUnit9Ctrl->GetValue();
	m_record.amountStrgFull = m_amFullStrgCtrl->GetValue();
	m_record.entryDate = m_entryDate->GetValue().Format((wxS("%Y.%m.%d")));

	if(m_resultPage)
		m_resultPage->Destroy();
	mainSizer->Detach(0);
	m_page3->Hide();
	this->initResultPage();
	mainSizer->Add(m_resultPage, 1, wxEXPAND);
	m_resultPage->Show();
	mainSizer->Layout();

	evt.Skip();

}

void Add_panel::OnP3_ButtonPrev(wxMouseEvent& evt)
{
	mainSizer->Detach(0);
	m_page3->Hide();
	mainSizer->Add(m_page2, 1, wxEXPAND);
	m_page2->Show();
	mainSizer->Layout();
	evt.Skip();
}


void Add_panel::OnP3_CheckBoxUp(wxCommandEvent& evt)
{
	if (p3_strgCheck->status & p3_strgCheck->flag_active)
	{
		m_amFullStrgCtrl->SetEditable(1);
		m_amFullStrgCtrl->ShowNativeCaret();
		Refresh();
	}
		
	else
	{
		m_amFullStrgCtrl->Clear();
		m_amFullStrgCtrl->HideNativeCaret();
		m_amFullStrgCtrl->SetEditable(0);
		Refresh();
	}
		
}


void Add_panel::OnPR_ButtonApply(wxMouseEvent& evt)
{

	DBMain* dataBase = new DBMain;
	wxString storage = "";
	if (m_record.amountStrgFull != "")
	{
		storage = dataBase->checkFullStorage(m_record.code);

		if (storage != "")
		{
			wxMessageBox("Значение \"Хранение\" уже существует для данного вида отхода, значение учитываться не будет.\n" + storage);
			m_record.amountStrgFull = "";
			dataBase->insertNewEntry(m_record);
		}
		else
			dataBase->insertFirstEntry(m_record);
	}
	else
	{
		dataBase->insertNewEntry(m_record);
	}
	

	delete dataBase;

}
void Add_panel::OnPR_ButtonPrevious(wxMouseEvent& evt)
{
	mainSizer->Detach(0);
	
	m_resultPage->Hide();
	mainSizer->Add(m_page3, 1, wxEXPAND);
	m_page3->Show();
	mainSizer->Layout();
	evt.Skip();
}