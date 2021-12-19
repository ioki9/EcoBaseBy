#pragma once
#include "../Database/DBMain.h"
#include "PDF_Pod9.h"
#include "PDF_Pod10.h"
#include "PDF_Journal.h"


class PDF_Main
{
public:
	PDF_Main()
	{
	}
	~PDF_Main();
private:
	std::unique_ptr<DBMain> m_dataBase = std::make_unique<DBMain>();
	wxString formatToYMD(wxDateTime date);
protected:
	
public:
	void formJournal(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName);
	void formPod9(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName,const wxString& unitName,const wxString& unitID);
	void formPod10(const wxDateTime& startDate, const wxDateTime& endDate, const wxString& orgName);
};

