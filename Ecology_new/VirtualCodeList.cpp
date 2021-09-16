#include "VirtualCodeList.h"

VirtualCodeList::VirtualCodeList(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size) 
	: wxListCtrl(parent,winid,pos,size, wxLC_REPORT | wxLC_VIRTUAL)
{
	m_db.getCodeInfoList(m_items);
	SetItemCount(m_items.size());
	this->InsertColumn(0, "Код отхода");
	this->InsertColumn(1, "Норма образования");
}

VirtualCodeList::~VirtualCodeList()
{
}

wxString VirtualCodeList::OnGetItemText(long index, long column) const
{

	return m_items[index][column];
}

std::optional < std::reference_wrapper<std::vector<wxString>>> VirtualCodeList::GetSelectedItemRef()
{
	if (GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) == -1)
		return std::nullopt;

	return  std::optional < std::reference_wrapper <std::vector<wxString>> > {m_items[GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)]};
}