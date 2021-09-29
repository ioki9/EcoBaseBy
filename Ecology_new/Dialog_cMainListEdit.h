#pragma once
#include <wx\wx.h>
#include <wx/datetime.h>
#include "MaterialButton.h"
#include "Structs.h"
#include "DBMain.h"
#include "myGridLabelsEnum.h"
#include "GUI_parameters.h"
#include <wx/datectrl.h>

class Dialog_cMainListEdit : public wxDialog
{
public:
	Dialog_cMainListEdit(wxWindow* parent, addPageInfo& info, const std::map<Grid_label, wxString>& gridLabels, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 600),
		long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxDialogNameStr);
	~Dialog_cMainListEdit();
private:
	wxScrolledWindow *m_mainPanel = nullptr;
	wxPanel* m_buttonPanel = nullptr;
	addPageInfo m_record;
	wxTextCtrl* m_valueRegnum;
	wxDatePickerCtrl* m_valueDate;
	wxTextCtrl* m_valueCode;
	wxTextCtrl* m_valueOwner;
	wxTextCtrl* m_valueReceiver;
	wxTextCtrl* m_valueTransporter;
	wxTextCtrl* m_valueAmount_formed;
	wxTextCtrl* m_valueamount_received_phys;
	wxTextCtrl* m_valueamount_received_org;
	wxTextCtrl* m_valueamount_used;
	wxTextCtrl* m_valueamount_defused;
	wxTextCtrl* m_valueamount_burial;
	wxTextCtrl* m_valueamount_storage;
	wxTextCtrl* m_valueamount_tUsed;
	wxTextCtrl* m_valueamount_tDefused;
	wxTextCtrl* m_valueamount_tBurial;
	wxTextCtrl* m_valueamount_tStorage;
	wxTextCtrl* m_valuestruct_unitPOD9;
	wxTextCtrl* m_valuestruct_unitPOD10;
	wxTextCtrl* m_valuewaste_norm;
	void OnApply(wxMouseEvent& evt);
	void OnCancel(wxMouseEvent& evt);
	void setNewItem();
};

