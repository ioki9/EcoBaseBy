#pragma once
#include <wx/wx.h>
#include <wx/config.h>
#include <wx/filepicker.h>
#include <string>
#include <cstdint>
#include <vector>
#include "../Controls/MainMenuTabButton.h"
#include "../Controls/myDirPicker.h"
#include "../Controls/MaterialButton.h"
#include "../Controls/myGridTable.h"
#include "Settings_page.h"
#include "Add_panel.h"
#include "../Database/DBMain.h"





class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	void tryEvent(wxCommandEvent& evt);


private:


	DBMain* m_dataBase = new DBMain();

	//LIST PANEL
	wxPanel* m_listPanel = nullptr;
	wxPanel* m_listTopPanel = nullptr;
	wxPanel* m_listBottomPanel = nullptr;
	MaterialButton* m_deleteButton;
	wxBoxSizer* m_listMainSizer;
	myGridTable* m_grid = nullptr;
	void initListPanel();
	void OnOrgChanged(wxCommandEvent& evt);
	void OnOrgSelect(wxCommandEvent& evt);
	void OnUnitSelect(wxCommandEvent& evt);
	void UpdateOrgChoices();
	//MENU PANEL
	wxChoice* m_orgChoice;
	wxChoice* m_unitChoice;
	wxStaticText* m_unitText;
	wxStaticText* m_orgText;
	wxPanel* m_mainMenu = nullptr;
	wxWindow* m_activePanel = nullptr;
	MainMenuTabButton* m_menuButtonList = nullptr;
	MainMenuTabButton* m_menuButtonAdd = nullptr;
	MainMenuTabButton* m_menuButtonForm = nullptr;
	MainMenuTabButton* m_menuButtonSetting = nullptr;
	std::vector<MainMenuTabButton*> m_allMenuButtons;
	wxBoxSizer* m_mainSizer = nullptr;
	int m_mainMenuWidth = 270;
	void initMainMenu();
	//sets all menu buttons inactive, to then activate the one we need
	void setAllMenuBtnInactive();
	void setActiveMenuButton(MainMenuTabButton* activeBtn);
	//changes the active page by hiding, deataching old one and showing,ataching new one
	void changeActivePage(wxWindow* newPage);

	//ADD PANEL
	Add_panel* m_addPanel = nullptr;
	void initAddPanel();

	//FORM PDF PANEL
	void initFormPDFPage();
	wxScrolledWindow* m_formPDFPanel = nullptr;
	wxDatePickerCtrl* m_date1_pod9 = nullptr;
	wxDatePickerCtrl* m_date2_pod9 = nullptr;
	wxDatePickerCtrl* m_date1_pod10 = nullptr;
	wxDatePickerCtrl* m_date2_pod10 = nullptr;
	wxDatePickerCtrl* m_date1_journal = nullptr;
	wxDatePickerCtrl* m_date2_journal = nullptr;
	wxDateTime m_firstDate;
	wxDateTime m_lastDate;

	//SETTING PANEL
	void initSettingsPage();
	Settings_page* m_settingsPage = nullptr;


	//EVENTS
	void OnTabSwitch(wxCommandEvent& evt);
	void OnListEditButton(wxCommandEvent& evt);
	void OnListDeleteButton(wxCommandEvent& evt);
	void PostOrgEvents(wxCommandEvent& evt);
	void OnDbChange(wxCommandEvent& evt);
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
		ID_MAINMENU_SETTINGS_BUTTON,
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

