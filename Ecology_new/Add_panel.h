#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/datectrl.h>
#include <wx/valnum.h>
#include <wx/radiobut.h>
#include "MaterialButton.h"
#include "CustomCheckBox.h"
#include "Utility.h"
#include "cMain.h"
#include "Structs.h"
#include "VirtualListCtrl.h"


class cMain;


class Add_panel :
    public wxPanel
{
public:
    Add_panel(wxWindow* parent, std::vector<std::vector<wxString>>* listItems);
    ~Add_panel();

private:


    std::vector<std::vector<wxString>> *m_listItems;
    void addItem(const wxString& id);

    addPageInfo m_record;
    float m_validatorValue;
    wxSize txtCtrlSize = wxSize(500, 30);

    //___________PAGE1____________
    void initPage1();
    wxPanel* m_page1;
    wxTextCtrl* m_receiverCtrl;
    wxTextCtrl* m_transporterCtrl;
    wxTextCtrl* m_ownerCtrl;
    wxTextCtrl* m_regnumCtrl;
    wxTextCtrl* m_codeCtrl;
    wxTextCtrl* m_amountReceivedCtrl;
    wxRadioButton* amountFromedRadio;
    wxRadioButton* amountReceivedPhysRadio;
    wxRadioButton* amountReceivedOrgRadio;
    wxDatePickerCtrl* m_date;
    MaterialButton* p1_buttonNext;
    void OnP1_ButtonNext(wxCommandEvent& evt);
    
    //___________PAGE2____________
    void initPage2();
    wxPanel* m_page2;
    wxTextCtrl* m_amUsedCtrl;
    wxTextCtrl* m_amDefusedCtrl;
    wxTextCtrl* m_amStorageCtrl;
    wxTextCtrl* m_amBurialCtrl;
    wxTextCtrl* m_tamUsedCtrl;
    wxTextCtrl* m_tamDefusedCtrl;
    wxTextCtrl* m_tamStorageCtrl;
    wxTextCtrl* m_tamBurialCtrl;
    MaterialButton* p2_buttonNext;
    MaterialButton* p2_buttonPrevious;
    void OnP2_ButtonNext(wxCommandEvent& evt);
    void OnP2_ButtonPrev(wxCommandEvent& evt);

    //___________PAGE3____________
    void initPage3();
    wxPanel* m_page3;
    MaterialButton* p3_buttonNext;
    MaterialButton* p3_buttonPrevious;
    wxTextCtrl* m_structUnit10Ctrl;
    wxTextCtrl* m_structUnit9Ctrl;
  
   

    void OnP3_ButtonNext(wxCommandEvent& evt);
    void OnP3_ButtonPrev(wxCommandEvent& evt);
    //__________RESULT PAGE________
    void initResultPage();
    wxPanel* m_resultPage;
    wxPanel* m_rButtonPanel;
   
    MaterialButton* pr_buttonPrevious;
    MaterialButton* pr_buttonApply;
    wxScrolledWindow* pr_mainPanel;
    void OnPR_ButtonApply(wxCommandEvent& evt);
    void OnPR_ButtonPrevious(wxCommandEvent& evt);



    wxFont m_textFont = wxFontInfo(14).FaceName("Segoe UI");
    void OnPaint(wxPaintEvent& evt);
    wxBoxSizer* mainSizer;
    enum ID_ADD_PANEL
    {
        ID_PAGE1 = 100,
        ID_PAGE1_REGNUMTXT,
        ID_PAGE1_RECEIVERTXT,
        ID_PAGE1_OWNERTXT,
        ID_PAGE1_MANUFACTURERTXT,
        ID_PAGE1_TRANSPORTERTXT,
        ID_PAGE1_CALENDAR_DATE,
        ID_PAGE1_CALENDAR_ENTRYDATE,
        ID_PAGE1_AMOUNTTXT,
        ID_PAGE1_AMOUNTRADIO,
        ID_PAGE1_CODETXT,
        ID_PAGE1_BUTTON_NEXT,
        ID_PAGE1_BUTTON_PREVIOUS,
        ID_PAGE2,
        ID_PAGE3,
        ID_MAX
    };
};

