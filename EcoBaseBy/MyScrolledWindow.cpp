#include "MyScrolledWindow.h"

MyScrolledWindow::MyScrolledWindow(wxWindow* parent) : wxScrolledWindow(parent)
{
	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(MyScrolledWindow::OnSize));

}

void MyScrolledWindow::OnSize(wxSizeEvent& Event)
{
	wxScrolledWindow::HandleOnSize(Event);
	/*GetSizer()->SetDimension(0, 0, GetSize().GetWidth() - 15, 1000);*/
	Event.Skip();
}
