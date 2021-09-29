#include "Settings.h"
using namespace std;

wxString Settings::m_activeOrgName = "Default";
int Settings::m_activeOrgNum = -1;
bool Settings::m_isInitialized = false;
vector<organization> Settings::m_organizations{};
int Settings::m_lastAddedOrgID = -1;

vector<organization>* Settings::GetOrgArrayPtr()
{
	return &m_organizations;
}

bool Settings::setActiveOrg(int orgId)
{
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->SetPath(wxS("/organizations"));
	if (!pConfig->Exists(wxString::Format("%i", orgId)))
	{
		pConfig->SetPath(wxS("/"));
		return false;
	}
	pConfig->Write(wxS("active"), orgId);
	pConfig->SetPath("/organizations/" + wxString::Format("%i", orgId));
	pConfig->Read(wxS("name"), Settings::m_activeOrgName);
	m_activeOrgNum = orgId;
	pConfig->SetPath(wxS("/"));
	return true;
}

int Settings::getActiveOrg()
{
	return m_activeOrgNum;
}

void Settings::addNewOrg(const organization& organization)
{
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->SetPath(wxS("/organizations"));
	pConfig->Write(wxS("lastAddedID"), organization.id);
	pConfig->SetPath(wxS("/organizations/" + wxString::Format("%i", organization.id)));

	pConfig->Write(wxS("id"), organization.id);
	pConfig->Write(wxS("name"), organization.name);
	pConfig->Write(wxS("address"), organization.address);
	pConfig->Write(wxS("unp"), organization.unp);
	for (const auto& unit : organization.units)
	{
		pConfig->SetPath(wxS("/organizations/" + wxString::Format("%i", organization.id) + "/units/" + wxString::Format("%i",unit.id) ));
		pConfig->Write(wxS("name"), unit.name);
		pConfig->Write(wxS("id"), unit.id);
	}
	
	pConfig->SetPath(wxS("/"));
	m_organizations.push_back(organization);
	m_lastAddedOrgID = organization.id;
}

void Settings::deleteOrg(const organization& org)
{
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->SetPath(wxS("/organizations/"));
	pConfig->DeleteGroup(wxString::Format("%i", org.id));
	size_t count{ 0 };
	for (auto& orgIt : m_organizations)
	{
		if (orgIt.id == org.id)
			break;
		count++;
	}
	m_organizations.erase(m_organizations.begin() + count);
}

void Settings::editOrg(const organization& organizationRef)
{
	deleteOrg(organizationRef);
	addNewOrg(organizationRef);
}


void Settings::LoadState()
{
	if (m_isInitialized)
		return;
	m_organizations = Settings::getAllOrgAndUnitNames();
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->SetPath(wxS("/organizations"));
	pConfig->Read(wxS("active"), &m_activeOrgNum, -1);
	pConfig->Read(wxS("lastAddedID"), &m_lastAddedOrgID, -1);
	pConfig->SetPath("/organizations/" + wxString::Format("%i", m_activeOrgNum));
	pConfig->Read(wxS("name"), &m_activeOrgName, "");
	pConfig->SetPath(wxS("/"));
	m_isInitialized = true;

}

void Settings::SaveState()
{

}

int Settings::getLastAddedOrgID()
{
	return m_lastAddedOrgID;
}

void Settings::DeleteAllSaveData()
{
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->DeleteAll();
}

vector<organization> Settings::getAllOrgAndUnitNames()
{
	wxConfig* pConfig = (wxConfig*)wxConfig::Get();
	pConfig->SetPath(wxS("/organizations"));
	if (pConfig->GetNumberOfGroups() == 0)
		return vector<organization>();
	vector<organization> res;
	organization tempOrg;
	wxString str;
	long dummy;
	bool bCont = pConfig->GetFirstGroup(str, dummy);
	while (bCont) {
		tempOrg.id = wxAtoi(str);
		res.push_back(tempOrg);
		bCont = pConfig->GetNextGroup(str, dummy);
	}

	wxString orgID;
	for (size_t i{ 0 }; i < res.size(); ++i)
	{
		orgID = wxString::Format("%i", res[i].id);
		pConfig->SetPath(wxS("/organizations/" + orgID));
		pConfig->Read(wxS("name"), &res[i].name, "");
		pConfig->Read(wxS("address"), &res[i].address, "");
		pConfig->Read(wxS("unp"), &res[i].unp, "");
		pConfig->SetPath(wxS("/organizations/" + orgID + "/units"));
		wxString temp;
		long it;
		bool moreUnits = pConfig->GetFirstGroup(temp, it);
		while (moreUnits) {
			res[i].units.push_back({ wxAtoi(temp),"" });
			moreUnits = pConfig->GetNextGroup(temp, it);
		}
		for (size_t k{ 0 }; k < res[i].units.size(); ++k)
		{
			pConfig->SetPath(wxS("/organizations/" + orgID + "/units/" + wxString::Format("%i", res[i].units[k].id)));
			pConfig->Read(wxS("name"), &res[i].units[k].name, "");
			pConfig->Read(wxS("id"), &res[i].units[k].id, -1);	
		}
	}
	pConfig->SetPath(wxS("/"));
	return res;
}
