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

private:
	DBMain m_db;
	std::map<Grid_label, wxString> m_gridLabels;
	int x = 20;
	std::vector<wxString> m_rowItem;
	int m_currentItemRow = -1;
	int m_currentItemID = -1;
	int GetNumberRows() wxOVERRIDE;
	int GetNumberCols() wxOVERRIDE;
	void SetColLabelValue(int col, const wxString& label)  wxOVERRIDE;
	wxString GetColLabelValue(int col) wxOVERRIDE;
	// to access values
	wxString GetValue(int row, int col) wxOVERRIDE;
	// to set values
	void SetValue(int row, int col, const wxString& value) wxOVERRIDE;
};

