#pragma once
#include <wx\wx.h>
#include <string>
#include <vector>
#include <cstdint>

#include "CustomCheckBox.h"
#include "MaterialButton.h"

class ColSelectDialog : public wxDialog
{
public:
	ColSelectDialog(wxWindow *parent, uint32_t activeColFlags,wxWindowID id = -1,const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,600), 
		long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxDialogNameStr);

	uint32_t dlg_activeColFlags = 0x00000000;
	~ColSelectDialog();
private:
	wxPanel* checkBoxPanel = nullptr;
	CustomCheckBox** checkBoxes;
	wxStaticText** checkText;

	std::vector < std::string> m_labels{};
	void initLabels();
	void OnCancel(wxMouseEvent& evt);
	void OnApply(wxMouseEvent& evt);
};

