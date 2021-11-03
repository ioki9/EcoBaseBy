#include "TransparentPanel.h"

TransparentPanel::TransparentPanel(wxWindow* parent) :
	wxTopLevelWindow(parent, -1,"jej", parent->GetPosition(), parent->GetSize()),
	m_wndwSize{ parent->GetSize() }, m_wndwPos{ parent->GetPosition()}
{
	
	this->Bind(wxEVT_ERASE_BACKGROUND, &TransparentPanel::OnPaint, this);
}

void TransparentPanel::OnPaint(wxEraseEvent& evt)
{

	wxImage image(m_wndwSize.GetX(), m_wndwSize.GetY());
	image.InitAlpha();

	unsigned char* alpha = image.GetAlpha();
	memset(alpha, wxIMAGE_ALPHA_TRANSPARENT, image.GetWidth() * image.GetHeight());

	wxGraphicsContext* gc = wxGraphicsContext::Create(image);
	gc->SetBrush(wxBrush(wxColour(0, 0, 0, 150)));
	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->DrawRectangle(m_wndwPos.x, m_wndwPos.y, m_wndwSize.GetX(), m_wndwSize.GetY());
	delete gc;
	
	wxBitmap bmp(image);
	evt.GetDC()->DrawBitmap(bmp, m_wndwPos);

}

