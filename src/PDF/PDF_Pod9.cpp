#include "PDF_Pod9.h"



void PDF_Pod9::Header()
{
    if (PageNo() == 1)
    {

        double indentL{ 5 };
        SetY(10);
        wxFont font(wxFontInfo(13).FaceName("Times New Roman").Bold().Encoding(wxFONTENCODING_CP1251));
        SetFont(font);

        Line(GetX(), GetY() + 3.5, GetX() + 205, GetY() + 3.5);
        Line(GetX() + 205, GetY() + 10.5, GetX() + 205, GetY() - 2.5);
        Line(GetX() + 205, GetY() + 3.5, GetPageWidth() - 10, GetY() + 3.5);
        Line(GetX() + 205, GetY() + 10.5, GetX() + 205, GetY() - 2.5);
        Line(GetX() + 246, GetY() + 10.5, GetX() + 246, GetY() - 2.5);
        Line(GetX(), GetY() + 10.5, GetPageWidth() - 10, GetY() + 10.5);
        Line(GetX(), GetY() + 15.5, GetPageWidth() - 10, GetY() + 15.5);
        Line(GetX(), GetY() + 20.5, GetPageWidth() - 10, GetY() + 20.5);
        //Line(GetX(), GetY() + 25.5, GetPageWidth() - 10, GetY() + 25.5);
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
        Cell(205, 1, wxString::FromUTF8("(наименование отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Cell(41, 1, wxString::FromUTF8("(код отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Cell(31, 1, wxString::FromUTF8("(степень опасности или"), 0, 0);
        Ln(3);
        SetX(256);
        Cell(31, 1, wxString::FromUTF8("класс опасности отхода)"), 0, 1);
        font.SetPointSize(12);
        font.MakeBold();
        SetFont(font);
        Cell(GetPageWidth() - 10, 8, m_data.wasteNorm, 0, 1, wxPDF_ALIGN_CENTER);
        font.SetPointSize(11);
        SetFont(font);
        Cell(GetPageWidth() - 10, 3, wxString::FromUTF8("(норматив образования отхода)"), 0, 0, wxPDF_ALIGN_CENTER);
        Ln(5.5);
        font.SetPointSize(13);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        SetFont(font);
        //WATCH HERE TOO
        MultiCell(GetPageWidth() - 10, 5, m_data.codeDescription, wxPDF_BORDER_BOTTOM, wxPDF_ALIGN_MIDDLE);
        Ln(2);
        font.SetPointSize(11);
        font.SetWeight(wxFONTWEIGHT_NORMAL);
        SetFont(font);
        Cell(GetPageWidth() - 10, 3,
            wxString::FromUTF8("(наименование вида деятельности и (или) технологического процесса, в результате которого образуются отходы)"),
            0, 0, wxPDF_ALIGN_CENTER);
        Ln(10);
    }

}
void PDF_Pod9::drawTableHeader(const std::vector<double>& w)
{
    Cell(w[0], 38, wxString::FromUTF8("Дата"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    Cell(w[1], 38, wxString::FromUTF8(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    centerRotatedText(w[1], 38, wxString::FromUTF8("Образовалось, т."), wxString::FromUTF8("(шт.)"));
    MultiCell(w[2] + w[3], 4.5, wxString::FromUTF8("Поступило\n от других организаций, структурных подразделений"), wxPDF_BORDER_FRAME, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[0] + w[1], GetY());
    Cell(w[2], 24.5, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    centerRotatedText(w[2], 24.5, wxString::FromUTF8("Количество,"), wxString::FromUTF8("т. (шт.)"));
    Cell(w[3], 24.5, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() - w[3], GetY() + 7.5);
    MultiCell(w[3], 5, wxString::FromUTF8("Наименование организации, структурного подразделения"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[0] + w[1] + w[2] + w[3], GetY() - 31);
    Cell(w[4], 38, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[4], 38, wxString::FromUTF8("Поступило от"), wxString::FromUTF8("физических лиц,"), wxString::FromUTF8("т.(шт.)"));
    Cell(w[5], 38, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[5], 38, wxString::FromUTF8("Использовано,"), wxString::FromUTF8("т. (шт.)"));
    Cell(w[6], 38, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[6], 38, wxString::FromUTF8("Обезврежено,"), wxString::FromUTF8("т. (шт.)"));
    Cell(w[7] + w[8] + w[9], 13.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[9] - w[8] - w[7], GetY() + 3);
    MultiCell(w[7] + w[8] + w[9], 3.75, wxString::FromUTF8("Передано на использование,\n обезвреживание, храниение, захоронение"), 0, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[0] + w[1] + w[2] + w[3] + w[4] + w[5] + w[6], GetY() + 3);
    Cell(w[7], 24.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[7], 24.5, wxString::FromUTF8("Количество,"), wxString::FromUTF8("т. (шт.)"));
    Cell(w[8], 24.5, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() - w[8], GetY() + 7.5);
    MultiCell(w[8], 5, wxString::FromUTF8("Наименование организации, структурного подразделения"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetPageWidth() - GetRightMargin() - w[10] - w[9], GetY() - 17.5);
    Cell(w[9], 24.5, wxString::FromUTF8("Цель"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX(), GetY() - 13.5);
    Cell(w[10], 38, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[10], 38, wxString::FromUTF8("Хранится,т. (шт.)"));
    Ln();
}
void PDF_Pod9::Footer()
{
    SetY(-30);
    double indentL{ 15.0 };
    SetFont(font);
    // 1st row
    Cell(indentL);
    Cell(60, 3, wxString::FromUTF8("Ответственный за ведение книги"));
    Line(GetX()+1, GetY()+3.5, GetX()+57, GetY()+3.5);
    Line(GetX() + 59, GetY() + 3.5, GetX() + 85, GetY() + 3.5);
    Line(GetX() + 87, GetY() + 3.5, GetX() + 137, GetY() + 3.5);
    font.SetPointSize(8);
    SetFont(font);
    Ln(6);
    Cell(indentL+60.0);
    Cell(57, 1, wxString::FromUTF8("(должность)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(26, 1, wxString::FromUTF8("(подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(50, 1,  wxString::FromUTF8("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);
    Ln(3);
    //2nd row
    Cell(indentL);
    font.SetPointSize(12);
    SetFont(font);
    Cell(57, 3, wxString::FromUTF8("Распорядительный документ №"));
    Line(GetX() + 3, GetY() + 3.5, GetX() + 35, GetY() + 3.5);
    Cell(42.5, 3, wxString::FromUTF8("от"),0,0,wxPDF_ALIGN_RIGHT);
    Cell(1, 3, wxString::FromUTF8("«"));
    Line(GetX() + 2.5, GetY() + 3.5, GetX() + 10, GetY() + 3.5);
    Cell(13.5, 3, wxString::FromUTF8("»"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX() + 0.7, GetY() + 3.5, GetX() + 36.7, GetY() + 3.5);
    Cell(42, 3, wxString::FromUTF8("г."), 0, 0, wxPDF_ALIGN_RIGHT);
    Ln(5);
    //3rd row
    Cell(indentL);
    Cell(17.5, 3, wxString::FromUTF8("Проверил"));
    Line(GetX() + 2, GetY() + 3.5, GetX() + 74.5, GetY() + 3.5);
    Line(GetX() + 76.5, GetY() + 3.5, GetX() + 119, GetY() + 3.5);
    Cell(124, 3, wxString::FromUTF8("«"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 5, GetY() + 3.5);
    Cell(9, 3, wxString::FromUTF8("»"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 15, GetY() + 3.5);
    Cell(22, 3, wxString::FromUTF8("20"), 0, 0, wxPDF_ALIGN_RIGHT);
    Line(GetX(), GetY() + 3.5, GetX() + 5, GetY() + 3.5);
    Cell(5.3);
    Cell(50, 3, wxString::FromUTF8("г."));
    Cell(70, 3, wxString::Format(wxString::FromUTF8("Страница %d"), PageNo()), 0, wxPDF_ALIGN_RIGHT);
    Ln(2);
    font.SetPointSize(8);
    SetFont(font);
    Cell(indentL + 19.5);
    Cell(72.5, 3, wxString::FromUTF8("(должность, подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(42.5, 3, wxString::FromUTF8("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);

}
void PDF_Pod9::drawTable()
{
    font.SetPointSize(11);
    SetFont(font);
    // Column parameters
    const std::vector<double> w = { 22.5,17,17,69,17,17,17,17,54,12.5,17 };
    std::array<double, 7> results{0, 0, 0, 0, 0, 0, 0};
    if(m_data.codeDangerLVL.empty())
        m_precision = 3;
    else if (m_data.codeDangerLVL[0] == '4' || m_data.codeDangerLVL[0] == wxString::FromUTF8("н"))
        m_precision = 2;
    else
        m_precision = 3;
    double h{ 5.0 };

    //Table header
    if (PageNo() == 1)
        drawTableHeader(w);
    
    //Row numeration
    int i;
    for (i = 0; i < 11; i++)
    {
        wxString hRowNum = wxString::Format(wxS("%i"), i+1);
        Cell(w[i], 5, hRowNum, wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    Ln();
    
   //table
    wxString prevDate{ m_data.date[0] };
    wxString purpose{};
    wxString fullStrgColValue{ "" };
    int j;
    std::vector<wxString> rowData{};
    double transferValue{0.0};

    for (j = 0; j < m_data.rowCount; j++)
    {
        //we check if row is initial, if it is we skip all the unnecessary steps and more importantly avoid reassignment
        if (m_data.regnum[j] == "initial")
        {
            rowData = { m_data.date[j], "", "","", "", "", "","", "","",getAmountString(m_data.amountFullStorage[j], m_precision) };
            //we reassign date here for correct prevDate check on next row
            if(m_data.rowCount > 1)
                m_data.date[j] = m_data.date[j + 1];
            goto drawRow;
        }

        if (j != 0)
        {
            prevDate = m_data.date[j-1];
        }

        if (m_data.amountTransferUsed[j] != 0)
        {
            transferValue = m_data.amountTransferUsed[j];
            purpose = wxString::FromUTF8("И");
        }
        else if (m_data.amountTransferDefused[j] != 0)
        {
            transferValue = m_data.amountTransferDefused[j];
            purpose = wxString::FromUTF8("О");
        }
        else if (m_data.amountTransferBurial[j] != 0)
        {
            transferValue = m_data.amountTransferBurial[j];
            purpose = wxString::FromUTF8("З");
        }
        else if(m_data.amountTransferStorage[j] != 0)
        {
            transferValue = m_data.amountTransferStorage[j];
            purpose = wxString::FromUTF8("Х");
        }
        else if (m_data.amountSelfstorage[j] != 0)
        {
            transferValue = m_data.amountSelfstorage[j];
            purpose = wxString::FromUTF8("Х");
        }
        else if (m_data.amountBurial[j] != 0)
        {
            transferValue = m_data.amountBurial[j];
            purpose = wxString::FromUTF8("З");
        }
        else
        {
            transferValue = 0.0;
            purpose = "";
        }
        
        rowData = { m_data.date[j], getAmountString(m_data.amountFormed[j],m_precision), getAmountString(m_data.amountReceivedOrg[j],m_precision),
                   m_data.owner[j], getAmountString(m_data.amountReceivedPhys[j],m_precision), getAmountString(m_data.amountUsed[j],m_precision),
                    getAmountString(m_data.amountDefused[j],m_precision), getAmountString(transferValue,m_precision),m_data.stuct_unit9[j],
                       purpose,"" };

       if (j != 0 && compareDates(prevDate,m_data.date[j]) != 0)
       {

           results[6] = m_data.amountFullStorage[j-1];
           drawResultRow(w, results);
           std::fill(results.begin(), results.end(), 0);
       }
       //table row
       drawRow:
       tableRow(h, w, rowData, wxPDF_BORDER_FRAME, wxPDF_ALIGN_CENTER);

       results[0] += m_data.amountFormed[j];
       results[1] += m_data.amountReceivedOrg[j];
       results[2] += m_data.amountReceivedPhys[j];
       results[3] += m_data.amountUsed[j];
       results[4] += m_data.amountDefused[j];
       results[5] += transferValue;
      
    }
   results[6] = m_data.amountFullStorage[j-1];
   drawResultRow(w, results);
   std::fill(results.begin(), results.end(), 0);
}

//draws result row for POD9
void PDF_Pod9::drawResultRow(const std::vector<double>& w, const std::array<double,7>& value)
{
    font.SetWeight(wxFONTWEIGHT_BOLD);
    SetFont(font); 
    Cell(w[0], 10, wxEmptyString, wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[0], GetY());
    Cell(w[0], 5, wxString::FromUTF8("ИТОГО"), 0, 1, wxPDF_ALIGN_CENTER);
    font.SetWeight(wxFONTWEIGHT_NORMAL);
    SetFont(font);
    Cell(w[0], 5, wxString::FromUTF8("за месяц"), 0,0, wxPDF_ALIGN_CENTER);
    SetXY(GetX(),GetY() - 5);
    Cell(w[1], 10, getAmountString(value[0], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[2], 10, getAmountString(value[1], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[3], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[4], 10, getAmountString(value[2], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[5], 10, getAmountString(value[3], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[6], 10, getAmountString(value[4], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[7], 10, getAmountString(value[5], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[8], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Cell(w[9], 10, wxS(""), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    if (value[6] == 0)
    {
        wxString val{ "0," };
        for (int j{ 0 }; j < m_precision; ++j)
            val += '0';
        Cell(w[10], 10, val, wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    else
        Cell(w[10], 10, getAmountString(value[6], m_precision), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    Ln();

}

