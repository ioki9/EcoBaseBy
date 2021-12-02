#include "PDF_Journal.h"
#include "../Settings.h"




void PDF_Journal::drawHeader()
{

	double hd_h{ 30.0 };
	AddPage();
	wxFont font(wxFontInfo(10).FaceName("Times New Roman").Bold().Encoding(wxFONTENCODING_CP1251));
	SetFont(font);
	tableHeaderCell(w[0], hd_h, wxString::FromUTF8("Регистра-\nционый номер сопроводи-\nтельного паспорта"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[1], hd_h, wxString::FromUTF8("Дата перевозки отходов произ-\nводства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[2], hd_h, wxString::FromUTF8("Перевозчик отходов производства, номер и дата договора на передачу отходов производства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[3], hd_h, wxString::FromUTF8("Получатель отходов\nпроизводства "), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[4], hd_h, wxString::FromUTF8("Код\nотходов"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[5], hd_h, wxString::FromUTF8("Класс\nопасности"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	double currentX{ GetX() };
	tableHeaderCell(w[6] + w[7] + w[8] + w[9], hd_h /3.0, wxString::FromUTF8("Передано отходов производства"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	SetXY(currentX, GetY() + hd_h / 3);
	tableHeaderCell(w[7], hd_h / 1.5, wxString::FromUTF8("на использо-\nвание, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[7], hd_h / 1.5, wxString::FromUTF8("на обезврежи-\nвание, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[8], hd_h / 1.5, wxString::FromUTF8("на захороне-\nние, тонн"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	tableHeaderCell(w[9], hd_h / 1.5, wxString::FromUTF8("на хранение, тонн"), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	font.SetWeight(wxFONTWEIGHT_NORMAL);
	SetFont(font);
	for (int i{ 0 }; i < 10; i++)
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
		for (int i{ 0 }; i < 10; i++)
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
		if (m_data.amountTransferUsed[row] != 0.0)
			m_amUsed = m_data.amountTransferUsed[row];
		else
			m_amUsed = m_data.amountUsed[row];

		if (m_data.amountTransferDefused[row] != 0.0)
			m_amDefused = m_data.amountTransferDefused[row];
		else
			m_amDefused = m_data.amountDefused[row];

		if (m_data.amountTransferBurial[row] != 0.0)
			m_amBurial = m_data.amountTransferBurial[row];
		else
			m_amBurial = m_data.amountBurial[row];

		if (m_data.amountTransferStorage[row] != 0.0)
			m_amStorage = m_data.amountTransferStorage[row];
		else
			m_amStorage = m_data.amountStorage[row];

		if (m_data.codeDangerLVL.empty())
			m_precision = 3;
		else if (m_data.codeDangerLVL[row][0] == '4' || m_data.codeDangerLVL[row][0] == 'н')
			m_precision = 2;
		else
			m_precision = 3;

		if (row != 0)
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
		resultData(resultRowCol, m_data.codeDangerLVL[row]);
		rowData = { m_data.regnum[row], newDate , m_data.transporter[row], m_data.receiver[row],
			m_data.code[row], m_data.codeDangerLVL[row],  getAmountString(m_amUsed,m_precision),
			getAmountString(m_amDefused,m_precision) , getAmountString(m_amBurial,m_precision),
			getAmountString(m_amStorage,m_precision) };

		tableRow(h, w, rowData, wxPDF_BORDER_FRAME, wxPDF_ALIGN_MIDDLE);
	}
	drawResultRow(resultRowCol);
	
}

void PDF_Journal::resultData(std::array<std::array<double, 5>, 4>& value, const wxString& codeDngLvl)
{
	if (codeDngLvl.Contains(wxS("1")))
	{
		value[0][0] += m_amUsed;
		value[1][0] += m_amDefused;
		value[2][0] += m_amBurial;
		value[3][0] += m_amStorage;
	}
	else if (codeDngLvl.Contains(wxS("2")))
	{
		value[0][1] += m_amUsed;
		value[1][1] += m_amDefused;
		value[2][1] += m_amBurial;
		value[3][1] += m_amStorage;
	}
	else if (codeDngLvl.Contains(wxS("3")))
	{
		value[0][2] += m_amUsed;
		value[1][2] += m_amDefused;
		value[2][2] += m_amBurial;
		value[3][2] += m_amStorage;
	}
	else if (codeDngLvl.Contains(wxS("4")))
	{
		value[0][3] += m_amUsed;
		value[1][3] += m_amDefused;
		value[2][3] += m_amBurial;
		value[3][3] += m_amStorage;
	}
	else
	{
		value[0][4] += m_amUsed;
		value[1][4] += m_amDefused;
		value[2][4] += m_amBurial;
		value[3][4] += m_amStorage;
	}

}


void PDF_Journal::drawResultRow(const std::array<std::array<double, 5>, 4>& value)
{
	wxFont font(wxFontInfo(10).FaceName("Times New Roman").Bold().Encoding(wxFONTENCODING_CP1251));
	SetFont(font);
	Cell(w[0] + w[1] + w[2] + w[3] + w[4], h * 5, wxString::FromUTF8("Итого передано в налоговый период"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	double x{ GetX() };

	Cell(w[5], h, wxString::FromUTF8("1-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][0], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][0], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][0], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][0],3), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxString::FromUTF8("2-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][1], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][1], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][1], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][1], 3), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxString::FromUTF8("3-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][2], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][2], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][2], 3), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][2], 3), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxString::FromUTF8("4-го класса"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][3], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][3], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][3], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][3], 2), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	SetXY(x, GetY());
	Cell(w[5], h, wxString::FromUTF8("неопасных"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[6], h, getAmountString(value[0][4], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[7], h, getAmountString(value[1][4], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[8], h, getAmountString(value[2][4], 2), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
	Cell(w[9], h, getAmountString(value[3][4], 2), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
	font.SetWeight(wxFONTWEIGHT_NORMAL);
	SetFont(font);
}



void PDF_Journal::createJournal(const wxString& startDate, const wxString& endDate, const wxString& orgName)
{
	if (!wxDirExists(Settings::GetPdfSavePath() + "/" + orgName))
		wxFileName::Mkdir(Settings::GetPdfSavePath() + "/" + orgName, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	m_dataBase->getJournalTableInfo(m_data, startDate, endDate);
	if (m_data.date.empty())
	{
		wxMessageBox(wxString::FromUTF8("Отсутствуют данные для создания журнала."));
		return;
	}
	drawTable();
	SaveAsFile(Settings::GetPdfSavePath() + "/" + orgName + wxString::FromUTF8("/Журнал паспортов.pdf"));
}

