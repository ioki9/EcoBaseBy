#pragma once
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>
#include <vector>


struct pod10Info
{
public:
	wxString date{};
	wxString entryDate{};
	wxArrayString code{};
	wxArrayString codeDangerLVL{};
	wxArrayString codeDescription{};
	wxArrayDouble amountFormed{};
	wxArrayDouble amountReOrg{};
	wxArrayDouble amountRePhys{};
	wxArrayDouble amountUsed{};
	wxArrayDouble amountDefused{};
	wxArrayDouble amountSelfstorage{};
	wxArrayDouble amountBurial{};
	wxArrayDouble amountTransferUsed{};
	wxArrayDouble amountTransferDefused{};
	wxArrayDouble amountTransferStorage{};
	wxArrayDouble amountTransferBurial{};
	wxArrayDouble amountSelfstorageFull{};
	wxArrayDouble wasteNorm{};
	wxArrayString structuralUnit{};


	int tableCount{ 0 };
	wxArrayString allDates;
	int rowCount{ 0 };

	void emptyPod10StructInfo()
	{
		date.Empty();
		code.Empty();
		codeDangerLVL.Empty();
		codeDescription.Empty();
		amountFormed.Empty();
		amountReOrg.Empty();
		amountRePhys.Empty();
		amountUsed.Empty();
		amountDefused.Empty();
		amountBurial.Empty();
		amountSelfstorage.Empty();
		amountSelfstorageFull.Empty();
		amountTransferUsed.Empty();
		amountTransferDefused.Empty();
		amountTransferStorage.Empty();
		amountTransferBurial.Empty();
		wasteNorm.Empty();
		structuralUnit.Empty();
		rowCount = 0;
	}
	~pod10Info()
	{
		allDates.Clear();
		code.Clear();
		amountTransferBurial.Clear();
		amountTransferUsed.Clear();
		amountTransferDefused.Clear();
		amountTransferStorage.Clear();
		amountSelfstorageFull.Clear();
		amountSelfstorage.Clear();
		amountBurial.Clear();
		amountDefused.Clear();
		amountUsed.Clear();
		amountRePhys.Clear();
		amountReOrg.Clear();
		amountFormed.Clear();
		codeDangerLVL.Clear();
		codeDescription.Clear();
		wasteNorm.Clear();
		structuralUnit.Clear();
	}
};

struct passportPod9Info
{

	wxArrayString uniqueCodes;
	wxArrayInt id;
	wxArrayString idString;
	wxArrayDouble amount;
	wxArrayString amountString;
	wxArrayString manufacturer;
	wxArrayString owner;
	wxArrayString receiver;
	wxArrayString transporter;
	wxArrayString date;
	wxArrayString regnum;
	wxArrayString stuct_unit9;
	wxArrayDouble amountFormed;
	wxArrayDouble amountReceivedOrg;
	wxArrayDouble amountReceivedPhys;
	wxArrayDouble amountUsed;
	wxArrayDouble amountDefused;
	wxArrayDouble amountBurial;
	wxArrayDouble amountSelfstorage;
	wxArrayDouble amountFullStorage;
	wxArrayDouble amountTransferUsed;
	wxArrayDouble amountTransferDefused;
	wxArrayDouble amountTransferStorage;
	wxArrayDouble amountTransferBurial;

	wxString codeDangerLVL;
	wxString codeDescription;
	int rowCount{ 0 };
	~passportPod9Info()
	{
		uniqueCodes.Clear();
		id.Clear();
		idString.Clear();
		owner.Clear();
		manufacturer.Clear();
		amountString.Clear();
		codeDangerLVL.Clear();
		receiver.Clear();
		transporter.Clear();
		regnum.Clear();
		date.Clear();
		amountTransferBurial.Clear();
		amountTransferUsed.Clear();
		amountTransferDefused.Clear();
		amountTransferStorage.Clear();
		amountFullStorage.Clear();
		amountSelfstorage.Clear();
		amountBurial.Clear();
		amountDefused.Clear();
		amountUsed.Clear();
		amountReceivedPhys.Clear();
		amountReceivedOrg.Clear();
		amountFormed.Clear();
	}

	void emptyPodStruct9Info()
	{
		id.Empty();
		idString.Empty();
		amount.Empty();
		amountString.Empty();
		date.Empty();
		manufacturer.Empty();
		receiver.Empty();
		owner.Empty();
		transporter.Empty();
		regnum.Empty();
		amountFormed.Empty();
		amountReceivedOrg.Empty();
		amountReceivedPhys.Empty();
		amountUsed.Empty();
		amountDefused.Empty();
		amountBurial.Empty();
		amountSelfstorage.Empty();
		amountFullStorage.Empty();
		amountTransferUsed.Empty();
		amountTransferDefused.Empty();
		amountTransferStorage.Empty();
		amountTransferBurial.Empty();
	}
};

struct passportStorageInfo
{
	wxDouble amountFormed{0};
	wxDouble amountReceivedOrg{0};
	wxDouble amountReceivedPhys{0};
	wxDouble amountUsed{0};
	wxDouble amountDefused{0};
	wxDouble amountSelfstorage{0};
	wxDouble amountBurial{0};
	wxDouble amountTransferUsed{0};
	wxDouble amountTransferDefused{0};
	wxDouble amountTransferStorage{0};
	wxDouble amountTransferBurial{0};
	wxDouble amountSelfstorageFull{0};
	wxString wasteNorm{ "" };
	wxString structuralUnit{ "" };
};

struct passportJournalInfo
{
	std::vector<double> amountTransferUsed;
	std::vector<double> amountTransferDefused;
	std::vector<double> amountTransferStorage;
	std::vector<double> amountTransferBurial;
	std::vector<double> amountUsed;
	std::vector<double> amountDefused;
	std::vector<double> amountStorage;
	std::vector<double> amountBurial;
	wxArrayString date{};
	wxArrayString regnum{};
	wxArrayString transporter{};
	wxArrayString receiver{};
	wxArrayString code{};
	wxArrayString codeDangerLVL{};
	~passportJournalInfo()
	{
		code.Clear();
		codeDangerLVL.Clear();
		receiver.Clear();
		transporter.Clear();
		regnum.Clear();
		date.Clear();
		amountTransferBurial.clear();
		amountTransferUsed.clear();
		amountTransferDefused.clear();
		amountTransferStorage.clear();
	}
};


struct addPageInfo
{
	wxString receiver;
	wxString transporter;
	wxString owner;
	wxString regnum;
	wxString code;
	wxString oldCode;
	wxString amountReceivedPhys;
	wxString amountReceivedOrg;
	wxString amountFormed;
	wxString date;
	wxString codeDngLvl;
	wxString oldDate;
	wxString entryDate;
	wxString wasteNorm;
	wxString structUnit10;
	wxString oldStructUnit10;
	wxString structUnit9;
	wxString amountStrgFull;
	wxString amountUsed;
	wxString amountDefused;
	wxString amountStorage;
	wxString amountBurial;
	wxString tamountUsed;
	wxString tamountDefused;
	wxString tamountStorage;
	wxString tamountBurial;
	wxString activeUnitID;
	wxString actveRecieverUnitID;
	wxString amountUsedUnit;
	wxString amountDefusedUnit;
	wxString amountStorageUnit;
	wxString amountBurialUnit;
	wxString tamountUsedUnit;
	wxString tamountDefusedUnit;
	wxString tamountStorageUnit;
	wxString tamountBurialUnit;
	wxString id;
	wxString storageId;
	wxString dependency;
};