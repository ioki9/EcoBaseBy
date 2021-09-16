#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include "GUI_parameters.h"
#include "MaterialButton.h"
#include "Dialog_OrgAddEdit.h"

class Settings_page : public wxPanel
{
public:
	Settings_page(wxWindow* parent);
	~Settings_page();
private:
	wxPanel* m_mainPanel = nullptr;
	wxListBox* m_orgList = nullptr;
	void OnListEditBtn(wxCommandEvent& evt);
};

