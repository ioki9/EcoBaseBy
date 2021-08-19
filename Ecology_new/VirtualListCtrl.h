#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <cstdint>

#include <wx/imaglist.h>
#include <wx/gdicmn.h> 
#include "ColSelectDialog.h"
#include "itemdata.h"

class VirtualListCtrl : public wxListCtrl
{
public:

	VirtualListCtrl(wxWindow* parent, const wxWindowID winid, const wxPoint& pos, const wxSize& size);
	~VirtualListCtrl();

	std::vector<std::vector<wxString>> m_items;

	void RefrestAfterUpdate();

protected:
	virtual wxString OnGetItemText(long index, long column) const wxOVERRIDE;
	virtual wxItemAttr* OnGetItemAttr(long item) const wxOVERRIDE;
	virtual int OnGetItemImage(long item) const wxOVERRIDE;
private:

	int skipAmount{ 0 };
	wxWindow* m_parent;
	wxFont m_font = wxFont(wxFontInfo(12).FaceName("Segoe UI"));
	bool sortAscending = true;
	wxItemAttr* m_itemAttr = new wxItemAttr(wxColour(40, 40, 40), *wxWHITE, wxFontInfo(12).FaceName("Segeo UI").AntiAliased());
	uint32_t currentColFlags = 0x00000000;
	std::vector<wxListItem> m_headerList;
	std::vector<wxString> m_headerLabels;
	wxImageList* m_imageList;
	
	void sortByColumn(int column);
	void OnColRightClick(wxListEvent& evt);
	void OnColClick(wxListEvent& evt);
	void initHeaderList();
	void setColumnWidths();
	long getFirstSelectedIndex() const;
	long findIndexOfDataIndex(long dataIndex) const;
	
public:

	void SetHeaderFont(const wxFont& font);
	std::vector<wxString>& GetSelectedItemRef();
	std::vector<wxString> GetColumnLabels();
	void SetActiveColumns(std::uint32_t activeCol);
	enum class ColumnFlags : std::uint32_t
	{
		date = 1ul << 0,
		entry_date = 1ul << 1,
		manuf = 1ul << 2,
		owner = 1ul << 3,
		receiver = 1ul << 4,
		transporter = 1ul << 5,
		code = 1ul << 6,
		regnum = 1ul << 7,
		a_formed = 1ul << 8,
		a_rec_phys = 1ul << 9,
		a_rec_org = 1ul << 10,
		am_used = 1ul << 11,
		am_defused = 1ul << 12,
		am_burial = 1ul << 13,
		am_storage = 1ul << 14,
		amt_used = 1ul << 15,
		amt_defused = 1ul << 17,
		amt_burial = 1ul << 18,
		amt_strg = 1ul << 19,
		sruct_unit = 1ul << 19,
		strg_full = 1ul << 20,
		waste_norm = 1ul << 21,
			
		activate_all = ~0ul // activate all columns
	};
};