#pragma once
#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/graphics.h>
#include <wx/toplevel.h>
#include <wx/dcclient.h>
#include "Structs.h"
#include "MaterialButton.h"
#include "GUI_parameters.h"
#include "DBMain.h"

class Dialog_askDeleteEntry : public wxDialog
{
public:
	Dialog_askDeleteEntry(wxWindow* parent, const addPageInfo& info, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,220),
		long style = wxDEFAULT_DIALOG_STYLE & ~(wxDEFAULT_DIALOG_STYLE), const wxString& name = wxDialogNameStr);
	~Dialog_askDeleteEntry();

	
private:
	addPageInfo m_record;
	wxPanel *m_mainPanel = nullptr;
	MaterialButton* m_btnYES = nullptr;
	MaterialButton* m_btnNO = nullptr;
	void OnNoButton(wxCommandEvent& evt);
	void OnYesButton(wxCommandEvent& evt);
	void OnButtonMotion(wxMouseEvent& evt);
	void OnButtonMotionOUT(wxMouseEvent& evt);
	void OnPaint(wxPaintEvent& evt);

};

