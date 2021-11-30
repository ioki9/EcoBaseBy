#include "VirtualCodeList.h"

VirtualCodeList::VirtualCodeList(wxWindow* parent, DBMain *db, const wxPoint& pos, const wxSize& size) 
	: wxListCtrl(parent,-1,pos,size, wxLC_REPORT | wxLC_VIRTUAL), m_db{db}
{
	m_db->getCodeInfoList(m_items);
	SetItemCount(m_items.size());
	this->InsertColumn(0, "Код отхода",0, 214);
	this->InsertColumn(1, "Норма образования",0,214);
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

bool VirtualCodeList::AddNewEntry(const wxString& code, const wxString& wasteNorm)
{
	short result{ m_db->AddCodeInfoEntry(code, wasteNorm) };
	switch( result)
	{
		case 0:
		{
			return false;
		}
		case 1:
		{
			m_items.emplace_back(std::vector<wxString>{code, wasteNorm});
			SetItemCount(m_items.size());
			Refresh();
			return true;
		}
		case 2:
		{
			for (auto& row : m_items)
			{
				if (row[0] == code)
				{
					row[1] = wasteNorm;
					Refresh();
					return true;
				}
					
			}
		}
	}
	return false;
	
}

bool VirtualCodeList::DeleteSelectedEntry()
{
	if (long selected{ GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) }; selected != -1)
	{
		if (m_db->DeleteCodeInfoEntry(m_items[selected][0]))
		{
			m_items.erase(m_items.begin() + selected);
			SetItemCount(m_items.size());
			Refresh();
			return true;
		}
	}
	return false;
}

bool VirtualCodeList::EditSelectedEntry(const wxString& code, const wxString& wasteNorm)
{
	if (long selected{ GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) }; selected != -1)
	{
		if (m_db->EditCodeInfoEntry(m_items[selected][0],code, wasteNorm))
		{
			m_items[selected][0] = code;
			m_items[selected][1] = wasteNorm;
			Refresh();
			return true;
		}
	}
	return false;
}
