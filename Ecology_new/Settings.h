#pragma once
#include <wx/string.h>
#include <wx/config.h>
#include <wx/wx.h>
#include <map>
#include <vector>
#include <optional>


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
	static bool setActiveOrg(int org);
	static int getActiveOrg();
	static void addNewOrg(const organization& organization);
	static void editOrg(const organization& organization);
	static void deleteOrg(const organization& org);
	static void LoadState();
	static void SaveState();
	static int getLastAddedOrgID();
	static void DeleteAllSaveData();
	static std::vector<organization>* GetOrgArrayPtr();
private:
	static wxString m_activeOrgName;
	static int m_activeOrgNum;
	static bool m_isInitialized;
	static int m_lastAddedOrgID;

	static std::vector<organization> m_organizations;
	static std::vector<organization> getAllOrgAndUnitNames();
	Settings() {};
};

            
//Config structure by group ->key: organizations-> active, lastAddedID
//								   organizations/[org number] -> id,name,address,unp
//								   organizations/[org number]/units/[unit number] -> name, id