#pragma once
#include "DBMain.h"
#include <wx/pdfdoc.h>
#include "PDF_Main.h"
#include "PDF_Helper.h"
#include "Structs.h"

class PDF_Pod10 : public PDF_Helper
{
public:
	PDF_Pod10(int orientation = wxLANDSCAPE,
		const wxString &unit = wxString(wxT("mm")),
		wxPaperSize format = wxPaperSize::wxPAPER_A4) : PDF_Helper{orientation, unit, format }
	{
		SetMargins(10.0, 5.0, 10.0);
		SetAutoPageBreak(1,5.0);
	}
	~PDF_Pod10() { delete m_db; };
private:
	wxFont font{ 12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP1251 };
	pod10Info m_data;
	DBMain *m_db = new DBMain;
	bool m_tableLast{ 0 };

protected:

	void drawTableSignature();
	void drawTableHeader(const std::vector<double> &w);
	void drawMulticellRows(const std::vector<double> &w);
	
	wxString convertDateToMonthString(const wxString &date);
	void Footer() override;
	void drawTable();
public:


	void createDoc();
	

};

