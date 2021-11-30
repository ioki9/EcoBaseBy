#pragma once
#include <wx/wx.h>
#include <wx/validate.h>
#include "../Database/DBMain.h"
#include "../Database/DBColumnEnums.h"

class CustomCodeValidator : public wxValidator
{

public:
	CustomCodeValidator();
	~CustomCodeValidator();
	wxValidator* Clone() const;
	CustomCodeValidator(const CustomCodeValidator& valid); 
	virtual bool Validate(wxWindow* parent) wxOVERRIDE;
	void onChar(wxKeyEvent& evt);
	wxChoice m_dngLvl;
	void ChangeDngLvl(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();
private:
	
	DBMain m_db;
};

