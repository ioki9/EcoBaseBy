#pragma once
#include <wx/string.h>
#include <string>
#include <wx/dynarray.h>
#include <algorithm>
#include <wx/textfile.h>
#include <wx/wx.h>
#include <vector>
#include "Global variables.h"




 namespace utility
{

	void draw();
	wxString Hyphenate(const wxString &word);

}

