#include "PDF_Journal.h"





void PDF_Journal::drawHeader()
{

	double hd_h{ 30.0 };
	AddPage();
	wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_ROMAN).Bold().Encoding(wxFONTENCODING_CP1251));
	SetFont(font);
	tableHeaderCell(w[0], hd_h, wxS("Регистра-\nционый номер сопроводи-\nтельного паспорта"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[1], hd_h, wxS("Дата перевозки отходов произ-\nводства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[2], hd_h, wxS("Перевозчик отходов производства, номер и дата договора на передачу отходов производства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[3], hd_h, wxS("Получатель отходов\nпроизводства "), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[4], hd_h, wxS("Код\nотходов"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[5], hd_h, wxS("Класс\nопасности"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	double currentX{ GetX() };
	tableHeaderCell(w[6] + w[7] + w[8] + w[9], hd_h /3.0, wxS("Передано отходов производства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	SetXY(currentX, GetY() + hd_h / 3);
	tableHeaderCell(w[7], hd_h / 1.5, wxS("на использо-\nвание, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[7], hd_h / 1.5, wxS("на обезврежи-\nвание, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[8], hd_h / 1.5, wxS("на захороне-\nние, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[9], hd_h / 1.5, wxS("на хранение, тонн"), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	font.SetWeight(wxFONTWEIGHT_NORMAL);
	SetFont(font);
	for (size_t i{ 0 }; i < 10; i++)
	{
		wxString hRowNum = wxString::Format(wxS("%i"), i + 1);
		Cell(w[i], 4, hRowNum, wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	}
	Ln();
}
void PDF_Journal::Header()
{
	if (PageNo() != 1)
	{
		for (size_t i{ 0 }; i < 10; i++)
		{
			wxString hRowNum = wxString::Format(wxS("%i"), i + 1);
			Cell(w[i], 4, hRowNum, wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
		}
	}
	Ln();
}

void PDF_Journal::drawTable()
{
	drawHeader();
	std::vector<wxString> rowData{};
	std::array<std::array<double, 5>, 4> resultRowCol{};
	for (auto& elem : resultRowCol)
		std::fill(elem.begin(), elem.end(), 0);
	wxString newDate{};
	wxString lastResultDate{ utility::convertDate(m_data.date[0]) };
	int dateDiff{ 0 };
	rowData.reserve(10);
	for (size_t row{ 0 }; row < m_data.date.GetCount(); ++row)
	{
		if(row!=0)
			lastResultDate = utility::convertDate(m_data.date[row-1]);
		newDate = utility::convertDate(m_data.date[row]);
		if (compareDates(lastResultDate, newDate) != 0)
			++dateDiff;
		if(dateDiff>2)
		{
			drawResultRow(resultRowCol);
			lastResultDate = m_data.date[row];
			for (auto &elem : resultRowCol) 
				std::fill(elem.begin(), elem.end(), 0);
			dateDiff = 0;
		}
			

		rowData.clear();
		resultData(resultRowCol, m_data.codeDangerLVL[row], row);
		rowData = { m_data.regnum[row], newDate , m_data.transporter[row], m_data.receiver[row],
			m_data.code[row], m_data.codeDangerLVL[row],  getAmountString(m_data.amountTransferUsed[row]),
			getAmountString(m_data.amountTransferDefused[row]) , getAmountString(m_data.amountTransferBurial[row]),
			getAmountString(m_data.amountTransferStorage[row]) };

		tableRow(h, w, rowData, wxPDF_BORDER_FRAME, wxPDF_ALIGN_MIDDLE);
	}
	drawResultRow(resultRowCol);
	
}

void PDF_Journal::resultData(std::array<std::array<double, 5>, 4>& value, const wxString& codeDngLvl, int row)
{
	if (codeDngLvl.Contains(wxS("1")))
	{
		value[0][0] += m_data.amountTransferUsed[row];
		value[1][0] += m_data.amountTransferDefused[row];
		value[2][0] += m_data.amountTransferBurial[row];
		value[3][0] += m_data.amountTransferStorage[row];
	}
	else if (codeDngLvl.Contains(wxS("2")))
	{
		value[0][1] += m_data.amountTransferUsed[row];
		value[1][1] += m_data.amountTransferDefused[row];
		value[2][1] += m_data.amountTransferBurial[row];
		value[3][1] += m_data.amountTransferStorage[row];
	}
	else if (codeDngLvl.Contains(wxS("3")))
	{
		value[0][2] += m_data.amountTransferUsed[row];
		value[1][2] += m_data.amountTransferDefused[row];
		value[2][2] += m_data.amountTransferBurial[row];
		value[3][2] += m_data.amountTransferStorage[row];
	}
	else if (codeDngLvl.Contains(wxS("4")))
	{
		value[0][3] += m_data.amountTransferUsed[row];
		value[1][3] += m_data.amountTransferDefused[row];
		value[2][3] += m_data.amountTransferBurial[row];
		value[3][3] += m_data.amountTransferStorage[row];
	}
	else
	{
		value[0][4] += m_data.amountTransferUsed[row];
		value[1][4] += m_data.amountTransferDefused[row];
		value[2][4] += m_data.amountTransferBurial[row];
		value[3][4] += m_data.amountTransferStorage[row];
	}

}


void PDF_Journal::drawResultRow(const std::array<std::array<double, 5>, 4>& value)
{
	wxFont font(wxFontInfo(10).Family(wxFONTFAMILY_ROMAN).Bold().Encoding(wxFONTENCODING_CP1251));
	SetFont(font);
	Cell(w[0] + w[1] + w[2] + w[3] + w[4], h * 5, wxS("Итого передано в налоговый период"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	double x{ GetX() };

	Cell(w[5], h, wxS("1-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][0]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][0]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][0]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][0]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxS("2-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][1]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][1]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][1]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][1]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxS("3-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][2]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][2]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][2]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][2]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxS("4-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][3]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][3]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][3]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][3]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxS("неопасных"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][4]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][4]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][4]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][4]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	font.SetWeight(wxFONTWEIGHT_NORMAL);
	SetFont(font);
}



void PDF_Journal::createJournal()
{
	m_dataBase->getJournalTableInfo(m_data,m_startDate);
	drawTable();
	SaveAsFile(wxGetCwd() + wxS("/Test/11Журнал.pdf"));
}

