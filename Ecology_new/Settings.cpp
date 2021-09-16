#include "Settings.h"

wxString Settings::activeOrgName = "Default";
int Settings::activeOrgNum = -1;

bool Settings::setActiveOrg(int org)
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxS("/organizations"));
	if (!pConfig->Exists(wxString::Format("%i", org)))
	{
		pConfig->SetPath(wxS("/"));
		return false;
	}
	pConfig->Write(wxS("active"), org);
	pConfig->SetPath("/organizations/" + wxString::Format("%i", org));
	pConfig->Read(wxS("name"), Settings::activeOrgName);
	activeOrgNum = org;
	pConfig->SetPath(wxS("/"));
	return true;
}

int Settings::getActiveOrg()
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxS("/organizations"));
	int activeOrg;
	pConfig->Read(wxS("active"), &activeOrg, -1);
	pConfig->SetPath(wxS("/"));
	return activeOrg;
}

int Settings::addNewOrg(const wxString& name, const wxString& address, const wxString& unp)
{
	wxConfigBase* pConfig = wxConfigBase::Get();
	pConfig->SetPath(wxS("/organizations"));
	size_t orgID{};
	if(pConfig->Read(wxS("lastAddedID"), &orgID))
	{
		pConfig->Write(wxS("lastAddedID"), orgID+1);
		pConfig->SetPath(wxS("/organizations/" + wxString::Format("%i", orgID + 1)));

	}
	else
	{
		orgID = 0;
		pConfig->Write(wxS("lastAddedID"), orgID);
		pConfig->SetPath(wxS("/organizations/" + wxString::Format("%i", orgID)));
	}
	
	pConfig->Write(wxS("name"), name);
	pConfig->Write(wxS("address"), address);
	pConfig->Write(wxS("unp"), unp);
	pConfig->SetPath(wxS("/"));

	return orgID + 1;
}
