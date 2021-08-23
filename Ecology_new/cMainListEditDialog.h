#pragma once
#include <wx\wx.h>
#include "MaterialButton.h"
#include "Structs.h"
#include "DBMain.h"

class cMainListEditDialog : public wxDialog
{
public:
	cMainListEditDialog(wxWindow* parent,std::vector<wxString>& item, const std::vector<wxString>& labels, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 600),
		long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxDialogNameStr);
	~cMainListEditDialog();
private:
	wxScrolledWindow *m_mainPanel = nullptr;
	wxPanel* m_buttonPanel = nullptr;
	addPageInfo m_record;
	std::vector<wxString> m_item;
	wxStaticText** m_staticText;
	wxTextCtrl** m_textCtrl;
	void OnApply(wxMouseEvent& evt);
	void OnCancel(wxMouseEvent& evt);
	void setNewItem();
};

