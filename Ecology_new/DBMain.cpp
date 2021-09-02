#pragma once
#include "DBMain.h"
#include "DMColumnEnums.h"
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std::chrono;



DBMain::DBMain()
{
	Open(DBPathPassp);
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + ""));
	getStorageColumnNames();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + ""));
	getPassportColumnNames();
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + ""));
	while (m_rs.NextRow())
	{
		m_codeNameDiscDng[m_rs.GetAsString(0)] = std::make_pair(m_rs.GetAsString(1),m_rs.GetAsString(2));
	}

}

DBMain::~DBMain()
{
	m_codeNameDiscDng.clear();
	m_dbStorageColumns.clear();
	m_rs.Finalize();

	if (IsOpen())
		Close();
	
		
}

void DBMain::getPassportColumnNames()
{

	m_dbPasspColumns[DB_COLUMN_ID] = m_rs.GetColumnName(0);
	m_dbPasspColumns[DB_COLUMN_MANUFACTURER] = m_rs.GetColumnName(1);
	m_dbPasspColumns[DB_COLUMN_OWNER] = m_rs.GetColumnName(2);
	m_dbPasspColumns[DB_COLUMN_RECEIVER] = m_rs.GetColumnName(3);
	m_dbPasspColumns[DB_COLUMN_TRANSPORT] = m_rs.GetColumnName(4);
	m_dbPasspColumns[DB_COLUMN_DATE] = m_rs.GetColumnName(5);
	m_dbPasspColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(6);
	m_dbPasspColumns[DB_COLUMN_REGNUM] = m_rs.GetColumnName(7);
	m_dbPasspColumns[DB_COLUMN_AMOUNT] = m_rs.GetColumnName(8);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED] = m_rs.GetColumnName(9);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] = m_rs.GetColumnName(10);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = m_rs.GetColumnName(11);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_USED] = m_rs.GetColumnName(12);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_DEFUSED] = m_rs.GetColumnName(13);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] = m_rs.GetColumnName(14);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_BURIAL] = m_rs.GetColumnName(15);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_PURPOSE] = m_rs.GetColumnName(16);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] = m_rs.GetColumnName(17);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = m_rs.GetColumnName(18);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = m_rs.GetColumnName(19);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = m_rs.GetColumnName(20);
	m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] = m_rs.GetColumnName(21);
	m_dbPasspColumns[DB_COLUMN_WASTE_NORM] = m_rs.GetColumnName(22);
	m_dbPasspColumns[DB_COLUMN_STRUCTURAL_FORMED] = m_rs.GetColumnName(23);
	m_dbPasspColumns[DB_COLUMN_ENTRYDATE] = m_rs.GetColumnName(24);
	m_dbPasspColumns[DB_COLUMN_STRUCTURAL_TRANSPORT] = m_rs.GetColumnName(25);
	m_rs.Finalize();
}

void DBMain::getStorageColumnNames()
{
	
	m_dbStorageColumns[DB_COLUMN_DATE] =  m_rs.GetColumnName(0);
	m_dbStorageColumns[DB_COLUMN_CODE] = m_rs.GetColumnName(1);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED] = m_rs.GetColumnName(2);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] = m_rs.GetColumnName(3);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] = m_rs.GetColumnName(4);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] = m_rs.GetColumnName(5);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] = m_rs.GetColumnName(6);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] = m_rs.GetColumnName(7);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] = m_rs.GetColumnName(8);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] = m_rs.GetColumnName(9);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] = m_rs.GetColumnName(10);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] = m_rs.GetColumnName(11);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] = m_rs.GetColumnName(12);
	m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] = m_rs.GetColumnName(13);
	m_dbStorageColumns[DB_COLUMN_WASTE_NORM] = m_rs.GetColumnName(14);
	m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] = m_rs.GetColumnName(15);
	m_dbStorageColumns[DB_COLUMN_ENTRYDATE] = m_rs.GetColumnName(16);
	m_dbStorageColumns[DB_COLUMN_ID] = m_rs.GetColumnName(17);
	m_rs.Finalize();
}

wxString DBMain::GetLastPassportID()
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " ORDER BY " + m_dbPasspColumns[DB_COLUMN_ID] + " DESC"));
	m_rs.NextRow();
	wxString id = m_rs.GetAsString(m_dbPasspColumns[DB_COLUMN_ID]);
	m_rs.Finalize();
	return id;
}

wxString DBMain::convertDate(const wxString &date)
{
	wxDateTime newDate;
	newDate.ParseDate(date);
	return newDate.Format(wxS("%d.%m.%Y"));
}

int DBMain::getUniqueCodes(passportPod9Info &data)
{
		m_rs = ExecuteQuery(wxS("SELECT DISTINCT Code FROM " + DBPasspTableName));
		while (m_rs.NextRow())
		{
			data.uniqueCodes.Add(m_rs.GetString(0));
		}
		m_rs.Finalize();
	return ExecuteScalar(wxS("SELECT COUNT(DISTINCT Code) FROM " + DBPasspTableName));
}


void DBMain::getNextPod9Portion(passportPod9Info &data,const wxString &code)
{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + code + "' ORDER BY Date"));
		int count{0};
		if (!data.id.IsEmpty())
		{
			data.emptyPodStruct9Info();
		}

		while (m_rs.NextRow())
		{
			data.id.Add(m_rs.GetInt(DB_COLUMN_ID));
			data.idString.Add(m_rs.GetAsString(DB_COLUMN_ID));
			data.amount.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT));
			data.amountString.Add(m_rs.GetAsString(DB_COLUMN_AMOUNT));
			data.date.Add(convertDate(m_rs.GetString(DB_COLUMN_DATE)));
			data.manufacturer.Add(m_rs.GetString(DB_COLUMN_MANUFACTURER));
			data.receiver.Add(m_rs.GetString(DB_COLUMN_RECEIVER));
			data.owner.Add(m_rs.GetString(DB_COLUMN_OWNER));
			data.transporter.Add(m_rs.GetString(DB_COLUMN_TRANSPORT));
			data.regnum.Add(m_rs.GetString(DB_COLUMN_REGNUM));
			data.amountFormed.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_FORMED));
			data.amountReceivedPhys.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_PHYS));
			data.amountReceivedOrg.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_ORG));
			data.amountUsed.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_USED));
			data.amountDefused.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_DEFUSED));
			data.amountSelfstorage.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_SELFSTORAGE));
			data.amountBurial.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_BURIAL));
			data.amountTransferUsed.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_USED));
			data.amountTransferDefused.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_DEFUSED));
			data.amountTransferStorage.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_STORAGE));
			data.amountTransferBurial.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_BURIAL));
			data.amountFullStorage.Add(m_rs.GetDouble(DB_COLUMN_AMOUNT_SELFSTORAGE_FULL));
			count++;
		}
		data.rowCount = std::move(count);
		m_rs.Finalize();

		//m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + code + "'"));
		//data.codeDangerLVL = m_codeNameDiscDng[code].second;
		//data.codeDescription = m_codeNameDiscDng[code].first;
		data.codeDangerLVL = m_rs.GetString(2);
		data.codeDescription = m_rs.GetString(1);
		m_rs.Finalize();

}


//returns code/date string if fullstorage value already exists, empty string otherwise
wxString DBMain::checkFullStorage(const wxString& code)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" + code + "' ORDER BY Date DESC"));
	if (!m_rs.NextRow())
	{
		m_rs.Finalize();
		return "";
	}
	else
	{
		wxString string{ "Код отхода: " + m_rs.GetAsString(m_dbStorageColumns[DB_COLUMN_CODE]) 
			+ "\nДата: " + m_rs.GetAsString(m_dbStorageColumns[DB_COLUMN_DATE]) + "\nЗначение: " 
			+ m_rs.GetAsString(m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) };
		m_rs.Finalize();
		return string;
	}
		
}

bool DBMain::deleteEntry(const addPageInfo& info)
{
	wxString pAmountColumn, amount, sAmountColumn, strDiffrAm;

	auto getAmount = [](wxString amount) { 
	if (amount == "")
		return amount + "0";
	else
		return amount; };

	if (info.amountFormed != "")
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (info.amountReceivedOrg != "")
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}

	float diffrAm = wxAtof(info.amountStorage) + (wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
		- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));

	strDiffrAm = wxString::Format("%f", diffrAm * -1);



	ExecuteUpdate(wxS("DELETE FROM " + DBPasspTableName + " WHERE id = " + info.id));
	updateSubsqPasspStrg(info.code, info.date, strDiffrAm);

	ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET " +
		m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + strDiffrAm + ", "
		+ sAmountColumn + " = " + sAmountColumn + " - " + getAmount(amount) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(info.amountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(info.amountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(info.amountStorage) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(info.amountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(info.tamountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(info.tamountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(info.tamountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(info.tamountStorage)
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + 
		" WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));
	m_rs.NextRow();
	if (m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0 
		&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) == 0
		&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_USED]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED]) == 0 
		&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL]) == 0
		&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) == 0
		&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) == 0)
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("DELETE FROM " + DBStorageTableName + " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));
	}

	this->updateSubsqPOD10Strg(info.code, info.date, getAmount(wxString::Format("%f", diffrAm)),info.id);
		
	return true;
}

bool DBMain::editEntry(const addPageInfo& info)
{
	auto getAmount = [](wxString amount) {
		if (amount == "")
			return amount + "0";
		else
			return amount; };


	wxString pAmountColumn, amount, sAmountColumn, amountStorageFull;
	float newDiffrAm, oldDiffrAM;

	if (wxAtof(info.amountFormed)>0)
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (wxAtof(info.amountReceivedOrg)>0)
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}




	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE id = '" + info.id + "'"));
	m_rs.NextRow();

	newDiffrAm = wxAtof(info.amountStorage) + (wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
		- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));

	oldDiffrAM = m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) + ( m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) 
		+ m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) + m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED]) 
		- m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) - m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_BURIAL]) 
		- m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_USED]) - m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_DEFUSED]) 
		- m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) - m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) 
		- m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) - m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) );


	m_rs.Finalize();

	//substract old diffrance from subsequent passport table entrys
	this->updateSubsqPasspStrg(info.oldCode, info.oldDate, wxString::Format("%f", oldDiffrAM * -1));
	
	wxString test1 = wxS("UPDATE " + DBStorageTableName + " SET " +
		m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", oldDiffrAM * -1) + ", "
		+ sAmountColumn + " = " + sAmountColumn + " - " + getAmount(amount) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(info.amountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(info.amountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(info.amountStorage) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(info.amountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(info.tamountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(info.tamountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(info.tamountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(info.tamountStorage)
		+ " WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'");

	//substract old diffrance from old/current entry in storage table
	ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET " +
		m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", oldDiffrAM * -1) + ", "
		+ sAmountColumn + " = " + sAmountColumn + " - " + getAmount(amount) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " - " + getAmount(info.amountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " - " + getAmount(info.amountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " - " + getAmount(info.amountStorage) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " - " + getAmount(info.amountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " - " + getAmount(info.tamountUsed) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " - " + getAmount(info.tamountDefused) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " - " + getAmount(info.tamountBurial) + ", "
		+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " - " + getAmount(info.tamountStorage)
		+ " WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));

	//substract old diffrance from subsequent storage table entrys
	this->updateSubsqPOD10Strg(info.oldCode, info.oldDate, wxString::Format("%f", oldDiffrAM * -1),info.id);

	//delete storage table entry if code is changed and entry is empty
	if (info.oldCode != info.code)
	{
		m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));
		m_rs.NextRow();
		if (m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED]) == 0
			&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS]) == 0
			&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_USED]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED]) == 0
			&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL]) == 0
			&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED]) == 0
			&& m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE]) == 0 && m_rs.GetDouble(m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL]) == 0)
		{
			m_rs.Finalize();
			ExecuteUpdate(wxS("DELETE FROM " + DBStorageTableName + " WHERE Code = '" + info.oldCode + "' AND Date LIKE '%" + info.oldDate.Mid(0, 7) + "%'"));
		}
	}

	

	wxString test = wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + info.code + "' AND Date <= '" + info.date + "' ORDER BY Date DESC, id DESC");

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + info.code + "' AND Date <= '" + info.date + "' ORDER BY Date DESC, id DESC"));
	while (m_rs.NextRow())
	{
		if (m_rs.GetAsString(m_dbPasspColumns[DB_COLUMN_ID]) != info.id)
		{
			amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + newDiffrAm);
			break;
		}
			
	}
	if(amountStorageFull.IsEmpty())
		amountStorageFull = wxString::Format("%f", newDiffrAm);

	m_rs.Finalize();
	


	//set new entry info
	ExecuteUpdate(wxS("UPDATE " + DBPasspTableName + " SET "
		+ m_dbPasspColumns[DB_COLUMN_OWNER] + " = '" + info.owner + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + info.amountReceivedPhys + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + info.amountReceivedOrg + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + info.amountFormed + "', "
		+ m_dbPasspColumns[DB_COLUMN_RECEIVER] + " = '" + info.receiver + "', "
		+ m_dbPasspColumns[DB_COLUMN_TRANSPORT] + " = '" + info.transporter + "', "
		+ m_dbPasspColumns[DB_COLUMN_DATE] + " = '" + info.date + "', "
		+ m_dbPasspColumns[DB_COLUMN_CODE] + " = '" + info.code + "', "
		+ m_dbPasspColumns[DB_COLUMN_REGNUM] + " = '" + info.regnum + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_USED] + " = '" + info.amountUsed + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + info.amountDefused + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + info.amountStorage + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + info.amountBurial + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + info.tamountUsed + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + info.tamountDefused + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + info.tamountStorage + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + info.tamountBurial + "', "
		+ m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + amountStorageFull + "', "
		+ m_dbPasspColumns[DB_COLUMN_WASTE_NORM] + " = '" + info.wasteNorm + "', "
		+ m_dbPasspColumns[DB_COLUMN_STRUCTURAL_TRANSPORT] + " = '" + info.structUnit9 + "', "
		+ m_dbPasspColumns[DB_COLUMN_STRUCTURAL_FORMED] + " = '" + info.structUnit10
		+ "' WHERE id = '" + info.id + "'"));
	
	//add new diffrance to subsequent storage in passport table entrys
	this->updateSubsqPasspStrg(info.code, info.date, wxString::Format("%f", newDiffrAm));


	//if entry in storage table with such code and date exists - update this entry, if not - insert new entry
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

	if (m_rs.NextRow())
	{
		m_rs.Finalize();

		ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET " +
			m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + amountStorageFull + ", "
			+ sAmountColumn + " = " + sAmountColumn + " + " + getAmount(amount) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " + " + getAmount(info.amountUsed) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " + " + getAmount(info.amountDefused) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " + " + getAmount(info.amountStorage) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " + " + getAmount(info.amountBurial) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " + " + getAmount(info.tamountUsed) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " + " + getAmount(info.tamountDefused) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " + " + getAmount(info.tamountBurial) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " + " + getAmount(info.tamountStorage)
			+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

	}
	else
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("INSERT INTO " + DBStorageTableName +
			" (" + m_dbStorageColumns[DB_COLUMN_DATE] + ", " + m_dbStorageColumns[DB_COLUMN_CODE] +
			", " + sAmountColumn + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] +
			", " + m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
			") VALUES ('" + info.date + "', '" + info.code + "', '"
			+ amount + "', '" + info.amountUsed + "', '" + info.amountDefused + "', '"
			+ info.amountStorage + "', '" + info.amountBurial + "', '"
			+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
			+ "', '" + info.tamountBurial + "', '" + info.structUnit10
			+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "')"));

	}

	//we are adding new diffrance ammount to subsequent entrys in storage table reagrless
	this->updateSubsqPOD10Strg(info.code, info.date, getAmount(wxString::Format("%f", newDiffrAm)),info.id);

	return false;
}


//
//void DBMain::insertFirstEntry(const addPageInfo& info)
//{
//	wxString pAmountColumn,amount,sAmountColumn, amountStorageFull;
//	float f_amountStorageFull;
//
//	f_amountStorageFull = wxAtof(info.amountStrgFull) + wxAtof(info.amountStorage) + ( wxAtof(info.amountGet) - wxAtof(info.amountStorage) 
//		- wxAtof(info.amountBurial) - wxAtof(info.amountUsed) - wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) 
//		- wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused));
//	amountStorageFull = wxString::Format("%f", f_amountStorageFull);
//
//	if (info.amountFormed != "")
//	{
//		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED];
//		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED];
//		amount = info.amountFormed;
//	}
//		
//	else if (info.amountReceivedOrg != "")
//	{
//		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
//		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
//		amount = info.amountReceivedOrg;
//	}
//	else
//	{
//		sAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
//		pAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
//		amount = info.amountReceivedPhys;
//	}
//
//
//	ExecuteUpdate(wxS("INSERT INTO " + DBPasspTableName +
//		"(" + m_dbPasspColumns[DB_COLUMN_REGNUM]+", " + m_dbPasspColumns[DB_COLUMN_DATE] +
//		", " + m_dbPasspColumns[DB_COLUMN_OWNER] + ", " + m_dbPasspColumns[DB_COLUMN_TRANSPORT] +
//		", " + m_dbPasspColumns[DB_COLUMN_RECEIVER] +", " + m_dbPasspColumns[DB_COLUMN_CODE] +
//		", " + pAmountColumn + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_USED] +
//		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
//		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
//		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
//		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_dbPasspColumns[DB_COLUMN_STRUCTURAL_FORMED] +
//		", " + m_dbPasspColumns[DB_COLUMN_STRUCTURAL_TRANSPORT] + ", " + m_dbPasspColumns[DB_COLUMN_ENTRYDATE] +
//		", " + m_dbPasspColumns[DB_COLUMN_WASTE_NORM] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
//		") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
//		+ "', '" + info.transporter + "', '" + info.receiver + "', '" + info.code + "', '"
//		+ amount + "', '" + info.amountUsed + "', '" + info.amountDefused + "', '"
//		+ info.amountStorage + "', '" + info.amountBurial + "', '"
//		+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
//		+ "', '" + info.tamountBurial + "', '" + info.structUnit10
//		+ "', '" + info.structUnit9 + "', '" + info.entryDate
//		+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "')"));
//
//	ExecuteUpdate(wxS("INSERT INTO " + DBStorageTableName +
//		"(" + m_dbStorageColumns[DB_COLUMN_DATE] + ", " + m_dbStorageColumns[DB_COLUMN_CODE] +
//		", " + sAmountColumn + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] +
//		", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
//		", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
//		", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
//		", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] +
//		", " + m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
//		") VALUES ('"+ info.date + "', '"  + info.code + "', '"
//		+ amount + "', '" + info.amountUsed + "', '" + info.amountDefused + "', '"
//		+ info.amountStorage + "', '" + info.amountBurial + "', '"
//		+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
//		+ "', '" + info.tamountBurial + "', '" + info.structUnit10
//		+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "')"));
//}

/// <summary>
/// inserts entry if such code already exists or full storage amount has custom value
/// </summary>
/// <returns>true if successful, false otherwise</returns>
bool DBMain::insertNewEntry(const addPageInfo& info)
{
	
	wxString pAmountColumn, amount, sAmountColumn, amountStorageFull;
	float diffrAm;

	if (info.amountFormed != "")
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_FORMED];
		amount = info.amountFormed;
	}

	else if (info.amountReceivedOrg != "")
	{
		sAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		pAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG];
		amount = info.amountReceivedOrg;
	}
	else
	{
		sAmountColumn = m_dbPasspColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		pAmountColumn = m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS];
		amount = info.amountReceivedPhys;
	}

	diffrAm = wxAtof(info.amountStorage) + ( wxAtof(amount) - wxAtof(info.amountStorage) - wxAtof(info.amountBurial) - wxAtof(info.amountUsed)
			- wxAtof(info.amountDefused) - wxAtof(info.tamountBurial) - wxAtof(info.tamountStorage) - wxAtof(info.tamountUsed) - wxAtof(info.tamountDefused) );
	
	//check if we already have entrys, if yes, get storage from them, otherwise get storage from custom user value or 0
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + info.code + "' AND Date <= '" + info.date + "' ORDER BY Date DESC, id DESC"));
	if (m_rs.NextRow())
		amountStorageFull = wxString::Format("%f", m_rs.GetDouble(m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]) + diffrAm);

	else
		amountStorageFull = wxString::Format("%f", wxAtof(info.amountStrgFull) + diffrAm);
	
	m_rs.Finalize();
	
	auto getAmount = [](wxString amount) { if (amount == "")
												return amount + " + 0";
											else if (wxAtof(amount) > 0)
												return " + " + amount;
											else
												return " - " + amount; };

	ExecuteUpdate(wxS("INSERT INTO " + DBPasspTableName + " (" 
		+ m_dbPasspColumns[DB_COLUMN_REGNUM] + ", " + m_dbPasspColumns[DB_COLUMN_DATE] +
		", " + m_dbPasspColumns[DB_COLUMN_OWNER] + ", " + m_dbPasspColumns[DB_COLUMN_TRANSPORT] +
		", " + m_dbPasspColumns[DB_COLUMN_RECEIVER] + ", " + m_dbPasspColumns[DB_COLUMN_CODE] +
		", " + pAmountColumn + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_USED] +
		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
		", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_dbPasspColumns[DB_COLUMN_STRUCTURAL_FORMED] +
		", " + m_dbPasspColumns[DB_COLUMN_STRUCTURAL_TRANSPORT] + ", " + m_dbPasspColumns[DB_COLUMN_ENTRYDATE] +
		", " + m_dbPasspColumns[DB_COLUMN_WASTE_NORM] + ", " + m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
		") VALUES ('" + info.regnum + "', '" + info.date + "', '" + info.owner
		+ "', '" + info.transporter + "', '" + info.receiver + "', '" + info.code + "', '"
		+ amount + "', '" + info.amountUsed + "', '" + info.amountDefused + "', '"
		+ info.amountStorage + "', '" + info.amountBurial + "', '"
		+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
		+ "', '" + info.tamountBurial + "', '" + info.structUnit10
		+ "', '" + info.structUnit9 + "', '" + info.entryDate
		+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "')"));

	this->updateSubsqPasspStrg(info.code, info.date, getAmount(wxString::Format("%f", diffrAm)));



	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName 
		+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%' ORDER BY Date DESC"));

	if (m_rs.NextRow())
	{
		m_rs.Finalize();

		ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET " +
			m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + wxString::Format("%f", diffrAm) + ", "
			+ sAmountColumn + " = " + sAmountColumn + getAmount(amount) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + getAmount(info.amountUsed) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + getAmount(info.amountDefused) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + getAmount(info.amountStorage) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + getAmount(info.amountBurial) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + getAmount(info.tamountUsed) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + getAmount(info.tamountDefused) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + getAmount(info.tamountBurial) + ", "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + getAmount(info.tamountStorage)
			+ " WHERE Code = '" + info.code + "' AND Date LIKE '%" + info.date.Mid(0, 7) + "%'"));

		this->updateSubsqPOD10Strg(info.code, info.date, getAmount(wxString::Format("%f", diffrAm)),info.id);
	}

	else
	{
		m_rs.Finalize();
		ExecuteUpdate(wxS("INSERT INTO " + DBStorageTableName +
			" (" + m_dbStorageColumns[DB_COLUMN_DATE] + ", " + m_dbStorageColumns[DB_COLUMN_CODE] +
			", " + sAmountColumn + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] +
			", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + ", " + m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] +
			", " + m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + ", " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] +
			") VALUES ('" + info.date + "', '" + info.code + "', '"
			+ amount + "', '" + info.amountUsed + "', '" + info.amountDefused + "', '"
			+ info.amountStorage + "', '" + info.amountBurial + "', '"
			+ info.tamountUsed + "', '" + info.tamountDefused + "', '" + info.tamountStorage
			+ "', '" + info.tamountBurial + "', '" + info.structUnit10
			+ "', '" + info.wasteNorm + "', '" + amountStorageFull + "')"));
	}

	return true;

}

//Updates subsequent full storage amount in passport table
void  DBMain::updateSubsqPasspStrg(const wxString& code, const wxString& date, const wxString& diffAm)
{

	ExecuteUpdate(wxS("UPDATE OR IGNORE " + DBPasspTableName + " SET " + 
		m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbPasspColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " + " + diffAm +
		" WHERE Code = '" + code + "' AND Date > '" + date + "'"));

}

//Updates subsequent full storage amount in storage table
void  DBMain::updateSubsqPOD10Strg(const wxString& code, const wxString& date, const wxString& diffAm,const wxString& id)
{

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" + code
		+ "' AND Date >= '%" + date.Mid(0, 7) + "%'"));
	wxString testQuery = wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" + code
		+ "' AND Date >= '%" + date.Mid(0, 7) + "%'");

	while (m_rs.NextRow())
	{

		wxString test = wxS("UPDATE " + DBStorageTableName + " SET " +
			m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]
			+ " + " + diffAm + " WHERE Code = '" + code + "' AND Date LIKE '%" + m_rs.GetAsString(DB_COLUMN_DATE) + "%'");

		if (id == m_rs.GetAsString(DB_COLUMN_ID))
			continue;
		ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET " +
			m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = " + m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL]
			+ " + " + diffAm + " WHERE id = '" + m_rs.GetAsString(DB_COLUMN_ID) + "'"));
	}
	m_rs.Finalize();


}

void DBMain::setMonthlyResult(const wxString &code,const wxDateTime &date)
{
	if (code == "")
		return;

	wxString myDate = date.Format(wxS("%Y.%m"));
	wxString fullStorageAmount = calculateFullStorageResult(code, myDate);
	passportStorageInfo values;

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + code 
							+ "' AND Date LIKE '%" + myDate + "%'"));

	while (m_rs.NextRow())
	{
		values.amountFormed += m_rs.GetDouble(DB_COLUMN_AMOUNT_FORMED);
		values.amountReceivedPhys +=  m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_PHYS);
		values.amountReceivedOrg += m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_ORG);
		values.amountUsed += m_rs.GetDouble(DB_COLUMN_AMOUNT_USED);
		values.amountDefused += m_rs.GetDouble(DB_COLUMN_AMOUNT_DEFUSED);
		values.amountSelfstorage += m_rs.GetDouble(DB_COLUMN_AMOUNT_SELFSTORAGE);
		values.amountBurial += m_rs.GetDouble(DB_COLUMN_AMOUNT_BURIAL);
		values.amountTransferUsed += m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_USED);
		values.amountTransferDefused += m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_DEFUSED);
		values.amountTransferStorage += m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_STORAGE);
		values.amountTransferBurial += m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_BURIAL);
	}
	values.structuralUnit = m_rs.GetAsString(DB_COLUMN_STRUCTURAL_FORMED);
	values.wasteNorm = m_rs.GetAsString(DB_COLUMN_WASTE_NORM);
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" 
							+ code + "' AND Date LIKE '%" + myDate + "%'"));

	if (!m_rs.NextRow())
	{
		ExecuteUpdate(wxS("INSERT INTO " + DBStorageTableName + " (" + m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED] + "," 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + "," 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + "," + m_dbStorageColumns[DB_COLUMN_CODE] + "," 
			+ m_dbStorageColumns[DB_COLUMN_DATE] + "," + m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + "," + m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED]
			+") VALUES ('"+ wxString::Format(wxS("%f"), values.amountFormed)+"','"+ wxString::Format(wxS("%f"), values.amountReceivedPhys) +"','" 
			+ wxString::Format(wxS("%f"), values.amountReceivedOrg) +"','" + wxString::Format(wxS("%f"), values.amountUsed)+"','" 
			+ wxString::Format(wxS("%f"), values.amountDefused)+"','" + wxString::Format(wxS("%f"), values.amountSelfstorage)+"','" 
			+ wxString::Format(wxS("%f"), values.amountBurial) +"','" + wxString::Format(wxS("%f"), values.amountTransferUsed)+ "','" 
			+ wxString::Format(wxS("%f"), values.amountTransferDefused) + "','" + wxString::Format(wxS("%f"), values.amountTransferStorage)+ "','" 
			+ wxString::Format(wxS("%f"), values.amountTransferBurial) + "','" + fullStorageAmount + "','"
			+ code + "','" + myDate +"','" + values.wasteNorm + "','" + values.structuralUnit + "')"));
		m_rs.Finalize();
	}
	else
	{
		wxString string = "UPDATE " + DBStorageTableName + " SET "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + wxString::Format(wxS("%f"), values.amountFormed) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + wxString::Format(wxS("%f"), values.amountReceivedPhys) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + wxString::Format(wxS("%f"), values.amountReceivedOrg) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = '" + wxString::Format(wxS("%f"), values.amountUsed) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + wxString::Format(wxS("%f"), values.amountDefused) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + wxString::Format(wxS("%f"), values.amountSelfstorage) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + wxString::Format(wxS("%f"), values.amountBurial) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + wxString::Format(wxS("%f"), values.amountTransferUsed) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + wxString::Format(wxS("%f"), values.amountTransferDefused) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + wxString::Format(wxS("%f"), values.amountTransferStorage) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + wxString::Format(wxS("%f"), values.amountTransferBurial) + "', "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + fullStorageAmount + "', "
			+ m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + " = '" + values.wasteNorm + "', "
			+ m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] + " = '" + values.structuralUnit
			+ "' WHERE Code = '" + code + "' AND Date LIKE '%" + myDate + "%'";
		ExecuteUpdate(wxS("UPDATE " + DBStorageTableName + " SET "
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED] + " = '" + wxString::Format(wxS("%f"), values.amountFormed) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + " = '" + wxString::Format(wxS("%f"), values.amountReceivedPhys) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + " = '" + wxString::Format(wxS("%f"), values.amountReceivedOrg) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + " = '" + wxString::Format(wxS("%f"), values.amountUsed) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + " = '" + wxString::Format(wxS("%f"), values.amountDefused) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + " = '" + wxString::Format(wxS("%f"), values.amountSelfstorage) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + " = '" + wxString::Format(wxS("%f"), values.amountBurial) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + " = '" + wxString::Format(wxS("%f"), values.amountTransferUsed) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + " = '" + wxString::Format(wxS("%f"), values.amountTransferDefused) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + " = '" + wxString::Format(wxS("%f"), values.amountTransferStorage) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + " = '" + wxString::Format(wxS("%f"), values.amountTransferBurial) + "', " 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + fullStorageAmount + "', "
			+ m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + " = '" + values.wasteNorm + "', "
			+ m_dbStorageColumns[DB_COLUMN_STRUCTURAL_FORMED] + " = '" + values.structuralUnit
			+ "' WHERE Code = '"+ code + "' AND Date LIKE '%" + myDate + "%'"));
		m_rs.Finalize();
	}

}

wxString DBMain::calculateFullStorageResult(const wxString& code, const wxString& date)
{
	double fullStorageAmount{};

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + code + "' AND Date >= '" + date + "'"));
	while (m_rs.NextRow())
	{
		fullStorageAmount += m_rs.GetDouble(DB_COLUMN_AMOUNT_FORMED) + m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_PHYS)
			+ m_rs.GetDouble(DB_COLUMN_AMOUNT_RECEIVED_ORG) + m_rs.GetDouble(DB_COLUMN_AMOUNT_SELFSTORAGE)
			- m_rs.GetDouble(DB_COLUMN_AMOUNT_USED) - m_rs.GetDouble(DB_COLUMN_AMOUNT_DEFUSED)
			- m_rs.GetDouble(DB_COLUMN_AMOUNT_BURIAL) - m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_USED)
			- m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_DEFUSED) - m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_BURIAL);
	}
	m_rs.Finalize();
	return wxString::Format(wxS("%f"), fullStorageAmount);
}

void DBMain::getPod10TableCount(pod10Info &data)
{
	data.tableCount = ExecuteScalar(wxS("SELECT COUNT(DISTINCT Date) FROM " + DBStorageTableName));
	m_rs = ExecuteQuery(wxS("SELECT DISTINCT Date FROM " + DBStorageTableName));
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
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Date LIKE '%" + date + "%' ORDER BY Date"));
	while (m_rs.NextRow())
	{
		data.date = m_rs.GetAsString(0);
		data.code.Add(m_rs.GetAsString(1));
		data.amountFormed.Add(m_rs.GetAsString(2));
		data.amountReOrg.Add(m_rs.GetAsString(3));
		data.amountRePhys.Add(m_rs.GetAsString(4));
		data.amountUsed.Add(m_rs.GetAsString(5));
		data.amountDefused.Add(m_rs.GetAsString(6));
		data.amountSelfstorage.Add(m_rs.GetAsString(7));
		data.amountBurial.Add(m_rs.GetAsString(8));
		data.amountTransferUsed.Add(m_rs.GetAsString(9));
		data.amountTransferDefused.Add(m_rs.GetAsString(10));
		data.amountTransferStorage.Add(m_rs.GetAsString(11));
		data.amountTransferBurial.Add(m_rs.GetAsString(12));
		data.amountSelfstorageFull.Add(m_rs.GetAsString(13));
		data.wasteNorm.Add(m_rs.GetAsString(14));
		data.structuralUnit.Add(m_rs.GetAsString(15));
		count++;
	}
	data.rowCount = std::move(count);
	m_rs.Finalize();


}

void DBMain::getPod10TableCodeDngr(pod10Info &data, const wxArrayString &codes)
{
	wxString query1{ "SELECT * FROM codes WHERE Code IN (" };
	wxString query2{ ") ORDER BY " };
	size_t nextCode{ 0 };
	size_t codeCount{ codes.GetCount() };
	for (size_t i = 0; i < codeCount ; i++)
	{
		nextCode++;
		if (nextCode == codeCount)
		{
			query1 = query1 + codes[i];
			query2 = query2 + "Code = " + codes[i] + " DESC";
		}
				
		else
		{
			query1 = query1 + codes[i] + ", ";
			query2 = query2 + "Code = " + codes[i] + " DESC, ";
		}
	}
	m_rs = ExecuteQuery(query1 + query2);
	while(m_rs.NextRow())
	{
		data.codeDangerLVL.Add(m_rs.GetAsString(2));
		data.codeDescription.Add(m_rs.GetAsString(1));
	}
	m_rs.Finalize();
}

void DBMain::getJournalTableInfo(passportJournalInfo& data,const wxString& startDate)
{

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Date >= '" + startDate + "' ORDER BY Date"));
	while (m_rs.NextRow())
	{
		data.amountTransferBurial.push_back(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_BURIAL));
		data.amountTransferDefused.push_back(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_DEFUSED));
		data.amountTransferUsed.push_back(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_USED));
		data.amountTransferStorage.push_back(m_rs.GetDouble(DB_COLUMN_AMOUNT_TRANSFER_STORAGE));
		data.code.push_back(m_rs.GetAsString(DB_COLUMN_CODE));
		data.date.push_back(m_rs.GetAsString(DB_COLUMN_DATE));
		data.receiver.push_back(m_rs.GetAsString(DB_COLUMN_RECEIVER));
		data.regnum.push_back(m_rs.GetAsString(DB_COLUMN_REGNUM));
		data.transporter.push_back(m_rs.GetAsString(DB_COLUMN_TRANSPORT));

	}
	m_rs.Finalize();
	getJournalCodeInfo(data);
	
}

void DBMain::getJournalCodeInfo(passportJournalInfo& data)
{


	for (size_t i = 0; i < data.code.size(); ++i)
	{
		data.codeDangerLVL.Add(m_codeNameDiscDng[data.code[i]].second);
	}
	
	m_rs.Finalize();
}


//ID should always be last in array
void DBMain::getListItemData(std::vector<std::vector<wxString>>& item)
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + ""));
	int count{ 0 };
	while (m_rs.NextRow())
	{
		item.push_back(std::vector<wxString>());
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_REGNUM));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_DATE));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_OWNER));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_RECEIVER));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_TRANSPORT));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_CODE));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_FORMED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_RECEIVED_PHYS));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_RECEIVED_ORG));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_USED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_DEFUSED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_SELFSTORAGE));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_BURIAL));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_TRANSFER_USED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_TRANSFER_DEFUSED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_TRANSFER_STORAGE));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_TRANSFER_BURIAL));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_AMOUNT_SELFSTORAGE_FULL));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_STRUCTURAL_FORMED));
		item[count].push_back(m_rs.GetAsString(DB_COLUMN_STRUCTURAL_TRANSPORT));

		item[count].push_back(m_rs.GetAsString(DB_COLUMN_ID));



		count++;
	}
	m_rs.Finalize();
}

//returns Y.m.d format
wxDateTime DBMain::getFirstEntryDate()
{
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " ORDER BY " + m_dbPasspColumns[DB_COLUMN_DATE] + " ASC"));
	wxDateTime date = m_rs.GetDate(m_dbPasspColumns[DB_COLUMN_DATE]);
	m_rs.Finalize();
	return date;

}