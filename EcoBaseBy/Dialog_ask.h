#pragma once
#include <wx/wx.h>
#include "MaterialButton.h"
#include "GUI_parameters.h"
#include "Utility.h"


class Dialog_ask : public wxDialog
{
public:
	Dialog_ask(wxWindow* parent, const wxString& title, const wxString& text, const wxString& acptBtnLabel = "Удалить",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,220),
		long style = wxDEFAULT_DIALOG_STYLE & ~(wxDEFAULT_DIALOG_STYLE), const wxString& name = wxDialogNameStr);
	~Dialog_ask();

private:
	bool m_isYesPressed{ false };
	wxWindow* m_parent = nullptr;
	wxPanel *m_mainPanel = nullptr;
	MaterialButton* m_btnYES = nullptr;
	MaterialButton* m_btnNO = nullptr;
	void OnNoButton(wxCommandEvent& evt);
	void OnYesButton(wxCommandEvent& evt);
	void OnButtonMotion(wxMouseEvent& evt);
	void OnButtonMotionOUT(wxMouseEvent& evt);
	void OnPaint(wxPaintEvent& evt);

};

