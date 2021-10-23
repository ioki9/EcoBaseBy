#include "CustomCheckBox.h"


CustomCheckBox::CustomCheckBox(wxPanel* parent, wxWindowID id, const wxString& label,
	const wxPoint& pos) : wxPanel(parent, id, pos, wxSize(15, 15)), m_text{ label }
{

	this->SetDoubleBuffered(true);
	this->Bind(wxEVT_LEAVE_WINDOW, &CustomCheckBox::OnLeave, this);
	this->Bind(wxEVT_LEFT_DOWN, &CustomCheckBox::OnKeyDown, this);
	this->Bind(wxEVT_MOTION, &CustomCheckBox::OnMotion, this);
	this->Bind(wxEVT_PAINT, &CustomCheckBox::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &CustomCheckBox::OnClick, this);
}

CustomCheckBox::~CustomCheckBox()
{
}



void CustomCheckBox::SetCheckBoxActive()
{
	status |= flag_active;
	this->Refresh();
}

void CustomCheckBox::setCheckBoxColour(const wxColour& colour)
{
	m_checkBoxColour = colour;
}



void CustomCheckBox::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	gc->DisableOffset();
	wxGCDC gcdc(gc);
	if (status & flag_active)
	{
		wxPoint yLeftMid{ 2, 7 };
		wxPoint xBotMid{ 5 , 11 };
		if(status & flag_motionIN)
			gc->SetPen(wxPen(m_checkBoxColour.ChangeLightness(140),3));
		else
			gc->SetPen(wxPen(m_checkBoxColour));

		if(status & flag_leftKeyDown)
			gc->SetBrush(wxBrush(m_checkBoxColour.ChangeLightness(130)));
		else
			gc->SetBrush(wxBrush(m_checkBoxColour));
		gc->DrawRectangle(0,0,this->GetSize().x, this->GetSize().y);
		gcdc.SetPen(wxPen(*wxWHITE, 2));
		gcdc.DrawLine(yLeftMid, xBotMid);
		gcdc.DrawLine(xBotMid, wxPoint(12, 3));
	}
	else
	{
		if(status & flag_motionIN)
			gc->SetPen(wxPen(m_checkBoxColour, 3));
		else
			gc->SetPen(wxPen(*wxBLACK, 3));

		if (status & flag_leftKeyDown)
			gc->SetBrush(wxBrush(m_checkBoxColour.ChangeLightness(145)));
		gc->DrawRectangle(0,0,15,15);
	}
}

void CustomCheckBox::OnMotion(wxMouseEvent& evt)
{
	status |= flag_motionIN;
	status &= ~(flag_motionOUT);
	this->Refresh();
	evt.Skip();
}

void CustomCheckBox::OnClick(wxMouseEvent& evt)
{
	status &= ~(flag_leftKeyDown);
	status ^= flag_active;
	wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
	evt.SetEventObject(this);
	HandleWindowEvent(event);
	this->Refresh();
	evt.Skip();
}

void CustomCheckBox::OnLeave(wxMouseEvent& evt)
{
	status &= ~(flag_motionIN | flag_leftKeyDown);
	status |= flag_motionOUT;
	this->Refresh();
	evt.Skip();
}

void CustomCheckBox::OnKeyDown(wxMouseEvent& evt)
{
	status |= flag_leftKeyDown;
	this->Refresh();
	evt.Skip();
}