#pragma once
#include "PDF_Main.h"
#include <chrono>



using namespace std::chrono;
PDF_Main::~PDF_Main()
{
	delete m_dataBase;
}


void PDF_Main::formPod9()
{

	passportPod9Info passData;
	wxString codename;
	int unique{ m_dataBase->getUniqueCodes(passData) };
	int i{};
	int time{ 0 };
	for (i = 0; i < unique; i++)
	{
		m_dataBase->getNextPod9Portion(passData, passData.uniqueCodes[i]);
		PDF_Pod9 pdf(passData, passData.uniqueCodes[i]);

		pdf.AddPage();
		pdf.drawTable();
		pdf.SaveAsFile(wxGetCwd() + wxS("/Test/" + passData.uniqueCodes[i] + ".pdf"));
	}
	wxMessageBox(std::to_string(time));

}


void PDF_Main::formJournal(wxDateTime *startDate)
{
	wxString date{};
	if (startDate != nullptr)
		date = startDate->Format(wxS("%Y.%m.%d"));
	else
		date = "1900.01.01";

	passportJournalInfo journalData;
	PDF_Journal *journal = new PDF_Journal(m_dataBase,journalData, date);
	journal->createJournal();
	delete journal;
}
