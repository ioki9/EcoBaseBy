#pragma once
#include "wx/datetime.h"
#include "wx/string.h"
#include <wx/font.h>
#include "Structs.h"
#include "wx/pdfdoc.h"
#include <wx/numformatter.h>
#include "DBMain.h"
#include "PDF_Main.h"
#include "PDF_Helper.h"

class PDF_Pod9 :public PDF_Helper
{
public:
	PDF_Pod9(const passportPod9Info &data, const wxString &code, int orientation = wxLANDSCAPE,
		const wxString &unit = wxString(wxT("mm")), wxPaperSize format = wxPaperSize::wxPAPER_A4) 
		: m_data{ data }, m_codename{ code }, PDF_Helper{ orientation, unit, format }
	{
		SetMargins(10.0, 5.0, 10.0);
		SetAutoPageBreak(1, 30.0);
	}
	~PDF_Pod9() { };
private:

	wxFont font{ 12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP1251 };
	passportPod9Info m_data;
	wxString m_codename;
	

protected:
	void drawTableHeader(const std::vector<double>& w);
	void Footer() override;
	void Header() override;
	void drawResultRow(const std::vector<double>& w, const std::array<double, 7>& value);

public:

	void drawTable();
private:

};