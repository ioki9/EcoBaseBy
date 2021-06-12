#pragma once
#include <wx/wx.h>
#include <wx/pdfdocument.h>
#include <iostream>
#include <fstream>
class createpdf : public wxPdfDocument
{
public:
	createpdf();
	~createpdf();

	int createPdf(){
		wxPdfDocument pdf;
		pdf.AddPage(1);
		pdf.SetFont(wxS("Helvetica"), wxS("B"), 16);
		pdf.Cell(40, 10, wxS("Hello World!"));
		pdf.SaveAsFile(wxS("tutorial1.pdf"));
		return 0;
	}

};

