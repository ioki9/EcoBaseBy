#include "Dialog_askDeleteEntry.h"

Dialog_askDeleteEntry::Dialog_askDeleteEntry(wxWindow* parent, const addPageInfo& info, wxWindowID id, const wxString& title, const wxPoint& pos, 
	const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos,size, style, name), m_record{info}
{
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	m_mainPanel->SetFont(gui_MainFont);
	wxPanel* topGreenPanel = new wxPanel(m_mainPanel);
	topGreenPanel->SetBackgroundColour(gui_MainColour);
	wxStaticText *topText = new wxStaticText(topGreenPanel, wxID_ANY, "Удаление записи",wxDefaultPosition,wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	topText->SetForegroundColour(*wxWHITE);
	topText->SetFont(wxFontInfo(14).FaceName("Segoe UI Semibold"));
	wxBoxSizer* topTextSizer = new wxBoxSizer(wxHORIZONTAL);
	topTextSizer->Add(topText,0,wxALIGN_CENTER_VERTICAL | wxLEFT , 10);
	topGreenPanel->SetSizerAndFit(topTextSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* mainText = new wxStaticText(m_mainPanel, wxID_ANY, "Вы уверены, что хотите удалить выбранную запись? Это действие нельзя отменить.", 
		wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_VERTICAL);
	wxBoxSizer* mainTextSizer = new wxBoxSizer(wxHORIZONTAL);
	mainTextSizer->Add(mainText, 1,wxEXPAND | wxTOP | wxLEFT, 10);
	
	m_btnNO = new MaterialButton(m_mainPanel, wxID_ANY, "Отмена",true,wxDefaultPosition,wxSize(70, 35));
	m_btnNO->SetButtonLineColour(*wxWHITE);
	m_btnNO->SetLabelColour(wxColour(90, 90, 90));
	m_btnNO->SetButtonShadow(false);
	m_btnNO->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
	m_btnYES = new MaterialButton(m_mainPanel, wxID_ANY, "Удалить", true, wxDefaultPosition, wxSize(70, 35));
	m_btnYES->SetButtonLineColour(*wxWHITE);
	m_btnYES->SetLabelColour(wxColour(165, 42, 42));
	m_btnYES->SetButtonShadow(false);
	m_btnYES->SetTextFont(wxFontInfo(13).FaceName("Segoe UI").Bold());
	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	btnSizer->Add(m_btnYES,0,wxRIGHT,15);
	btnSizer->Add(m_btnNO, 0, wxRIGHT);
	
	mainSizer->Add(topGreenPanel, 1, wxEXPAND);
	mainSizer->Add(mainTextSizer,2,wxEXPAND);
	mainSizer->Add(btnSizer,0,wxBOTTOM|wxRIGHT | wxALIGN_RIGHT,20);
	m_mainPanel->SetSizerAndFit(mainSizer);
	m_btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_askDeleteEntry::OnNoButton, this);
	m_btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Dialog_askDeleteEntry::OnYesButton, this);
	m_btnNO->Bind(wxEVT_MOTION, &Dialog_askDeleteEntry::OnButtonMotion, this);
	m_btnNO->Bind(wxEVT_LEAVE_WINDOW, &Dialog_askDeleteEntry::OnButtonMotionOUT, this);
	m_btnYES->Bind(wxEVT_MOTION, &Dialog_askDeleteEntry::OnButtonMotion, this);
	m_btnYES->Bind(wxEVT_LEAVE_WINDOW, &Dialog_askDeleteEntry::OnButtonMotionOUT, this);
	this->Bind(wxEVT_PAINT, &Dialog_askDeleteEntry::OnPaint, this);


	this->CenterOnParent(wxHORIZONTAL);
	this->ShowModal();

}

Dialog_askDeleteEntry::~Dialog_askDeleteEntry()
{
}

void Dialog_askDeleteEntry::OnNoButton(wxCommandEvent& evt)
{
	this->Close();
}

void Dialog_askDeleteEntry::OnYesButton(wxCommandEvent& evt)
{
	DBMain* db = new DBMain;
	db->deleteEntry(m_record);
	delete db;
	this->Close();
}

void Dialog_askDeleteEntry::OnButtonMotion(wxMouseEvent& evt)
{
	SetCursor(wxCURSOR_HAND);
}

void Dialog_askDeleteEntry::OnButtonMotionOUT(wxMouseEvent& evt)
{
	SetCursor(wxCURSOR_DEFAULT);
}

void Dialog_askDeleteEntry::OnPaint(wxPaintEvent& evt)
{
		wxWindowDC* dc = new wxWindowDC(this->GetParent());
		wxImage image(this->GetParent()->GetSize());
		image.InitAlpha();

		unsigned char* alpha = image.GetAlpha();
		memset(alpha, wxIMAGE_ALPHA_TRANSPARENT, image.GetWidth() * image.GetHeight());

		wxGraphicsContext* gc = wxGraphicsContext::Create(image);
		gc->SetBrush(wxBrush(wxColour(0, 0, 0, 176)));
		gc->SetPen(*wxTRANSPARENT_PEN);
		gc->DrawRectangle(0, 0, this->GetParent()->GetSize().GetX(), this->GetParent()->GetSize().GetY());
		delete gc;

		wxBitmap bmp(image);

		dc->DrawBitmap(bmp, 0, 0);

		delete dc;
}


