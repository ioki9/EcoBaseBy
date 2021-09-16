#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <map>
#include <algorithm>  
#include "DBMain.h"
#include "myGridLabelsEnum.h"


class myGridTableData : public wxGridTableBase
{
public:
	myGridTableData(const std::map< Grid_label, wxString> &gridLables );
	~myGridTableData();

	void getRowData(addPageInfo& info, const wxString& id);
	wxString getSelectedRowID(int row);
private:
	DBMain m_db;
	std::map<Grid_label, wxString> m_gridLabels;
	std::vector<wxString> m_rowItem;
	int m_currentItemRow;
	int m_currentItemRowSub;
	wxString m_currentItemID;
	wxString m_lastSortItem;
	int m_rowOffset;
	bool m_isOffsetPositive;
	int GetNumberRows() wxOVERRIDE;
	int GetNumberCols() wxOVERRIDE;
	void SetColLabelValue(int col, const wxString& label)  wxOVERRIDE;
	wxString GetColLabelValue(int col) wxOVERRIDE;
	// to access values
	wxString GetValue(int row, int col) wxOVERRIDE;
	// to set values
	void SetValue(int row, int col, const wxString& value) wxOVERRIDE;



	
};

