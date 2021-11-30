#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/platinfo.h>
#include "../Controls/MaterialButton.h"
#include "../Structs.h"
#include "../Controls/CustomCheckBox.h"
#include "MyScrolledWindow.h"




class Add_panel :
    public wxPanel
{
public:
    Add_panel(wxWindow* parent);
    ~Add_panel();

private:

    wxSize txtCtrlSize{};
    bool VerifyValues();
    //___________PAGE1____________
    void initPage1();
    wxArrayString GetUnitChoicesArr(const wxString& exclusion = "\u00AD");
    wxPanel* m_page1;
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
    CustomCheckBox* m_transDestCheckBox;
    wxRadioButton* amountFromedRadio;
    wxRadioButton* amountReceivedPhysRadio;
    wxRadioButton* amountReceivedOrgRadio;
    wxDatePickerCtrl* m_date;
    MaterialButton* m_applyButton;
    wxRadioButton* m_orgTransRadio;
    wxRadioButton* m_selfTransRadio;
    void UnitChoiceChange(wxCommandEvent& evt);
    void OnAmMovmSelect(wxCommandEvent& evt);
    void OnRadioButton(wxCommandEvent& evt);
    void OnButtonApply(wxCommandEvent& evt);
    void OnEnteredCodeExists(wxCommandEvent& evt);
    void ClearControls();
    wxBoxSizer* m_mainSizer;
    enum ID_ADD_PANEL
    {
        ID_RADIO_ORG_TRANSPORT = 100,
        ID_RADIO_SELF_TRANSPORT,
        ID_MAX
    };
};

