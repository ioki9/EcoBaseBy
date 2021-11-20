#pragma once
#include <wx/textcompleter.h>
#include <wx/wx.h>
#include "../Database/DBMain.h"
#include <map>

enum class dbTables
{
    passport,
    storage,
    codes
};
 
typedef wxString(DBMain::* DBMainFuncPtr)(void);

class CustomAutoComplete : public wxTextCompleterSimple
{
public:
    CustomAutoComplete(dbTables table, int dbColumnEnum);
    CustomAutoComplete(CustomAutoComplete&& a) noexcept;
    ~CustomAutoComplete();
    void onChar(wxKeyEvent& evt);
    wxDECLARE_EVENT_TABLE();
private:
    DBMain m_db{};
    int m_columnEnum{};
    dbTables m_table{};
    DBMainFuncPtr m_getTable = nullptr;
    std::map<int, wxString> m_columns{};
    wxSQLite3ResultSet m_resSet{};
    virtual void GetCompletions(const wxString& prefix, wxArrayString& res) wxOVERRIDE;

};

