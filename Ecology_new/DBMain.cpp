#pragma once
#include "DBMain.h"
#include "DMColumnEnums.h"

DBMain::DBMain()
{
	Open(DBPathPassp);
	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + ""));
	getStorageColumnNames();

}

DBMain::~DBMain()
{
	Close();
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
	m_dbStorageColumns[DB_COLUMN_STRUCTURAL_UNIT] = m_rs.GetColumnName(15);
	m_rs.Finalize();
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

		m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBCodesTableName + " WHERE Code = '" + code + "'"));

		data.codeDangerLVL = m_rs.GetString(2);
		data.codeDescription = m_rs.GetString(1);
		m_rs.Finalize();

}

void DBMain::updateDBPassport(const wxArrayString &info)
{
	ExecuteUpdate(wxS("INSERT INTO " + DBPasspTableName +
		"(Manufacturer,Owner,Receiver,Transporter,Code,Regnumber,Amount,Date,Amount_formed," +
		"Amount_received_org,Amount_received_phys,Amount_used,Amount_defused,Amount_selfstorage," +
		"Amount_burial,Transfer_purpose,Amount_transfer_used,Amount_transfer_defused" +
		",Amount_transfer_storage,Amount_transfer_burial,Waste_norm,Structural_unit) " +
		"VALUES ('"	+ info[DB_COLUMN_MANUFACTURER] + "', '"+ info[DB_COLUMN_OWNER] + "', '" + info[DB_COLUMN_RECEIVER] 
		+ "', '" + info[DB_COLUMN_TRANSPORT] + "', '" + info[DB_COLUMN_CODE] + "', '" + info[DB_COLUMN_REGNUM] + "', '"
		+ info[DB_COLUMN_AMOUNT] + "', '"  + info[DB_COLUMN_DATE] + "', '" + info[DB_COLUMN_AMOUNT_FORMED] + "', '" 
		+ info[DB_COLUMN_AMOUNT_RECEIVED_ORG] + "', '" + info[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + "', '"
		+ info[DB_COLUMN_AMOUNT_USED] + "', '" + info[DB_COLUMN_AMOUNT_DEFUSED] + "', '" + info[DB_COLUMN_AMOUNT_SELFSTORAGE] 
		+ "', '" + info[DB_COLUMN_AMOUNT_BURIAL] + "', '" + info[DB_COLUMN_AMOUNT_TRANSFER_PURPOSE]
		+ "', '" + info[DB_COLUMN_AMOUNT_TRANSFER_USED] + "', '" + info[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] 
		+ "', '" + info[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + "', '" + info[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + "', '"+info[DB_COLUMN_WASTE_NORM]
		+ "', '"+ info[DB_COLUMN_STRUCTURAL_UNIT] +"')"));
}



void DBMain::setMonthlyResult(const wxString &code,const wxDateTime &date)
{
	if (code == "")
		return;

	wxString myDate = date.Format(wxS("%Y.%m"));
	wxString fullStorageAmount = calculateFullStorageResult(code, myDate);
	passportStorageInfo values;

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBPasspTableName + " WHERE Code = '" + code + "' AND Date LIKE '%" + myDate + "%'"));

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
	values.structuralUnit = m_rs.GetAsString(DB_COLUMN_STRUCTURAL_UNIT);
	values.wasteNorm = m_rs.GetAsString(DB_COLUMN_WASTE_NORM);
	m_rs.Finalize();

	m_rs = ExecuteQuery(wxS("SELECT * FROM " + DBStorageTableName + " WHERE Code = '" + code + "' AND Date LIKE '%" + myDate + "%'"));

	if (!m_rs.NextRow())
	{
		ExecuteUpdate(wxS("INSERT INTO " + DBStorageTableName + " (" + m_dbStorageColumns[DB_COLUMN_AMOUNT_FORMED] + "," 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_PHYS] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_RECEIVED_ORG] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_USED] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_DEFUSED] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_BURIAL] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_USED] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_DEFUSED] + ","
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_STORAGE] + "," + m_dbStorageColumns[DB_COLUMN_AMOUNT_TRANSFER_BURIAL] + "," 
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + "," + m_dbStorageColumns[DB_COLUMN_CODE] + "," 
			+ m_dbStorageColumns[DB_COLUMN_DATE] + "," + m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + "," + m_dbStorageColumns[DB_COLUMN_STRUCTURAL_UNIT]
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
			+ m_dbStorageColumns[DB_COLUMN_AMOUNT_SELFSTORAGE_FULL] + " = '" + fullStorageAmount
			+ m_dbStorageColumns[DB_COLUMN_WASTE_NORM] + " = '" + values.wasteNorm
			+ m_dbStorageColumns[DB_COLUMN_STRUCTURAL_UNIT] + " = '" + values.structuralUnit
			+ "' WHERE Code = '"+ code + "' AND Date LIKE '%" + myDate + "%'"));
		m_rs.Finalize();
	}

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



wxString DBMain::calculateFullStorageResult(const wxString &code, const wxString &date)
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
	wxString query1{ "SELECT * FROM " + DBCodesTableName + " WHERE Code IN(" };
	wxString query2{ ") ORDER BY " };
	size_t nextCode{ 0 };
	size_t codeCount{ data.code.GetCount() };
	for (size_t i = 0; i < codeCount; ++i)
	{
		nextCode++;
		if (nextCode == codeCount)
		{
			query1 = query1 + data.code[i];
			query2 = query2 + "Code = " + data.code[i] + " DESC";
		}

		else
		{
			query1 = query1 + data.code[i] + ", ";
			query2 = query2 + "Code = " + data.code[i] + " DESC, ";
		}
	}
	m_rs = ExecuteQuery(query1 + query2);
	std::map<wxString, wxString> codeDng{};
	int count{ 0 };
	while (m_rs.NextRow())
	{
		codeDng[m_rs.GetAsString(0)] = m_rs.GetAsString(2);
	}
	for (size_t i = 0; i < codeCount; ++i)
	{
		data.codeDangerLVL.Add(codeDng[data.code[i]]);
	}
	
	m_rs.Finalize();
}
