#include "VirtualOrgList.h"

VirtualOrgList::VirtualOrgList(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size) 
    : wxListCtrl(parent, winid, pos, size, wxLC_REPORT | wxLC_VIRTUAL), m_items{Settings::GetOrgArrayPtr()}
{
	SetItemCount(m_items->size());
    this->InsertColumn(0, "Название организации", 0, 428);
}

VirtualOrgList::~VirtualOrgList()
{
}

std::optional<std::reference_wrapper<organization>> VirtualOrgList::GetSelectedItemRef()
{
	if (GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) == -1)
		return std::nullopt;

	return std::optional<std::reference_wrapper<organization>> {m_items->at(GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED))};
}

wxString VirtualOrgList::OnGetItemText(long index, long column) const
{
	return m_items->at(index).name;
}

void VirtualOrgList::UpdateAfterEdit()
{
	SetItemCount(m_items->size());
}