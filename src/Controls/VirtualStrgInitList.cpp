#include "VirtualStrgInitList.h"

VirtualStrgInitList::VirtualStrgInitList(wxWindow* parent, DBMain* db, const wxPoint& pos, const wxSize& size)
	: wxListCtrl(parent, -1, pos, size, wxLC_REPORT | wxLC_VIRTUAL), m_db{db}
{
	m_db->getInitStorageList(m_items);
	SetItemCount(m_items.size());
	this->InsertColumn(0, "Дата", 0, 142);
	this->InsertColumn(1, "Код отхода", 0, 143);
	this->InsertColumn(2, "Хранение", 0, 143);
}

VirtualStrgInitList::~VirtualStrgInitList()
{
}

wxString VirtualStrgInitList::OnGetItemText(long index, long column) const
{

	return m_items[index][column];
}

std::optional < std::reference_wrapper<std::vector<wxString>>> VirtualStrgInitList::GetSelectedItemRef()
{
	if (GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) == -1)
		return std::nullopt;

	return  std::optional < std::reference_wrapper <std::vector<wxString>> > {m_items[GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)]};
}

bool VirtualStrgInitList::AddNewEntry(const wxString& code, const wxDateTime& date, const wxString& strgAmount)
{
	if (m_db->insertInitStorageEntry(code, date, strgAmount))
	{
		m_items.emplace_back(std::vector<wxString>{date.Format(wxS("%d.%m.%Y")), code, strgAmount});
		SetItemCount(m_items.size());
		Refresh();
		return true;
	}
	return false;
}

bool VirtualStrgInitList::DeleteSelectedEntry()
{
	if (int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED); selected != -1)
	{
		if (m_db->deleteInitStorageEntry(m_items[selected][1], m_items[selected][2]))
		{
			m_items.erase(m_items.begin() + selected);
			SetItemCount(m_items.size());
			Refresh();
			return true;
		}
	}
	return false;
}

bool VirtualStrgInitList::EditSelectedEntry(const wxString& code, const wxDateTime& date, const wxString& strgAmount)
{
	if (int selected = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED); selected != -1)
	{
		if (m_db->editInitStorageEntry(code, date, strgAmount, m_items[selected][1]))
		{
			m_items[selected][0] = date.Format(wxS("%d.%m.%Y"));
			m_items[selected][1] = code;
			m_items[selected][2] = strgAmount;
			Refresh();
			return true;
		}
	}
	return false;
}
