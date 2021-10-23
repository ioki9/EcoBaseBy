#include "VirtualListCtrl.h"


VirtualListCtrl::VirtualListCtrl(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size)
	:wxListCtrl(parent, winid, pos, size, wxLC_REPORT | wxLC_VIRTUAL), m_parent{ parent }
{
	wxBitmap bmp(wxBITMAP_PNG(ICON_LIST_LINE));
	m_imageList = new wxImageList(32, 32, false);
	m_imageList->Add(bmp);
	this->SetImageList(m_imageList, wxIMAGE_LIST_SMALL);
	this->initHeaderList();

	int k{ 0 };
	for (auto it = m_headerList.begin(); it != m_headerList.end(); ++it)
	{
		currentColFlags |= (1ul << k);
		this->InsertColumn(k, *it);
		
		k += 1;
	}
	setColumnWidths();
	this->Bind(wxEVT_LIST_COL_CLICK, &VirtualListCtrl::OnColClick, this);
	this->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &VirtualListCtrl::OnColRightClick, this);
}





VirtualListCtrl::~VirtualListCtrl()
{
	m_headerList.clear();
	m_headerLabels.clear();
	for (auto& i : m_items)
	{
		i.clear();
	}
	m_items.clear();
	delete m_itemAttr;
	delete m_imageList;
}


void VirtualListCtrl::RefrestAfterUpdate()
{
	
	this->SetItemCount(m_items.size());
	this->Refresh();
}

wxString VirtualListCtrl::OnGetItemText(long index, long column) const
{
	wxListItem item;
	item.SetMask(wxLIST_MASK_TEXT);
	GetColumn(column, item);
	auto found = std::find(m_headerLabels.begin(), m_headerLabels.end(), item.GetText());
	if (found != m_headerLabels.end())
		return m_items[index][std::distance(m_headerLabels.begin(),found)];
	return "";

}

int VirtualListCtrl::OnGetItemImage(long item) const
{
	return 0;
}

void VirtualListCtrl::sortByColumn(int column)
{

	static auto genericNumCompare = [](auto i1, auto i2, bool ascending) {
		if (ascending)
		{
			if (i1.length() > i2.length())
				return true;
			if (i2.length() > i1.length())
				return false;
			else
				return (i1 > i2);
		}
		else
		{
			if (i1.length() < i2.length())
				return true;
			if (i2.length() < i1.length())
				return false;
			else
				return (i1 < i2);
		}
	};
	static auto genericCompare = [](auto i1, auto i2, bool ascending) {
		return ascending ? i1 < i2 : i1> i2;
	};


	bool ascending = this->sortAscending;

	std::sort(m_items.begin(), m_items.end(), [&column, &ascending](std::vector<wxString> i1, std::vector<wxString> i2) {
		switch (column) {
		case 0:
			return genericCompare(i1[0], i2[0], ascending);
		case 1:
			return genericCompare(i1[1], i2[1], ascending);
		case 2:
			return genericCompare(i1[2], i2[2], ascending);
		default:
			return false;
		}
	});
}


wxItemAttr* VirtualListCtrl::OnGetItemAttr(long item) const
{
	return m_itemAttr;
}

long VirtualListCtrl::getFirstSelectedIndex() const 
{
	return GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

long VirtualListCtrl::findIndexOfDataIndex(long dataIndex) const
{
	return std::find_if(m_items.begin(), m_items.end(), [dataIndex](std::vector<wxString> i) {return wxAtoi(i[0]) == dataIndex;}) - m_items.begin();
}

void VirtualListCtrl::OnColClick(wxListEvent& evt)
{

	auto selectedIndex = getFirstSelectedIndex();
	long selectedDataIndex;

	if (selectedIndex != -1)
	{
		selectedDataIndex = wxAtoi(this->m_items[selectedIndex][0]);
		this->SetItemState(selectedIndex, 0, wxLIST_STATE_SELECTED);
	}
	this->sortByColumn(evt.GetColumn());
	this->RefrestAfterUpdate();

	if (selectedIndex != -1)
	{
		long indexToSelect = findIndexOfDataIndex(selectedDataIndex);
		this->SetItemState(indexToSelect, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
		this->EnsureVisible(indexToSelect);
	}
	this->sortAscending = !this->sortAscending;
}

void VirtualListCtrl::initHeaderList()
{
	m_headerLabels.push_back("Рег. №");
	m_headerLabels.push_back("Дата");
	m_headerLabels.push_back("Поступило от орг.");
	m_headerLabels.push_back("Получатель отходов");
	m_headerLabels.push_back("Перевозчик отходов");
	m_headerLabels.push_back("Код отходов");
	m_headerLabels.push_back("Образовалось, т.(шт.)");
	m_headerLabels.push_back("Поступило от физ. лиц, т.(шт.)");
	m_headerLabels.push_back("Поступило от др. орг., т.(шт.)");
	m_headerLabels.push_back("Использовано, т.(шт.)");
	m_headerLabels.push_back("Обезврежено, т.(шт.)");
	m_headerLabels.push_back("Направлено на хранение, т.(шт.)");
	m_headerLabels.push_back("Захоронено, т.(шт.)");
	m_headerLabels.push_back("Передано на использование, т.(шт.)");
	m_headerLabels.push_back("Передано на обезвреживание, т.(шт.)");
	m_headerLabels.push_back("Передано на хранение, т.(шт.)");
	m_headerLabels.push_back("Передано на захоронение, т.(шт.)");
	m_headerLabels.push_back("Хранится суммарно, т.(шт.)");
	m_headerLabels.push_back("Структурные подразделения (ПОД 10)");
	m_headerLabels.push_back("Структурные подразделения (ПОД 9)");
	int count{ 0 };
	for (auto it = m_headerLabels.begin(); it != m_headerLabels.end(); ++it)
	{
		wxListItem item{};
		item.SetText(*it);
		item.SetFont(m_font);
		item.SetId(count);
		item.SetWidth(100);
		m_headerList.push_back(item);
		++count;
	}
}

void VirtualListCtrl::OnColRightClick(wxListEvent& evt)
{

	Dialog_ListColumnSelect* dialog = new Dialog_ListColumnSelect(this, currentColFlags);
	currentColFlags = dialog->dlg_activeColFlags;
	dialog->Destroy();
	
	SetActiveColumns(currentColFlags);
}

void  VirtualListCtrl::SetActiveColumns(std::uint32_t activeCol)
{
	this->DeleteAllColumns();
	for (size_t i{ 0 }; i < 32; ++i)
	{
		if (activeCol & (1ul << i))
		{
			this->InsertColumn(i, m_headerList[i]);
			//this->SetColumnWidth(i, 100);
		}
	}
	this->Refresh();
}

void VirtualListCtrl::SetHeaderFont(const wxFont& font)
{
	wxItemAttr item;
	item.SetFont(font);
	this->SetHeaderAttr(item);
}

std::optional < std::reference_wrapper<std::vector<wxString>>> VirtualListCtrl::GetSelectedItemRef()
{
	if (GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED) == -1)
		return std::nullopt;
	
	return  std::optional < std::reference_wrapper <std::vector<wxString>> > { m_items[GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)]};
}

std::vector<wxString> VirtualListCtrl::GetColumnLabels()
{

	return m_headerLabels;
}

void VirtualListCtrl::setColumnWidths()
{
	for (int i{ 0 }; i < GetColumnCount(); ++i)
	{
		this->SetColumnWidth(i, 100);
	}
	this->Refresh();
}