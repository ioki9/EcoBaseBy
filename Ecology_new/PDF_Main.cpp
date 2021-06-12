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
		pdf.SaveAsFile(wxS("" + passData.uniqueCodes[i] + ".pdf"));
	}
	delete db;

}

