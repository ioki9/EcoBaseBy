#pragma once
#include <wx/wx.h>
#include <wx/dirdlg.h>
#include "MaterialButton.h"
#include "GUI_parameters.h"
class myDirPicker : public wxPanel
{
public:
	myDirPicker(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& initPath = wxEmptyString, const wxString& dialogName = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	~myDirPicker();
	wxString getDirectory() const;
	void SetPathFont(const wxFont& font);
private:
	void onBrowseBtn(wxMouseEvent& evt);
	wxString m_dlgName;
	wxFont m_fontTxtCtrl = wxFontInfo(12).FaceName("Segoe UI");
	wxTextCtrl* m_pathTxt = nullptr;
	wxString m_initPath;
};

