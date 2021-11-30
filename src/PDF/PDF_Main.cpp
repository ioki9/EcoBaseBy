#include "PDF_Main.h"
#include "../Settings.h"
#include <wx/version.h>

PDF_Main::~PDF_Main()
{
	delete m_dataBase;
}

wxString PDF_Main::formatToYMD(wxDateTime date)
{
	return date.Format(wxS("%Y.%m.%d"));
}

void PDF_Main::formPod9(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName, const wxString& unitName, const wxString& unitID)
{
	wxString BSunitName{ '/'+ unitName  };
	if (unitName.IsEmpty())
		BSunitName = "";
	if (!wxDirExists(Settings::GetPdfSavePath() + "/" + orgName + "/ПОД9" + BSunitName))
		wxFileName::Mkdir(Settings::GetPdfSavePath() + "/" + orgName + "/ПОД9" + BSunitName, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	passportPod9Info passData;
	wxString codename;
	int unique{ m_dataBase->getUniqueCodes(passData,unitID,formatToYMD(startDate),formatToYMD(endDate)) };
	int i{};
	for (i = 0; i < unique; i++)
	{
		m_dataBase->getNextPod9Portion(passData, passData.uniqueCodes[i], unitID, formatToYMD(startDate), formatToYMD(endDate));
		PDF_Pod9 pdf(passData, passData.uniqueCodes[i]);
		pdf.AddPage();
		pdf.drawTable();

		pdf.SaveAsFile(Settings::GetPdfSavePath() + "/" + orgName + "/ПОД9" + BSunitName + '/' + passData.uniqueCodes[i] + ".pdf");
	}

}

void PDF_Main::formPod10(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName)
{
	PDF_Pod10* pod10 = new PDF_Pod10();
	pod10->createDoc(formatToYMD(startDate).Mid(0, 7), formatToYMD(endDate).Mid(0, 7),orgName);
	delete pod10;
}


void PDF_Main::formJournal(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName)
{
	PDF_Journal *journal = new PDF_Journal();
	journal->createJournal(formatToYMD(startDate), formatToYMD(endDate), orgName);
	delete journal;
}
