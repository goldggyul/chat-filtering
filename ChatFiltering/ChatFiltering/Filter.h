#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include<set>

class Filter
{
public:
	Filter(std::wstring filter) : word_(filter) {}
	static void AddLettersToIgnore(std::wstring letters_to_ignore);
	std::wstring Filtering(std::wstring input);

private:
	static const wchar_t REPLACEMENT_LETTER = '*';
	static const int FAIL = -1;

	static std::set<wchar_t>& GetLettersToIgnore()
	{
		static std::set<wchar_t>* letters_to_ignore = new std::set<wchar_t>();
		return *letters_to_ignore;
	}

	int GetLastIndexIfReplaceable(const std::wstring& input, int input_idx, int word_idx, bool isFirstCapture, wchar_t ignore_letter);
	bool IsIgnoreLetter(wchar_t letter);
	
	std::wstring word_;
};

