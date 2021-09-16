#include "Dialog_OrgAddEdit.h"

Dialog_OrgAddEdit::Dialog_OrgAddEdit(wxWindow* parent, bool isAddDialog, wxWindowID id, const wxString& title, const wxPoint& pos,
	const wxSize& size, long style, const wxString& name) : wxDialog(parent,id,title,pos,size,style,name), m_isAddDialog{isAddDialog}
{
	this->SetFont(gui_MainFont);
	wxString headerStr;
	if (isAddDialog)
		headerStr = "Добавить организацию";
	else
		headerStr = "Изменение данных организации";
	m_mainPanel = new wxPanel(this);
	m_mainPanel->SetBackgroundColour(*wxWHITE);
	
	headerPanel = new wxPanel(m_mainPanel,wxID_ANY,wxDefaultPosition);
	headerPanel->SetBackgroundColour(gui_MainColour);
	wxStaticText* headerText = new wxStaticText(headerPanel, wxID_ANY, headerStr);
	headerText->SetForegroundColour(*wxWHITE);
	headerText->SetFont(wxFontInfo(13).FaceName("Segoe UI Semibold"));
	wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);
	headerSizer->Add(headerText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
	headerPanel->SetSizerAndFit(headerSizer);

	m_1stPage = new wxScrolledWindow(m_mainPanel);
	m_buttonPanel = new wxPanel(m_mainPanel);
	m_mainSizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText* staticOrgName = new wxStaticText(m_1stPage, wxID_ANY, wxS("Название организации:"));
	m_orgName = new wxTextCtrl(m_1stPage, wxID_ANY);

	wxStaticText* staticOrgAddress = new wxStaticText(m_1stPage, wxID_ANY, wxS("Адрес организации:"));
	m_orgAddress = new wxTextCtrl(m_1stPage, wxID_ANY);

	wxStaticText* staticOrgUnp = new wxStaticText(m_1stPage, wxID_ANY, wxS("УНП организации:"));
	m_orgUnp = new wxTextCtrl(m_1stPage, wxID_ANY);

	m_wasteNormList = new VirtualCodeList(m_1stPage, wxID_ANY, wxDefaultPosition, wxSize(200,200));


	wxBoxSizer * firstPageSizer = new wxBoxSizer(wxVERTICAL);
	firstPageSizer->Add(staticOrgName, 0, wxEXPAND);
	firstPageSizer->Add(m_orgName, 0, wxEXPAND);
	firstPageSizer->Add(staticOrgAddress, 0, wxEXPAND);
	firstPageSizer->Add(m_orgAddress, 0, wxEXPAND);
	firstPageSizer->Add(staticOrgUnp, 0, wxEXPAND);
	firstPageSizer->Add(m_orgUnp, 0, wxEXPAND);
	firstPageSizer->Add(m_wasteNormList, 0, wxEXPAND);
	m_1stPage->SetSizerAndFit(firstPageSizer);

	
	
	m_mainSizer->Add(headerPanel, 1, wxEXPAND);
	m_mainSizer->Add(m_1stPage, 6, wxEXPAND);
	m_mainSizer->Add(m_buttonPanel, 0,wxEXPAND);
	m_mainPanel->SetSizerAndFit(m_mainSizer);
	m_1stPage->SetScrollRate(5, 5);
	this->CenterOnParent(wxHORIZONTAL);

	this->Bind(wxEVT_PAINT, &Dialog_OrgAddEdit::onPaint, this);
	headerText->Bind(wxEVT_LEFT_UP, &Dialog_OrgAddEdit::OnMouseLUp, this);
	headerText->Bind(wxEVT_MOTION, &Dialog_OrgAddEdit::OnMouseMove, this);
	headerText->Bind(wxEVT_LEAVE_WINDOW, &Dialog_OrgAddEdit::OnMouseLeave, this);
	headerText->Bind(wxEVT_LEFT_DOWN, &Dialog_OrgAddEdit::OnMouseLDown, this);
	headerText->Bind(wxEVT_MOUSE_CAPTURE_LOST, &Dialog_OrgAddEdit::OnMouseCaptureLost, this);
	
	headerText->Bind(wxEVT_LEFT_DOWN, &Dialog_OrgAddEdit::OnMouseLDown, this);
	headerText->Bind(wxEVT_MOUSE_CAPTURE_LOST, &Dialog_OrgAddEdit::OnMouseCaptureLost, this);
	this->ShowModal();
}

Dialog_OrgAddEdit::~Dialog_OrgAddEdit()
{
}

void Dialog_OrgAddEdit::OnMouseMove(wxMouseEvent& event)
{
	if (event.LeftIsDown() && event.Dragging())
	{
		wxPoint pt = event.GetPosition();
		wxPoint wndLeftTopPt = GetPosition();
		int distanceX = pt.x - mLastPt.x;
		int distanceY = pt.y - mLastPt.y;

		wxPoint desPt;
		desPt.x = distanceX + wndLeftTopPt.x;
		desPt.y = distanceY + wndLeftTopPt.y;
		this->Move(desPt);

	}

	if (event.LeftDown())
	{
		mLastPt = event.GetPosition();
	}
}

void Dialog_OrgAddEdit::OnMouseLeave(wxMouseEvent& event)
{
	if (event.LeftIsDown() && event.Dragging())
	{
		wxPoint pt = event.GetPosition();
		wxPoint wndLeftTopPt = GetPosition();
		int distanceX = pt.x - mLastPt.x;
		int distanceY = pt.y - mLastPt.y;

		wxPoint desPt;
		desPt.x = distanceX + wndLeftTopPt.x;
		desPt.y = distanceY + wndLeftTopPt.y;
		this->Move(desPt);

	}
}
void Dialog_OrgAddEdit::OnMouseLUp(wxMouseEvent& event)
{
	if (HasCapture())
		ReleaseMouse();
}

void Dialog_OrgAddEdit::OnMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
	if (HasCapture())
		ReleaseMouse();
}

void Dialog_OrgAddEdit::OnMouseLDown(wxMouseEvent& event)
{
	this->CaptureMouse();
}

void Dialog_OrgAddEdit::paintDarkBackground(wxWindowDC* dc)
{

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


}

void Dialog_OrgAddEdit::onPaint(wxPaintEvent& evt)
{
	if (!m_isDrawn)
	{
		wxWindowDC* dc = new wxWindowDC(this->GetParent());
		paintDarkBackground(dc);
		m_isDrawn = true;
		delete dc;
	}

}
