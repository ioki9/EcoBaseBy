#pragma once
#include <wx/string.h>
#include <string>
#include <wx/dynarray.h>
#include <algorithm>
#include <wx/textfile.h>
#include <wx/graphics.h>
#include <wx/wx.h>
#include <vector>




 namespace utility
{

	void draw();
	void paintDarkBackground(wxWindowDC* dc,wxWindow* parent);
	wxString Hyphenate(const wxString &word);
	wxString convertDate(const wxString& date);
}

