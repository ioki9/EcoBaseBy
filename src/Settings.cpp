#include "Settings.h"
#include "Utility/CustomEvents.h"

using namespace std;
wxFileInputStream Settings::cfgInStream(Settings::GetCfgFile());
wxString Settings::m_activeOrgName = "Default";
int Settings::m_activeOrgID = -1;
bool Settings::m_isInitialized = false;
vector<organization> Settings::m_organizations{};
int Settings::m_activeUnitID = -1;
int Settings::m_lastAddedOrgID = -1;
wxFileConfig Settings::pConfig(Settings::cfgInStream);
wxString Settings::m_pdfSavePath{ wxGetCwd() + "/Documents"};
std::int32_t Settings::m_gridActiveColumns = 0xffffffff;

vector<organization>* Settings::GetOrgArrayPtr()
{
	return &m_organizations;
}

void Settings::SetPdfSavePath(const wxString& path)
{
	m_pdfSavePath = path;
	pConfig.Write(wxS("pdfSavePath"), m_pdfSavePath);
	pConfig.SetPath(wxS("/"));
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}

wxString Settings::GetPdfSavePath()
{
	return m_pdfSavePath;
}

std::int32_t Settings::GetGridActiveCol()
{
	return m_gridActiveColumns;
}

void Settings::SaveGridActiveCol(std::int32_t activeCol)
{
	m_gridActiveColumns = activeCol;
	pConfig.Write(wxS("activeColumns"), m_gridActiveColumns);
	pConfig.SetPath(wxS("/"));
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}

bool Settings::setActiveOrg(int orgID,wxWindow* reciever)
{
	pConfig.SetPath(wxS("/organizations"));
	if (!pConfig.Exists(wxString::Format("%i", orgID)))
	{
		pConfig.SetPath(wxS("/"));
		return false;
	}
	pConfig.Write(wxS("active"), orgID);
	pConfig.SetPath("/organizations/" + wxString::Format("%i", orgID));
	pConfig.Read(wxS("name"), Settings::m_activeOrgName);
	m_activeOrgID = orgID;
	pConfig.SetPath(wxS("/"));
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
	SendEventActiveOrgChanged(reciever);
	return true;
}

int Settings::getActiveOrg()
{
	return m_activeOrgID;
}

bool Settings::setActiveUnit(int unitID,wxWindow* reciever)
{
	if (!pConfig.Exists((wxS("/organizations/" + wxString::Format("%i", m_activeOrgID) + "/units/" + wxString::Format("%i", unitID)))))
		return false;
	pConfig.SetPath(wxS("/organizations/" + wxString::Format("%i", m_activeOrgID)));
	pConfig.Write(wxS("activeUnit"), unitID);
	m_activeUnitID = unitID;
	SendEventActiveUnitChanged(reciever);
	pConfig.SetPath(wxS("/"));
	return true;
}

int Settings::getActiveUnitID()
{
	return m_activeUnitID;
}

wxString Settings::getActiveUnitString()
{
	for (const auto& it : *Settings::GetOrgArrayPtr())
	{
		if (it.id == Settings::getActiveOrg())
		{
			for (const auto& unit : it.units)
				if (unit.id == m_activeUnitID)
				{
					return unit.name;
				}
		}
	}
	return "";
}

wxString Settings::getActiveOrgName()
{
	return m_activeOrgName;
}

void Settings::addNewOrg(const organization& org)
{
	pConfig.SetPath(wxS("/organizations"));
	pConfig.Write(wxS("lastAddedID"), org.id);
	pConfig.SetPath(wxS("/organizations/" + wxString::Format("%i", org.id)));
	pConfig.Write(wxS("id"), org.id);
	pConfig.Write(wxS("name"), org.name);
	pConfig.Write(wxS("address"), org.address);
	pConfig.Write(wxS("unp"), org.unp);
	for (const auto& unit : org.units)
	{
		pConfig.SetPath(wxS("/organizations/" + wxString::Format("%i", org.id) + "/units/" + wxString::Format("%i",unit.id) ));
		pConfig.Write(wxS("name"), unit.name);
		pConfig.Write(wxS("id"), unit.id);
	}
	pConfig.SetPath(wxS("/"));
	m_organizations.push_back(org);
	m_lastAddedOrgID = org.id;
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}

void Settings::deleteOrg(const organization& org)
{
	pConfig.SetPath(wxS("/organizations/"));
	pConfig.DeleteGroup(wxString::Format("%i", org.id));
	size_t count{ 0 };
	for (auto& orgIt : m_organizations)
	{
		if (orgIt.id == org.id)
			break;
		count++;
	}
	m_organizations.erase(m_organizations.begin() + count);
	pConfig.SetPath(wxS("/"));
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}

void Settings::addNewOrgAndNotify(const organization& org, wxWindow* reciever)
{
	addNewOrg(org);
	SendEventOrgChanged(reciever);
}

void Settings::editOrgAndNotify(const organization& org, wxWindow* reciever)
{
	editOrg(org);
	SendEventOrgChanged(reciever);
}

void Settings::deleteOrgAndNotify(const organization& org, wxWindow* reciever)
{
	deleteOrg(org);
	SendEventOrgChanged(reciever);
}

void Settings::editOrg(const organization& org)
{
	pConfig.SetPath(wxS("/organizations/" + wxString::Format("%i", org.id)));
	pConfig.Write(wxS("name"), org.name);
	pConfig.Write(wxS("address"), org.address);
	pConfig.Write(wxS("unp"), org.unp);
	for (const auto& unit : org.units)
	{
		pConfig.SetPath(wxS("/organizations/" + wxString::Format("%i", org.id) + "/units/" + wxString::Format("%i", unit.id)));
		pConfig.Write(wxS("name"), unit.name);
		pConfig.Write(wxS("id"), unit.id);
	}
	pConfig.SetPath(wxS("/"));
	
	for (auto& orgIt : m_organizations)
	{
		if (orgIt.id == org.id)
		{
			orgIt.name = org.name;
			orgIt.address = org.address;
			orgIt.unp = org.unp;
			orgIt.units = org.units;
			break;
		}
	}
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}


void Settings::LoadState()
{

	if (m_isInitialized)
		return;
		
	pConfig.Read(wxS("pdfSavePath"), &m_pdfSavePath, wxGetCwd() + "/Documents");
	pConfig.Read(wxS("activeColumns"), &m_gridActiveColumns, 0xffffffff);
	m_organizations = Settings::getAllOrgAndUnitNames();
	pConfig.SetPath(wxS("/organizations"));
	pConfig.Read(wxS("active"), &m_activeOrgID, -1);
	pConfig.Read(wxS("lastAddedID"), &m_lastAddedOrgID, -1);
	pConfig.SetPath("/organizations/" + wxString::Format("%i", m_activeOrgID));
	pConfig.Read(wxS("activeUnit"), &m_activeUnitID,-1);
	pConfig.Read(wxS("name"), &m_activeOrgName, "");
	pConfig.SetPath(wxS("/"));
	m_isInitialized = true;
}

void Settings::SaveState()
{
	pConfig.Write(wxS("pdfSavePath"), m_pdfSavePath);
	pConfig.SetPath(wxS("/"));
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}

int Settings::getLastAddedOrgID()
{
	return m_lastAddedOrgID;
}

void Settings::DeleteAllSaveData()
{
	pConfig.DeleteAll();
	wxFileOutputStream out(Settings::GetCfgFile());
	pConfig.Save(out);
}



void Settings::SendEventOrgChanged(wxWindow* reciever)
{
	wxCommandEvent evt(EVT_ORGANIZATION_CHANGED);
	wxPostEvent(reciever,evt);
}

void Settings::SendEventActiveOrgChanged(wxWindow* reciever)
{
	wxCommandEvent evt(EVT_ACTIVE_ORG_CHANGED);
	wxPostEvent(reciever, evt);
}

void Settings::SendEventActiveUnitChanged(wxWindow* reciever)
{
	wxCommandEvent evt(EVT_ACTIVE_UNIT_CHANGED);
	wxPostEvent(reciever, evt);
}

wxString Settings::GetCfgFile()
{
	if (!wxFile::Exists(wxGetCwd() + "/config.cfg"))
	{
		wxFile temp;
		temp.Create(wxGetCwd() + "/config.cfg");
	}
	return wxGetCwd() + "/config.cfg";
}

vector<organization> Settings::getAllOrgAndUnitNames()
{
	pConfig.SetPath(wxS("/organizations"));
	if (pConfig.GetNumberOfGroups() == 0)
		return vector<organization>();
	vector<organization> res;
	organization tempOrg;
	wxString str;
	long dummy;
	bool bCont = pConfig.GetFirstGroup(str, dummy);
	while (bCont) {
		tempOrg.id = wxAtoi(str);
		res.push_back(tempOrg);
		bCont = pConfig.GetNextGroup(str, dummy);
	}

	wxString orgID;
	for (size_t i{ 0 }; i < res.size(); ++i)
	{
		orgID = wxString::Format("%i", res[i].id);
		pConfig.SetPath(wxS("/organizations/" + orgID));
		pConfig.Read(wxS("name"), &res[i].name, "");
		pConfig.Read(wxS("address"), &res[i].address, "");
		pConfig.Read(wxS("unp"), &res[i].unp, "");
		pConfig.SetPath(wxS("/organizations/" + orgID + "/units"));
		wxString temp;
		long it;
		bool moreUnits = pConfig.GetFirstGroup(temp, it);
		while (moreUnits) {
			res[i].units.push_back({ wxAtoi(temp),"" });
			moreUnits = pConfig.GetNextGroup(temp, it);
		}
		for (size_t k{ 0 }; k < res[i].units.size(); ++k)
		{
			pConfig.SetPath(wxS("/organizations/" + orgID + "/units/" + wxString::Format("%i", res[i].units[k].id)));
			pConfig.Read(wxS("name"), &res[i].units[k].name, "");
			pConfig.Read(wxS("id"), &res[i].units[k].id, -1);
		}
	}
	pConfig.SetPath(wxS("/"));
	pConfig.Flush();
	return res;
}
