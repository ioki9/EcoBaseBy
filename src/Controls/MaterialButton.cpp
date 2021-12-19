#include "MaterialButton.h"
#include <wx/dcgraph.h>
#include <wx/gdicmn.h>
#include <wx/platinfo.h>

MaterialButton::MaterialButton(wxWindow* parent, wxWindowID id, const wxString& text,bool isOutlined,
	const wxPoint& pos, const wxSize& size) :wxPanel(parent, id, pos, size), m_size{ size }, m_text{ text }
{
	this->SetDoubleBuffered(true);
	this->SetBackgroundColour(parent->GetBackgroundColour());
	if (isOutlined)
		status |= flag_outlined;
	status |= flag_shadowDrawn;
	if(wxPlatformInfo::Get().GetOperatingSystemId() & wxOS_UNIX)
	{	
		SetButtonShadow(false);
	}
	this->Bind(wxEVT_LEAVE_WINDOW, &MaterialButton::OnMotionOUT, this);
	this->Bind(wxEVT_LEFT_DOWN, &MaterialButton::OnLeftDown, this);
	this->Bind(wxEVT_MOTION, &MaterialButton::OnMotionIN, this);
	this->Bind(wxEVT_PAINT, &MaterialButton::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &MaterialButton::OnLeftUp, this);
	this->Bind(wxEVT_SIZE, [this](wxSizeEvent& event) { Refresh(); event.Skip(); });
}

MaterialButton::~MaterialButton()
{
}


wxSize MaterialButton::DoGetBestSize() const
{
	return m_size;
}

void MaterialButton::SetTextFont(const wxFont& font)
{
	m_txtFont = font;
}

void MaterialButton::SetButtonFillColour(const wxColour& colour)
{
	m_colourBtnBrush = colour;
	this->Refresh();
}

void MaterialButton::SetButtonLineColour(const wxColour& colour)
{
	m_colourBtnPen = colour;
	this->Refresh();
}

void MaterialButton::SetLabelColour(const wxColour& colour)
{
	m_colourText = colour;
	this->Refresh();
}

void MaterialButton::SetButtonColour(const wxColour& colour)
{
	m_colourBtnPen = colour;
	m_colourBtnBrush = colour;
	this->Refresh();

}

void MaterialButton::SetButtonShadow(bool isDrawn)
{
	if (isDrawn)
		status |= flag_shadowDrawn;
	else
		status &= ~(flag_shadowDrawn);
}

void MaterialButton::disableButton(bool disable)
{
	if (disable)
		status |= flag_isDisabled;
	else
		status &= ~(flag_isDisabled);

}

bool MaterialButton::SetLineWidth(uint8_t width)
{
	if (width > 8)
		return false;
	rectInfo.LineWidth = width;
	this->Refresh();
	this->Update();
	return true;
}

bool MaterialButton::SetButtonRadius(uint8_t radius)
{
	if (radius > 8)
		return false;
	rectInfo.Radius = radius;
	this->Refresh();
	this->Update();
	return true;
}

void MaterialButton::OnPaint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	wxGCDC gcdc(dc);
	wxColour shadow(wxColour(210, 210, 210));


		if ((status & (flag_leftKeyDown | flag_motionIN)) == (flag_leftKeyDown | flag_motionIN))
		{
			if (status & flag_shadowDrawn)
			{
				gcdc.SetBrush(wxBrush(shadow));
				gcdc.SetPen(wxPen(shadow));
				gcdc.DrawRoundedRectangle(2, 0, m_size.x - 2, m_size.y, rectInfo.Radius);
			}

			if (status & flag_outlined)
			{
				gcdc.SetPen(wxPen(m_colourBtnPen, rectInfo.LineWidth));
				gcdc.SetBrush(wxBrush(m_colourBtnPen.ChangeLightness(160)));
			}
			else
			{
				gcdc.SetBrush(wxBrush(m_colourBtnPen.ChangeLightness(110)));
				gcdc.SetPen(wxPen(m_colourBtnPen.ChangeLightness(115), rectInfo.LineWidth));
			}

		}
		else if (status & flag_motionIN)
		{
			if (status & flag_shadowDrawn)
			{
				gcdc.SetBrush(wxBrush(shadow));
				gcdc.SetPen(wxPen(shadow));
				gcdc.DrawRoundedRectangle(2, 0, m_size.x - 2, m_size.y, rectInfo.Radius);
			}
			if (status & flag_outlined)
			{
				gcdc.SetPen(wxPen(m_colourBtnPen, rectInfo.LineWidth));
				gcdc.SetBrush(wxBrush(m_colourBtnPen.ChangeLightness(190)));
			}
			else
			{
				gcdc.SetBrush(wxBrush(m_colourBtnPen.ChangeLightness(107)));
				gcdc.SetPen(wxPen(m_colourBtnPen.ChangeLightness(107), rectInfo.LineWidth));
			}
		}
		else
		{
			gcdc.SetBrush(wxBrush(m_colourBtnBrush));
			gcdc.SetPen(wxPen(m_colourBtnPen, rectInfo.LineWidth));
		}
	
	
		
	if(status & flag_shadowDrawn)
		gcdc.DrawRoundedRectangle(0, 0, m_size.x, m_size.y-3, rectInfo.Radius);
	else
		gcdc.DrawRoundedRectangle(0, 0, m_size.x, m_size.y, rectInfo.Radius);
	gcdc.SetFont(m_txtFont);
	gcdc.SetTextForeground(m_colourText);
	wxSize txtSize{ gcdc.GetTextExtent(m_text) };
	gcdc.DrawText(m_text, wxPoint((m_size.x - txtSize.x) / 2, (m_size.y - txtSize.y) / 2));
	
}

void MaterialButton::OnLeftDown(wxMouseEvent& evt)
{
	status |= flag_leftKeyDown;
	this->Refresh();
	this->Update();
	evt.Skip();
}

void MaterialButton::OnLeftUp(wxMouseEvent& evt)
{
	status &= ~(flag_leftKeyDown);
	wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
	evt.SetEventObject(this);
	HandleWindowEvent(event);
	this->Refresh();
	this->Update();
	evt.Skip();
}

void MaterialButton::OnMotionIN(wxMouseEvent& evt)
{
	status |= flag_motionIN;
	status &= ~(flag_motionOUT);
	this->Refresh();
	this->Update();
	evt.Skip();
}

void MaterialButton::OnMotionOUT(wxMouseEvent& evt)
{
	status &= ~(flag_motionIN | flag_leftKeyDown);
	status |= flag_motionOUT;
	this->Refresh();
	this->Update();
	evt.Skip();
}
