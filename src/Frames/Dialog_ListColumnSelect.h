#pragma once
#include <wx\wx.h>
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include "../Controls/CustomCheckBox.h"
#include "../Controls/MaterialButton.h"
#include "../Controls/myGridLabelsEnum.h"

class Dialog_ListColumnSelect : public wxDialog
{
public:
	Dialog_ListColumnSelect(wxWindow *parent, const std::map<Grid_label, wxString>& grid_labels, uint32_t activeColFlags,wxWindowID id = -1,const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,600), 
		long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxDialogNameStr);

	uint32_t dlg_activeColFlags = 0x00000000;
	~Dialog_ListColumnSelect();
private:
	wxPanel* checkBoxPanel = nullptr;
	CustomCheckBox** checkBoxes;
	wxStaticText** checkText;

	std::map<Grid_label, wxString> m_gridLabels;
	void initLabels();
	void OnCancel(wxMouseEvent& evt);
	void OnApply(wxMouseEvent& evt);
};

