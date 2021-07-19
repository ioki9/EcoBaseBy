#pragma once
#include <wx/wx.h>
#include "cMenuAddDialog.h"
#include <wx/listctrl.h>
#include "Global variables.h"
#include "PDF_Pod9.h"
#include "Utility.h"
#include "PDF_Journal.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:

	wxMenuBar* m_MenuBar = nullptr;
	wxMenu* menuFile;
	wxMenu* menuAbout;
	wxListCtrl* myList;
	wxPanel* mainPanel;
	void onTestButton(wxCommandEvent &evt);
	void OnMenuFileAdd(wxCommandEvent & evt);

private:
	enum PASSPORT_ID
	{
		ID_LISTCOL_ID,
		ID_LISTCOL_MANUFACTURER,
		ID_LISTCOL_OWNER,
		ID_LISTCOL_RECEIVER,
		ID_LISTCOL_TRANSPORT,
		ID_LISTCOL_CODE,
		ID_LISTCOL_REGNUM,
		ID_LISTCOL_AMOUNT,
		ID_LISTCOL_DATE,
		ID_MenuFileAdd,
		ID_TEST_BUTTON,
		ID_MAXIDS
	};

};
