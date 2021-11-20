#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <optional>
#include "../Database/DBMain.h"

class VirtualCodeList : public wxListCtrl
{
public:

	VirtualCodeList(wxWindow* parent, DBMain *db, const wxPoint& pos, const wxSize& size);
	~VirtualCodeList();

	bool AddNewEntry(const wxString& code, const wxString& wasteNorm);
	bool DeleteSelectedEntry();
	bool EditSelectedEntry(const wxString& code, const wxString& wasteNorm);
	std::optional < std::reference_wrapper<std::vector<wxString>>> GetSelectedItemRef();
protected:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
private:

	std::vector<std::vector<wxString>> m_items;
	DBMain *m_db;

};

