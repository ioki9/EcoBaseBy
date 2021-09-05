#pragma once

#include "DBMain.h"
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
	DBMain *m_dataBase;
	wxString formatToYMD(wxDateTime date);
protected:
	
public:
	void formJournal(const wxDateTime& startDate, const wxDateTime& endDate);
	void formPod9(const wxDateTime& startDate, const wxDateTime& endDate);
	void formPod10(const wxDateTime& startDate, const wxDateTime& endDate);
};

