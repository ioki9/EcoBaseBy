#include "myGridTableData.h"



myGridTableData::myGridTableData(const std::map<Grid_label, wxString> &gridLables) : m_gridLabels{gridLables}
{
	m_rowItem.reserve(static_cast<int>(Grid_label::grid_max_labels) + 1);
	m_rowItem.resize(static_cast<int>(Grid_label::grid_max_labels) + 1);

	for (size_t i{ 0 }; i < static_cast<int>(Grid_label::grid_max_labels); ++i)
	{
		this->SetColLabelValue(i, m_gridLabels[static_cast<Grid_label>(i)]);
	}
}

myGridTableData::~myGridTableData()
{
}


int myGridTableData::GetNumberRows()
{
	return m_db.getPasspRowAmount();
}
int myGridTableData::GetNumberCols()
{
	return static_cast<int>(Grid_label::grid_max_labels);
}
void myGridTableData::SetColLabelValue(int col, const wxString& label)
{
	m_gridLabels[static_cast<Grid_label>(col)] = label;
}
wxString myGridTableData::GetColLabelValue(int col)
{
	
	return m_gridLabels[static_cast<Grid_label>(col)];
}
// to access values
wxString myGridTableData::GetValue(int row, int col)
{
	if (m_rowItem.empty() || m_currentItemRow != row)
	{
		m_db.getNextRowData(m_rowItem, wxString::Format("%i", row));
		m_currentItemRow = row;
	}
	return m_rowItem[col];
}
// to set values
void myGridTableData::SetValue(int row, int col, const wxString& value)
{


}
