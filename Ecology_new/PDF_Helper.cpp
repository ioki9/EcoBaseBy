#pragma once
#include "PDF_Helper.h"
#include <wx/tokenzr.h>
#include <wx/hashmap.h>


PDF_Helper::~PDF_Helper()
{
}

void PDF_Helper::tableRow(double h, const std::vector<double>& w, std::vector<wxString>& str, int border, int align)
{
    for (size_t k{ 0 }; k < str.size(); ++k)
    {

        str[k] = autoCellHyphenation(w[k], str[k]);

    }

    double r_h{ getMulticellRowHeight(h,str,w) };
    double currentX{ 0 };
    double  currentY{ 0 };
    for (size_t col{ 0 }; col < str.size(); ++col)
    {
        currentX = GetX();
        Cell(w[col], r_h, wxEmptyString, border, 0, align);
        currentY = GetY();
        SetXY(currentX, currentY + ((r_h - (LineCount(w[col], str[col]) * h)) / 2.0));
        MultiCell(w[col], h, str[col], 0, align);
        if (col != str.size() - 1)
            SetXY(currentX + w[col], currentY);
        else
            SetXY(GetX(), currentY + r_h);

    }

}



// h - height of one line cell(reak height will be h*linecount)
void PDF_Helper::POD10TableRow(double h, const std::vector<double> &w, std::vector<wxString> &str, int align, int border)
{
    

    str[1] = autoCellHyphenation(w[1], str[1]);
    str[5] = autoCellHyphenation(w[5], str[5]);
  
    double r_h{ getMulticellRowHeight(h,str,w) };
    double currentX{ GetX() };
    double  currentY{ GetY() };
    if ((currentY + r_h) > (GetPageHeight() - 10.0))
    {
        Line(currentX, currentY, currentX + w[0], currentY);
        AddPage();
        currentX = GetX();
        currentY = GetY();
        Line(currentX, currentY, GetX() + w[0], currentY);
        SetXY(currentX, currentY);
    }
    
        
    for (size_t col{ 0 }; col < str.size(); ++col)
    {
        currentY = GetY();
        currentX = GetX();
        if (col == 0)
            Cell(w[col], r_h, wxEmptyString, wxPDF_BORDER_LEFT, 0, align);
        else
        {
            Cell(w[col], r_h, wxEmptyString, border, 0, align);
            SetXY(currentX, currentY + ((r_h - (LineCount(w[col], str[col]) * h)) / 2.0));
            if (col == 1)
                MultiCell(w[col], h, str[col], 0, wxPDF_ALIGN_LEFT);
            else
                MultiCell(w[col], h, str[col], 0, align);
            if (col != str.size() - 1)
                SetXY(currentX + w[col], currentY);
            else
                SetXY(GetX(), currentY + r_h);
        }


    }
}



void PDF_Helper::tableHeaderCell(double w, double h, const wxString& text, int border, int ln, int align)
{
    double currentX{ GetX() };
    double  currentY{ GetY() };
    Cell(w, h, wxS(""), border, 0, align);
    SetXY(currentX, currentY + ((h - static_cast<double>((LineCount(w,text) * 4))) / 2.0));
    MultiCell(w, 4, text, 0, align);
    if (ln != 1)
        SetXY(currentX + w, currentY);
    else
        SetXY(GetX(), currentY + h);
}


void PDF_Helper::tableMultiCell(double w, double h,const wxString &text,int border,int ln, int align)
{
    double currentX{ GetX() };
    double  currentY{ GetY() };

    Cell(w, h, wxEmptyString, border, 0, align);
    SetXY(currentX, currentY + ((h - (LineCount(w, text) * h)) / 2.0));
    MultiCell(w, h, autoCellHyphenation(w,text), 0, align);
    if (ln != 1)
        SetXY(currentX + w, currentY);
    else
        SetXY(GetX(), currentY + h);
    
}


wxString PDF_Helper::autoCellHyphenation(double w, const wxString& text)
{

    if (text.IsEmpty())
        return text;


    wxStringTokenizer tokens(text,wxDEFAULT_DELIMITERS);
    wxArrayString wordsArray{};
    wxString hyphenatedString{};

    bool haveHyphens{ false };
    size_t pos{ 0 };
    double spaceWidth{ GetStringWidth(' ') };
    double hyphWidth{ GetStringWidth('-') };
    double cellWidth{ w - 2.0 };
    size_t minOffset{ 0 };
    double lineWidth{ 0 };
    while (tokens.HasMoreTokens())
    {
        wordsArray.Add((tokens.GetNextToken()));
    }

    for (size_t word{ 0 }; word < wordsArray.GetCount(); ++word)
    {
        size_t noHyphOffset{};
        lineWidth += GetStringWidth(wordsArray[word]) + spaceWidth;
        if (lineWidth - spaceWidth > cellWidth) // 2.0 is cell margins
        {
            if ((cellWidth -(lineWidth - spaceWidth - GetStringWidth(wordsArray[word]))) < (2.0 + hyphWidth))
            {
                lineWidth = GetStringWidth(wordsArray[word])+ spaceWidth;
                continue;
            }
            haveHyphens = 0; //reseting variables for next word hyphenation 
            pos = 0;
            while (lineWidth > (w - 2.0)) // in case of word taking 2+ lines
            {
                wxString c_hyphString{};
                wxString substr{};
                if (haveHyphens)
                    substr = wordsArray[word].Mid(noHyphOffset + 2);
                else
                    substr = wordsArray[word];


                minOffset = 0;
                if (!haveHyphens)
                {
                    while ((GetStringWidth(substr) + GetStringWidth('-')) > (w - (lineWidth - GetStringWidth(wordsArray[word]))))
                    {
                        if (substr.size() == 1)
                            break;
                        substr.RemoveLast();
                        ++minOffset;
                    }
                }
                else
                {
                    while ((GetStringWidth(substr) + GetStringWidth('-')) > w)
                    {
                        if (substr.size() == 1)
                            break;
                        substr.RemoveLast();
                        ++minOffset;
                    }
                }

                noHyphOffset = wordsArray[word].size() - minOffset;

                if (substr.size() == 1) // multicell will line break for us
                {
                    lineWidth = GetStringWidth(wordsArray[word]) + spaceWidth;
                    break;
                }

                if (!haveHyphens)
                {
                    c_hyphString = utility::Hyphenate(wordsArray[word]);
                    hyphenatedString = c_hyphString;
                }
                else
                    c_hyphString = hyphenatedString;

                haveHyphens = false;
                for (size_t i{ 0 }, offset{ c_hyphString.size() - 1 }; i != minOffset + 1; ++i, --offset)
                {
                    if (c_hyphString.at(offset) == '\u00AD')
                    {
                        haveHyphens = true;
                        ++minOffset;
                    }

                }

                for (size_t k{ c_hyphString.size() - minOffset - 1 }; k > 0; --k)
                {
                    if (k > c_hyphString.size() - 3 && c_hyphString[k] == '\u00AD')
                        continue;
                    if (c_hyphString[k] == '\u00AD' || c_hyphString[k] == '-')
                    {
                        pos = k;
                        break;
                    }
                    else if (k == 1)
                        pos = 0;
                    --noHyphOffset;
                }

                if (pos <= 1) // multicell will line break for us
                {
                    lineWidth = GetStringWidth(wordsArray[word]) + spaceWidth;
                    break;
                }
                else
                {
                    c_hyphString.insert(pos + 1, '\n');
                    ++minOffset;
                    size_t posNoHyph{ removeUnwantedHyphens(c_hyphString, pos) };
                    if (posNoHyph != 0)
                    {
                        wordsArray[word].insert(posNoHyph, '\n');

                        if(wordsArray[word][posNoHyph-1] != '-')
                            wordsArray[word].insert(posNoHyph, '\u00AD');
                    }

                }

                lineWidth = GetStringWidth(wordsArray[word].AfterLast('\n')) + spaceWidth;

                if (!haveHyphens)
                    break;
            }
        }
    }
    wxString hyphenatedText{};
    for (size_t i{ 0 }; i < wordsArray.size(); ++i)
    {
        hyphenatedText += wordsArray[i];
        if (i + 1 != wordsArray.size())
            hyphenatedText += " ";
    }
    return hyphenatedText;

}

size_t PDF_Helper::removeUnwantedHyphens(wxString& word, unsigned int pos)
{

    size_t wordSize{ word.size() };

    for (size_t ch{ 1 }; ch < wordSize; ++ch)
    {
        if (word[ch] == '\u00AD')
        {
        word.erase(ch, 1);;
        --ch;
        --wordSize;
        }
    }

    for (size_t ch{ 1 }; ch < wordSize; ++ch)
    {

        if (word[ch] == '\n' )
        {
            return ch;
        }
            
    }
    return 0;
}

void PDF_Helper::centerRotatedText(double w, double h, const wxString& string1, const wxString& string2, const wxString& string3)
{

    if (string2.IsEmpty())
    {
        RotatedText(GetX() - (w * 0.5) + 1, GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
    }
    else if (string3.IsEmpty())
    {
        RotatedText(GetX() - (w * 0.5), GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
        RotatedText(GetX() - (w * 0.5) + 4, GetY() + h - ((h - GetStringWidth(string2)) / 2), string2, 90);
    }
    else
    {

        RotatedText(GetX() - (w * 0.5) - 2, GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
        RotatedText(GetX() - (w * 0.5) + 2, GetY() + h - ((h - GetStringWidth(string2)) / 2), string2, 90);
        RotatedText(GetX() - (w * 0.5) + 5.5, GetY() + h - ((h - GetStringWidth(string3)) / 2), string3, 90);
    }
}


// h - height of one line cell(reak height will be h*linecount)
double PDF_Helper::getMulticellRowHeight(double h, const std::vector<wxString>& arr, const std::vector<double>& w)
{
    int maxLineCount{ 0 };
    for (size_t k{ 0 }; k < arr.size(); ++k)
    {
        if (LineCount(w[k], arr[k]) > maxLineCount)
            maxLineCount = LineCount(w[k], arr[k]);
    }

    return static_cast<double>(maxLineCount) * h;
}

wxString PDF_Helper::getAmountString(double amount)
{
    if (amount == 0) 
        return wxString("");
    else
    {
        wxString string = wxNumberFormatter::ToString(amount, 3, 3);
        string.Replace(".", ",");
        if (!string.Contains(","))
            string.insert(string.Len(), wxS(",0"));
        return string;
    }
}

wxString PDF_Helper::getAmountString(wxString& amount)
{
    if (amount == "" || amount[0] == '0')
        return "";
    else
    {
        amount.Replace(".", ",");
        if (!amount.Contains(","))
            amount.insert(amount.Len(), wxS(",0"));
        return amount;
    }
}


int PDF_Helper::compareDates(const wxString& startDate, const wxString& endDate)
{
    wxDateTime sDate{};
    wxDateTime eDate{};
    sDate.ParseFormat(startDate, wxS("%d.%m.%Y"));
    eDate.ParseFormat(endDate, wxS("%d.%m.%Y"));
    wxDateSpan dsDate{ wxAtoi(sDate.Format(wxS("%Y"))), wxAtoi(sDate.Format(wxS("%m"))) };
    wxDateSpan deDate{ wxAtoi(eDate.Format(wxS("%Y"))), wxAtoi(eDate.Format(wxS("%m"))) };
    wxDateSpan dfDate = deDate - dsDate;
    return dfDate.GetTotalMonths();       
}