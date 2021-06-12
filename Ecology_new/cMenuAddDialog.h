#pragma once
#include <wx/wx.h>
#include <string.h>
#include <map>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/wxsqlite3.h>
#include <wx/pdfdoc.h>
#include <wx/valnum.h>

class cMenuAddDialog: public wxDialog
{
public:
	cMenuAddDialog(const wxString &title);
	~cMenuAddDialog();

private:
	wxTextCtrl *txtNameOwnerCtrl;
	wxTextCtrl *txtNameManufCtrl;
	wxTextCtrl *txtNameReceiverCtrl;
	wxTextCtrl *txtNameTransportCtrl;
	wxDatePickerCtrl *txtDateCtrl;
	wxTextCtrl *txtCodeCtrl;
	wxTextCtrl *txtRegNumCtrl;
	wxTextCtrl *txtAmountCtrl;
	wxTextCtrl *txtAmountFormedCtrl;
	wxTextCtrl *txtAmountReceivedOrgCtrl;
	wxTextCtrl *txtAmountReceivedPhysCtrl;
	wxTextCtrl *txtAmountUsedCtrl;
	wxTextCtrl *txtAmountDefusedCtrl;
	wxTextCtrl *txtAmountSelfstorageCtrl;
	wxTextCtrl *txtAmountBurialCtrl;
	wxTextCtrl *txtAmountTransferPurposeCtrl;
	wxTextCtrl *txtAmountTransferUsedCtrl;
	wxTextCtrl *txtAmountTransferDefusedCtrl;
	wxTextCtrl *txtAmountTransferStorageCtrl;
	wxTextCtrl *txtAmountTransferBurialCtrl;
	wxTextCtrl *txtStructUnitCtrl;
	wxTextCtrl *txtWasteNormCtrl;
	wxString m_myDate;
	float m_value{};
protected:
	void getDialogValues(wxArrayString &sArray);
	void getDialogValues(std::map<int,wxString> &map);
public:
	void onAddButton (wxCommandEvent &evt);
	void onCancelButton (wxCommandEvent &evt);
	double getValue() { return m_value; }
};



