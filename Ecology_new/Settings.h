#pragma once
#include <wx/string.h>
#include <wx/config.h>
#include <wx/wx.h>

class Settings
{
public:
	static bool setActiveOrg(int org);
	static int getActiveOrg();
	static int addNewOrg(const wxString& name, const wxString& address, const wxString& unp);
private:
	static wxString activeOrgName;
	static int activeOrgNum;
	
	Settings() {};
};

            
//Config structure by group ->key: organizations-> active, lastAddedID
//								   organizations/[org number] -> name,address,unp