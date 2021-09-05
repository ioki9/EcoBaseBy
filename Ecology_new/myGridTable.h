#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <map>
#include "myGridLabelsEnum.h"
#include "myGridTableData.h"

class myGridTable : public wxGrid
{
public:
	myGridTable(wxWindow *parent, wxWindowID id, const wxPoint& pos , const wxSize& size );
	~myGridTable();

private:

	void AutoSizeAllColLabelSize();
	std::map< Grid_label, wxString> m_gridLabels;
	void initGridLabels();
};

