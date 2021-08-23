#pragma once
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <chrono>
#include <string>
#include <cstdint>
#include <vector>
#include <wx/pdfdoc.h>
#include <wx/pdffontmanager.h>
#include "Add_panel.h"
#include "cMenuAddDialog.h"
#include "Utility.h"
#include "VirtualListCtrl.h"
#include "MaterialButton.h"
#include "DBMain.h"
#include "cMainListEditDialog.h"
#include "GUI_parameters.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	DBMain *m_dataBase = new DBMain();

private:
	wxMenuBar* m_MenuBar = nullptr;
	wxMenu* m_menuFile = nullptr;
	wxMenu* m_menuAbout = nullptr;

	//LIST PANEL
	VirtualListCtrl* m_myList;
	wxPanel* m_listPanel = nullptr;
	wxPanel* m_listTopPanel = nullptr;
	wxPanel* m_listBottomPanel = nullptr;
	wxPanel* m_listBotRightPanel = nullptr;

	//MENU PANEL
	wxPanel* m_mainMenu = nullptr;
	wxPanel* m_dataMenuTab = nullptr;
	wxStaticText* m_dataMenuText = nullptr;
	wxBoxSizer* m_mainSizer = nullptr;

	//ADD PANEL
	wxPanel* m_addPanel = nullptr;

	wxPanel* m_formPDFPanel = nullptr;

	void onTestButton(wxCommandEvent& evt);
	void OnMenuFileAdd(wxCommandEvent& evt);
	void OnTabSwitch(wxMouseEvent& evt);
	void OnListEditButton(wxMouseEvent& evt);
	void OnListDeleteButton(wxMouseEvent& evt);
	void initListPanel();
	void initAddPanel();
	void initMainMenu();
	void initNewOrgPage();
	void initFormPDFPage();
	void OnSize(wxSizeEvent& evt);
	enum ID_MAINFRAME
	{
		ID_LIST_PANEL,
		ID_MAINMENU_PANEL,
		ID_MAINMENU_LIST_BUTTON,
		ID_MAINMENU_ADD_BUTTON,
		ID_MAXIDS
	};

	uint_fast8_t m_pageFlags = FLAGS_ACTIVE_LISTPAGE;
	enum FLAGS_ACTIVE_PAGE : char
	{
		FLAGS_NONE = 0x0,
		FLAGS_ACTIVE_LISTPAGE = 0x1,
		FLAGS_ACTIVE_ADDPAGE = 0x2

		
	};

};

