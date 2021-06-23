#pragma once
#include "PDF_Helper.h"
#include <wx/tokenzr.h>
#include <wx/hashmap.h>




void PDF_Helper::centerRotatedText(double w, double h, const wxString &string1, const wxString &string2, const wxString &string3)
{

    if (string2.IsEmpty())
    {
        RotatedText(GetX() - (w * 0.5) + 1, GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
    }
    else if (string3.IsEmpty())
    {
        RotatedText(GetX() - (w * 0.5), GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
        RotatedText(GetX() - (w * 0.5) + 3, GetY() + h - ((h - GetStringWidth(string2)) / 2), string2, 90);
    }
    else
    {

        RotatedText(GetX() - (w * 0.5) - 2, GetY() + h - ((h - GetStringWidth(string1)) / 2), string1, 90);
        RotatedText(GetX() - (w * 0.5) + 1, GetY() + h - ((h - GetStringWidth(string2)) / 2), string2, 90);
        RotatedText(GetX() - (w * 0.5) + 4, GetY() + h - ((h - GetStringWidth(string3)) / 2), string3, 90);
    }
}

// h - height of one line cell(reak height will be h*linecount)
void PDF_Helper::POD10TableRow(double h, const std::vector<double> &w, std::vector<wxString> &str, int align, int border)
{
    
    for (size_t k{ 1 }; k < str.size(); ++k)
    {
        str[k] = autoCellHyphenation(w[k], str[k]);

    }
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

// h - height of one line cell(reak height will be h*linecount)
double PDF_Helper::getMulticellRowHeight(double h,const std::vector<wxString>& arr, const std::vector<double>& w)
{
    int maxLineCount{ 0 };
    for (size_t k{ 0 }; k < arr.size(); ++k)
    {
        if (LineCount(w[k], arr[k]) > maxLineCount)
            maxLineCount = LineCount(w[k], arr[k]);
    }

    return static_cast<double>(maxLineCount) * h;
}

void PDF_Helper::tableRow(double h, const std::vector<double> &w, std::vector<wxString> &str,int border,int align)
{
    for (size_t k{ 0 }; k < str.size(); ++k)
    {
        str[k] = autoCellHyphenation(w[k], str[k]);

    }
    double r_h{ getMulticellRowHeight(h,str,w) };
    double currentX{ GetX() };
    double  currentY{ GetY() };
    for (size_t col{ 0 }; col < str.size(); ++col)
    {
        Cell(w[col], r_h, wxEmptyString, border, 0, align);
        SetXY(currentX, currentY + ((r_h - (LineCount(w[col], str[col]) * r_h)) / 2.0));
        MultiCell(w[col], r_h, str[col], 0, align);
        if (col == str.size()-1)
            SetXY(currentX + w[col], currentY);
        else
            SetXY(GetX(), currentY + r_h);

    }

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


wxString PDF_Helper::autoCellHyphenation(double w, const wxString &text)
{
    if (text.IsEmpty())
        return text;

    wxStringTokenizer tokens(text,' ');
    wxArrayString wordsArray{};
    double lineWidth{ 0 };
    while (tokens.HasMoreTokens())
    {
        wordsArray.Add((tokens.GetNextToken()));
    }

    for (size_t word{ 0 }; word < wordsArray.GetCount(); ++word)
    {


        lineWidth += GetStringWidth(wordsArray[word]) + GetStringWidth(' ') ;
        if (lineWidth - GetStringWidth(' ') > (w - 2.0)) // 2.0 is cell margins
        {
            while (lineWidth > (w - 2.0)) // in case of word taking 2+ lines
            {

                wxString substr{ wordsArray[word] };
                wxString hyphenatedString{};
                size_t minOffset{ 0 };


                while ((GetStringWidth(substr) + GetStringWidth('-')) > (w - (lineWidth - GetStringWidth(wordsArray[word]))))
                {
                    if (substr.size() == 1)
                        break;
                    substr.RemoveLast();
                    ++minOffset;

                }

                if ( substr.size() == 1 ) // multicell will line break for us
                {
                    lineWidth = GetStringWidth(wordsArray[word]);
                    break;
                }
                
                hyphenatedString = utility::Hyphenate(wordsArray[word]);
                size_t hyphCount{ hyphenatedString.size() - wordsArray[word].size() };

                for (size_t i{ 0 }, offset{ hyphenatedString.size() - 1}; i != minOffset + 1; ++i, --offset)
                {
                    if (hyphenatedString.at(offset) == '\u00AD')
                    {
                        ++minOffset;
                    }
                
                }

                size_t pos{ 0 };
           
                for (size_t k{ hyphenatedString.size() - minOffset - 1 }; k > 0; --k)
                {
                    if (k > hyphenatedString.size() - 3 && hyphenatedString[k] == '\u00AD')
                        continue;
                    if (hyphenatedString[k] == '\u00AD' || hyphenatedString[k] == '-')
                    {
                        pos = k;
                        break;
                    }
                    else if (k == 1)
                        pos = 0;
                
                }


                if (pos <= 1) // multicell will line break for us
                {
                    lineWidth = GetStringWidth(wordsArray[word]);
                   break;
                }
                else
                {
                    hyphenatedString.insert(pos + 1, '\n');
                    ++minOffset;
                    for (size_t ch{ 0 }; ch < pos - 1; ++ch)
                    {
                        if (hyphenatedString.size() < ch)
                            break;
                        if (hyphenatedString.at(ch) == '\u00AD')
                        {
                            hyphenatedString.erase(ch, 1);
                            --ch;
                            --pos;
                        }
                    }
                    for (size_t ch{ pos + 1 }; ch < hyphenatedString.size(); ++ch)
                    {
                        if (hyphenatedString.size() < ch)
                            break;
                        if (hyphenatedString.at(ch) == '\u00AD')
                        {
                            hyphenatedString.erase(ch, 1);;
                            --ch;
                        }
                    }
                    wordsArray[word] = hyphenatedString;
                    if (wordsArray[word].find('\n') != -1)
                        lineWidth = GetStringWidth(wordsArray[word].After('\n'));
                    else
                        lineWidth = GetStringWidth(wordsArray[word]);
                }
            }
        }
    }
    wxString hyphenatedText{};
    for (size_t i{ 0 }; i < wordsArray.size(); ++i)
    {
        hyphenatedText += wordsArray[i];
        if(i+1!=wordsArray.size())
            hyphenatedText += " ";
    }
    return hyphenatedText;
}

