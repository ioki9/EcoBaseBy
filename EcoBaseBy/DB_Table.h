#pragma once
#include "wx/wxsqlite3.h"
#include <utility>
#include <vector>


template <typename T>
class DB_Table
{
private:
	size_t m_numColumns{0};
public:
	//function takes parameter std::tuple<column name, value, value type>
	wxSQLite3Statement insertData(wxSQLite3Database *db, const wxString &tableName, std::vector<std::tuple<wxString, wxString, T>> column);
	//function takes parameter std::tuple<column name, value, value type>
	wxSQLite3Statement insertData(wxSQLite3Database *db, const wxString &tableName, std::tuple<wxString, wxString, T> column);

	
};

