#pragma once
#include <wx/string.h>

const wxString DBPasspTableName{ "passport" };
const wxString DBCodesTableName{ "codes" };
const wxString DBStorageTableName{ "storageInfo" };
const wxString DBPathPassp{ wxGetCwd() + wxS("/passdat.db") };
const wxString patternsFileName{ "/hyph-ru.pat.txt" };