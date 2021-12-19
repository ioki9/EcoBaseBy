#pragma once
#include <wx/pdfdoc.h>
#include <memory>
#include "PDF_Main.h"
#include "PDF_Helper.h"
#include "../Structs.h"
#include "../Database/DBMain.h"

class PDF_Pod10 : public PDF_Helper
{
public:
	PDF_Pod10(int orientation = wxLANDSCAPE,
		const wxString& unit = wxString(wxT("mm")),
		wxPaperSize format = wxPaperSize::wxPAPER_A4) : PDF_Helper{ orientation, unit, format }
	{
		SetMargins(10.0, 5.0, 10.0);
		SetAutoPageBreak(1,5.0);
	}
	~PDF_Pod10() { };
private:
	wxFont font{ 12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Times New Roman", wxFONTENCODING_CP1251 };
	pod10Info m_data;
	int m_precision{ };
	bool m_tableLast{ 0 };
	std::unique_ptr<DBMain> m_dataBase;
protected:

	void drawTableSignature();
	void drawTableHeader(const std::vector<double> &w);
	void drawMulticellRows(const std::vector<double> &w);
	
	wxString convertDateToMonthString(const wxString &date);
	void Footer() override;
	void drawTable();
public:


	void createDoc(const wxString& startDate, const wxString& endDate, const wxString& orgName);
	

};

