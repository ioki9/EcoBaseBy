#pragma once
#include <wx/wx.h>
#include "../Controls/VirtualOrgList.h"
#include "../Controls/myDirPicker.h"


class Settings_page : public wxPanel
{
public:
	Settings_page(wxWindow* parent,wxChoice* orgChoice);
	~Settings_page();
private:
	wxPanel* m_mainPanel = nullptr;
	wxChoice* m_mainOrgChoice;
	wxWindow* m_parent;
	myDirPicker* m_dir;
	VirtualOrgList* m_orgList = nullptr;
	void OnListEditBtn(wxCommandEvent& evt);
	void OnListAddBtn(wxCommandEvent& evt);
	void OnListDeleteBtn(wxCommandEvent& evt);
	void OnDirChange(wxCommandEvent& evt);
};

