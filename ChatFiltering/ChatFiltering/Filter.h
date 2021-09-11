#pragma once
#include <iostream>
#include <string>
#include <set>

class Filter
{
public:
	Filter(std::wstring text) : text_(text) {}

	static void AddLettersToIgnore(std::wstring ignorable_letters)
	{
		std::set<wchar_t>& ignorable_letters_ = Filter::GetIgnorableLetters();
		for (wchar_t letter : ignorable_letters)
			ignorable_letters_.insert(letter);
	}

	std::wstring Filtering(const std::wstring& msg);

private:
	static std::set<wchar_t>& GetIgnorableLetters()
	{
		static std::set<wchar_t>* ignorable_letters = new std::set<wchar_t>();
		return *ignorable_letters;
	}
	static const wchar_t REPLACEMENT_LETTER = '*';
	static const int FAIL = -1;

	int GetLastIndexToFilter(const std::wstring& msg, int msg_idx, int word_idx, wchar_t ignorable_letter);
	bool IsIgnorableLetter(wchar_t letter);
	std::wstring text_;
};

