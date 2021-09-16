#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include "Settings.h"
#include "VirtualCodeList.h"
#include "GUI_parameters.h"

class Dialog_OrgAddEdit : public wxDialog
{
public:
	Dialog_OrgAddEdit(wxWindow* parent,bool isAddDialog, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 220),
		long style = wxDEFAULT_DIALOG_STYLE & ~(wxDEFAULT_DIALOG_STYLE), const wxString& name = wxDialogNameStr);
	~Dialog_OrgAddEdit();
private:
	bool m_isAddDialog;
	wxPanel* m_mainPanel = nullptr;
	wxPanel* m_buttonPanel;
	wxPanel* headerPanel;
	wxTextCtrl* m_orgName;
	wxTextCtrl* m_orgAddress;
	wxTextCtrl* m_orgUnp;
	wxScrolledWindow* m_1stPage;
	wxScrolledWindow* m_2ndPage = nullptr;
	VirtualCodeList* m_wasteNormList;
	wxBoxSizer* m_mainSizer;

	wxPoint mLastPt;
	bool dragging{ false };
	int x, y;

	bool m_isDrawn{ false };
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLeave(wxMouseEvent& event);
	void OnMouseLDown(wxMouseEvent& event);
	void OnMouseLUp(wxMouseEvent& event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
	void paintDarkBackground(wxWindowDC* dc);
	void onPaint(wxPaintEvent& evt);
};

