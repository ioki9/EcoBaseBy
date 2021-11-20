#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <optional>
#include "../Database/DBMain.h"
#include "../Utility/Utility.h"

class VirtualStrgInitList : public wxListCtrl
{
public:

	VirtualStrgInitList(wxWindow* parent, DBMain *db, const wxPoint& pos, const wxSize& size);
	~VirtualStrgInitList();
	std::optional < std::reference_wrapper<std::vector<wxString>>> GetSelectedItemRef();
	bool AddNewEntry(const wxString& code, const wxDateTime& date,const wxString& strgAmount);
	bool DeleteSelectedEntry();
	bool EditSelectedEntry(const wxString& code, const wxDateTime& date, const wxString& strgAmount);
protected:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
private:


	std::vector<std::vector<wxString>> m_items;
	DBMain* m_db;
};

