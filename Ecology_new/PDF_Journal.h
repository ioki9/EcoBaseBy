#pragma once
#include <wx\pdfdoc.h>
#include <vector>
#include <wx/font.h>
#include <array>
#include "PDF_Helper.h"
#include "PDF_Main.h"
#include "DBMain.h"

class PDF_Journal : public PDF_Helper
{
public:
	PDF_Journal(int orientation = wxLANDSCAPE,
		const wxString& unit = wxString(wxS("mm")), wxPaperSize format = wxPaperSize::wxPAPER_A4)
		: PDF_Helper{ orientation, unit, format }
	{
		SetMargins(10.0, 5.0, 10.0);
		SetAutoPageBreak(1, 5.0);
	}
	~PDF_Journal() { delete m_dataBase; };
private:
	passportJournalInfo m_data;
	wxString m_startDate;
	DBMain* m_dataBase;
	const std::vector<double> w { 20.5,19.5,60.5,60.5,17.0,19.0,20.0,20.0,20.0,20.0 };
	const double h{ 5.0 };
protected:
private:
	void drawHeader();
	void drawTable();
	void resultData(std::array<std::array<double, 5>, 4>& value, const wxString& codeDngLvl, int row);
	void drawResultRow(const std::array<std::array<double, 5>, 4>& value);
	void Header() override;
public:
	void createJournal(const wxString& startDate, const wxString& endDate);
	
};

