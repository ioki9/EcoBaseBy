#pragma once
#include "PDF_Main.h"


PDF_Main::~PDF_Main()
{
}


void PDF_Main::formPod9()
{
	DBMain *db = new DBMain;
	passportPod9Info passData;
	wxString codename;
	int unique{ db->getUniqueCodes(passData) };
	int i;
	for (i = 0; i < unique; i++)
	{
		db->getNextPod9Portion(passData, passData.uniqueCodes[i]);

		PDF_Pod9 pdf(passData, passData.uniqueCodes[i]);

		pdf.AddPage();
		pdf.drawTable();
		pdf.SaveAsFile(wxGetCwd() + wxS("/Test/" + passData.uniqueCodes[i] + ".pdf"));
	}
	delete db;

}


void PDF_Main::formJournal(wxDateTime *startDate)
{
	wxString date{};
	if (startDate != nullptr)
		date = startDate->Format(wxS("%Y.%m.%d"));
	else
		date = "1900.01.01";

	passportJournalInfo journalData;
	PDF_Journal *journal = new PDF_Journal(journalData, date);
	journal->createJournal();
	delete journal;
}
