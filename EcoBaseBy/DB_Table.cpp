#include "DB_Table.h"

//template <typename T>
//wxSQLite3Statement insertData(wxSQLite3Database *db, const wxString &tableName, std::vector<std::tuple<wxString, wxString, T>> column)
//{
//	for (column::const_iterator i = column.begin(); i != column.end(); i++)
//	{
//		db->PrepareStatement("INSERT INTO " + tableName + "(" + std::get<0>(*i)+") VALUES " )
//	}
//
//	wxSQLite3Statement st = db;
//	return st;
//}