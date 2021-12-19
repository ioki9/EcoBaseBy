#pragma once
#include <wx/string.h>
#include <wx/fileconf.h>
#include <wx/wx.h>
#include <wx/wfstream.h>
#include <vector>


struct organization
{
	struct units
	{
		int id;
		wxString name;
	};
	int id;
	wxString name;
	wxString unp;
	wxString address;
	std::vector<units> units;
};
class Settings
{
public:
	static bool setActiveOrg(int orgID, wxWindow* receiver);
	static int getActiveOrg();
	static bool setActiveUnit(int unitID, wxWindow* receiver);
	static int getActiveUnitID();
	static long getTimeElapsed() { return m_timeElapsed; }
	static wxString getActiveUnitString();
	static wxString getActiveOrgName();
	static void addNewOrg(const organization& org);
	static void editOrg(const organization& org);
	static void deleteOrg(const organization& org);
	static void addNewOrgAndNotify(const organization& org, wxWindow* receiver);
	static void editOrgAndNotify(const organization& org, wxWindow* receiver);
	static void deleteOrgAndNotify(const organization& org, wxWindow* receiver);
	static void LoadState();
	static void SaveState();
	static int getLastAddedOrgID();
	static void DeleteAllSaveData();
	static std::vector<organization>* GetOrgArrayPtr();
	static void SetPdfSavePath(const wxString& path);
	static wxString GetPdfSavePath();
	static std::int32_t GetGridActiveCol();
	static void SaveGridActiveCol(std::int32_t activeCol);
	static void initAllVar();
	static void SaveTimeElapsed(wxLongLong timeElapsed, long maxTimeElapsed);
private:
	static wxString GetCfgFile();
	static wxString m_pdfSavePath;
	static wxString m_activeOrgName;
	static int m_activeOrgID;
	static bool m_isInitialized;
	static int m_lastAddedOrgID;
	static int m_activeUnitID;

	static void SendEventOrgChanged(wxWindow* receiver);
	static void SendEventActiveOrgChanged(wxWindow* receiver);
	static void SendEventActiveUnitChanged(wxWindow* receiver);

	static std::vector<organization> m_organizations;
	static std::vector<organization> getAllOrgAndUnitNames();

	static std::int32_t m_gridActiveColumns;
	static long m_timeElapsed;
	Settings() {};
};

            
//Config structure by group ->key: organizations-> active, lastAddedID
//								   organizations/[org number] -> id,name,address,unp
//								   organizations/[org number]/units/[unit number] -> name, id