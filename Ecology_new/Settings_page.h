#pragma once
#include <wx/wx.h>
#include "VirtualOrgList.h"


class Settings_page : public wxPanel
{
public:
	Settings_page(wxWindow* parent,wxChoice* orgChoice);
	~Settings_page();
private:
	wxPanel* m_mainPanel = nullptr;
	wxChoice* m_mainOrgChoice;
	VirtualOrgList* m_orgList = nullptr;
	void OnListEditBtn(wxCommandEvent& evt);
	void OnListAddBtn(wxCommandEvent& evt);
	void OnListDeleteBtn(wxCommandEvent& evt);
};

