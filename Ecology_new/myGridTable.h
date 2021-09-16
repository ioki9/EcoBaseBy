#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <map>
#include <wx/graphics.h>
#include "myGridLabelsEnum.h"
#include "myGridTableData.h"
#include "Structs.h"

class myGridTable : public wxGrid
{
public:
	myGridTable(wxWindow *parent, wxWindowID id, const wxPoint& pos , const wxSize& size );
	~myGridTable();
	bool isRowSelected();
	void getSelectedRowData(addPageInfo& info);
	std::map<Grid_label, wxString> getGridLabels();
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
};

