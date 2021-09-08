#pragma once
#include <wx/wx.h>
#include <wx/wxsqlite3.h>
#include <wx/string.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <map>
#include <string>
#include <optional>
#include "Structs.h"
#include "myGridLabelsEnum.h"

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
	void updateSubsqPasspStrg(const wxString& code, const wxString& date, const wxString& diffAm, const wxString& id);
	void updateSubsqPOD10Strg(const wxString& code, const wxString& date, const wxString& diffAm, const wxString& id);
	wxString gridToDBLabel(Grid_label gridLabel);
public:

	wxString GetLastPassportID();
	bool insertInitStorageEntry();
	bool deleteEntry(const addPageInfo& info);
	bool editEntry(const addPageInfo& info);
	bool insertNewEntry(const addPageInfo& info);
	void insertFirstEntry(const addPageInfo& info);
	wxString checkFullStorage(const wxString& code);

	wxString convertDate(const wxString &date);
	int getUniqueCodes(passportPod9Info &data,const wxString& startDate,const wxString& endDate);
	void getNextPod9Portion(passportPod9Info &data, const wxString &code, const wxString& startDate, const wxString& endDate);

	void setMonthlyResult(const wxString &code, const wxDateTime &date);

	void getPod10TableCount(pod10Info &data, const wxString& startDate, const wxString& endDate);
	void getPod10TableInfo(pod10Info &data, const wxString &date);
	void getPod10TableCodeDngr(pod10Info &data,const wxArrayString &codes);

	void getJournalTableInfo(passportJournalInfo& data, const wxString& startDate, const wxString& endDate);
	void getJournalCodeInfo(passportJournalInfo& data);

	wxDateTime getFirstEntryDate();
	wxDateTime getLastEntryDate();

	int getPasspRowAmount();
	void getNextRowData(std::vector<wxString>& rowItem, const wxString& id, bool idIsHigher, const wxString& offset);
	//returns id of row by offset of last visible row
	wxString getIdByRowOffset(const wxString& id, bool idIsHigher, const wxString& offset);
	//ID should always be last in array
	void getListItemData(std::vector<std::vector<wxString>>& item);
	wxString getIdOfRow(const wxString& row);
	void getRowDataByID(addPageInfo& info, const wxString& id);
};
 