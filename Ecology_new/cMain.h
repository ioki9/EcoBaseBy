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
#include <wx/filepicker.h>
#include "Add_panel.h"
#include "cMenuAddDialog.h"
#include "Utility.h"
#include "VirtualListCtrl.h"
#include "MaterialButton.h"
#include "DBMain.h"
#include "cMainListEditDialog.h"
#include "myDirPicker.h"
#include "GUI_parameters.h"
#include "MainMenuTabButton.h"



class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	DBMain *m_dataBase = new DBMain();

private:


	//LIST PANEL
	VirtualListCtrl* m_myList;
	wxPanel* m_listPanel = nullptr;
	wxPanel* m_listTopPanel = nullptr;
	wxPanel* m_listBottomPanel = nullptr;
	void initListPanel();

	//MENU PANEL
	wxPanel* m_mainMenu = nullptr;
	wxWindow* m_activePanel = nullptr;
	MainMenuTabButton* m_menuButtonList = nullptr;
	MainMenuTabButton* m_menuButtonAdd = nullptr;
	MainMenuTabButton* m_menuButtonForm = nullptr;
	std::vector<MainMenuTabButton*> m_allMenuButtons;
	wxBoxSizer* m_mainSizer = nullptr;
	int m_mainMenuWidth = 270;
	void initMainMenu();
	//sets all menu buttons inactive, to then activate the one we need
	void setAllMenuBtnInactive();
	void setActiveButton(MainMenuTabButton* activeBtn);
	//changes the active page by hiding, deataching old one and showing,ataching new one
	void changeActivePage(wxWindow* newPage);

	//ADD PANEL
	wxPanel* m_addPanel = nullptr;
	void initAddPanel();

	//FORM PDF PANEL
	void initFormPDFPage();
	wxScrolledWindow* m_formPDFPanel = nullptr;
	myDirPicker* m_dir_pod10 = nullptr;
	myDirPicker* m_dir_journal = nullptr;
	myDirPicker* m_dir_pod9 = nullptr;
	wxDatePickerCtrl* m_date1_pod9 = nullptr;
	wxDatePickerCtrl* m_date2_pod9 = nullptr;
	wxDatePickerCtrl* m_date1_pod10 = nullptr;
	wxDatePickerCtrl* m_date2_pod10 = nullptr;
	wxDatePickerCtrl* m_date1_journal = nullptr;
	wxDatePickerCtrl* m_date2_journal = nullptr;

	//EVENTS
	void onTestButton(wxCommandEvent& evt);
	void OnMenuFileAdd(wxCommandEvent& evt);
	void OnTabSwitch(wxCommandEvent& evt);
	void OnListEditButton(wxCommandEvent& evt);
	void OnListDeleteButton(wxCommandEvent& evt);
	void OnFromPDFButton(wxCommandEvent& evt);
	void OnSize(wxSizeEvent& evt);


	
	void initNewOrgPage();



	enum ID_MAINFRAME
	{
		ID_LIST_PANEL=800,
		ID_MAINMENU_PANEL,
		ID_MAINMENU_LIST_BUTTON,
		ID_MAINMENU_ADD_BUTTON,
		ID_MAINMENU_FORM_BUTTON,
		ID_FORMPDF_POD9_BUTTON,
		ID_FORMPDF_POD10_BUTTON,
		ID_FORMPDF_JOURNAL_BUTTON,
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

