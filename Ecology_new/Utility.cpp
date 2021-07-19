#pragma once
#include "Utility.h"

using namespace utility;

namespace {
	struct u_pattern
	{
		wxString str;
		wxString level;
	};

	const bool pattern_compare(const u_pattern* a, const u_pattern* b)
	{
		bool first = a->str.size() < b->str.size();
		size_t min_size = first ? a->str.size() : b->str.size();
		for (size_t i = 0; i < min_size; ++i)
		{
			if (a->str[i] < b->str[i])
				return true;
			else if (a->str[i] > b->str[i])
				return false;
		}
		return first;
	}
	struct u_pattern_list
	{
		std::vector<u_pattern*> list;

		u_pattern_list()
		{
			wxString currentLine{};
			wxString level{};
			wxTextFile pat_file;
			pat_file.Open(wxGetCwd() + patternsFileName);
			list.reserve((pat_file.GetLineCount()));

			for (size_t line{ 0 }; line < pat_file.GetLineCount(); ++line)
			{
				list.emplace_back(new u_pattern{});
				level.Empty();
				currentLine = pat_file[line];

				for (size_t ch{ 0 }; ch < currentLine.length(); ++ch)
				{

					if (currentLine[ch] > '0' && currentLine[ch] < '9')
					{
						level += currentLine[ch];
						currentLine.Remove(ch, 1);
					}
					else
					{
						level += '0';
					}

				}

				list[line]->level = level;
				list[line]->str = currentLine;
			}
			std::sort(list.begin(), list.end(), pattern_compare);
		}

		~u_pattern_list()
		{
			for (auto &i : list)
			{
				delete i;
			}
			list.clear();
		}
	};
	
	const u_pattern_list pattern_list{};

}


wxString utility::Hyphenate(const wxString &word)
{
	wxString word_string{ "." + word + "." };
	wxString word_levels{};
	
	word_levels.assign(word_string.size(), '0');

	for (size_t ch{ 0 }; ch < word_string.size() - 2; ++ch) //word
	{
		std::vector<u_pattern*>::const_iterator pattern_iter = pattern_list.list.begin();

		for (size_t count{ 1 }; count <= word_string.size() - ch; ++count) //word pattern
		{
			u_pattern word_pattern;
			word_pattern.str = word_string.substr(ch, count);
			
			if (pattern_compare(&word_pattern, *pattern_iter))
				continue;
			pattern_iter = std::lower_bound(pattern_iter, pattern_list.list.end(), &word_pattern, pattern_compare);
			if (pattern_iter == pattern_list.list.end())
				break;
			if (!pattern_compare(&word_pattern, *pattern_iter))
			{
				for (size_t level_i = 0; level_i < (*pattern_iter)->level.size(); ++level_i)
				{
					wxChar l = (*pattern_iter)->level[level_i];
					if (l > word_levels[ch + level_i])
						word_levels[ch + level_i] = l;
				}

			}
			
		}
	}

	unsigned int mask_size = word_levels.size() - 2;
	unsigned char *mask = new unsigned char[mask_size];
	for (size_t i = 0; i < mask_size; ++i)
	{
		if (word_levels[i+1].GetValue() % 2 && i && word_levels[i+1].GetValue() != '7')
			mask[i] = 1;
		else
			mask[i] = 0;
	}
	word_string.Remove(0, 1);
	word_string.RemoveLast();
	
	unsigned int offset{ 0 };
	for (size_t k{ 0 }; k < mask_size; ++k)
	{
		//try
		//{
			if (mask[k] == 1)
			{
				word_string.insert(k + offset, '\u00AD');
				++offset;
			}
		//}
		//catch (...)
		//{
		//	
		//	wxMessageBox("word: " + word_string + "\nk: " + std::to_string(k) + "\nmask: " + mask + "\noffset: " + std::to_string(offset));
		//}


	}
	delete[]mask;


	return word_string;
}


wxString utility::convertDate(const wxString& date)
{
	wxDateTime newDate;
	newDate.ParseDate(date);
	return newDate.Format(wxS("%d.%m.%Y"));
}

void utility::draw()
{

}