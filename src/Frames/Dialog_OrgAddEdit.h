#pragma once
#include <wx/wx.h>
#include <vector>
#include "../Controls/VirtualCodeList.h"
#include "../Controls/VirtualStrgInitList.h"
#include "../Database/DBMain.h"
#include "../Settings.h"


class Dialog_OrgAddEdit : public wxDialog
{
public:
	Dialog_OrgAddEdit(wxWindow* parent,organization* org, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 220),
		long style = wxDEFAULT_DIALOG_STYLE & ~(wxDEFAULT_DIALOG_STYLE), const wxString& name = wxDialogNameStr);
	~Dialog_OrgAddEdit();
private:
	wxWindow* m_parent = nullptr;

	organization m_org;
	wxPanel* m_mainPanel = nullptr;
	wxPanel* m_buttonPanel;
	wxPanel* headerPanel;
	wxTextCtrl* m_orgName;
	wxTextCtrl* m_orgAddress;
	wxTextCtrl* m_orgUnp;
	wxScrolledWindow* m_1stPage;
	wxScrolledWindow* m_2ndPage = nullptr;
	VirtualCodeList* m_wasteNormList;
	VirtualStrgInitList* m_strgList;
	wxListCtrl* m_unitList;
	wxBoxSizer* m_mainSizer;
	DBMain m_db;
	
	bool m_firstStartCanceled{ false };
	bool m_isDrawn{ false };
	bool m_openedAsEdit{};
	void OnCancel(wxCommandEvent& evt);
	void OnApply(wxCommandEvent& evt);
	void onPaint(wxPaintEvent& evt);

	void OnWasteListEdit(wxCommandEvent& evt);
	void OnWasteListDelete(wxCommandEvent& evt);
	void OnWasteListAdd(wxCommandEvent& evt);

	void OnStorageListEdit(wxCommandEvent& evt);
	void OnStorageListDelete(wxCommandEvent& evt);
	void OnStorageListAdd(wxCommandEvent& evt);

	void OnUnitListEdit(wxCommandEvent& evt);
	void OnUnitListDelete(wxCommandEvent& evt);
	void OnUnitListAdd(wxCommandEvent& evt);

};

