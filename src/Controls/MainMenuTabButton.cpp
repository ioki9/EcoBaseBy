#include "MainMenuTabButton.h"
#include <wx/dcgraph.h>
#include <wx/gdicmn.h>

MainMenuTabButton::MainMenuTabButton(wxWindow* parent, const wxString& text, wxWindowID id, bool droppable,
	const wxSize& size, const wxPoint& pos) : wxPanel(parent, id, pos, size),  m_text{ text }, m_size{size}
{
	this->SetDoubleBuffered(true);

	if (droppable)
		status |= flag_isDroppable;

	this->Bind(wxEVT_LEAVE_WINDOW, &MainMenuTabButton::OnMotionOUT, this);
	this->Bind(wxEVT_LEFT_DOWN, &MainMenuTabButton::OnLeftDown, this);
	this->Bind(wxEVT_MOTION, &MainMenuTabButton::OnMotionIN, this);
	this->Bind(wxEVT_PAINT, &MainMenuTabButton::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &MainMenuTabButton::OnLeftUp, this);
	this->Bind(wxEVT_PAINT,&MainMenuTabButton::OnPaint,this);
}

MainMenuTabButton::~MainMenuTabButton()
{

}
void MainMenuTabButton::setSelected(bool selected )
{
	if (selected)
		status |= flag_isSelected;
	else
		status &= ~(flag_isSelected);
}

void MainMenuTabButton::setDropArrowtSize(const wxSize& size)
{
	if (!(size.GetX() % 2))
		m_dropArrowSize = size;
	else
		m_dropArrowSize = { size.GetX() - 1,size.GetY() };

}

void MainMenuTabButton::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	wxGCDC gcdc(dc);


	if ((status & (flag_leftKeyDown | flag_motionIN)) == (flag_leftKeyDown | flag_motionIN))
	{
		gcdc.SetPen(wxPen(gui_MainColour));
		gcdc.SetBrush(wxBrush(gui_MainColour.ChangeLightness(80)));
	
	}
	else if (status & flag_motionIN)
	{
		gcdc.SetPen(wxPen(gui_MainColour));
		gcdc.SetBrush(wxBrush(gui_MainColour.ChangeLightness(90)));

	}
	else if(status & flag_isSelected)
	{
		gcdc.SetPen(wxPen(gui_MainColour));
		gcdc.SetBrush(wxBrush(gui_MainColour.ChangeLightness(80)));

	}
	else
	{
		gcdc.SetPen(wxPen(gui_MainColour));
		gcdc.SetBrush(wxBrush(gui_MainColour.ChangeLightness(100)));
	}

	gcdc.DrawRectangle(0, 0, m_size.GetWidth(), m_size.GetHeight());
	gcdc.SetTextForeground(*wxWHITE);
	gcdc.SetFont(gui_MenuFont);
	wxSize txtSize{ gcdc.GetTextExtent(m_text) };
	
	gcdc.DrawText(m_text, wxPoint(30, (m_size.GetHeight() - txtSize.GetHeight()) / 2));

	if (status & flag_isSelected)
	{
		gcdc.SetPen(wxPen(*wxWHITE,3));
		gcdc.SetBrush(wxBrush(*wxWHITE));
		
		gcdc.DrawLine(2, m_size.GetHeight()/5, 2 ,m_size.GetHeight() - m_size.GetHeight() / 5);

	}

	if (status & flag_isDroppable)
	{
		int startPos{ (m_size.GetWidth() - 22) };
		int halfLength{ m_dropArrowSize.GetWidth() / 2 };
		if (status & flag_isSelected)
		{
			gcdc.SetPen(wxPen(*wxWHITE, 2));
			gcdc.SetBrush(wxBrush(*wxWHITE));

			gcdc.DrawLine(startPos, m_size.GetHeight() - m_size.GetHeight() / 2.3,
				startPos - halfLength, m_size.GetHeight() / 2.3);

			gcdc.DrawLine(startPos - 2 * halfLength, m_size.GetHeight() - m_size.GetHeight() / 2.3,
				startPos - halfLength, m_size.GetHeight() / 2.3);
		}
		else
		{
			gcdc.SetPen(wxPen(*wxWHITE, 2));
			gcdc.SetBrush(wxBrush(*wxWHITE));

			gcdc.DrawLine(startPos, m_size.GetHeight() / 2.3,
				startPos - halfLength, m_size.GetHeight() - m_size.GetHeight() / 2.3);

			gcdc.DrawLine(startPos - 2 * halfLength, m_size.GetHeight() / 2.3,
				startPos - halfLength, m_size.GetHeight() - m_size.GetHeight() / 2.3);
		}
	}

}



void MainMenuTabButton::OnLeftDown(wxMouseEvent& evt)
{
	status |= flag_leftKeyDown;
	this->Refresh();
	evt.Skip();
}

void MainMenuTabButton::OnLeftUp(wxMouseEvent& evt)
{
	status &= ~(flag_leftKeyDown);
	wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
	evt.SetEventObject(this);
	HandleWindowEvent(event);
	this->Refresh();
	evt.Skip();
}

void MainMenuTabButton::OnMotionIN(wxMouseEvent& evt)
{
	status |= flag_motionIN;
	status &= ~(flag_motionOUT);
	this->Refresh();
	evt.Skip();
}

void MainMenuTabButton::OnMotionOUT(wxMouseEvent& evt)
{
	status &= ~(flag_motionIN | flag_leftKeyDown);
	status |= flag_motionOUT;
	this->Refresh();
	evt.Skip();
}
