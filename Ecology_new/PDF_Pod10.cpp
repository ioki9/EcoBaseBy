#pragma once
#include "PDF_Pod10.h"
#include <algorithm>
#include <wx/pdfxml.h>

void PDF_Pod10::createDoc()
{
    m_db->getPod10TableCount(m_data);
    int tableCount{ m_data.tableCount };
    int nextTable{ 0 };
    AddPage();
    wxPdfDocument pdft;
    for (int t = 0; t < tableCount; t++)
    {
        nextTable++;
        m_db->getPod10TableInfo(m_data, m_data.allDates[t]);
        m_db->getPod10TableCodeDngr(m_data, m_data.code);
        if (nextTable == tableCount)
            m_tableLast = true;
        else
            m_tableLast = false;
        drawTable();
       
        
    }
    SaveAsFile(wxS("1testPOD10.pdf"));
}

void PDF_Pod10::Footer()
{
    font.SetPointSize(12);
    SetFont(font);
    SetXY(148.5,-6);
    Cell(0, 3, wxString::Format(wxS("%d"), PageNo()), 0, wxPDF_ALIGN_CENTER);
   
}

void PDF_Pod10::drawTable()
{
    font.SetPointSize(12);
    SetFont(font);
    Cell(0, 10, convertDateToMonthString(m_data.date), 0, 1, wxPDF_ALIGN_CENTER);
    // Column parameters
    double w[18] = { 17,32.5,17,12,12,27,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5};
    drawTableHeader(w);
    drawMulticellRows(w);
    drawTableSignature();
}




void PDF_Pod10::drawTableHeader(const std::vector<double> &w)
{
    font.SetPointSize(10);
    SetFont(font);
    Cell(w[0], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[0], GetY() + 2.25);
    MultiCell(w[0], 4, wxS("Дата внесения учетной записи в книгу обшего\n учета\n отходов"), 0, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[0], GetY() - 34.25);
    Cell(w[1], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[1], GetY() + 14.25);
    MultiCell(w[1], 4, wxS("Наименование отхода"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[1] + w[0], GetY() - 22.25);
    Cell(w[2], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[2], GetY() + 14.25);
    MultiCell(w[2], 4, wxS("Код отхода"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[1] + w[0] + w[2], GetY() - 22.25);
    Cell(w[3], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[3], 36.5, wxS("Степень опасности"), wxS("или класс"));
    Cell(w[4], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[4], 36.5, wxS("Норматив"), wxS("образования отходов"));
    Cell(w[5], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[5], GetY() + 6.25);
    MultiCell(w[5], 4, wxS("Структурные подразделения, в которых образовался данный вид отхода"), 0, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[0] + w[1] + w[2] + w[3] + w[4] + w[5], GetY() - 30.25);
    Cell(w[6], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[6], 36.5, wxS("Образовалось, т. (шт.)"));
    Cell(w[7], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[7], 36.5, wxS("Поступило от других"), wxS("организаций, т. (шт.)"));
    Cell(w[8], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[8], 36.5, wxS("Поступило отх"), wxS("физических лиц, т."), wxS("(шт.)"));
    Cell(w[9], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[9], 36.5, wxS("Использовано, т. (шт.)"));
    Cell(w[10], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[10], 36.5, wxS("Обезврежено, т. (шт.)"));
    Cell(w[11], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[11], 36.5, wxS("Направлено на"), wxS("хранение, т. (шт.)"));
    Cell(w[12], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[12], 36.5, wxS("Захоронено, т. (шт.)"));
    Cell(w[13] + w[14] + w[15] + w[16], 6, wxS("Передано, т. (шт.)"), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[12] + w[11] + w[10] + w[9] + w[8] + w[7] + w[6] + w[5] + w[4] + w[3] + w[2] + w[1] + w[0], GetY());
    Cell(w[13], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[13], 30.5, wxS("на"), wxS("использование"));
    Cell(w[14], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[14], 30.5, wxS("на"), wxS("обезвреживание"));
    Cell(w[15], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[15], 30.5, wxS("на хранение"));
    Cell(w[16], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[16], 30.5, wxS(" на захоронение"));
    SetXY(GetX(), GetY() - 6);
    Cell(w[17], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[17], 36.5, wxS("Хранится, т. (шт.)"));
    Ln();
    size_t i;
    for (i = 0; i < 18; i++)
    {
        Cell(w[i], 5, wxString::Format(wxS("%i"), i + 1), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    Ln();
}


void PDF_Pod10::drawMulticellRows(const std::vector<double> &w)
{
    
    double h{};
    double currentY{};
    double currentX{};
    std::vector<wxString> str{}; 

    SetAutoPageBreak(0);
    for (int row{ 0 }, nextRow{ 1 }; row < m_data.rowCount; ++row,++nextRow)
    {
        str.empty();
        str = {m_data.codeDescription[row], m_data.code[row], m_data.codeDangerLVL[row], 
            m_data.wasteNorm[row], m_data.structuralUnit[row], m_data.amountFormed[row],
            m_data.amountReOrg[row] ,m_data.amountRePhys[row], m_data.amountUsed[row], 
            m_data.amountDefused[row], m_data.amountSelfstorage[row] ,m_data.amountBurial[row],
            m_data.amountTransferUsed[row], m_data.amountTransferDefused[row], m_data.amountTransferStorage[row], 
            m_data.amountTransferBurial[row], m_data.amountSelfstorageFull[row] };

        currentY = GetY();
        currentX = GetX();
        
        
        
            if (currentY == 5.0)
        {
                POD10TableRow(w, str, wxPDF_BORDER_LEFT | wxPDF_BORDER_TOP, wxPDF_ALIGN_CENTER, wxPDF_BORDER_FRAME);
            //Cell(w[0], h, wxS(""), wxPDF_BORDER_LEFT | wxPDF_BORDER_TOP);
            //tableMultiCell(w[1], h, m_data.codeDescription[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_LEFT);
            //tableMultiCell(w[2], h, m_data.code[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[3], h, m_data.codeDangerLVL[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[4], h, m_data.wasteNorm[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[5], h, m_data.structuralUnit[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[6], h, m_data.amountFormed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[7], h, m_data.amountReOrg[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[8], h, m_data.amountRePhys[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[9], h, m_data.amountUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[10], h, m_data.amountDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[11], h, m_data.amountSelfstorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[12], h, m_data.amountBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[13], h, m_data.amountTransferUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[14], h, m_data.amountTransferDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[15], h, m_data.amountTransferStorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[16], h, m_data.amountTransferBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[17], h, m_data.amountSelfstorageFull[row], wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
        }
          else if (nextRow != m_data.rowCount && (currentY + getMulticellRowHeight(nextRow, w)) > (GetPageHeight() - 10.0))
        {
            POD10TableRow(w, str, wxPDF_BORDER_LEFT | wxPDF_BORDER_BOTTOM, wxPDF_ALIGN_CENTER, wxPDF_BORDER_FRAME);
            //Cell(w[0], h, wxS(""), wxPDF_BORDER_LEFT | wxPDF_BORDER_BOTTOM);
            //tableMultiCell(w[1], h, m_data.codeDescription[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_LEFT);
            //tableMultiCell(w[2], h, m_data.code[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[3], h, m_data.codeDangerLVL[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[4], h, m_data.wasteNorm[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[5], h, m_data.structuralUnit[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[6], h, m_data.amountFormed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[7], h, m_data.amountReOrg[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[8], h, m_data.amountRePhys[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[9], h, m_data.amountUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[10], h, m_data.amountDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[11], h, m_data.amountSelfstorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[12], h, m_data.amountBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[13], h, m_data.amountTransferUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[14], h, m_data.amountTransferDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[15], h, m_data.amountTransferStorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[16], h, m_data.amountTransferBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[17], h, m_data.amountSelfstorageFull[row], wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
            AddPage();
        }
        else
        {
            POD10TableRow(w, str, wxPDF_BORDER_LEFT, wxPDF_ALIGN_CENTER, wxPDF_BORDER_FRAME);
            //Cell(w[0], h, wxS(""), wxPDF_BORDER_LEFT);
            //tableMultiCell(w[1], h, m_data.codeDescription[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_LEFT);
            //tableMultiCell(w[2], h, m_data.code[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[3], h, m_data.codeDangerLVL[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[4], h, m_data.wasteNorm[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[5], h, m_data.structuralUnit[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[6], h, m_data.amountFormed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[7], h, m_data.amountReOrg[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[8], h, m_data.amountRePhys[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[9], h, m_data.amountUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[10], h, m_data.amountDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[11], h, m_data.amountSelfstorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[12], h, m_data.amountBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[13], h, m_data.amountTransferUsed[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[14], h, m_data.amountTransferDefused[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[15], h, m_data.amountTransferStorage[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[16], h, m_data.amountTransferBurial[row], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
            //tableMultiCell(w[17], h, m_data.amountSelfstorageFull[row], wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
        }


      /*  Ln();*/
        


    }
    SetXY(GetX(), GetY() - h);
    Cell(w[0], h, "", wxPDF_BORDER_BOTTOM);
    Ln();
    SetAutoPageBreak(1, 5.0);
}


//returns row height


void PDF_Pod10::drawTableSignature()
{
    if (GetY() > 179) //210 - 19 - 10
    {
        AddPage();
    }
    SetXY(GetX(), GetY() + 7.5);
    double indentL{ 15.0 };
    wxFont font(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP1251);
    SetFont(font);

    // 1st row
    Cell(indentL);
    Cell(60, 3, wxS("Ответственный за ведение книги"));
    Line(GetX() + 1, GetY() + 3.5, GetX() + 57, GetY() + 3.5);
    Line(GetX() + 59, GetY() + 3.5, GetX() + 85, GetY() + 3.5);
    Line(GetX() + 87, GetY() + 3.5, GetX() + 137, GetY() + 3.5);
    font.SetPointSize(8);
    SetFont(font);
    Ln(6);
    Cell(indentL + 60.0);
    Cell(57, 1, wxS("(должность)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(26, 1, wxS("(подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(50, 1, wxS("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);
    Ln(3);
    //2nd row
    Cell(indentL);
    font.SetPointSize(12);
    SetFont(font);
    Cell(57, 3, wxS("Распорядительный документ №"));
    Line(GetX() + 3, GetY() + 3.5, GetX() + 35, GetY() + 3.5);
    Cell(42.5, 3, wxS("от"), 0, 0, wxPDF_ALIGN_RIGHT);
    Cell(1, 3, wxS("«"));
    Line(GetX() + 2.5, GetY() + 3.5, GetX() + 10, GetY() + 3.5);
    Cell(13.5, 3, wxS("»"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX() + 0.7, GetY() + 3.5, GetX() + 36.7, GetY() + 3.5);
    Cell(42, 3, wxS("г."), 0, 0, wxPDF_ALIGN_RIGHT);
    Ln(5);
    //3rd row
    Cell(indentL);
    Cell(17.5, 3, wxS("Проверил"));
    Line(GetX() + 2, GetY() + 3.5, GetX() + 74.5, GetY() + 3.5);
    Line(GetX() + 76.5, GetY() + 3.5, GetX() + 119, GetY() + 3.5);
    Cell(124, 3, wxS("«"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 5, GetY() + 3.5);
    Cell(9, 3, wxS("»"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 15, GetY() + 3.5);
    Cell(22, 3, wxS("20"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 5, GetY() + 3.5);
    Cell(5.3);
    Cell(50, 3, wxS("г."));
    Ln(5);
    font.SetPointSize(8);
    SetFont(font);
    Cell(indentL + 19.5);
    Cell(72.5, 3, wxS("(должность, подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(42.5, 3, wxS("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);

    if (m_tableLast != true)
    {
        AddPage();
    }
 
        
}

wxString PDF_Pod10::convertDateToMonthString(const wxString &date)
{
    
    wxString year = date.Mid(0, 4);
    wxString month = date.Mid(5, 2);
    wxString newDate;
    if (month == "01")
    {
        newDate = wxS("Январь " + year + "г.");
    }
    else if (month == "02")
    {
        newDate = wxS("Февраль " + year + "г.");
    }
    else if (month == "03")
    {
        newDate = wxS("Март " + year + "г.");
    }
    else if (month == "04")
    {
        newDate = wxS("Апрель " + year + "г.");
    }
    else if (month == "05")
    {
        newDate = wxS("Май " + year + "г.");
    }
    else if (month == "06")
    {
        newDate = wxS("Июнь " + year + "г.");
    }
    else if (month == "07")
    {
        newDate = wxS("Июль " + year + "г.");
    }
    else if (month == "08")
    {
        newDate = wxS("Август " + year + "г.");
    }
    else if (month == "09")
    {
        newDate = wxS("Сентябрь " + year + "г.");

    }
    else if (month == "10")
    {
        newDate = wxS("Октябрь " + year + "г.");
    }
    else if (month == "11")
    {
        newDate = wxS("Ноябрь " + year + "г.");
    }
    else if (month == "12")
    {
        newDate = wxS("Декабрь " + year + "г.");
    }
    return newDate;
}
