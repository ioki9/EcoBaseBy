#include "CustomCodeValidator.h"
#include "CustomEvents.h"


wxBEGIN_EVENT_TABLE(CustomCodeValidator, wxValidator)
    EVT_CHAR(CustomCodeValidator::onChar)
    EVT_TEXT(-1,CustomCodeValidator::ChangeDngLvl)
wxEND_EVENT_TABLE()

CustomCodeValidator::CustomCodeValidator() : wxValidator()
{

}

CustomCodeValidator::~CustomCodeValidator()
{
}

bool CustomCodeValidator::Validate(wxWindow* parent)
{
    if (!wxDynamicCast(parent, wxTextCtrl))
        return true;
    wxTextEntry* const text = (wxTextCtrl*)parent;

    wxSQLite3ResultSet res = m_db.ExecuteQuery(wxS("SELECT * FROM " + m_db.GetActiveCodeTable() + " WHERE "
        + m_db.GetCodesColumns()[DB_COLUMN_CODE] + "  LIKE '" + text->GetValue() + "%'"));
    if (res.NextRow())
    {
        res.Finalize();
        return false;
    }
    return true;
}

void CustomCodeValidator::onChar(wxKeyEvent& evt)
{
    evt.Skip();
    if (!wxDynamicCast(evt.GetEventObject(), wxTextCtrl))
        return;
#if wxUSE_UNICODE
    // We only filter normal, printable characters.
    int keyCode = evt.GetUnicodeKey();
#else // !wxUSE_UNICODE
    int keyCode = evt.GetKeyCode();
    if (keyCode > WXK_START)
        return;
#endif // wxUSE_UNICODE/!wxUSE_UNICODE

    // we don't filter special keys and delete
    if (keyCode < WXK_SPACE || keyCode == WXK_DELETE)
        return;
    wxTextEntry* const text = (wxTextCtrl*)evt.GetEventObject();
    int l = text->GetInsertionPoint();
    wxSQLite3ResultSet res = m_db.ExecuteQuery(wxS("SELECT * FROM " + m_db.GetActiveCodeTable() + " WHERE "
        + m_db.GetCodesColumns()[DB_COLUMN_CODE] + "  LIKE '" + text->GetValue().Mid(0,l) + evt.GetUnicodeKey() + "%'"));
    if (!res.NextRow())
    {
        res.Finalize();
        wxBell();
        evt.Skip(false);
        return;
    }
    res.Finalize();
 
}

void CustomCodeValidator::ChangeDngLvl(wxCommandEvent& evt)
{
    wxSQLite3ResultSet res = m_db.ExecuteQuery(wxS("SELECT * FROM " + m_db.GetActiveCodeTable() + " WHERE "
        + m_db.GetCodesColumns()[DB_COLUMN_CODE] + " = '" + evt.GetString() + "'"));
    if (res.NextRow())
    {
        res.Finalize();
        wxCommandEvent event(EVT_ENTERED_CODE_EXISTS);
        event.SetString(m_db.GetDngFromCode(evt.GetString()));
        wxPostEvent(GetWindow(), event);
    }
    res.Finalize();
}



wxValidator* CustomCodeValidator::Clone() const 
{ 
    return new CustomCodeValidator(*this);
}

CustomCodeValidator::CustomCodeValidator(const CustomCodeValidator& valid) : wxValidator(valid)
{

}
