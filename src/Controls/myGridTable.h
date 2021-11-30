#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <map>
#include <cstdint>
#include "myGridLabelsEnum.h"
#include "myGridTableData.h"
#include "../Structs.h"
#include "../Settings.h"


class myGridTable : public wxGrid
{
public:
	myGridTable(wxWindow *parent, wxWindowID id, const wxPoint& pos , const wxSize& size );
	~myGridTable();
	bool isRowSelected();
	void getSelectedRowData(addPageInfo& info);
	std::map<Grid_label, wxString> getGridLabels();
	void updateGrid();
private:

	void AutoSizeAllColLabelSize();
	std::map< Grid_label, wxString> m_gridLabels;
	myGridTableData* m_tableData;
	wxString m_selectedRowID { "" };

	void OnCellSelect(wxGridEvent& evt);
	void DisableRangeHandler(wxGridRangeSelectEvent& evt);
	void DisableRangeSelectCellHandler(wxGridEvent& evt);
	void DisableCtrlMaiusHandler(wxGridEvent& evt);
	void DisableDraggingHandler(wxMouseEvent& evt);
	void initGridLabels();
	void SetActiveColumns();
	

	std::uint32_t m_activeCol = Settings::GetGridActiveCol();
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

		activate_all = ~0u // activate all columns
	};
};

