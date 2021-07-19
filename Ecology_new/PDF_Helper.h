#pragma once
#include <wx/pdfdoc.h>
#include "Structs.h"
#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/pdfdoc.h>
#include <wx/numformatter.h>
#include "DBMain.h"
#include "Utility.h"




class PDF_Helper: public wxPdfDocument
{
public:
	PDF_Helper(int orientation = wxLANDSCAPE,
		const wxString &unit = wxString(wxT("mm")),
		wxPaperSize format = wxPaperSize::wxPAPER_A4) : wxPdfDocument{ orientation, unit, format }
	{
		SetMargins(10, 5, 10);
		SetAutoPageBreak(1, 10);
		SetFont(m_font);
	}
private:
	
	wxFont m_font{ 12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP1251 };
	size_t removeUnwantedHyphens(wxString& word, unsigned int pos);


protected:
	double getMulticellRowHeight(double h, const std::vector<wxString> &arr, const std::vector<double> &w) ;
	void tableRow(double h, const std::vector<double> &w, std::vector<wxString> &str, int border, int align);
	void POD10TableRow(double h,const std::vector<double> &w, std::vector<wxString> &str, int align, int border);
	void centerRotatedText(double w, double h, const wxString &string1, const wxString &string2 = "", const wxString &string3 = "");
	void tableMultiCell(double w, double h, const wxString &text, int border = 0,int ln = 0, int align = 0);
	wxString autoCellHyphenation(double w, const wxString &text);
	wxString getAmountString(double amount);
	wxString getAmountString(wxString& amount);
	int compareDates(const wxString& startDate, const wxString& endDate);
	void tableHeaderCell(double w, double h, const wxString& text, int border, int ln, int align);
};

