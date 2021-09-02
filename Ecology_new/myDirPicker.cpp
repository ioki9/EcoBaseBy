#include "myDirPicker.h"

myDirPicker::myDirPicker(wxWindow* parent, wxWindowID id , const wxString& initPath , const wxString& dialogName , 
	const wxPoint& pos , const wxSize& size) : wxPanel(parent,id,pos,size), m_dlgName{dialogName},m_initPath{initPath}
{
	this->SetDoubleBuffered(true);

	m_pathTxt = new wxTextCtrl(this, wxID_ANY, initPath, wxDefaultPosition,wxSize(size.GetX(),size.GetY()-3));
	m_pathTxt->SetFont(m_fontTxtCtrl);
	MaterialButton* browseBtn = new MaterialButton(this, wxID_ANY, wxS("Îבחמנ..."), false,wxDefaultPosition,wxSize(75, size.GetY()));
	browseBtn->SetTextFont(wxFontInfo(11).FaceName("Segoe UI Semibold"));
	browseBtn->SetButtonColour(gui_MainColour);
	browseBtn->SetLabelColour(*wxWHITE);
	browseBtn->SetButtonRadius(0);
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(m_pathTxt, 1);
	sizer->Add(browseBtn, 0,wxLEFT,6);
	this->SetSizerAndFit(sizer);
	browseBtn->Bind(wxEVT_LEFT_UP,&myDirPicker::onBrowseBtn,this);
}


myDirPicker::~myDirPicker()
{
	
}

wxString myDirPicker::getDirectory() const
{
	return m_pathTxt->GetValue();
}

void myDirPicker::SetPathFont(const wxFont& font)
{
	m_fontTxtCtrl = font;
}



void myDirPicker::onBrowseBtn(wxMouseEvent& evt)
{
	wxDirDialog *dlg = new wxDirDialog(this, m_dlgName, m_initPath,
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	dlg->ShowModal();
	m_pathTxt->SetValue(dlg->GetPath());
	dlg->Destroy();
	
}
