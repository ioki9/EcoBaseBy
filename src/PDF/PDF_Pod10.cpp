#include "PDF_Pod10.h"
#include "../Settings.h"
#include <wx/pdffontmanager.h>

void PDF_Pod10::createDoc(const wxString &startDate, const wxString& endDate, const wxString& orgName)
{
    
    if (!wxDirExists(Settings::GetPdfSavePath() + "/" + wxString::FromUTF8(orgName)))
        wxFileName::Mkdir(Settings::GetPdfSavePath() + "/" + orgName, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    m_dataBase = new DBMain();
    m_dataBase->getPod10TableCount(m_data, startDate, endDate);
    int tableCount{ m_data.tableCount };
    int nextTable{ 0 };
    AddPage();
    for (int t = 0; t < tableCount; t++)
    {
            nextTable++;

            m_dataBase->getPod10TableInfo(m_data, m_data.allDates[t]);
            m_dataBase->getPod10TableCodeDngr(m_data, m_data.code);
         
            if (nextTable == tableCount)
                m_tableLast = true;
            else
                m_tableLast = false;
        
            drawTable();
    }

    SaveAsFile(Settings::GetPdfSavePath() + "/" + orgName + wxString::FromUTF8("/ПОД10.pdf"));
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
    const std::vector<double> w{ 17,32.5,15,14,12,27,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5,13.5};
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
    MultiCell(w[0], 4, wxString::FromUTF8("Дата внесения учетной записи в книгу обшего\n учета\n отходов"), 0, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[0], GetY() - 34.25);
    Cell(w[1], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[1], GetY() + 14.25);
    MultiCell(w[1], 4, wxString::FromUTF8("Наименование отхода"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[1] + w[0], GetY() - 22.25);
    Cell(w[2], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[2], GetY() + 14.25);
    MultiCell(w[2], 4, wxString::FromUTF8("Код отхода"), 0, wxPDF_ALIGN_MIDDLE);
    SetXY(GetX() + w[1] + w[0] + w[2], GetY() - 22.25);
    Cell(w[3], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[3], 36.5, wxString::FromUTF8("Степень опасности"), wxS("или класс"));
    Cell(w[4], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[4], 36.5, wxString::FromUTF8("Норматив"), wxString::FromUTF8("образования отходов"));
    Cell(w[5], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    SetXY(GetX() - w[5], GetY() + 6.25);
    MultiCell(w[5], 4, wxString::FromUTF8("Структурные подразделения, в которых образовался данный вид отхода"), 0, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[0] + w[1] + w[2] + w[3] + w[4] + w[5], GetY() - 30.25);
    Cell(w[6], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[6], 36.5, wxString::FromUTF8("Образовалось, т. (шт.)"));
    Cell(w[7], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[7], 36.5, wxString::FromUTF8("Поступило от других"), wxString::FromUTF8("организаций, т. (шт.)"));
    Cell(w[8], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[8], 36.5, wxString::FromUTF8("Поступило отх"), wxString::FromUTF8("физических лиц, т."), wxString::FromUTF8("(шт.)"));
    Cell(w[9], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[9], 36.5, wxString::FromUTF8("Использовано, т. (шт.)"));
    Cell(w[10], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[10], 36.5, wxString::FromUTF8("Обезврежено, т. (шт.)"));
    Cell(w[11], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[11], 36.5, wxString::FromUTF8("Направлено на"), wxString::FromUTF8("хранение, т. (шт.)"));
    Cell(w[12], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[12], 36.5, wxString::FromUTF8("Захоронено, т. (шт.)"));
    Cell(w[13] + w[14] + w[15] + w[16], 6, wxString::FromUTF8("Передано, т. (шт.)"), wxPDF_BORDER_FRAME, 1, wxPDF_ALIGN_CENTER);
    SetXY(GetX() + w[12] + w[11] + w[10] + w[9] + w[8] + w[7] + w[6] + w[5] + w[4] + w[3] + w[2] + w[1] + w[0], GetY());
    Cell(w[13], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[13], 30.5, wxString::FromUTF8("на"), wxString::FromUTF8("использование"));
    Cell(w[14], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[14], 30.5, wxString::FromUTF8("на"), wxString::FromUTF8("обезвреживание"));
    Cell(w[15], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[15], 30.5, wxString::FromUTF8("на хранение"));
    Cell(w[16], 30.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[16], 30.5, wxString::FromUTF8(" на захоронение"));
    SetXY(GetX(), GetY() - 6);
    Cell(w[17], 36.5, wxS(""), wxPDF_BORDER_FRAME);
    centerRotatedText(w[17], 36.5, wxString::FromUTF8("Хранится, т. (шт.)"));
    Ln();
    int i;
    for (i = 0; i < 18; i++)
    {
        Cell(w[i], 5, wxString::Format(wxS("%i"), i + 1), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);
    }
    Ln();
}


void PDF_Pod10::drawMulticellRows(const std::vector<double> &w)
{
    
    double h{4.5};
    double currentY{};
    double currentX{};
    std::vector<wxString> rowData{};
    rowData.reserve(18);

    SetAutoPageBreak(0);
    int page{ PageNo() };
    double startRowY{GetY()};
    for (int row{ 0 }, nextRow{ 1 }; row < m_data.rowCount; ++row,++nextRow)
    {
        if (page != PageNo())
        {
            page = PageNo();
            startRowY = GetTopMargin();
        }
        if (m_data.codeDangerLVL[row].empty())
            m_precision = 3;
        else if (m_data.codeDangerLVL[row][0] == '4' || m_data.codeDangerLVL[row][0] == wxString::FromUTF8("н"))
            m_precision = 2;
        else
            m_precision = 3;
    
        rowData.clear();
        rowData = {m_data.entryDate, m_data.codeDescription[row], m_data.code[row], m_data.codeDangerLVL[row],
            getAmountString(m_data.wasteNorm[row], m_precision), m_data.structuralUnit[row],  getAmountString(m_data.amountFormed[row], m_precision),
             getAmountString(m_data.amountReOrg[row], m_precision) , getAmountString(m_data.amountRePhys[row], m_precision), getAmountString(m_data.amountUsed[row], m_precision),
            getAmountString(m_data.amountDefused[row], m_precision),  getAmountString(m_data.amountSelfstorage[row], m_precision) , getAmountString(m_data.amountBurial[row], m_precision),
            getAmountString(m_data.amountTransferUsed[row], m_precision), getAmountString(m_data.amountTransferDefused[row], m_precision),
            getAmountString(m_data.amountTransferStorage[row], m_precision), getAmountString(m_data.amountTransferBurial[row], m_precision),
             getAmountString(m_data.amountSelfstorageFull[row], m_precision) };
        
        
     
        POD10TableRow(h, w, rowData, wxPDF_ALIGN_CENTER, wxPDF_BORDER_FRAME,startRowY);
      
    
    }
    if (page != PageNo())
        startRowY = GetTopMargin();
    SetXY(GetX(), GetY() - h);
    Cell(w[0], h, "", wxPDF_BORDER_BOTTOM,1);
    double meY{ GetY() };
    double meX{ GetX() };
    SetXY(GetX(), startRowY);
    Cell(w[0], meY - startRowY, m_data.entryDate, wxPDF_BORDER_NONE, 0, wxPDF_ALIGN_MIDDLE);
    SetXY(meX, meY);
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
    wxFont font(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Times New Roman", wxFONTENCODING_CP1251);
    SetFont(font);
   
    // 1st row
    Cell(indentL);
    Cell(60, 3, wxString::FromUTF8("Ответственный за ведение книги"));
    Line(GetX() + 1, GetY() + 3.5, GetX() + 57, GetY() + 3.5);
    Line(GetX() + 59, GetY() + 3.5, GetX() + 85, GetY() + 3.5);
    Line(GetX() + 87, GetY() + 3.5, GetX() + 137, GetY() + 3.5);
    font.SetPointSize(8);
    SetFont(font);
    Ln(6);
    Cell(indentL + 60.0);
    Cell(57, 1, wxString::FromUTF8("(должность)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(26, 1, wxString::FromUTF8("(подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(50, 1, wxString::FromUTF8("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);
    Ln(3);
    //2nd row
    Cell(indentL);
    font.SetPointSize(12);
    SetFont(font);
    Cell(57, 3, wxString::FromUTF8("Распорядительный документ №"));
    Line(GetX() + 3, GetY() + 3.5, GetX() + 35, GetY() + 3.5);
    Cell(42.5, 3, wxString::FromUTF8("от"), 0, 0, wxPDF_ALIGN_RIGHT);
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
    Ln(5);
    font.SetPointSize(8);
    SetFont(font);
    Cell(indentL + 19.5);
    Cell(72.5, 3, wxString::FromUTF8("(должность, подпись)"), 0, 0, wxPDF_ALIGN_CENTER);
    Cell(2);
    Cell(42.5, 3, wxString::FromUTF8("(инициалы, фамилия)"), 0, 0, wxPDF_ALIGN_CENTER);

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
        newDate = wxString::FromUTF8("Январь " + year + "г.");
    }
    else if (month == "02")
    {
        newDate = wxString::FromUTF8("Февраль " + year + "г.");
    }
    else if (month == "03")
    {
        newDate = wxString::FromUTF8("Март " + year + "г.");
    }
    else if (month == "04")
    {
        newDate = wxString::FromUTF8("Апрель " + year + "г.");
    }
    else if (month == "05")
    {
        newDate = wxString::FromUTF8("Май " + year + "г.");
    }
    else if (month == "06")
    {
        newDate = wxString::FromUTF8("Июнь " + year + "г.");
    }
    else if (month == "07")
    {
        newDate = wxString::FromUTF8("Июль " + year + "г.");
    }
    else if (month == "08")
    {
        newDate = wxString::FromUTF8("Август " + year + "г.");
    }
    else if (month == "09")
    {
        newDate = wxString::FromUTF8("Сентябрь " + year + "г.");

    }
    else if (month == "10")
    {
        newDate = wxString::FromUTF8("Октябрь " + year + "г.");
    }
    else if (month == "11")
    {
        newDate = wxString::FromUTF8("Ноябрь " + year + "г.");
    }
    else if (month == "12")
    {
        newDate = wxString::FromUTF8("Декабрь " + year + "г.");
    }
    return newDate;
}
