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
	Dialog_cMainListEdit(wxWindow* parent, addPageInfo& info, wxWindowID id = -1, const wxString& title = "",
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 600),
		long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = wxDialogNameStr);
	~Dialog_cMainListEdit();
private:
    double m_amountRecVal{};
    DBMain m_db;
    wxPanel*m_mainPanel = nullptr;
	wxPanel* m_buttonPanel = nullptr;
	addPageInfo m_record;
    wxTextCtrl* m_receiverCtrl;
    wxTextCtrl* m_transporterCtrl;
    wxTextCtrl* m_ownerCtrl;
    wxTextCtrl* m_regnumCtrl;
    wxTextCtrl* m_codeCtrl;
    wxTextCtrl* m_amountReceivedCtrl;
    wxTextCtrl* m_structUnit9Ctrl;
    wxChoice* m_structUnit10Ctrl;
    wxStaticText* m_unit10Static;
    wxStaticText* m_owner;
    wxStaticText* m_recievedPhysText;
    wxChoice* m_dngLvlCtrl;
    wxChoice* m_amMovmCtrl;
    wxChoice* m_amRecCtrl;
    wxChoice* m_amMovmStructCtrl;
    wxChoice* m_structUnitChoice;
    wxRadioButton* amountFromedRadio;
    wxRadioButton* amountReceivedPhysRadio;
    wxRadioButton* amountReceivedOrgRadio;
    wxDatePickerCtrl* m_date;
    MaterialButton* m_applyButton;
    wxRadioButton* m_orgTransRadio;
    wxRadioButton* m_selfTransRadio;
    wxArrayString GetUnitChoicesArr(const wxString& exclusion = wxEmptyString);
	void OnApply(wxMouseEvent& evt);
	void OnCancel(wxMouseEvent& evt);
    void UnitChoiceChange(wxCommandEvent& evt);
    void OnAmMovmSelect(wxCommandEvent& evt);
    void OnRadioButton(wxCommandEvent& evt);
    void OnEnteredCodeExists(wxCommandEvent& evt);
    void SetValues();
    wxString GetMovementStringAndSetAmount();
};

