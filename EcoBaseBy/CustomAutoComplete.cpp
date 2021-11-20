#include "CustomAutoComplete.h"



CustomAutoComplete::CustomAutoComplete(dbTables table, int dbColumnEnum) : wxTextCompleterSimple(), m_table{table}, m_columnEnum{dbColumnEnum}
{
    if (table == dbTables::codes)
    {
        m_getTable = &DBMain::GetActiveCodeTable;
        m_columns = m_db.GetCodesColumns();
    }
        
    else if (table == dbTables::passport)
    {
        m_getTable = &DBMain::GetActivePasspTable;
        m_columns = m_db.GetPassportColumns();
    }
        
    else
    {
        m_getTable = &DBMain::GetActiveStrgTable;
        m_columns = m_db.GetStorageColumns();
    }
    
}

CustomAutoComplete::CustomAutoComplete(CustomAutoComplete&& a) noexcept
    : m_columns{ a.m_columns },m_table{a.m_table}, m_getTable{a.m_getTable}, m_columnEnum{a.m_columnEnum }, m_resSet{a.m_resSet}
{
}

CustomAutoComplete::~CustomAutoComplete()
{
}

void CustomAutoComplete::GetCompletions(const wxString& prefix, wxArrayString& res)
{
    m_resSet = m_db.ExecuteQuery(wxS("SELECT DISTINCT " + m_columns[m_columnEnum] + " FROM " + (m_db.*m_getTable)()
        + " WHERE " + m_columns[m_columnEnum] + " LIKE '%" + prefix + "%'"));
    while (m_resSet.NextRow())
    {
        res.push_back(m_resSet.GetAsString(m_columns[m_columnEnum]));
    }
    m_resSet.Finalize();
}


void CustomAutoComplete::onChar(wxKeyEvent& evt)
{

}