#pragma once
#include <wx/wx.h>
#include <wx/wxsqlite3.h>
#include <wx/string.h>
#include <map>
#include <string>
#include "myGridLabelsEnum.h"
#include "Structs.h"




class DBMain : public wxSQLite3Database
{
public:
	DBMain();
	virtual ~DBMain();
private:
	wxSQLite3ResultSet m_rs;
	int m_activeOrg{ -1 };
	std::map<int,wxString> m_codesColumns;
	std::map<int, wxString> m_storageColumns;
	std::map<int, wxString> m_passpColumns;
	std::map<int, wxString> m_codeInfoColumns;
	wxString DBPasspTableName { "passport" };
	wxString DBCodesTableName { "codes" };
	wxString DBStorageTableName { "storageInfo" };
	wxString DBCodeInfoTableName { "codeInfo" };
	wxString DBPathPassp{ wxGetCwd() + wxS("/passdat.db") };

	
	


	void getStorageColumnNames();
	void getPassportColumnNames();
	void getCodeInfoColumnNames();
protected: 
	void updateSubsqPasspStrg(const wxString& code, const wxString& date);
	void updateSubsqPOD10Strg(const wxString& code, const wxString& date, const wxString& diffAm, const wxString& id);
	wxString gridToDBLabel(Grid_label gridLabel);
public:
	wxString GetMovmStringFromDepend(const wxString& dependency);
	bool IsCodeExists(const wxString& code);
	wxString GetDngFromCode(const wxString& code);
	wxArrayString GetAllPossibleCodes();
	wxString GetActiveCodeTable();
	wxString GetActivePasspTable();
	wxString GetActiveStrgTable();
	wxString GetActiveCodeInfoTable();
	std::map<int, wxString> GetCodesColumns();
	std::map<int, wxString> GetStorageColumns();
	std::map<int, wxString> GetPassportColumns();
	std::map<int, wxString> GetCodeInfoColumns();
	bool CreateOrgTables(const wxString& orgId);
	void SetOrg(int orgId);
	void SetActiveOrg();

	wxString GetLastPassportID();
	bool insertInitStorageEntry(const wxString& code, const wxDateTime& date, const wxString& amount);
	bool editInitStorageEntry(const wxString& code, const wxDateTime& date, const wxString& amount, const wxString& oldCode);
	bool deleteInitStorageEntry(const wxString& code, const wxString& storage);
	bool deleteEntry(const addPageInfo& info);
	bool editEntry(const addPageInfo& info, bool willHaveDepend);
	bool insertNewEntry(const addPageInfo& info);
	bool insertNewDoubleEntry(const addPageInfo& info);
	void insertFirstEntry(const addPageInfo& info);
	wxString checkFullStorage(const wxString& code);

	wxString convertDate(const wxString &date);
	int getUniqueCodes(passportPod9Info &data,const wxString& startDate,const wxString& endDate);
	void getNextPod9Portion(passportPod9Info &data, const wxString &code, const wxString& startDate, const wxString& endDate);

	void getPod10TableCount(pod10Info &data, const wxString& startDate, const wxString& endDate);
	void getPod10TableInfo(pod10Info &data, const wxString &date);
	void getPod10TableCodeDngr(pod10Info &data,const wxArrayString &codes);

	void getJournalTableInfo(passportJournalInfo& data, const wxString& startDate, const wxString& endDate);

	wxDateTime getFirstEntryDate();
	wxDateTime getFirstEntryByCodeNoInit(const wxString& code);
	wxDateTime getLastEntryDate();

	int getPasspRowAmount();
	void getNextRowData(std::vector<wxString>& rowItem, const wxString& id, bool idIsHigher, const wxString& offset);
	//returns id of row by offset of last visible row
	wxString getIdByRowOffset(const wxString& id, bool idIsHigher, const wxString& offset);
	//ID should always be last in array
	void getListItemData(std::vector<std::vector<wxString>>& item);
	wxString getIdOfRow(const wxString& row);
	void getRowDataByID(addPageInfo& info, const wxString& id);

	bool AskToEnterAllEntryDates(const wxString& startDate,const wxString& endDate);

	void getInitStorageList(std::vector<std::vector<wxString>>& list);
	void getCodeInfoList(std::vector<std::vector<wxString>>& list);
	int getCodeInfoRowAmount();
	wxString GetWasteNormByCode(const wxString& code);

	short AddCodeInfoEntry(const wxString& code, const wxString& wasteNorm);
	bool DeleteCodeInfoEntry(const wxString& code);
	bool EditCodeInfoEntry(const wxString& oldCode, const wxString& code, const wxString& wasteNorm);
	bool isInitStorageViable(const wxString& code, const wxString& date);
	bool DeleteAllUnitEntrys(int unitID);
	bool DeleteOrgTables(int orgID);
	
};
 