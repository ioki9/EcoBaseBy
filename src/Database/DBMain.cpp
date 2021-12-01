#include "DBMain.h"
#include "DBColumnEnums.h"
#include <stdlib.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <algorithm>   
#include <vector>
#include "../Settings.h"
#include "../GUI_parameters.h"
#include "../Controls/MaterialButton.h"
#include <wx/datetime.h>



DBMain::DBMain()
{
	Open(DBPathPassp);
	if (Settings::getLastAddedOrgID() == -1)
	{
		CreateOrgTables("0");
	}
		
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + ""));
	getStorageColumnNames();
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + ""));
	getPassportColumnNames();
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + ""));
	m_codesColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(0);
	m_codesColumns[DB_COLUMN_CODE_DESCRIPTION] = m_rs.GetColumnName(1);
	m_codesColumns[DB_COLUMN_DNG_LVL] = m_rs.GetColumnName(2);
	m_codesColumns[DB_COLUMN_ID] = m_rs.GetColumnName(3);
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveCodeInfoTable() + ""));
	getCodeInfoColumnNames();
	m_rs.Finalize();
}

DBMain::~DBMain()
{
	m_storageColumns.clear();
	m_rs.Finalize();
	if (IsOpen())
		Close();
}

void DBMain::getPassportColumnNames()
{
	m_passpColumns[DB_COLUMN_ID] = m_rs.GetColumnName(0);
	m_passpColumns[DB_COLUMN_OWNER] = m_rs.GetColumnName(1);
	m_passpColumns[DB_COLUMN_RECEIVER] = m_rs.GetColumnName(2);
	m_passpColumns[DB_COLUMN_TRANSPORT] = m_rs.GetColumnName(3);
	m_passpColumns[DB_COLUMN_DATE] = m_rs.GetColumnName(4);
	m_passpColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(5);
	m_passpColumns[DB_COLUMN_REGNUM] = m_rs.GetColumnName(6);
	m_passpColumns[DB_COLUMN_AMOUNT_FORMED] = m_rs.GetColumnName(7);
	m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] = m_rs.GetColumnName(8);
	m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = m_rs.GetColumnName(9);
	m_passpColumns[DB_COLUMN_AMOUNT_USED] = m_rs.GetColumnName(10);
	m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] = m_rs.GetColumnName(11);
	m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] = m_rs.GetColumnName(12);
	m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] = m_rs.GetColumnName(13);
	m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] = m_rs.GetColumnName(14);
	m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = m_rs.GetColumnName(15);
	m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = m_rs.GetColumnName(16);
	m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = m_rs.GetColumnName(17);
	m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] = m_rs.GetColumnName(18);
	m_passpColumns[DB_COLUMN_WASTE_NORM] = m_rs.GetColumnName(19);
	m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] = m_rs.GetColumnName(20);
	m_passpColumns[DB_COLUMN_ENTRYDATE] = m_rs.GetColumnName(21);
	m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] = m_rs.GetColumnName(22);
	m_passpColumns[DB_COLUMN_INITIAL] = m_rs.GetColumnName(23);
	m_passpColumns[DB_COLUMN_UNIT_ID] = m_rs.GetColumnName(24);
	m_passpColumns[DB_COLUMN_DEPENDENCY] = m_rs.GetColumnName(25);
	m_passpColumns[DB_COLUMN_STORAGE_ID] = m_rs.GetColumnName(26);
	m_passpColumns[DB_COLUMN_DNG_LVL] = m_rs.GetColumnName(27);
	
}

void DBMain::getCodeInfoColumnNames()
{
	m_codeInfoColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(0);
	m_codeInfoColumns[DB_COLUMN_WASTE_NORM] = m_rs.GetColumnName(1);
	m_codeInfoColumns[DB_COLUMN_SYMBOLS_AFTER_COMA] = m_rs.GetColumnName(2);
}

void DBMain::getStorageColumnNames()
{
	
	m_storageColumns[DB_COLUMN_DATE] =  m_rs.GetColumnName(0);
	m_storageColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(1);
	m_storageColumns[DB_COLUMN_AMOUNT_FORMED] = m_rs.GetColumnName(2);
	m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] = m_rs.GetColumnName(3);
	m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = m_rs.GetColumnName(4);
	m_storageColumns[DB_COLUMN_AMOUNT_USED] = m_rs.GetColumnName(5);
	m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] = m_rs.GetColumnName(6);
	m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] = m_rs.GetColumnName(7);
	m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] = m_rs.GetColumnName(8);
	m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] = m_rs.GetColumnName(9);
	m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = m_rs.GetColumnName(10);
	m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = m_rs.GetColumnName(11);
	m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = m_rs.GetColumnName(12);
	m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] = m_rs.GetColumnName(13);
	m_storageColumns[DB_COLUMN_WASTE_NORM] = m_rs.GetColumnName(14);
	m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] = m_rs.GetColumnName(15);
	m_storageColumns[DB_COLUMN_ENTRYDATE] = m_rs.GetColumnName(16);
	m_storageColumns[DB_COLUMN_ID] = m_rs.GetColumnName(17);
	m_storageColumns[DB_COLUMN_INITIAL] = m_rs.GetColumnName(18);
	m_storageColumns[DB_COLUMN_DNG_LVL] = m_rs.GetColumnName(19);
}

wxString DBMain::GetLastPassportID()
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " ORDER BY " + m_passpColumns[DB_COLUMN_ID] + " DESC"));
	m_rs.NextRow();
	wxString id = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
	m_rs.Finalize();
	return id;
}

bool DBMain::CreateOrgTables(const wxString& orgId )
{
	if(!TableExists(DBPasspTableName + orgId))
		ExecuteUpdate(wxS("CREATE TABLE " + DBPasspTableName + orgId +
			" (id	INTEGER," 
			"Owner	TEXT," 
			"Receiver	TEXT," 
			"Transporter	TEXT," 
			"Date	TEXT," 
			"Code	INTEGER," 
			"Regnumber	TEXT," 
			"Amount_formed	REAL," 
			"Amount_received_org	REAL," 
			"Amount_received_phys	REAL," 
			"Amount_used	REAL," 
			"Amount_defused	REAL," 
			"Amount_selfstorage	REAL," 
			"Amount_burial	REAL," 
			"Amount_transfer_used	REAL," 
			"Amount_transfer_defused	REAL," 
			"Amount_transfer_storage	REAL," 
			"Amount_transfer_burial	REAL," 
			"Amount_selfstorage_full	REAL," 
			"Waste_norm	REAL," 
			"Structural_unit_formed	TEXT," 
			"Entry_date	TEXT," 
			"Structural_unit_transfered	TEXT," 
			"Initial	INTEGER," 
			"Unit_id	INTEGER,"
			"Dependency	TEXT,"
			"Storage_id INTEGER,"
			"Code_dng_lvl TEXT,"
			"PRIMARY KEY('id'))"));

	if (!TableExists(DBStorageTableName + orgId))
		ExecuteUpdate(wxS("CREATE TABLE " + DBStorageTableName + orgId + " ("
			"Date	TEXT,"
			"Code	INTEGER,"
			"Amount_formed	REAL,"
			"Amount_received_org	REAL,"
			"Amount_received_phys	REAL,"
			"Amount_used	REAL,"
			"Amount_defused	REAL,"
			"Amount_seflstorage	REAL,"
			"Amount_burial	REAL,"
			"Amount_transfer_used	REAL,"
			"Amount_transfer_defused	REAL,"
			"Amount_transfer_storage	REAL,"
			"Amount_transfer_burial	REAL,"
			"Amount_selfstorage_full	REAL,"
			"Waste_norm	REAL,"
			"Structural_unit	TEXT,"
			"Entry_date	TEXT,"
			"id	INTEGER,"
			"Initial	INTEGER,"
			"Code_dngLvl	TEXT,"
			"PRIMARY KEY('id'))"));

	if (!TableExists(DBCodeInfoTableName + orgId))
		ExecuteUpdate(wxS("CREATE TABLE " + DBCodeInfoTableName + orgId + " ("
			"code	INTEGER UNIQUE,"
			"Waste_norm	REAL,"
			"symbols_after_coma	INTEGER)"));

	return true;
}

void DBMain::SetOrg(int orgId)
{
	m_activeOrg = orgId;
}

void  DBMain::SetActiveOrg()
{
	m_activeOrg = -1;
}

wxString DBMain::GetMovmStringFromDepend(const wxString& dependency)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE "
		+ m_passpColumns[DB_COLUMN_ID] + " = '" + dependency.Mid(2) + "'"));
	wxString movm;
	if (!m_rs.NextRow())
	{
		m_rs.Finalize();
		return wxString();
	}

	if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])!="")
		movm = wxString::FromUTF8("Захоронено");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED]) != "")
		movm = wxString::FromUTF8("Использовано");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]) != "")
		movm = wxString::FromUTF8("Обезврежено");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) != "")
		movm = wxString::FromUTF8("Направлено на хранение");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) != "")
		movm = wxString::FromUTF8("Передано на захоронение");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) != "")
		movm = wxString::FromUTF8("Передано на использование");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) != "")
		movm = wxString::FromUTF8("Передано на обезвреживание");
	else if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) != "")
		movm = wxString::FromUTF8("Передано на хранение");
	m_rs.Finalize();
	return movm;
}

bool DBMain::IsCodeExists(const wxString& code)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveCodeTable() + " WHERE "
		+ m_codesColumns[DB_COLUMN_CODE] + " = '" + code + "'"));
	if (m_rs.NextRow())
	{
		m_rs.Finalize();
		return true;
	}
	m_rs.Finalize();
	return false;
}

wxString DBMain::GetDngFromCode(const wxString& code)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE " + m_codesColumns[DB_COLUMN_CODE] + " = '" + code + "'"));
	if (m_rs.NextRow())
	{
		wxString str;
		str = m_rs.GetAsString(m_codesColumns[DB_COLUMN_DNG_LVL]);
		m_rs.Finalize();
		return str;
	}
	m_rs.Finalize();
	return "";
}

wxArrayString DBMain::GetAllPossibleCodes()
{
	wxArrayString arr;
	m_rs = ExecuteQuery(wxS("SELECT " + m_codesColumns[DB_COLUMN_CODE] + " FROM " + DBCodesTableName));
	while (m_rs.NextRow())
		arr.Add(m_rs.GetAsString(m_codesColumns[DB_COLUMN_CODE]));
	return arr;
}

wxString DBMain::GetActiveCodeTable()
{
	return DBCodesTableName;
}

wxString DBMain::GetActivePasspTable()
{

	if (m_activeOrg > -1 && TableExists(DBPasspTableName + wxString::Format("%i", m_activeOrg)))
		return DBPasspTableName + wxString::Format("%i", m_activeOrg);

	else if (m_activeOrg == -1 && Settings::getActiveOrg() != -1)
		return DBPasspTableName + wxString::Format("%i", Settings::getActiveOrg());

	else
		return DBPasspTableName + "0";
}

wxString DBMain::GetActiveStrgTable()
{
	if (m_activeOrg > -1 && TableExists(DBStorageTableName + wxString::Format("%i", m_activeOrg)))
		return DBStorageTableName + wxString::Format("%i", m_activeOrg);

	 else if (m_activeOrg == -1 && Settings::getActiveOrg() != -1)
		return DBStorageTableName + wxString::Format("%i", Settings::getActiveOrg());

	else
		return DBStorageTableName + "0";
}

wxString DBMain::GetActiveCodeInfoTable()
{
	if (m_activeOrg > -1 && TableExists(DBCodeInfoTableName + wxString::Format("%i", m_activeOrg)))
		return DBCodeInfoTableName + wxString::Format("%i", m_activeOrg);

	else if (m_activeOrg == -1 && Settings::getActiveOrg() != -1)
		return DBCodeInfoTableName + wxString::Format("%i", Settings::getActiveOrg());

	else
		return DBCodeInfoTableName + "0";
}

std::map<int, wxString> DBMain::GetCodesColumns()
{
	return m_codesColumns;
}

std::map<int, wxString> DBMain::GetStorageColumns()
{
	return m_storageColumns;
}

std::map<int, wxString> DBMain::GetPassportColumns()
{
	return m_passpColumns;
}

std::map<int, wxString> DBMain::GetCodeInfoColumns()
{
	return m_codeInfoColumns;
}

wxString DBMain::convertDate(const wxString &date)
{
	wxDateTime newDate;
	newDate.ParseDate(date);
	return newDate.Format(wxS("%d.%m.%Y"));
}

int DBMain::getUniqueCodes(passportPod9Info &data, const wxString& unitID, const wxString& startDate, const wxString& endDate)
{
		m_rs = ExecuteQuery(wxS("SELECT DISTINCT Code FROM " + GetActivePasspTable() + " WHERE " 
			+ m_passpColumns[DB_COLUMN_DATE] + " >= '" + startDate + "' AND " + m_passpColumns[DB_COLUMN_DATE] + " <= '" + endDate + "' AND "
			+ m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + unitID +"'"));
		while (m_rs.NextRow())
		{
			data.uniqueCodes.Add(m_rs.GetString(0));
		}
		m_rs.Finalize();
	return ExecuteScalar(wxS("SELECT COUNT(DISTINCT Code) FROM " + GetActivePasspTable() + " WHERE " + m_passpColumns[DB_COLUMN_DATE] + " >= '" + startDate + "' AND " +
		m_passpColumns[DB_COLUMN_DATE] + " <= '" + endDate + "' AND " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + unitID + "'"));
}

void DBMain::getNextPod9Portion(passportPod9Info &data,const wxString &code,const wxString& unitID, const wxString& startDate, const wxString& endDate)
{
	int count{ 0 };
	if (!data.id.IsEmpty())
	{
		data.emptyPodStruct9Info();
	}

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE Code = '" + code + "' AND " +
		m_passpColumns[DB_COLUMN_DATE] + " <= '" + startDate + "' ORDER BY " + m_passpColumns[DB_COLUMN_DATE] + " DESC"));

	while (m_rs.NextRow())
	{
		if (m_rs.GetInt(m_passpColumns[DB_COLUMN_INITIAL]) == 1)
		{
			data.id.Add(m_rs.GetInt(m_passpColumns[DB_COLUMN_ID]));
			data.idString.Add(m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]));
			data.stuct_unit9.Add(m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]));
			data.date.Add(convertDate(m_rs.GetString(m_passpColumns[DB_COLUMN_DATE])));
			data.receiver.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_RECEIVER]));
			data.wasteNorm = m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]);
			if (m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]) == m_rs.GetString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD10]))
				if (m_rs.GetString(m_passpColumns[DB_COLUMN_DEPENDENCY]).starts_with('2'))
					data.owner.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]));
				else
					data.owner.Add("");
			else
				data.owner.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]));
			data.transporter.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_TRANSPORT]));
			data.regnum.Add("initial");
			data.amountFormed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]));
			data.amountReceivedPhys.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]));
			data.amountReceivedOrg.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]));
			data.amountUsed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED]));
			data.amountDefused.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]));
			data.amountSelfstorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]));
			data.amountBurial.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]));
			data.amountTransferUsed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]));
			data.amountTransferDefused.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
			data.amountTransferStorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
			data.amountTransferBurial.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]));
			data.amountFullStorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
			data.codeDangerLVL = m_rs.GetString(m_passpColumns[DB_COLUMN_DNG_LVL]);
			++count;
			break;
		}
		if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_DATE]) != startDate)
			break;
	}
		
	m_rs.Finalize();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE Code = '" + code + "' AND " +
		m_passpColumns[DB_COLUMN_DATE] + " >= '" + startDate + "' AND " + m_passpColumns[DB_COLUMN_DATE] + " <= '" + endDate +
		"' AND " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + unitID + "' ORDER BY Date"));




		while (m_rs.NextRow())
		{
			data.id.Add(m_rs.GetInt(m_passpColumns[DB_COLUMN_ID]));
			data.idString.Add(m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]));
			data.stuct_unit9.Add(m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]));
			data.date.Add(convertDate(m_rs.GetString(m_passpColumns[DB_COLUMN_DATE])));
			data.receiver.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_RECEIVER]));
			data.wasteNorm = m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]);
			if (m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]) == m_rs.GetString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD10]))
				if (m_rs.GetString(m_passpColumns[DB_COLUMN_DEPENDENCY]).starts_with('2'))
					data.owner.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]));
				else
					data.owner.Add("");
			else
				data.owner.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_OWNER]));
	
			data.transporter.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_TRANSPORT]));
			data.regnum.Add(m_rs.GetString(m_passpColumns[DB_COLUMN_REGNUM]));
			data.amountFormed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]));
			data.amountReceivedPhys.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]));
			data.amountReceivedOrg.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]));
			data.amountUsed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED]));
			data.amountDefused.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]));
			data.amountSelfstorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]));
			data.amountBurial.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]));
			data.amountTransferUsed.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]));
			data.amountTransferDefused.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
			data.amountTransferStorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
			data.amountTransferBurial.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]));
			data.amountFullStorage.Add(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
			data.codeDangerLVL = m_rs.GetString(m_passpColumns[DB_COLUMN_DNG_LVL]);
			count++;
		}

		data.rowCount = std::move(count);
		m_rs.Finalize();

		m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + code + "'"));

		data.codeDescription = m_rs.GetString(1);
		m_rs.Finalize();

}

//returns code/date string if fullstorage value already exists, empty string otherwise
wxString DBMain::checkFullStorage(const wxString& code)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Code = '" + code + "' ORDER BY Date DESC"));
	if (!m_rs.NextRow())
	{
		m_rs.Finalize();
		return "";
	}
	else
	{
		wxString string{ wxString::FromUTF8("Код отхода: ") + m_rs.GetAsString(m_storageColumns[DB_COLUMN_CODE])
			+ wxString::FromUTF8("\nДата: ") + m_rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]) + wxString::FromUTF8("\nЗначение: ")
			+ m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) };
		m_rs.Finalize();
		return string;
	}
}

bool DBMain::deleteEntry(const addPageInfo& info)
{
	Begin();
	wxString pAmountColumn, amount, sAmountColumn, strDiffrAm, amountStorageFull;

	auto getAmount = [](wxString amount) { 
	if (amount == "")
		return amount + "0";
	else
		return amount; };

	if (info.amountFormed != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (info.amountReceivedOrg != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}


	//if we have double entry we have to check what entry we got into function, calculate diffrance amount and update storage accrodingly
	double diffrAm;
	if (info.dependency != "")
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE id = " + info.dependency.Mid(2)));
		if (info.dependency[0] == '1')
		{
			diffrAm = m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) + (wxAtof(amount) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) 
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) 
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) 
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
			strDiffrAm = wxString::Format("%f", diffrAm * -1);
			
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + strDiffrAm + ", "
				+ sAmountColumn + " = " + sAmountColumn + " - " + getAmount(amount) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]))
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
		}
		else
		{
			diffrAm = wxAtof(info.amountStorage) + (m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]) + m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])
				+ m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
				- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));
			strDiffrAm = wxString::Format("%f", diffrAm * -1);
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + strDiffrAm + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " - " + getAmount(m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_FORMED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " - " + getAmount(m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " - " + getAmount(m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(info.amountUsed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(info.amountDefused) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(info.amountStorage) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(info.amountBurial) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(info.tamountUsed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(info.tamountDefused) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(info.tamountBurial) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(info.tamountStorage)
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
		}
		m_rs.Finalize();
	}
	else
	{
		diffrAm = wxAtof(info.amountStorage) + (wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
			- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));
		strDiffrAm = wxString::Format("%f", diffrAm * -1);
		ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
			m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + strDiffrAm + ", "
			+ sAmountColumn + " = " + sAmountColumn + " - " + getAmount(amount) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(info.amountUsed) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(info.amountDefused) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(info.amountStorage) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(info.amountBurial) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(info.tamountUsed) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(info.tamountDefused) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(info.tamountBurial) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(info.tamountStorage)
			+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
	}

	

	//check if storage entry is empty after update, if yes - delete it
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
	m_rs.NextRow();
	//we are getting full storage to update other entrys on same date and code
	amountStorageFull = m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);
	if (m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) == 0 
		&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_USED]) == 0 
		&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) == 0 
		&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_BURIAL]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) == 0 
		&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) == 0 
		&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) == 0)
	{

		ExecuteUpdate(wxS("DELETE FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' AND " 
			+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10 + "'"));
	}
	else if (m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0)
	{
		ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = ''" +
			" WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' AND " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10 + "'"));

	}

	//we have to combine entrys without structUnit10 into entry with structUnit10 or combine all the empty entrys into one
	if (ExecuteScalar(wxS("SELECT COUNT(*) FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'")) > 1)
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable()
			+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " ASC"));
		wxString tempId, tempQuery;
		while (true)
		{
			if (!m_rs.CursorMoved())
				m_rs.NextRow();
			if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) == "")
			{
				tempId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
				tempQuery = "UPDATE " + GetActiveStrgTable() + " SET "
					+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_USED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_BURIAL]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]);
				if (!m_rs.NextRow())
					break;
				ExecuteUpdate(tempQuery + " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]) + "'");
				ExecuteUpdate(wxS("DELETE FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + tempId + "'"));
			}
			else
				break;
		}
	}

	//we are updating full storage in case of multiple entrys for one date
	ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
		m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + amountStorageFull
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

	this->updateSubsqPOD10Strg(info.code, info.date,strDiffrAm, m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]));
	m_rs.Finalize();

	ExecuteUpdate(wxS("DELETE FROM " + GetActivePasspTable() + " WHERE id = " + info.id));
	if (info.dependency != "")
		ExecuteUpdate(wxS("DELETE FROM " + GetActivePasspTable() + " WHERE id = " + info.dependency.Mid(2)));

	updateSubsqPasspStrg(info.code, info.date);
	Commit();
	return true;
}

bool DBMain::editEntry(const addPageInfo& info, bool willHaveDepend)
{
	Begin();
	auto getAmount = [](wxString amount) {
		if (amount == "")
			return amount + "0";
		else
			return amount; };


	wxString pAmountColumn, amount, sAmountColumn, amountStorageFull,storageId;
	double newDiffrAm, oldDiffrAM;

	if (wxAtof(info.amountFormed) > 0)
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (wxAtof(info.amountReceivedOrg) > 0)
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}
	//calculate and substract old difference amount from storage table
	if (info.dependency != "")
	{
		
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE id = " + info.dependency.Mid(2)));
		m_rs.NextRow();

		if (info.dependency[0] == '1')
		{
			
			oldDiffrAM = m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]);
			
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET "
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]))
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
			
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE id = " + info.id));
			m_rs.NextRow();
			
			oldDiffrAM += m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]) +
				m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) + m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]);


		
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET "
				+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])) + " "
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
			//we updating storage separately in case of multiple entrys for same date and code
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", oldDiffrAM * -1) +
				" WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));
		}
		else
		{
			oldDiffrAM = m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]) + m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])
				+ m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]);

			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " 
				+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])) + ", "
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE id = " + info.id));
			m_rs.NextRow();

			oldDiffrAM += m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])
				- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]);

			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " 
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]))
				+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));
			//we updating storage separately in case of multiple entrys for same date and code
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", oldDiffrAM * -1) +
				" WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));
		}
	}
	else
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE id = " + info.id));
		m_rs.NextRow();

		oldDiffrAM = m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) + (m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS])
			+ m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) + m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_FORMED])
			- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])
			- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED])
			- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED])
			- m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) - m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
		
		//substract old diffrance from old/current entry in storage table
		ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET "
			+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL])) + ", "
			+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]))
			+ " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + info.storageId + "'"));

		//we updating storage separately in case of multiple entrys for same date and code
		ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
			m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", oldDiffrAM * -1) +
			" WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));
	}
	m_rs.Finalize();

	
	if (willHaveDepend)
		newDiffrAm = wxAtof(info.amountStorageUnit) + (wxAtof(amount) - wxAtof(info.amountStorageUnit) - wxAtof(info.amountBurialUnit) - wxAtof(info.amountUsedUnit)
			- wxAtof(info.amountDefusedUnit) - wxAtof(info.tamountBurialUnit) - wxAtof(info.tamountStorageUnit) - wxAtof(info.tamountUsedUnit) - wxAtof(info.tamountDefusedUnit));
	else
		newDiffrAm = wxAtof(info.amountStorage) + (wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
			- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorageUnit) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));

	//substract old diffrance from subsequent storage table entrys
	this->updateSubsqPOD10Strg(info.oldCode, info.oldDate, wxString::Format("%f", oldDiffrAM * -1), info.id);

	//delete storage table entry if code or date is changed and entry is empty
	if (info.oldCode != info.code || info.oldDate != info.date || info.oldStructUnit10 != info.structUnit10)
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + 
			" WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%' AND " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.oldStructUnit10 + "'"));
		m_rs.NextRow();
		if (m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) == 0
			&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_USED]) == 0
			&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) == 0
			&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_BURIAL]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) == 0
			&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) == 0 && m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) == 0
			&& m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) == 0)
		{
			ExecuteUpdate(wxS("DELETE FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" 
				+ info.oldDate.Mid(0, 7) + "%' AND " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.oldStructUnit10 + "'"));
		}
		//we have to check if we have formed amount left in entry we edited, if we dont,then we erase structunit10 name from edited entry
		else if (m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0)
		{
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = ''" +
				" WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%' AND " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.oldStructUnit10 + "'"));
			
		}
		m_rs.Finalize();
	}


	//get current full storage amount and if entry in storage table with such code and date exists - update this entry, if not - insert new entry
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable()
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY "+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]+ " ASC"));
	while (true)
	{
		wxString structUnit10{ info.structUnit10 };
		if (m_rs.NextRow())
		{
			if (info.structUnit10 == "")
			{
				// if struct is empty we dont care on what entry we are setting the values so we skip next check 
				structUnit10 = m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]);
			}
			else if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != info.structUnit10 && m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != "")
				continue;

			amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + newDiffrAm);
			if (!willHaveDepend)
			{
				ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
					m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", newDiffrAm) + ", "
					+ sAmountColumn + " = " + sAmountColumn + " + " + getAmount(amount) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " + " + getAmount(info.amountUsed) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " + " + getAmount(info.amountDefused) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " + " + getAmount(info.amountStorage) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " + " + getAmount(info.amountBurial) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " + " + getAmount(info.tamountUsed) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " + " + getAmount(info.tamountDefused) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " + " + getAmount(info.tamountBurial) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " + " + getAmount(info.tamountStorage) + ", "
					+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + structUnit10
					+ "' WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]) + "'"));
				storageId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
				break;
			}
			else
			{
				ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
					m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", newDiffrAm) + ", "
					+ sAmountColumn + " = " + sAmountColumn + " + " + getAmount(amount) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " + " + getAmount(info.amountUsedUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " + " + getAmount(info.amountDefusedUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " + " + getAmount(info.amountStorageUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " + " + getAmount(info.amountBurialUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " + " + getAmount(info.tamountUsedUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " + " + getAmount(info.tamountDefusedUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " + " + getAmount(info.tamountBurialUnit) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " + " + getAmount(info.tamountStorageUnit) + ", "
					+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + structUnit10
					+ "' WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]) + "'"));
				storageId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
				break;
			}
		}
		else
		{
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code
				+ "' AND Date <= '" + info.date.Mid(0, 7) + "' ORDER BY Date DESC"));
			if (m_rs.NextRow())
				amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + newDiffrAm);
			else
				amountStorageFull = wxString::Format("%f", wxAtof(info.amountStrgFull) + newDiffrAm);

			if (!willHaveDepend)
			{
				ExecuteUpdate(wxS("INSERT INTO " + GetActiveStrgTable() +
					" (" + m_storageColumns[DB_COLUMN_DATE] + ", " + m_storageColumns[DB_COLUMN_CODE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + +", " + m_storageColumns[DB_COLUMN_AMOUNT_USED] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] +
					", " + m_storageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
					", " + m_storageColumns[DB_COLUMN_DNG_LVL] + ") VALUES('" + info.date.Mid(0, 7) + "', '" + info.code + "', '" + info.amountFormed + "', '"
					+ info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '" + info.amountUsed + "', '"
					+ info.amountDefusedUnit + "', '" + info.amountStorageUnit + "', '" + info.amountBurialUnit + "', '"
					+ info.tamountUsedUnit + "', '" + info.tamountDefusedUnit + "', '" + info.tamountStorageUnit
					+ "', '" + info.tamountBurialUnit + "', '" + info.structUnit10 + "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.codeDngLvl + "')"));
				int idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActiveStrgTable()));
				storageId = wxString::Format("%ld", idTemp);
				break;
			}
			else
			{

				ExecuteUpdate(wxS("INSERT INTO " + GetActiveStrgTable() +
					" (" + m_storageColumns[DB_COLUMN_DATE] + ", " + m_storageColumns[DB_COLUMN_CODE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + +", " + m_storageColumns[DB_COLUMN_AMOUNT_USED] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
					", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] +
					", " + m_storageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
					", " + m_storageColumns[DB_COLUMN_DNG_LVL] + ") VALUES('" + info.date.Mid(0, 7) + "', '" + info.code + "', '" + info.amountFormed + "', '"
					+ info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '" + info.amountUsed + "', '"
					+ info.amountDefused + "', '" + info.amountStorage + "', '" + info.amountBurial + "', '"
					+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
					+ "', '" + info.tamountBurial + "', '" + info.structUnit10 + "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.codeDngLvl + "')"));
				int idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActiveStrgTable()));
				storageId = wxString::Format("%ld", idTemp);
				break;
			}

		}
	}
	m_rs.Finalize();

	//we have to combine entrys without structUnit10 into entry with structUnit10 or combine all the empty entrys into one
	if (ExecuteScalar(wxS("SELECT COUNT(*) FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'")) > 1)
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable()
			+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " ASC"));
		wxString tempId,tempQuery;
		while (true)
		{
			if (!m_rs.CursorMoved())
				m_rs.NextRow();
			if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) == "")
			{
				tempId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
				tempQuery = "UPDATE " + GetActiveStrgTable() + " SET "
					+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_USED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_BURIAL]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) + ", "
					+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " + " + m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]);
				if (!m_rs.NextRow())
					break;
				ExecuteUpdate(tempQuery + " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]) + "'");
				ExecuteUpdate(wxS("DELETE FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + tempId + "'"));
			}
			else
				break;
		}
	}

	//we are updating full storage in case of multiple entrys for one date
	ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
		m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + amountStorageFull
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

	//we are adding new diffrance ammount to subsequent entrys in storage table reagrdless
	this->updateSubsqPOD10Strg(info.code, info.date, wxString::Format("%f", newDiffrAm), info.id);
	//substract old diffrance from subsequent passport table entrys
	this->updateSubsqPasspStrg(info.oldCode, info.oldDate);
	//set new entry info depending on whatever we have double entry or not
	if (willHaveDepend)
	{
		if (info.dependency != "")
		{
			wxString tempId1st,tempId2nd;
			if (info.dependency[0] == '1')
			{
				tempId1st = info.id;
				tempId2nd = info.dependency.Mid(2);
			}
			else
			{
				tempId2nd = info.id;
				tempId1st = info.dependency.Mid(2);
			}
				
			ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET "
				+ m_passpColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + info.amountReceivedPhys + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountReceivedOrg + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + info.amountFormed + "', "
				+ m_passpColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
				+ m_passpColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
				+ m_passpColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
				+ m_passpColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
				+ m_passpColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
				+ m_passpColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + " = '" + info.structUnit9 + "', "
				+ m_passpColumns[DB_COLUMN_STORAGE_ID] + " = '" + storageId + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10
				+ "' WHERE id = '" + tempId1st + "'"));

			ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET "
				+ m_passpColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountFormed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + " = '', "
				+ m_passpColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
				+ m_passpColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
				+ m_passpColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
				+ m_passpColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
				+ m_passpColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsedUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefusedUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorageUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurialUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsedUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefusedUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorageUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurialUnit + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
				+ m_passpColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + " = '', "
				+ m_passpColumns[DB_COLUMN_STORAGE_ID] + " = '" + storageId + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10
				+ "' WHERE id = '" + tempId2nd + "'"));
		}
		else
		{

			ExecuteUpdate(wxS("INSERT INTO " + GetActivePasspTable() + " ("
				+ m_passpColumns[DB_COLUMN_REGNUM] + ", " + m_passpColumns[DB_COLUMN_DATE] +
				", " + m_passpColumns[DB_COLUMN_OWNER] + ", " + m_passpColumns[DB_COLUMN_TRANSPORT] + ", " + m_passpColumns[DB_COLUMN_CODE] +
				", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_USED] +
				", " + m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
				", " + m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
				", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
				", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] +
				+", " + m_passpColumns[DB_COLUMN_ENTRYDATE] + ", " + m_passpColumns[DB_COLUMN_WASTE_NORM] + ", "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + ", " + m_passpColumns[DB_COLUMN_UNIT_ID] + ", "
				+ m_passpColumns[DB_COLUMN_DEPENDENCY] + ", " + m_passpColumns[DB_COLUMN_STORAGE_ID] +
				") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
				+ "', '" + info.transporter + "', '" + info.code + "', '"
				+ amount + "', '" + info.amountUsedUnit + "', '" + info.amountDefusedUnit + "', '" + info.amountStorageUnit + "', '"
				+ info.amountBurialUnit + "', '" + info.tamountUsedUnit + "', '" + info.tamountDefusedUnit + "', '" + info.tamountStorageUnit
				+ "', '" + info.tamountBurialUnit + "', '" + info.structUnit10 + "', '" + info.entryDate + "', '" + info.wasteNorm
				+ "', '" + amountStorageFull + "', '" + info.actveRecieverUnitID + "', '2/" + info.id + "', '" + storageId + "')"));

			int idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActivePasspTable()));
			wxString currentRowId = wxString::Format("%ld", idTemp);

			ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET "
				+ m_passpColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + info.amountReceivedPhys + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountReceivedOrg + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + info.amountFormed + "', "
				+ m_passpColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
				+ m_passpColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
				+ m_passpColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
				+ m_passpColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
				+ m_passpColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
				+ m_passpColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + " = '" + info.structUnit9 + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10 + "', "
				+ m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + info.activeUnitID + "', "
				+ m_passpColumns[DB_COLUMN_STORAGE_ID] + " = '" + storageId + "', "
				+ m_passpColumns[DB_COLUMN_DEPENDENCY] + " = '1/" + currentRowId
				+ "' WHERE id = '" + info.id + "'"));
		}
	}
	else
	{
		if (info.dependency != "")
		{
			wxString tempId1st, tempId2nd;
			if (info.dependency[0] == '1')
			{
				tempId1st = info.id;
				tempId2nd = info.dependency.Mid(2);
			}
			else
			{
				tempId2nd = info.id;
				tempId1st = info.dependency.Mid(2);
			}



			ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET "
				+ m_passpColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + info.amountReceivedPhys + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountReceivedOrg + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + info.amountFormed + "', "
				+ m_passpColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
				+ m_passpColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
				+ m_passpColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
				+ m_passpColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
				+ m_passpColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
				+ m_passpColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + " = '" + info.structUnit9 + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10 + "', "
				+ m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + info.activeUnitID + "', "
				+ m_passpColumns[DB_COLUMN_STORAGE_ID] + " = '" + storageId + "', "
				+ m_passpColumns[DB_COLUMN_DEPENDENCY] + " = '' WHERE id = '" + tempId1st + "'"));

			ExecuteUpdate(wxS("DELETE FROM " + GetActivePasspTable() + " WHERE id = '" + tempId2nd + "'"));

		}
		else
		{
			ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET "
				+ m_passpColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + info.amountReceivedPhys + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountReceivedOrg + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + info.amountFormed + "', "
				+ m_passpColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
				+ m_passpColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
				+ m_passpColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
				+ m_passpColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
				+ m_passpColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsed + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefused + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorage + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurial + "', "
				+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
				+ m_passpColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + " = '" + info.structUnit9 + "', "
				+ m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + info.structUnit10 + "', "
				+ m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + info.activeUnitID + "', "
				+ m_passpColumns[DB_COLUMN_STORAGE_ID] + " = '" + storageId + "', "
				+ m_passpColumns[DB_COLUMN_DEPENDENCY] + " = '' WHERE id = '" + info.id + "'"));
		}
	}

	//add new diffrance to subsequent storage in passport table entrys
	this->updateSubsqPasspStrg(info.code, info.date);
	Commit();
	return true;
}

/// <summary>
/// inserts entry if such code already exists or full storage amount has custom value
/// </summary>
/// <returns>true if successful, false otherwise</returns>
bool DBMain::insertNewEntry(const addPageInfo& info)
{
	Begin();
	wxString pAmountColumn, amount, sAmountColumn, amountStorageFull, storageId;
	double diffrAm;
	long idTemp;
	auto getAmount = [](wxString amount) { if (amount == "")
		return amount + " + 0";
	else if (wxAtof(amount) > 0)
		return " + " + amount;
	else
		return " - " + amount; };

	if (info.amountFormed != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (info.amountReceivedOrg != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}

	diffrAm = wxAtof(info.amountStorage) + (wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
		- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));

	//check if we already have entrys, if yes, get storage from them, otherwise get storage from custom user value or 0
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable()
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY Date DESC"));
	while (true)
	{
		wxString structUnit10{ info.structUnit10 };
		if (m_rs.NextRow())
		{
			if (info.structUnit10 == "")
			{
				// if struct is empty we dont care on what entry we are setting the values so we skip next check 
				structUnit10 = m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]);
			}
			else if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != info.structUnit10 && m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != "")
				continue;

			amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + diffrAm);
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", diffrAm) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + getAmount(info.amountFormed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + getAmount(info.amountReceivedPhys) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + getAmount(info.amountReceivedOrg) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + getAmount(info.amountUsed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + getAmount(info.amountDefused) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + getAmount(info.amountStorage) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + getAmount(info.amountBurial) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + getAmount(info.tamountUsed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + getAmount(info.tamountDefused) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + getAmount(info.tamountBurial) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + getAmount(info.tamountStorage) + ", "
				+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + structUnit10
				+ "' WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]) + "'"));

			storageId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
			this->updateSubsqPOD10Strg(info.code, info.date, wxString::Format("%f", diffrAm), storageId);
			break;
		}
		else
		{
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code
				+ "' AND Date <= '" + info.date.Mid(0, 7) + "' ORDER BY Date DESC"));
			if (m_rs.NextRow())
				amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + diffrAm);
			else
				amountStorageFull = wxString::Format("%f", wxAtof(info.amountStrgFull) + diffrAm);

			ExecuteUpdate(wxS("INSERT INTO " + GetActiveStrgTable() +
				" (" + m_storageColumns[DB_COLUMN_DATE] + ", " + m_storageColumns[DB_COLUMN_CODE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + +", " + m_storageColumns[DB_COLUMN_AMOUNT_USED] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] +
				", " + m_storageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
				", " + m_storageColumns[DB_COLUMN_DNG_LVL] + ") VALUES('" + info.date.Mid(0, 7) + "', '" + info.code + "', '" + info.amountFormed + "', '"
				+ info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '" + info.amountUsed + "', '"
				+ info.amountDefused + "', '" + info.amountStorage + "', '" + info.amountBurial + "', '"
				+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
				+ "', '" + info.tamountBurial + "', '" + info.structUnit10 + "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.codeDngLvl + "')"));
			idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActiveStrgTable()));
			storageId = wxString::Format("%ld", idTemp);
			this->updateSubsqPOD10Strg(info.code, info.date, wxString::Format("%f", diffrAm), storageId);
			break;
		}
	}

	//we are updating full storage in case of multiple entrys for one date
	ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
		m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + amountStorageFull
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));


	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE id = '" + storageId + "'"));
	amountStorageFull = m_rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);

	ExecuteUpdate(wxS("INSERT INTO " + GetActivePasspTable() + " ("
		+ m_passpColumns[DB_COLUMN_REGNUM] + ", " + m_passpColumns[DB_COLUMN_DATE] +
		", " + m_passpColumns[DB_COLUMN_OWNER] + ", " + m_passpColumns[DB_COLUMN_TRANSPORT] +
		", " + m_passpColumns[DB_COLUMN_RECEIVER] + ", " + m_passpColumns[DB_COLUMN_CODE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] +
		", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + ", " + m_passpColumns[DB_COLUMN_ENTRYDATE] +
		", " + m_passpColumns[DB_COLUMN_WASTE_NORM] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
		", " + m_passpColumns[DB_COLUMN_UNIT_ID] + ", " + m_passpColumns[DB_COLUMN_STORAGE_ID] + ", " + m_passpColumns[DB_COLUMN_DNG_LVL]
		+ ") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
		+ "', '" + info.transporter + "', '" + info.receiver + "', '" + info.code + "', '"
		+ info.amountFormed + "', '" + info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '"
		+ info.amountUsed + "', '" + info.amountDefused + "', '"
		+ info.amountStorage + "', '" + info.amountBurial + "', '"
		+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
		+ "', '" + info.tamountBurial + "', '" + info.structUnit10
		+ "', '" + info.structUnit9 + "', '" + info.entryDate
		+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.activeUnitID + "', '" + storageId + "', '" + info.codeDngLvl + "')"));

	updateSubsqPasspStrg(info.code, info.date);
	m_rs.Finalize();
	Commit();
	return true;

}

bool DBMain::insertNewDoubleEntry(const addPageInfo& info)
{
	Begin();
	wxString pAmountColumn, amount, sAmountColumn, newAmountStorageFull,amountStorageFull, storageId;
	double diffrAm;
	long idTemp;

	auto getAmount = [](wxString amount) { if (amount == "")
		return amount + " + 0";
	else if (wxAtof(amount) > 0)
		return " + " + amount;
	else
		return " - " + amount; };

	if (info.amountFormed != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (info.amountReceivedOrg != "")
	{
		sAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}

	diffrAm = wxAtof(info.amountStorageUnit) + (wxAtof(amount) - wxAtof(info.amountStorageUnit) - wxAtof(info.amountBurialUnit) - wxAtof(info.amountUsedUnit)
		- wxAtof(info.amountDefusedUnit) - wxAtof(info.tamountBurialUnit) - wxAtof(info.tamountStorageUnit) - wxAtof(info.tamountUsedUnit) - wxAtof(info.tamountDefusedUnit));
	
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable()
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " ASC"));
	//checking if entry with empty or equal structunit10 in storage table already exists, if yes then update it, otherwise create a new one
	while (true)
	{
		wxString structUnit10{ info.structUnit10 };
		if (m_rs.NextRow())
		{
			if (info.structUnit10 == "")
			{
				// if struct is empty we dont care on what entry we are setting the values so we skip next check 
				structUnit10 = m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]);
			}
			else if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != info.structUnit10 && m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]) != "")
				continue;
			amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + diffrAm);
			ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
				m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", diffrAm) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + getAmount(info.amountFormed) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + getAmount(info.amountReceivedPhys) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + getAmount(info.amountReceivedOrg) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_USED] + getAmount(info.amountUsedUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + getAmount(info.amountDefusedUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + getAmount(info.amountStorageUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + getAmount(info.amountBurialUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + getAmount(info.tamountUsedUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + getAmount(info.tamountDefusedUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + getAmount(info.tamountBurialUnit) + ", "
				+ m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + getAmount(info.tamountStorageUnit) + ", "
				+ m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] + " = '" + structUnit10
				+ "' WHERE " + m_storageColumns[DB_COLUMN_ID] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID])+"'"));
			
			storageId = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
			this->updateSubsqPOD10Strg(info.code, info.date, wxString::Format("%f", diffrAm), storageId);
			break;
		}
		else
		{
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Code = '" + info.code
				+ "' AND Date <= '" + info.date.Mid(0, 7) + "' ORDER BY Date DESC"));
			if (m_rs.NextRow())
				amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + diffrAm);
			else
				amountStorageFull = wxString::Format("%f", wxAtof(info.amountStrgFull) + diffrAm);

			ExecuteUpdate(wxS("INSERT INTO " + GetActiveStrgTable() +
				" (" + m_storageColumns[DB_COLUMN_DATE] + ", " + m_storageColumns[DB_COLUMN_CODE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + +", " + m_storageColumns[DB_COLUMN_AMOUNT_USED] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
				", " + m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_storageColumns[DB_COLUMN_STRUCTURAL_POD10] +
				", " + m_storageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
				", " + m_storageColumns[DB_COLUMN_DNG_LVL] + ") VALUES('" + info.date.Mid(0, 7) + "', '" + info.code + "', '" + info.amountFormed + "', '"
				+ info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '" + info.amountUsed + "', '"
				+ info.amountDefusedUnit + "', '" + info.amountStorageUnit + "', '" + info.amountBurialUnit + "', '"
				+ info.tamountUsedUnit + "', '" + info.tamountDefusedUnit + "', '" + info.tamountStorageUnit
				+ "', '" + info.tamountBurialUnit + "', '" + info.structUnit10 + "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.codeDngLvl + "')"));
			idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActiveStrgTable()));
			storageId = wxString::Format("%i", idTemp);
			this->updateSubsqPOD10Strg(info.code, info.date, wxString::Format("%f", diffrAm), storageId);
			break;
		}
	}
	m_rs.Finalize();
	//we are updating full storage in case of multiple entrys for one date
	ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
		m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + amountStorageFull
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0,7) + "%'"));


	idTemp = ExecuteScalar(wxS("SELECT max(ROWID) FROM " + GetActivePasspTable()));
	wxString passpId = wxString::Format("%ld", idTemp + 2);
	//inserting two new entries for each structural unit
	ExecuteUpdate(wxS("INSERT INTO " + GetActivePasspTable() + " ("
		+ m_passpColumns[DB_COLUMN_REGNUM] + ", " + m_passpColumns[DB_COLUMN_DATE] +
		", " + m_passpColumns[DB_COLUMN_OWNER] + ", " + m_passpColumns[DB_COLUMN_TRANSPORT] + ", " + m_passpColumns[DB_COLUMN_CODE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] +
		+", " + m_passpColumns[DB_COLUMN_ENTRYDATE] + ", " + m_passpColumns[DB_COLUMN_WASTE_NORM] + ", "
		+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + ", " + m_passpColumns[DB_COLUMN_UNIT_ID] + ", "
		+ m_passpColumns[DB_COLUMN_DEPENDENCY] + ", " + m_passpColumns[DB_COLUMN_STORAGE_ID] + ", " + m_passpColumns[DB_COLUMN_DNG_LVL] + 
		") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
		+ "', '" + info.transporter + "', '" + info.code + "', '"
		+ amount + "', '" + info.amountUsedUnit + "', '" + info.amountDefusedUnit + "', '" + info.amountStorageUnit + "', '"
		+ info.amountBurialUnit + "', '" + info.tamountUsedUnit + "', '" + info.tamountDefusedUnit + "', '" + info.tamountStorageUnit
		+ "', '" + info.tamountBurialUnit + "', '" + info.structUnit10 + "', '" + info.entryDate + "', '" + info.wasteNorm
		+ "', '" + amountStorageFull + "', '" + info.actveRecieverUnitID + "', '2/" + passpId + "', '" + storageId + "', '" + info.codeDngLvl + "')"));

	passpId = wxString::Format("%ld", idTemp + 1);
	ExecuteUpdate(wxS("INSERT INTO " + GetActivePasspTable() + " ("
		+ m_passpColumns[DB_COLUMN_REGNUM] + ", " + m_passpColumns[DB_COLUMN_DATE] +
		", " + m_passpColumns[DB_COLUMN_OWNER] + ", " + m_passpColumns[DB_COLUMN_TRANSPORT] +
		", " + m_passpColumns[DB_COLUMN_RECEIVER] + ", " + m_passpColumns[DB_COLUMN_CODE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_FORMED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
		", " + m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD10] +
		", " + m_passpColumns[DB_COLUMN_STRUCTURAL_POD9] + ", " + m_passpColumns[DB_COLUMN_ENTRYDATE] +
		", " + m_passpColumns[DB_COLUMN_WASTE_NORM] + ", " + m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
		", " + m_passpColumns[DB_COLUMN_UNIT_ID] + ", " + m_passpColumns[DB_COLUMN_DEPENDENCY] + ", " + m_passpColumns[DB_COLUMN_STORAGE_ID] + 
		", " + m_passpColumns[DB_COLUMN_DNG_LVL] + ") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
		+ "', '" + info.transporter + "', '" + info.receiver + "', '" + info.code + "', '"
		+ info.amountFormed + "', '" + info.amountReceivedPhys + "', '" + info.amountReceivedOrg + "', '"
		+ info.amountUsed + "', '" + info.amountDefused + "', '"
		+ info.amountStorage + "', '" + info.amountBurial + "', '"
		+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
		+ "', '" + info.tamountBurial + "', '" + info.structUnit10
		+ "', '" + info.structUnit9 + "', '" + info.entryDate
		+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "', '" + info.activeUnitID + "', '1/" + passpId + "', '" + storageId + "', '" + info.codeDngLvl + "')"));

	updateSubsqPasspStrg(info.code, info.date);
	m_rs.Finalize();
	Commit();
	return true;
}

bool DBMain::isInitStorageViable(const wxString& code, const wxString& date)
{
	m_rs = ExecuteQuery("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + code + "' AND " +
		m_storageColumns[DB_COLUMN_DATE] + " <= '" + date.Mid(0, 7) + "'");
	if (m_rs.NextRow())
	{
		m_rs.Finalize();
		return false;
	}
	return true;
}

wxString DBMain::GetWasteNormByCode(const wxString& code)
{
	m_rs = ExecuteQuery("SELECT * FROM " + GetActiveCodeInfoTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + " = " + code);
	wxString str;
	if (m_rs.NextRow())
	{
		str = m_rs.GetAsString(m_codeInfoColumns[DB_COLUMN_WASTE_NORM]);
	}
	m_rs.Finalize();
	return str;
}

bool DBMain::DeleteOrgTables(int orgID)
{
	Begin();
	ExecuteUpdate(wxS("DROP TABLE IF EXISTS " + DBPasspTableName + wxString::Format("%i", orgID)));
	ExecuteUpdate(wxS("DROP TABLE IF EXISTS " + DBStorageTableName + wxString::Format("%i", orgID)));
	ExecuteUpdate(wxS("DROP TABLE IF EXISTS " + DBCodeInfoTableName + wxString::Format("%i", orgID)));
	Commit();
	return true;
}

bool DBMain::insertInitStorageEntry(const wxString& code, const wxDateTime& date, const wxString& amount)
{
	Begin();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + code + "'"));
	m_rs.NextRow();
	wxString codeDng{ m_rs.GetAsString(2) };
	m_rs.Finalize();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + code + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));
	if (m_rs.NextRow())
	{
		m_rs.Finalize();
		return false;
	}
	m_rs.Finalize();
	wxString dateS = date.Format(wxS("%Y.%m.%d"));
	ExecuteUpdate(wxS("INSERT INTO " + GetActiveStrgTable() + " (" + m_storageColumns[DB_COLUMN_DATE] + ", " + m_storageColumns[DB_COLUMN_CODE] + ", "
		+ m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + ", " + m_storageColumns[DB_COLUMN_INITIAL] + ", " + m_storageColumns[DB_COLUMN_DNG_LVL] + ")" +
		" VALUES('"+ dateS.Mid(0, 7) + "', '" + code + "', '" + amount + "', '1', '" + codeDng + "')"));

	ExecuteUpdate(wxS("INSERT INTO " + GetActivePasspTable() + " (" + m_passpColumns[DB_COLUMN_DATE] + ", " + m_passpColumns[DB_COLUMN_CODE] + ", "
		+ m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + ", " + m_passpColumns[DB_COLUMN_INITIAL] + ", " + m_passpColumns[DB_COLUMN_DNG_LVL] + ") " +
		" VALUES ('" + dateS + "', '" + code + "', '" + amount + "', '1', '" + codeDng + "')"));

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + code + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));
	wxString idPod10 = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
	m_rs.Finalize();

	updateSubsqPasspStrg(code, dateS);
	updateSubsqPOD10Strg(code, dateS, amount, idPod10);
	Commit();
	return true;

}

bool DBMain::editInitStorageEntry(const wxString& code, const wxDateTime& date, const wxString& amount,const wxString& oldCode)
{
	Begin();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + code + "'"));
	m_rs.NextRow();
	wxString codeDng{ m_rs.GetAsString(2) };
	m_rs.Finalize();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + oldCode + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));
	if (!m_rs.NextRow())
	{
		m_rs.Finalize();
		return false;
	}
	double diff = wxAtof(amount) - m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);
	wxString diffS{ std::to_string(diff) };
	wxString oldStorage = wxString::Format("%f", -1 * m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
	wxString dateS = date.Format(wxS("%Y.%m.%d"));
	wxString idPOD10= m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
	m_rs.Finalize();


	ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
		m_storageColumns[DB_COLUMN_CODE] + "= '" + code + "', " +
		m_storageColumns[DB_COLUMN_DATE] + "= '" + dateS.Mid(0, 7) + "', " +
		m_storageColumns[DB_COLUMN_DNG_LVL] + "= '" + codeDng + "', " +
		m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + "= '" + amount +
		"' WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + oldCode + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));

	ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET " +
		m_passpColumns[DB_COLUMN_CODE] + "= '" + code + "', " +
		m_passpColumns[DB_COLUMN_DATE] + "= '" + dateS + "', " +
		m_passpColumns[DB_COLUMN_DNG_LVL] + "= '" + codeDng + "', " +
		m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + "= '" + amount +
		"' WHERE " + m_passpColumns[DB_COLUMN_CODE] + " = '" + oldCode + "' AND " +
		m_passpColumns[DB_COLUMN_INITIAL] + " = '1'"));

	if (oldCode == code)
	{
		updateSubsqPOD10Strg(code, dateS, diffS, idPOD10);
		updateSubsqPasspStrg(code, dateS);
	
	}
	else
	{
		updateSubsqPOD10Strg(oldCode, dateS, oldStorage, idPOD10);
		updateSubsqPasspStrg(oldCode, dateS);
		updateSubsqPOD10Strg(code, dateS, amount, idPOD10);
		updateSubsqPasspStrg(code, dateS);
	}
	m_rs.Finalize();
	Commit();
	return true;
}

bool DBMain::deleteInitStorageEntry(const wxString& code,const wxString& storage)
{
	Begin();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " = '" + code + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));
	if (!m_rs.NextRow())
	{
		m_rs.Finalize();
		return false;
	}
	wxString date = m_rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]);
	wxString idPOD10 = m_rs.GetAsString(m_storageColumns[DB_COLUMN_ID]);
	m_rs.Finalize();

	ExecuteUpdate(wxS("DELETE FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_CODE] + "= '" + code + "' AND " +
		m_storageColumns[DB_COLUMN_INITIAL] + " = '1'"));
	ExecuteUpdate(wxS("DELETE FROM " + GetActivePasspTable() + " WHERE " + m_passpColumns[DB_COLUMN_CODE] + "= '" + code + "' AND " +
		m_passpColumns[DB_COLUMN_INITIAL] + " = '1'"));

	updateSubsqPOD10Strg(code, date, '-' + storage, idPOD10);
	updateSubsqPasspStrg(code, date);
	Commit();
	return true;
}

//Updates subsequent full storage amount in passport table
void  DBMain::updateSubsqPasspStrg(const wxString& code, const wxString& date)
{
	wxSQLite3ResultSet rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Code = '" + code
		+ "' AND Date >= '" + date.Mid(0, 7) + "'"));
	while (rs.NextRow())
	{
		ExecuteUpdate(wxS("UPDATE " + GetActivePasspTable() + " SET " +
			m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + rs.GetAsString(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL])
			+ " WHERE Code = '" + code + "' AND Date LIKE '%" + rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]) + "%'"));
	}
	rs.Finalize();
}

//Updates subsequent full storage amount in storage table
void  DBMain::updateSubsqPOD10Strg(const wxString& code, const wxString& date, const wxString& diffAm,const wxString& id)
{
		ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET " +
			m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]
			+ " + " + diffAm + " WHERE Date > '" + date.Mid(0, 7) + "' AND " + m_storageColumns[DB_COLUMN_CODE] + " = '" + code + "'"));
}


void DBMain::getPod10TableCount(pod10Info &data, const wxString& startDate, const wxString& endDate)
{
	data.tableCount = ExecuteScalar(wxS("SELECT COUNT(DISTINCT Date) FROM " + GetActiveStrgTable() + " WHERE " + 
		m_storageColumns[DB_COLUMN_DATE] + " >= '" + startDate + 
		"' AND " + m_storageColumns[DB_COLUMN_DATE] + " <= '" + endDate + "'  AND ("
		+ m_storageColumns[DB_COLUMN_INITIAL] + " IS NULL OR " + m_storageColumns[DB_COLUMN_INITIAL] + " = '')"));

	m_rs = ExecuteQuery(wxS("SELECT DISTINCT Date FROM " + GetActiveStrgTable() + " WHERE " + 
		m_storageColumns[DB_COLUMN_DATE] + " >= '" + startDate + "' AND " 
		+ m_storageColumns[DB_COLUMN_DATE] + " <= '" + endDate + "' AND ("
		+ m_storageColumns[DB_COLUMN_INITIAL] + " IS NULL OR " + m_storageColumns[DB_COLUMN_INITIAL] + " = '')"));

	while (m_rs.NextRow())
	{
		data.allDates.Add(m_rs.GetAsString(0));
	}
	m_rs.Finalize();
	data.allDates.Sort();
}

void DBMain::getPod10TableInfo(pod10Info &data, const wxString &date)
{
	int count{0};
	if (data.rowCount != 0)
	{
		data.emptyPod10StructInfo();
	}
	m_rs = ExecuteQuery(wxS("SELECT DISTINCT " + m_storageColumns[DB_COLUMN_CODE] + " FROM " + GetActiveStrgTable()));
	std::vector<wxString> distinctCodes{};
	while (m_rs.NextRow())
	{
		distinctCodes.push_back(m_rs.GetAsString(m_storageColumns[DB_COLUMN_CODE]));
	}
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE Date LIKE '%" + date + "%' AND ("
		+ m_storageColumns[DB_COLUMN_INITIAL] + " IS NULL OR " + m_storageColumns[DB_COLUMN_INITIAL] + " = '')"));
	while (m_rs.NextRow())
	{
		data.date = m_rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]);
		data.entryDate = m_rs.GetDate(m_storageColumns[DB_COLUMN_ENTRYDATE]).Format("%d.%m.%Y");
		data.code.Add(m_rs.GetAsString(m_storageColumns[DB_COLUMN_CODE]));
		data.amountFormed.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_FORMED]));
		data.amountReOrg.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]));
		data.amountRePhys.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]));
		data.amountUsed.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_USED]));
		data.amountDefused.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_DEFUSED]));
		data.amountSelfstorage.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]));
		data.amountBurial.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_BURIAL]));
		data.amountTransferUsed.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]));
		data.amountTransferDefused.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
		data.amountTransferStorage.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
		data.amountTransferBurial.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]));
		data.amountSelfstorageFull.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
		data.wasteNorm.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_WASTE_NORM]));
		data.structuralUnit.Add(m_rs.GetAsString(m_storageColumns[DB_COLUMN_STRUCTURAL_POD10]));
		data.codeDangerLVL.Add(m_rs.GetAsString(m_storageColumns[DB_COLUMN_DNG_LVL]));
		distinctCodes.erase(std::find(distinctCodes.begin(), distinctCodes.end(), m_rs.GetAsString(m_storageColumns[DB_COLUMN_CODE])));
		count++;
	}
	m_rs.Finalize();
	if(!distinctCodes.empty())
	{
				//we gather all previous entrys that have sotrage amount
		wxString query = "SELECT MAX("+ m_storageColumns[DB_COLUMN_DATE] +"),* FROM " + GetActiveStrgTable() 
			+ " WHERE " + m_storageColumns[DB_COLUMN_CODE] + " IN (";
		for (const auto& it : distinctCodes)
		{
			query += it + ", ";
		}
		query.RemoveLast(2);
		query += ") AND " + m_storageColumns[DB_COLUMN_DATE] + " < '" + date + "' GROUP BY " + m_storageColumns[DB_COLUMN_CODE];
		m_rs = ExecuteQuery(query);
		while (m_rs.NextRow())
		{
			if (m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) > 0)
			{
				data.code.Add(m_rs.GetAsString(m_storageColumns[DB_COLUMN_CODE]));
				data.codeDangerLVL.Add(m_rs.GetAsString(m_storageColumns[DB_COLUMN_DNG_LVL]));
				data.amountSelfstorageFull.Add(m_rs.GetDouble(m_storageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
				data.amountFormed.Add(0.0);
				data.amountReOrg.Add(0.0);
				data.amountRePhys.Add(0.0);
				data.amountUsed.Add(0.0);
				data.amountDefused.Add(0.0);
				data.amountSelfstorage.Add(0.0);
				data.amountBurial.Add(0.0);
				data.amountTransferUsed.Add(0.0);
				data.amountTransferDefused.Add(0.0);
				data.amountTransferStorage.Add(0.0);
				data.amountTransferBurial.Add(0.0);
				data.wasteNorm.Add(0.0);
				data.structuralUnit.Add("");
				++count;
			}
		}
		m_rs.Finalize();
	}

	data.rowCount = std::move(count);
	data.sortByCode(0, data.code.size()-1);
	m_rs.Finalize();


}

void DBMain::getPod10TableCodeDngr(pod10Info &data, const wxArrayString &codes)
{
	for (size_t j{ 0 }; j < codes.size(); ++j)
	{
		m_rs = ExecuteQuery("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + codes[j] + "'");
		m_rs.NextRow();
		data.codeDescription.Add(m_rs.GetAsString(1));
		m_rs.Finalize();
	}
	m_rs.Finalize();
}

void DBMain::getJournalTableInfo(passportJournalInfo& data, const wxString& startDate, const wxString& endDate)
{

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE " + m_passpColumns[DB_COLUMN_DATE] + " >= '" + startDate +
		"' AND " + m_passpColumns[DB_COLUMN_DATE] + " <= '" + endDate + "' ORDER BY Date"));
	while (m_rs.NextRow())
	{
		if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_DEPENDENCY]).starts_with('2') || m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]) == "")
			continue;
		data.amountTransferBurial.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]));
		data.amountTransferDefused.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
		data.amountTransferUsed.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]));
		data.amountTransferStorage.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
		data.amountBurial.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]));
		data.amountDefused.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]));
		data.amountUsed.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_USED]));
		data.amountStorage.push_back(m_rs.GetDouble(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]));
		data.code.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]));
		data.codeDangerLVL.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_DNG_LVL]));
		data.date.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_DATE]));
		data.receiver.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_RECEIVER]));
		data.regnum.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_REGNUM]));
		data.transporter.push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]));

	}
	m_rs.Finalize();

}

//ID should always be last in array
void DBMain::getListItemData(std::vector<std::vector<wxString>>& item)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + ""));
	int count{ 0 };
	while (m_rs.NextRow())
	{
		item.push_back(std::vector<wxString>());
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_REGNUM]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_DATE]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_OWNER]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_RECEIVER]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD10]));
		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]));

		item[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]));

		count++;
	}
	m_rs.Finalize();
}

int DBMain::getCodeInfoRowAmount()
{
	return ExecuteScalar(wxS("SELECT COUNT(*) FROM " + GetActiveCodeInfoTable()));
}

void DBMain::getCodeInfoList(std::vector<std::vector<wxString>>& list)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveCodeInfoTable() + ""));
	int count{ 0 };
	while (m_rs.NextRow())
	{
		list.push_back(std::vector<wxString>());
		list[count].push_back(m_rs.GetAsString(m_codeInfoColumns[DB_COLUMN_CODE]));
		list[count].push_back(m_rs.GetAsString(m_codeInfoColumns[DB_COLUMN_WASTE_NORM]));
		count++;
	}
}

void DBMain::getInitStorageList(std::vector<std::vector<wxString>>& list)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE " + m_passpColumns[DB_COLUMN_INITIAL] + " = 1"));
	int count{ 0 };
	wxDateTime temp;
	while (m_rs.NextRow())
	{
		temp = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]);
		list.push_back(std::vector<wxString>());
		list[count].push_back(temp.Format("%d.%m.%Y"));
		list[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]));
		list[count].push_back(m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]));
		count++;
	}
}

//returns Y.m.d format
wxDateTime DBMain::getFirstEntryDate()
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " ORDER BY " + m_passpColumns[DB_COLUMN_DATE] + " ASC"));
	wxDateTime date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]);
	m_rs.Finalize();
	return date;

}
wxDateTime DBMain::getFirstEntryByCodeNoInit(const wxString& code)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE " + m_passpColumns[DB_COLUMN_CODE] + " = '" + code 
		+ "' ORDER BY " + m_passpColumns[DB_COLUMN_DATE] + " ASC"));

	wxDateTime date;
	if (m_rs.NextRow())
	{
		if (m_rs.GetInt(m_passpColumns[DB_COLUMN_INITIAL]) == 1)
		{
			if (m_rs.NextRow())
				date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]);
			else
				date = wxDateTime::Today();
		}
		else
			date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]);
	}
	else
		date = wxDateTime::Today();
	m_rs.Finalize();
	return date;

}
wxDateTime DBMain::getLastEntryDate()
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " ORDER BY " + m_passpColumns[DB_COLUMN_DATE] + " DESC"));
	wxDateTime date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]);
	m_rs.Finalize();
	return date;
}

int DBMain::getPasspRowAmount()
{
	return ExecuteScalar(wxS("SELECT COUNT(*) FROM " + GetActivePasspTable() +
		" WHERE " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + wxString::Format("%i", Settings::getActiveUnitID()) + "'"));
}

void DBMain::getNextRowData(std::vector<wxString> &rowItem,const wxString& id, bool idIsHigher,const wxString& offset)
{
	if (id.IsEmpty())
		return;
	wxString idOp, idSortOrder;
	if (idIsHigher)
	{
		idOp = ">=";
		idSortOrder = "ASC";
	}
	else
	{
		idOp = "<=";
		idSortOrder = "DESC";
	}

		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE rowid " + idOp + " " + id
			+ " AND " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + wxString::Format("%i", Settings::getActiveUnitID()) + 
			"' ORDER BY rowid " + idSortOrder + " LIMIT 1 OFFSET " + offset));

	if (m_rs.NextRow())
	{
		rowItem[static_cast<int>(Grid_label::grid_regnum)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_REGNUM]);
		rowItem[static_cast<int>(Grid_label::grid_code)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]);
		rowItem[static_cast<int>(Grid_label::grid_date)] = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]).Format(wxS("%d.%m.%Y"));
		rowItem[static_cast<int>(Grid_label::grid_owner)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_OWNER]);
		rowItem[static_cast<int>(Grid_label::grid_receiver)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_RECEIVER]);
		rowItem[static_cast<int>(Grid_label::grid_transporter)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]);
		rowItem[static_cast<int>(Grid_label::grid_amount_formed)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]);
		rowItem[static_cast<int>(Grid_label::grid_amount_received_phys)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]);
		rowItem[static_cast<int>(Grid_label::grid_amount_received_org)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]);
		rowItem[static_cast<int>(Grid_label::grid_amount_used)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED]);
		rowItem[static_cast<int>(Grid_label::grid_amount_defused)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]);
		rowItem[static_cast<int>(Grid_label::grid_amount_burial)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]);
		rowItem[static_cast<int>(Grid_label::grid_amount_storage)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]);
		rowItem[static_cast<int>(Grid_label::grid_amount_tUsed)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]);
		rowItem[static_cast<int>(Grid_label::grid_amount_tDefused)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]);
		rowItem[static_cast<int>(Grid_label::grid_amount_tBurial)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]);
		rowItem[static_cast<int>(Grid_label::grid_amount_tStorage)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]);
		rowItem[static_cast<int>(Grid_label::grid_amount_storageFull)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);
		rowItem[static_cast<int>(Grid_label::grid_struct_unitPOD9)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]);
		rowItem[static_cast<int>(Grid_label::grid_waste_norm)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]);
		rowItem[static_cast<int>(Grid_label::grid_max_labels)] = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
	}

	m_rs.Finalize();
}

wxString DBMain::getIdOfRow(const wxString& row)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE rowid AND " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '"+
		wxString::Format("%i",Settings::getActiveUnitID()) + "' LIMIT 1 OFFSET " + row));
	m_rs.NextRow();
	wxString newRow = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
	m_rs.Finalize();
	return newRow;
}

wxString DBMain::gridToDBLabel(Grid_label gridLabel)
{
	switch (gridLabel)
	{
	case Grid_label::grid_regnum:
		return m_passpColumns[DB_COLUMN_REGNUM];
	case Grid_label::grid_code:
		return m_passpColumns[DB_COLUMN_CODE];
	case Grid_label::grid_date:
		return m_passpColumns[DB_COLUMN_DATE];
	case Grid_label::grid_owner:
		return m_passpColumns[DB_COLUMN_OWNER];
	case Grid_label::grid_receiver:
		return m_passpColumns[DB_COLUMN_RECEIVER];
	case Grid_label::grid_transporter:
		return m_passpColumns[DB_COLUMN_TRANSPORT];
	case Grid_label::grid_amount_formed:
		return m_passpColumns[DB_COLUMN_AMOUNT_FORMED];
	case Grid_label::grid_amount_received_phys:
		return m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
	case Grid_label::grid_amount_received_org:
		return m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
	case Grid_label::grid_amount_used:
		return m_passpColumns[DB_COLUMN_AMOUNT_USED];
	case Grid_label::grid_amount_defused:
		return m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED];
	case Grid_label::grid_amount_burial:
		return m_passpColumns[DB_COLUMN_AMOUNT_BURIAL];
	case Grid_label::grid_amount_storage:
		return m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE];
	case Grid_label::grid_amount_tUsed:
		return m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED];
	case Grid_label::grid_amount_tDefused:
		return m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED];
	case Grid_label::grid_amount_tBurial:
		return m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL];
	case Grid_label::grid_amount_tStorage:
		return m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE];
	case Grid_label::grid_amount_storageFull:
		return m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL];
	case Grid_label::grid_struct_unitPOD9:
		return m_passpColumns[DB_COLUMN_STRUCTURAL_POD9];
	case Grid_label::grid_waste_norm:
		return m_passpColumns[DB_COLUMN_WASTE_NORM];
	default:
		return "";
	}
}

wxString DBMain::getIdByRowOffset(const wxString& id, bool idIsHigher, const wxString& offset)
{
	wxString idOp, idSortOrder;
	if (idIsHigher)
	{
		idOp = ">=";
		idSortOrder = "ASC";
	}
	else
	{
		idOp = "<=";
		idSortOrder = "DESC";
	}

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE rowid " + idOp + " " + id
		+ " AND " + m_passpColumns[DB_COLUMN_UNIT_ID] + " = '" + wxString::Format("%i", Settings::getActiveUnitID()) + 
		"' ORDER BY rowid " + idSortOrder + " LIMIT 1 OFFSET " + offset));
	wxString rowID = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
	m_rs.Finalize();
	return rowID;

}

void DBMain::getRowDataByID(addPageInfo& info, const wxString& id)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE rowid = " + id));
	if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_DEPENDENCY]) != "")
	{
		if (m_rs.GetAsString(m_passpColumns[DB_COLUMN_DEPENDENCY])[0] == '2')
		{
			wxString newID{ m_rs.GetAsString(m_passpColumns[DB_COLUMN_DEPENDENCY]).Mid(2) };
			m_rs.Finalize();
			m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActivePasspTable() + " WHERE rowid = " + newID));
		}
	}
	m_rs.NextRow();

	info.regnum = m_rs.GetAsString(DB_COLUMN_REGNUM);
	info.code = m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]);
	info.date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]).Format(wxS("%Y.%m.%d"));
	info.owner = m_rs.GetAsString(m_passpColumns[DB_COLUMN_OWNER]);
	info.receiver = m_rs.GetAsString(m_passpColumns[DB_COLUMN_RECEIVER]);
	info.transporter = m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]);
	info.amountFormed = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]);
	info.amountReceivedPhys = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]);
	info.amountReceivedOrg = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]);
	info.amountUsed = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED]);
	info.amountDefused = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]);
	info.amountBurial = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]);
	info.amountStorage = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]);
	info.tamountUsed= m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]);
	info.tamountDefused = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]);
	info.tamountBurial = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]);
	info.tamountStorage = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]);
	info.amountStrgFull = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);
	info.structUnit9 = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]);
	info.structUnit10 = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD10]);
	info.wasteNorm = m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]);
	info.id = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
	info.dependency = m_rs.GetAsString(m_passpColumns[DB_COLUMN_DEPENDENCY]);
	info.storageId = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STORAGE_ID]);
	m_rs.Finalize();
}

bool DBMain::AskToEnterAllEntryDates(const wxString& startDate, const wxString& endDate)
{
	Begin();
	bool dlgCancel{false};
	while(true)
	{

		m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveStrgTable() + " WHERE " + m_storageColumns[DB_COLUMN_DATE] + " >= '" + startDate.Mid(0, 7) +
			"' AND " + m_storageColumns[DB_COLUMN_DATE] + " <= '" + endDate.Mid(0, 7) + "' " + " AND (" 
			+ m_storageColumns[DB_COLUMN_ENTRYDATE] + " IS NULL OR "+ m_storageColumns[DB_COLUMN_ENTRYDATE] + " = '') AND (" 
			+ m_storageColumns[DB_COLUMN_INITIAL] + " IS NULL OR " + m_storageColumns[DB_COLUMN_INITIAL] + " = '')"));

		if (!m_rs.NextRow())
			break;
		
		if (m_rs.GetAsString(m_storageColumns[DB_COLUMN_ENTRYDATE]) == "")
		{
			wxDialog dlg(nullptr, wxID_ANY, wxString::FromUTF8("Добавить дату внесения учетной записи"), wxDefaultPosition, wxSize(370, 200), wxDEFAULT_DIALOG_STYLE);
			wxPanel* main = new wxPanel(&dlg);
			main->SetBackgroundColour(*wxWHITE);
			main->SetFont(gui_MainFont);
			wxStaticText* staticDate = new wxStaticText(main, wxID_ANY, 
			wxString::FromUTF8("Дата внесения уч. записи в книгу ПОД10\n на дату \"") + m_rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]) + "\":");
			staticDate->SetForegroundColour(*wxBLACK);
			wxDatePickerCtrl* dateCtrl = new wxDatePickerCtrl(main, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
			MaterialButton* btnNO = new MaterialButton(main, wxID_ANY, wxString::FromUTF8("Отмена"), true, wxDefaultPosition, wxSize(70, 35));
			btnNO->SetButtonLineColour(*wxWHITE);
			btnNO->SetLabelColour(wxColour(90, 90, 90));
			btnNO->SetButtonShadow(false);
			btnNO->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
			MaterialButton* btnYES = new MaterialButton(main, wxID_ANY, wxString::FromUTF8("Добавить"), true, wxDefaultPosition, wxSize(80, 35));
			btnYES->SetButtonLineColour(*wxWHITE);
			btnYES->SetLabelColour(gui_MainColour);
			btnYES->SetButtonShadow(false);
			btnYES->SetTextFont(wxFontInfo(12).FaceName("Segoe UI").Bold());
			wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
			btnSizer->Add(btnYES, 0, wxRIGHT, 15);
			btnSizer->Add(btnNO, 0, wxRIGHT);

			wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
			mainSizer->Add(staticDate, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
			mainSizer->Add(dateCtrl, 0, wxLEFT | wxRIGHT | wxEXPAND | wxTOP, 10);
			mainSizer->AddStretchSpacer(1);
			mainSizer->Add(btnSizer, 0, wxBOTTOM | wxRIGHT | wxALIGN_RIGHT | wxTOP, 10);
			main->SetSizerAndFit(mainSizer);

			btnYES->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
			btnYES->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
				[&dateCtrl, this, &dlg, &dlgCancel](wxCommandEvent& evt) {
					ExecuteUpdate(wxS("UPDATE " + GetActiveStrgTable() + " SET "
						+ m_storageColumns[DB_COLUMN_ENTRYDATE] + " = '" + dateCtrl->GetValue().Format("%Y.%m.%d") + "' WHERE "
						+ m_storageColumns[DB_COLUMN_DATE] + " = '" + m_rs.GetAsString(m_storageColumns[DB_COLUMN_DATE]) + "'"));
					dlgCancel = false;
					dlg.Close();
				});

			btnNO->Bind(wxEVT_MOTION, [](wxMouseEvent& evt) { wxSetCursor(wxCURSOR_HAND); });
			btnNO->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [&dlg, &dlgCancel,this](wxCommandEvent& evt) { dlgCancel = true;
																					Commit();
																					dlg.Close(); });
			
			dlg.ShowModal();

			if (dlgCancel)
				return false;
		}
	}
	Commit();
	m_rs.Finalize();
	return true;
}

short DBMain::AddCodeInfoEntry(const wxString& code, const wxString& wasteNorm)
{
	Begin();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + GetActiveCodeInfoTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + code + "'"));
	if (m_rs.NextRow())
	{
		if (m_rs.GetAsString(m_codeInfoColumns[DB_COLUMN_WASTE_NORM]) == "")
		{
			m_rs.Finalize();
			ExecuteUpdate(wxS("UPDATE " + GetActiveCodeInfoTable() +
				" SET " + m_codeInfoColumns[DB_COLUMN_WASTE_NORM] + " = '" + wasteNorm +
				"' WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + " = '" + code + "'"));
			Commit();
			return 2;
		}
		else
		{
			m_rs.Finalize();
			Commit();
			return 0;
		}
	}
	else
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("INSERT INTO " + GetActiveCodeInfoTable() +
			" (" + m_codeInfoColumns[DB_COLUMN_CODE] + ", " + m_codeInfoColumns[DB_COLUMN_WASTE_NORM] 
			+ ") VALUES ('" + code + "', '" + wasteNorm + "')"));
		Commit();
		return 1;
	}

}

bool DBMain::DeleteCodeInfoEntry(const wxString& code)
{
	Begin();
	m_rs = ExecuteQuery(wxS(" SELECT * FROM " + GetActiveCodeInfoTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + code + "'"));
	if (m_rs.NextRow())
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("DELETE FROM " + GetActiveCodeInfoTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + code + "'"));
		Commit();
		return true;
	}
	Commit();
	return false;
}

bool DBMain::EditCodeInfoEntry(const wxString& oldCode,const wxString& code, const wxString& wasteNorm)
{
	Begin();
	m_rs = ExecuteQuery(wxS(" SELECT * FROM " + GetActiveCodeInfoTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + oldCode + "'"));
	if (m_rs.NextRow())
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("UPDATE " + GetActiveCodeInfoTable() + " SET " +
			m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + code + "', " + 
			m_codeInfoColumns[DB_COLUMN_WASTE_NORM] + "= '" + wasteNorm + 
			"' WHERE "+ m_codeInfoColumns[DB_COLUMN_CODE] + "= '" + oldCode + "'"));
		Commit();
		return true;
	}
	Commit();
	return false;
}

bool DBMain::DeleteAllUnitEntrys(int unitID)
{
	Begin();
	m_rs = ExecuteQuery(wxS(" SELECT * FROM " + GetActivePasspTable() + " WHERE " + m_codeInfoColumns[DB_COLUMN_UNIT_ID] + "= '" + wxString::Format("%i",unitID) + "'"));
	addPageInfo info{};
	while (m_rs.NextRow())
	{
		info.regnum = m_rs.GetAsString(DB_COLUMN_REGNUM);
		info.code = m_rs.GetAsString(m_passpColumns[DB_COLUMN_CODE]);
		info.date = m_rs.GetDate(m_passpColumns[DB_COLUMN_DATE]).Format(wxS("%Y.%m.%d"));
		info.owner = m_rs.GetAsString(m_passpColumns[DB_COLUMN_OWNER]);
		info.receiver = m_rs.GetAsString(m_passpColumns[DB_COLUMN_RECEIVER]);
		info.transporter = m_rs.GetAsString(m_passpColumns[DB_COLUMN_TRANSPORT]);
		info.amountFormed = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_FORMED]);
		info.amountReceivedPhys = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]);
		info.amountReceivedOrg = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]);
		info.amountUsed = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_USED]);
		info.amountDefused = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_DEFUSED]);
		info.amountBurial = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_BURIAL]);
		info.amountStorage = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]);
		info.tamountUsed = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]);
		info.tamountDefused = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]);
		info.tamountBurial = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]);
		info.tamountStorage = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]);
		info.amountStrgFull = m_rs.GetAsString(m_passpColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]);
		info.structUnit9 = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD9]);
		info.structUnit10 = m_rs.GetAsString(m_passpColumns[DB_COLUMN_STRUCTURAL_POD10]);
		info.wasteNorm = m_rs.GetAsString(m_passpColumns[DB_COLUMN_WASTE_NORM]);
		info.id = m_rs.GetAsString(m_passpColumns[DB_COLUMN_ID]);
		deleteEntry(info);
	}
	m_rs.Finalize();
	Commit();
	return true;
}

