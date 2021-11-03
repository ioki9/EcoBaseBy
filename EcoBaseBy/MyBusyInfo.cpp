#include "MyBusyInfo.h"
#include "Utility.h"
#include "GUI_parameters.h"

MyBusyInfo::MyBusyInfo(wxWindow* parent,const wxString& message) : m_parent{parent}
{
    m_InfoFrame = new wxFrame(parent, wxID_ANY, wxString(),
        wxDefaultPosition, wxDefaultSize,
        wxSIMPLE_BORDER |
        wxFRAME_TOOL_WINDOW);

    wxPanel* const panel = new wxPanel(m_InfoFrame);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* title = new wxStaticText(panel, wxID_ANY, message,
            wxDefaultPosition,
            wxDefaultSize,
            wxALIGN_CENTRE);
        title->SetFont(gui_MainFont);

        sizer->Add(title, wxSizerFlags().DoubleBorder().Expand());

    // Vertically center the text in the window.
    sizer->AddStretchSpacer();


    panel->SetSizer(sizer);

    m_InfoFrame->SetCursor(*wxHOURGLASS_CURSOR);
    m_parent->SetCursor(*wxHOURGLASS_CURSOR);

    // We need to accommodate our contents, but also impose some minimal size
    // to make the busy info frame more noticeable.
    wxSize size = panel->GetBestSize();
    size.IncTo(wxSize(400, 80));

    m_InfoFrame->SetClientSize(size);
    m_InfoFrame->Layout();
    m_InfoFrame->Bind(wxEVT_PAINT, &MyBusyInfo::OnPaint, this);
    m_InfoFrame->Bind(wxEVT_LEFT_DCLICK, [&](wxMouseEvent& evt) 
        {
        m_InfoFrame->Hide(); 
        });
   
    m_InfoFrame->Centre(wxBOTH);
    m_InfoFrame->Show(true);
    m_InfoFrame->Refresh();
    m_InfoFrame->Update();
  
}

MyBusyInfo::~MyBusyInfo()
{
    m_parent->SetCursor(wxCURSOR_DEFAULT);
    m_InfoFrame->Show(false);
    m_InfoFrame->Close();
}

void MyBusyInfo::OnPaint(wxPaintEvent& evt)
{
	wxWindowDC* dc = new wxWindowDC(m_parent);
	utility::paintDarkBackground(dc, m_parent);
	delete dc;
}
