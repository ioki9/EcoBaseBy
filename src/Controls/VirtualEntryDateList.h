#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <optional>
#include "../Database/DBMain.h"

class VirtualEntryDateList : public wxListCtrl
{
public:

	VirtualEntryDateList(wxWindow* parent, DBMain* db, const wxPoint& pos, const wxSize& size);
	~VirtualEntryDateList();

	bool EditSelectedEntryDate(const wxString& entryDate);
	std::optional < std::reference_wrapper<std::vector<wxString>>> GetSelectedItemRef();
protected:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
private:

	std::vector<std::vector<wxString>> m_items;
	DBMain* m_db;

};
