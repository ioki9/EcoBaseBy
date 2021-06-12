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

void PDF_Helper::POD10TableRow(const std::vector<double> &w, std::vector<wxString> &str,int frowBorder, int align, int border)
{
    int maxLineCount{ 0 };
    for (size_t k{ 0 }; k < str.size(); ++k)
    {
        str[k] = autoCellHyphenation(w[k], str[k]);
        if (LineCount(w[k], str[k]) > maxLineCount)
            maxLineCount = LineCount(w[k], str[k]);
    }
    double h{ static_cast<double>(maxLineCount) * 4.5 };
    double currentX{};
    double  currentY{};
    for (size_t col{ 0 }; col < str.size(); ++col)
    {
        currentY = GetY();
        currentX = GetX();
        if (col == 0)
            Cell(w[col], h, wxEmptyString, frowBorder, 0, align);
        else
            Cell(w[col], h, wxEmptyString, border, 0, align);

        SetXY(currentX, currentY + ((h - (LineCount(w[col], str[col]) * h)) / 2.0));
        MultiCell(w[col], h, str[col], 0, align);
        if (col == str.size() - 1)
            SetXY(currentX + w[col], currentY);
        else
            SetXY(GetX(), currentY + h);

    }
}


void PDF_Helper::tableRow(const std::vector<double> &w, std::vector<wxString> &str,int border,int align)
{
    int maxLineCount{ 0 };
    for (size_t k{ 0 }; k < str.size(); ++k)
    {
        str[k] = autoCellHyphenation(w[k], str[k]);
        if (LineCount(w[k], str[k]) > maxLineCount)
            maxLineCount = LineCount(w[k], str[k]);
    }
    double h{ static_cast<double>(maxLineCount) * 4.5 };
    double currentX{ GetX() };
    double  currentY{ GetY() };
    for (size_t col{ 0 }; col < str.size(); ++col)
    {
        Cell(w[col], h, wxEmptyString, border, 0, align);
        SetXY(currentX, currentY + ((h - (LineCount(w[col], str[col]) * h)) / 2.0));
        MultiCell(w[col], h, str[col], 0, align);
        if (col == str.size()-1)
            SetXY(currentX + w[col], currentY);
        else
            SetXY(GetX(), currentY + h);

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

    wxStringTokenizer tokens(text);

    wxArrayString wordsArray{};
    double lineWidth{};
    while (tokens.HasMoreTokens())
    {
        wordsArray.Add((tokens.GetNextToken()));
    }

    for (size_t word{ 0 }; word < wordsArray.GetCount(); ++word)
    {
        lineWidth += GetStringWidth(wordsArray[word]) + 1.1;
        if (lineWidth > w)
        {
            
            wxString substr{ wordsArray[word] };
            wxString hyphenatedString{};
            size_t minOffset{};


            while ((static_cast<double>(GetStringWidth(substr)) + 3.0) > (w - (lineWidth - GetStringWidth(wordsArray[word]))))
            {
                substr.RemoveLast();
                ++minOffset;

                if (substr.size() == 1)
                    break;
            }
            if ( substr.size() == 1 )
            {
                wordsArray[word].insert(0, '\n');
                lineWidth = GetStringWidth(wordsArray[word]);
                continue;
            }
            hyphenatedString = utility::Hyphenate(wordsArray[word]);
            auto found{ std::find(hyphenatedString.begin() + wordsArray[word].size() - minOffset,hyphenatedString.end(), '\u00AD') };
            if (found == hyphenatedString.end())
            {
                hyphenatedString.insert(0, '\n');
                lineWidth = GetStringWidth(wordsArray[word]);
                continue;
            }
            else
            {
                size_t pos{ hyphenatedString.IterToImplPos(found) };
                hyphenatedString.insert(pos+1, '\n');
                ++minOffset;
                
                for (size_t ch{ 0 }; ch < pos-1; ++ch)
                {
                    if (hyphenatedString.size() < ch)
                        break;
                    if (hyphenatedString.at(ch) == '\u00AD')
                    {
                        hyphenatedString.erase(ch,1);
                        --ch;
                        --pos;
                    }
                }
                for (size_t ch{ pos+1 }; ch < hyphenatedString.size(); ++ch)
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
                lineWidth = GetStringWidth(wordsArray[word].After('\n'));
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

