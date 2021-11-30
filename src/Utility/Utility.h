#pragma once
#include <wx/wx.h>
#include <wx/valnum.h>


 namespace utility
{

	void paintDarkBackground(wxWindowDC* dc, wxWindow* parent);
	wxString Hyphenate(const wxString &word);
	wxString convertDate(const wxString& date);
	wxFloatingPointValidator<double> GetDoubleValidator(int precision,double initValue = 0.0);
	//we need to delete pattern instance
	void ClearVars();
}

