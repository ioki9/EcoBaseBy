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
protected:
	
public:
	void formJournal(wxDateTime* startDate = nullptr);
	void formPod9();

};

