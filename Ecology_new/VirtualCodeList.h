#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "DBMain.h"

class VirtualCodeList : public wxListCtrl
{
public:

	VirtualCodeList(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size);
	~VirtualCodeList();

protected:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
private:
	std::optional < std::reference_wrapper<std::vector<wxString>>> GetSelectedItemRef();

	std::vector<std::vector<wxString>> m_items;
	DBMain m_db;
};

