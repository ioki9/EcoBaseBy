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
	void sortByCode(int low, int high)
	{
		if (low < high)
		{
			//partition index
			int pi = sortPartition(low, high);

			// Separately sort elements before
			// partition and after partition
			sortByCode(low, pi - 1);
			sortByCode(pi + 1, high);
		}
	}
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
private:
	int sortPartition(int low, int high)
	{
		wxString pivot = code[high];
		int indexSmaller = low - 1;
		for (int j{ low }; j <= high - 1; ++j)
		{
			if (code[j] <= pivot)
			{
				//swap elements in all dependent arrays
				++indexSmaller;
				swap(code, indexSmaller, j);
				swap(codeDangerLVL, indexSmaller, j);
				swap(amountFormed, indexSmaller, j);
				swap(amountReOrg, indexSmaller, j);
				swap(amountRePhys, indexSmaller, j);
				swap(amountUsed, indexSmaller, j);
				swap(amountDefused, indexSmaller, j);
				swap(amountSelfstorage, indexSmaller, j);
				swap(amountBurial, indexSmaller, j);
				swap(amountTransferUsed, indexSmaller, j);
				swap(amountTransferDefused, indexSmaller, j);
				swap(amountTransferStorage, indexSmaller, j);
				swap(wasteNorm, indexSmaller, j);
				swap(amountTransferBurial, indexSmaller, j);
				swap(amountSelfstorageFull, indexSmaller, j);
				swap(structuralUnit,indexSmaller, j);
			}
		}
		swap(code,indexSmaller + 1,high);
		swap(codeDangerLVL, indexSmaller + 1, high);
		swap(amountFormed, indexSmaller + 1, high);
		swap(amountReOrg, indexSmaller + 1, high);
		swap(amountRePhys, indexSmaller + 1, high);
		swap(amountUsed, indexSmaller + 1, high);
		swap(amountDefused, indexSmaller + 1, high);
		swap(amountSelfstorage, indexSmaller + 1, high);
		swap(amountBurial, indexSmaller + 1, high);
		swap(amountTransferUsed, indexSmaller + 1, high);
		swap(amountTransferDefused, indexSmaller + 1, high);
		swap(amountTransferStorage, indexSmaller + 1, high);
		swap(wasteNorm, indexSmaller + 1, high);
		swap(amountTransferBurial, indexSmaller + 1, high);
		swap(amountSelfstorageFull, indexSmaller + 1, high);
		swap(structuralUnit, indexSmaller + 1, high);
		
		return (indexSmaller + 1);
	}

	void swap(wxArrayString& arr,int aPos,int bPos)
	{
		wxString temp = arr[aPos];
		arr[aPos] = arr[bPos];
		arr[bPos] = temp;
	}
	void swap(wxArrayDouble& arr, int aPos, int bPos)
	{
		double temp = arr[aPos];
		arr[aPos] = arr[bPos];
		arr[bPos] = temp;
	}
};

struct passportPod9Info
{
	wxString wasteNorm;
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
		uniqueCodes.Clear();
		idString.Clear();
		stuct_unit9.Clear();
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
		idString.Empty();
		stuct_unit9.Empty();
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