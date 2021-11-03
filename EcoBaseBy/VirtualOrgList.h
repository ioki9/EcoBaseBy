#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <optional>
#include "Settings.h"

class VirtualOrgList : public wxListCtrl
{
public:
	VirtualOrgList(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size);
	~VirtualOrgList();
	std::optional<std::reference_wrapper<organization>> GetSelectedItemRef();
	void UpdateAfterEdit();
private:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
	std::vector<organization>* m_items;
};

