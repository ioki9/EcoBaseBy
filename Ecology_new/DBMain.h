#pragma once
#include <wx/wxsqlite3.h>
#include <wx/string.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/hashmap.h>
#include <map>
#include <string>
#include <wx/wx.h>
#include "Structs.h"
#include "itemdata.h"

//WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, map_IntWxstring);



class DBMain : public wxSQLite3Database
{
public:
	DBMain();
	virtual ~DBMain();
private:
	wxSQLite3ResultSet m_rs;
	std::map<wxString, std::pair<wxString,wxString>> m_codeNameDiscDng;
	std::map<int, wxString> m_dbStorageColumns;
	std::map<int, wxString> m_dbPasspColumns;
	const wxString DBPasspTableName{ "passport" };
	const wxString DBCodesTableName{ "codes" };
	const wxString DBStorageTableName{ "storageInfo" };
	const wxString DBPathPassp{ wxGetCwd() + wxS("/passdat.db") };
	void getStorageColumnNames();
	void getPassportColumnNames();
protected: 
	wxString calculateFullStorageResult(const wxString &code, const wxString &date);
	void updateSubsequentStorage(const wxString& code, const wxString& date, const wxString& diffAm);
public:
	bool insertNewEntry(const addPageInfo& info);
	void insertFirstEntry(const addPageInfo& info);
	wxString checkFullStorage(const wxString& code);

	wxString convertDate(const wxString &date);
	int getUniqueCodes(passportPod9Info &data);
	void getNextPod9Portion(passportPod9Info &data, const wxString &code);

	void setMonthlyResult(const wxString &code, const wxDateTime &date);

	void getPod10TableCount(pod10Info &data);
	void getPod10TableInfo(pod10Info &data, const wxString &date);
	void getPod10TableCodeDngr(pod10Info &data,const wxArrayString &codes);

	void getJournalTableInfo(passportJournalInfo& data, const wxString& startDate);
	void getJournalCodeInfo(passportJournalInfo& data);

	void getListItemData(std::vector<ItemData>& item);
	void getListItemData(std::vector<std::vector<wxString>>& item);
};
 