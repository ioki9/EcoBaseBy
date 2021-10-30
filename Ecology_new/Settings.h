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
	static bool setActiveOrg(int orgID, wxWindow* reciever);
	static int getActiveOrg();
	static bool setActiveUnit(int unitID, wxWindow* reciever);
	static int getActiveUnit();
	static wxString getActiveOrgName();
	static void addNewOrg(const organization& org);
	static void editOrg(const organization& org);
	static void deleteOrg(const organization& org);
	static void addNewOrgAndNotify(const organization& org, wxWindow* reciever);
	static void editOrgAndNotify(const organization& org, wxWindow* reciever);
	static void deleteOrgAndNotify(const organization& org, wxWindow* reciever);
	static void LoadState();
	static void SaveState();
	static int getLastAddedOrgID();
	static void DeleteAllSaveData();
	static std::vector<organization>* GetOrgArrayPtr();
	static void SetPdfSavePath(const wxString& path);
	static wxString GetPdfSavePath();
	static std::uint32_t GetGridActiveCol();
	static void SaveGridActiveCol(std::uint32_t activeCol);
private:
	static wxString m_activeOrgName;
	static int m_activeOrgID;
	static bool m_isInitialized;
	static int m_lastAddedOrgID;
	static int m_activeUnitID;
	static wxString m_pdfSavePath;
	static void SendEventOrgChanged(wxWindow* reciever);
	static void SendEventActiveOrgChanged(wxWindow* reciever);
	static void SendEventActiveUnitChanged(wxWindow* reciever);
	static std::vector<organization> m_organizations;
	static std::vector<organization> getAllOrgAndUnitNames();
	static wxFileConfig pConfig;
	static wxFileInputStream cfgInStream;
	static std::uint32_t m_gridActiveColumns;
	Settings() {};
};

            
//Config structure by group ->key: organizations-> active, lastAddedID
//								   organizations/[org number] -> id,name,address,unp
//								   organizations/[org number]/units/[unit number] -> name, id