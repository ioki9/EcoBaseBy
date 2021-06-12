#pragma once
#include "PDF_Pod9.h"



void PDF_Pod9::Header()
{
    if (PageNo() == 1)
    {

        double indentL{ 5 };
        SetY(10);
        wxFont font(13, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString, wxFONTENCODING_CP1251);
        SetFont(font);

        Line(GetX(), GetY() + 3.5, GetX() + 205, GetY() + 3.5);
        Line(GetX() + 205, GetY() + 10.5, GetX() + 205, GetY() - 2.5);
        Line(GetX() + 205, GetY() + 3.5, GetPageWidth() - 10, GetY() + 3.5);
        Line(GetX() + 205, GetY() + 10.5, GetX() + 205, GetY() - 2.5);
        Line(GetX() + 246, GetY() + 10.5, GetX() + 246, GetY() - 2.5);
        Line(GetX(), GetY() + 10.5, GetPageWidth() - 10, GetY() + 10.5);
        Line(GetX(), GetY() + 15.5, GetPageWidth() - 10, GetY() + 15.5);
        Line(GetX(), GetY() + 20.5, GetPageWidth() - 10, GetY() + 20.5);
        Line(GetX(), GetY() + 25.5, GetPageWidth() - 10, GetY() + 25.5);
        //code description here
        Cell(205, 3, m_data.codeDescription, 0, 0, wxPDF_ALIGN_CENTER);
        //code number here
        Cell(41, 3, m_codename, 0, 0, wxPDF_ALIGN_CENTER);
        //code danger lvl here
        Cell(31, 3, m_data.codeDangerLVL, 0, 0, wxPDF_ALIGN_CENTER);
        Ln(5);
        font.SetWeight(wxFONTWEIGHT_NORMAL);
        font.SetPointSize(8);
        SetFont(font);
        Cell(205, 1, wxS("(наименование отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Cell(41, 1, wxS("(код отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Cell(31, 1, wxS("(степень опасности или"), 0, 0);
        Ln(3);
        SetX(256);
        Cell(31, 1, wxS("класс опасности отхода)"), 0, 0);
        font.SetPointSize(11);
        SetFont(font);
        Ln(8);
        Cell(GetPageWidth() - 10, 3, wxS("(норматив образования отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Ln(5.5);
        font.SetPointSize(13);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        SetFont(font);
        //WATCH HERE TOO
        Cell(GetPageWidth() - 10, 3, wxS("Деятельность по использованию отходов"), 0, 0, wxPDF_ALIGN_CENTER);
        Ln(5);
        font.SetPointSize(11);
        font.SetWeight(wxFONTWEIGHT_NORMAL);
        SetFont(font);
        Cell(GetPageWidth() - 10, 3,
            wxS("(наименование вида деятельности и (или) технологического процесса, в результате которого образуются отходы)"),
            0, 0, wxPDF_ALIGN_CENTER);
        Ln(10);
    }

}
void PDF_Pod9::Footer()
{
    SetY(-30);
    double indentL{ 15.0 };
    wxFont font(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_CP1251);
    SetFont(font);
    // 1st row
    Cell(indentL);
    Cell(60, 3, wxS("Ответственный за ведение книги"));
    Line(GetX()+1, GetY()+3.5, GetX()+57, GetY()+3.5);
    Line(GetX() + 59, GetY() + 3.5, GetX() + 85, GetY() + 3.5);
    Line(GetX() + 87, GetY() + 3.5, GetX() + 137, GetY() + 3.5);
    font.SetPointSize(8);
    SetFont(font);
    Ln(6);
    Cell(indentL+60.0);
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
    Cell(42.5, 3, wxS("от"),0,0,wxPDF_ALIGN_RIGHT);
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
    Cell(70, 3, wxString::Format(wxS("Страница %d"), PageNo()), 0, wxPDF_ALIGN_RIGHT);
    Ln(2);
    font.SetPointSize(8);
    SetFont(font);
    Cell(indentL + 19.5);
    Cell(72.5, 3, wxS("(должность, подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(42.5, 3, wxS("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);

}
void PDF_Pod9::drawTable()
{
    font.SetPointSize(11);
    SetFont(font);
    // Column parameters
    double w[11] = { 22.5,17,17,69,17,17,17,17,54,12.5,17 };
    double h{ 5.0 };
    double multiH1{ 5.0 };
    double multiH2{ 5.0 };
    //Table header
    if (PageNo() == 1)
    {
        Cell(w[0], 38, wxS("Дата"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
        Cell(w[1], 38, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
        centerRotatedText(w[1], 38, wxS("Образовалось, т."),wxS("(шт.)"));
        MultiCell(w[2] + w[3], 4.5, wxS("Поступило\n от других организаций, структурных подразделений"), wxPDF_BORDER_FRAME, wxPDF_ALIGN_MIDDLE);
        SetXY(GetX() + w[0] + w[1], GetY());
        Cell(w[2], 24.5, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
        centerRotatedText(w[2], 24.5, wxS("Количество,"), wxS("т. (шт.)"));
        Cell(w[3], 24.5, wxS(""), wxPDF_BORDER_FRAME,0, wxPDF_ALIGN_MIDDLE);
        SetXY(GetX() -w[3], GetY()+7.5);
        MultiCell(w[3], 5, wxS("Наименование организации, структурного подразделения"),0, wxPDF_ALIGN_MIDDLE);
        SetXY(GetX() + w[0] + w[1] + w[2]+w[3], GetY()-31);
        Cell(w[4], 38, wxS(""), wxPDF_BORDER_FRAME);
        centerRotatedText(w[4], 38, wxS("Поступило от"), wxS("физических лиц,"),wxS("т.(шт.)"));
        Cell(w[5], 38, wxS(""), wxPDF_BORDER_FRAME);
        centerRotatedText(w[5], 38, wxS("Использовано,"), wxS("т. (шт.)"));
        Cell(w[6], 38, wxS(""), wxPDF_BORDER_FRAME);
        centerRotatedText(w[6], 38, wxS("Обезврежено,"), wxS("т. (шт.)"));
        Cell(w[7] + w[8] + w[9], 13.5, wxS(""), wxPDF_BORDER_FRAME);
        SetXY(GetX() - w[9] - w[8] - w[7], GetY() + 3);
        MultiCell(w[7] + w[8] + w[9], 3.75, wxS("Передано на использование,\n обезвреживание, храниение, захоронение"), 0, wxPDF_ALIGN_CENTER);
        SetXY(GetX() + w[0] + w[1] + w[2] + w[3] + w[4] + w[5] + w[6], GetY()+3);
        Cell(w[7], 24.5, wxS(""), wxPDF_BORDER_FRAME);
        centerRotatedText(w[7], 24.5, wxS("Количество,"), wxS("т. (шт.)"));
        Cell(w[8], 24.5, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
        SetXY(GetX() - w[8], GetY() + 7.5);
        MultiCell(w[8], 5, wxS("Наименование организации, структурного подразделения"), 0, wxPDF_ALIGN_MIDDLE);
        SetXY(GetPageWidth()-GetRightMargin()-w[10]-w[9], GetY() - 17.5);
        Cell(w[9], 24.5, wxS("Цель"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
        SetXY(GetX(),GetY() - 13.5);
        Cell(w[10], 38, wxS(""), wxPDF_BORDER_FRAME);
        centerRotatedText(w[10], 38, wxS("Хранится,т. (шт.)"));
        Ln();
    }
    // Row numeration
    size_t i;
    for (i = 0; i < 11; i++)
    {
        wxString hRowNum = wxString::Format(wxS("%i"), i+1);
        Cell(w[i], 5, hRowNum, wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    Ln();
    
   //table
    wxDateTime myDate, myFirstDate;
    int j, lineCountM1,lineCountM2,lineCount;
    auto getAmountString{ [](double amount)->wxString { if (amount == 0) { return wxString(""); }
                                                       else {wxString string = wxNumberFormatter::ToString(amount,3,3);
                                                             string.Replace(".", ",");
                                                             if(!string.Contains(","))
                                                                string.insert(string.Len(),wxS(",0"));
                                                             return string;} } };
   for(j = 0; j < m_data.rowCount; j++)
    {
       if (j != 0)
       {
           myDate.ParseDate(m_data.date[j]);
           myFirstDate.ParseDate(m_data.date[j-1]);
       }
       //height logic(CHECK FOR INPUT INFO!!!)
       lineCountM1 = LineCount(w[3], m_data.manufacturer[j]);
       lineCountM2 = LineCount(w[8], m_data.manufacturer[j]);

       if (lineCountM1 > lineCountM2)
       {
       lineCount = lineCountM1;
       }
       else if (lineCountM1 < lineCountM2)
       {
           lineCount = lineCountM2;
       }
       else
       {
           lineCount = lineCountM1;
       }
       h = static_cast<double>(lineCount) * 5;
       //switch (lineCount)
       //{
       //case 1: h = 5.0;
       //    break;
       //case 2: h = 10.0;
       //    break;
       //case 3: h = 15.0;
       //    break;
       //case 4: h = 20.0;
       //    break;
       //case 5: h = 25.0;
       //    break;
       //}

       if (j != 0 && myDate.GetMonth()!=myFirstDate.GetMonth())
       {
           drawResultRow(w);
       }
       
       //table row
        Cell(w[0], h, m_data.date[j], wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[1], h, getAmountString( m_data.amountFormed[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[2], h, getAmountString (m_data.amountReceivedOrg[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[3], h, m_data.manufacturer[j], wxPDF_BORDER_FRAME,0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[4], h, getAmountString(m_data.amountReceivedPhys[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[5], h, getAmountString(m_data.amountUsed[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[6], h, getAmountString(m_data.amountDefused[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[7], h, getAmountString(m_data.amountTransferStorage[j]), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[8], h, m_data.manufacturer[j], wxPDF_BORDER_FRAME,0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[9], h, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
        tableMultiCell(w[10], h, getAmountString(m_data.amountTransferStorage[j]), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
    }
   drawResultRow(w);
}



//draws result row for POD9
void PDF_Pod9::drawResultRow(double w[])
{
    font.SetWeight(wxFONTWEIGHT_BOLD);
    SetFont(font);
    Cell(w[0], 5, wxS("ИТОГО"), wxPDF_BORDER_LEFT | wxPDF_BORDER_RIGHT,1, wxPDF_ALIGN_CENTER);
    font.SetWeight(wxFONTWEIGHT_NORMAL);
    SetFont(font);
    Cell(w[0], 5, wxS("за месяц"), wxPDF_BORDER_BOTTOM | wxPDF_BORDER_LEFT | wxPDF_BORDER_RIGHT,0, wxPDF_ALIGN_CENTER);
    SetXY(GetX(),GetY() - 5);
    Cell(w[1], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[2], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[3], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[4], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[5], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[6], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[7], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[8], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[9], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[10], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[11], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Ln();

}

//writes rotated text centered in a cell with parameters h,w
