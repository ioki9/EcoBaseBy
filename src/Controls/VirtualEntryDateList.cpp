#include "VirtualEntryDateList.h"

VirtualEntryDateList::VirtualEntryDateList(wxWindow* parent, DBMain* db, const wxPoint& pos, const wxSize& size) :
	wxListCtrl(parent, -1, pos, size, wxLC_REPORT | wxLC_VIRTUAL), m_db{ db }
{
	m_db->getEntryDateList(m_items);
	SetItemCount(m_items.size());
	this->InsertColumn(0, wxString::FromUTF8("Дата"), 0, 150);
	this->InsertColumn(1, wxString::FromUTF8("Дата внесения"), 0, 150);
}

VirtualEntryDateList::~VirtualEntryDateList()
{

}

bool VirtualEntryDateList::EditSelectedEntryDate(const wxString& entryDate)
{
	if (long selected{ GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) }; selected != -1)
	{
		if (m_db->editEntryDate(m_items[selected][0], entryDate))
		{
			m_items[selected][1] = entryDate;
			Refresh();
			return true;
		}
	}
	return false;
}

std::optional<std::reference_wrapper<std::vector<wxString>>> VirtualEntryDateList::GetSelectedItemRef()
{
	if (GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) == -1)
		return std::nullopt;

	return  std::optional <std::reference_wrapper <std::vector<wxString>>> {m_items[GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)]};
}

wxString VirtualEntryDateList::OnGetItemText(long index, long column) const
{
	return m_items[index][column];
}