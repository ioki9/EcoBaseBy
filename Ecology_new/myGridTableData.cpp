#include "myGridTableData.h"



myGridTableData::myGridTableData(const std::map<Grid_label, wxString> &gridLables) : m_gridLabels{gridLables}
{
	m_rowItem.reserve(static_cast<int>(Grid_label::grid_max_labels)+1);
	m_rowItem.resize(static_cast<int>(Grid_label::grid_max_labels)+1);
	m_rowItem[static_cast<int>(Grid_label::grid_max_labels)] = "18";
	for (size_t i{ 0 }; i < static_cast<int>(Grid_label::grid_max_labels); ++i)
	{
		this->SetColLabelValue(i, m_gridLabels[static_cast<Grid_label>(i)]);
	}
	//m_db.fuck(hash);
	//wxMessageBox(wxString::Format("%i", hash.size()));
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
	if (!m_currentItemID)
	{
		m_currentItemID = m_db.getIdOfRow(wxString::Format("%i",row));
		m_currentItemRow = row;
		m_rowOffset = row - m_currentItemRow;
		m_isOffsetPositive = m_rowOffset > 0 ? true : false;
		m_rowOffset = m_isOffsetPositive ? m_rowOffset : m_rowOffset * -1;
		m_db.getNextRowData(m_rowItem, m_currentItemID, m_isOffsetPositive, wxString::Format("%i", m_rowOffset));
		m_currentItemID = m_rowItem.back();
	}
	if (m_currentItemRow != row)
	{
		m_rowOffset = row - m_currentItemRow;
		m_isOffsetPositive = m_rowOffset > 0 ? true : false;
		m_rowOffset = m_isOffsetPositive ? m_rowOffset : m_rowOffset * -1;
		m_db.getNextRowData(m_rowItem, m_currentItemID, m_isOffsetPositive, wxString::Format("%i", m_rowOffset));
		m_currentItemID = m_rowItem.back();
	
		m_currentItemRow = row;

	}
	return m_rowItem[col];
}
// to set values
void myGridTableData::SetValue(int row, int col, const wxString& value)
{


}

void myGridTableData::getRowData(addPageInfo &info,const wxString& id)
{
	m_db.getRowDataByID(info, id);
}

wxString myGridTableData::getSelectedRowID(int row)
{
	int rowOffset = row - m_currentItemRow;
	bool positiveOffset = m_rowOffset > 0 ? true : false;
	rowOffset = positiveOffset ? rowOffset : rowOffset * -1;
	wxString rowID = m_db.getIdByRowOffset( m_currentItemID, positiveOffset, wxString::Format("%i", rowOffset));

	return rowID;
}

