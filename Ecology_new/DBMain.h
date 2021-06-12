#pragma once
#include <wx/wxsqlite3.h>
#include <wx/string.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/hashmap.h>
#include <map>
#include "Global variables.h"
#include <wx/wx.h>
#include "Structs.h"

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, map_IntWxstring);

class DBMain : public wxSQLite3Database
{
public:
	DBMain();
	~DBMain();
private:
	wxSQLite3ResultSet m_rs;
	map_IntWxstring m_dbStorageColumns;
	void getStorageColumnNames();
protected:
	wxString calculateFullStorageResult(const wxString &code, const wxString &date);

public:
	wxString convertDate(const wxString &date);
	int getUniqueCodes(passportPod9Info &data);
	void getNextPod9Portion(passportPod9Info &data, const wxString &code);
	void updateDBPassport(const wxArrayString &info);
	void setMonthlyResult(const wxString &code, const wxDateTime &date);
	void getPod10TableCount(pod10Info &data);
	void getPod10TableInfo(pod10Info &data, const wxString &date);
	void getPod10TableCodeDngr(pod10Info &data,const wxArrayString &codes);
};

