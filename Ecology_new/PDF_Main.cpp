#pragma once
#include "PDF_Main.h"
#include <chrono>



using namespace std::chrono;
PDF_Main::~PDF_Main()
{
	delete m_dataBase;
}

wxString PDF_Main::formatToYMD(wxDateTime date)
{
	return date.Format(wxS("%Y.%m.%d"));
}


void PDF_Main::formPod9(const wxDateTime& startDate, const wxDateTime& endDate)
{
	m_dataBase = new DBMain();
	passportPod9Info passData;
	wxString codename;
	int unique{ m_dataBase->getUniqueCodes(passData,formatToYMD(startDate),formatToYMD(endDate)) };
	int i{};
	int time{ 0 };
	for (i = 0; i < unique; i++)
	{
		m_dataBase->getNextPod9Portion(passData, passData.uniqueCodes[i], formatToYMD(startDate), formatToYMD(endDate));
		PDF_Pod9 pdf(passData, passData.uniqueCodes[i]);

		pdf.AddPage();
		pdf.drawTable();
		pdf.SaveAsFile(wxGetCwd() + wxS("/Test/" + passData.uniqueCodes[i] + ".pdf"));
	}
	wxMessageBox(std::to_string(time));

}

void PDF_Main::formPod10(const wxDateTime& startDate, const wxDateTime& endDate)
{
	PDF_Pod10* pod10 = new PDF_Pod10();
	pod10->createDoc(formatToYMD(startDate), formatToYMD(endDate));
	delete pod10;
}


void PDF_Main::formJournal(const wxDateTime& startDate, const wxDateTime& endDate)
{
	PDF_Journal *journal = new PDF_Journal();
	journal->createJournal(formatToYMD(startDate), formatToYMD(endDate));
	delete journal;
}
