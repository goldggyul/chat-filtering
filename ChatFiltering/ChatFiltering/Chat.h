#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Chat
{
private:
	static const int MIN_KOREAN = 0;
	static const int MAX_KOREAN = 127;
	static const wchar_t REPLACEMENT_LETTER = '*';

	std::vector<std::wstring> filters_;
	std::wstring letters_to_ignore_;

public:
	Chat()
	{
		letters_to_ignore_ = L"";
		// #1
		AddFilter(L"°­¾ÆÁö");
	}

	void AddFilter(std::wstring filter)
	{
		filters_.push_back(filter);
	}

	void AddLettersToIgnore(std::wstring letters_to_ignore)
	{
		letters_to_ignore_.append(letters_to_ignore);
	}

	void Play();
	std::wstring Filtering(const std::wstring& original_input);
	std::wstring FilteringUsingOneFilter(const std::wstring& input, const std::wstring& filter);
	std::wstring GetReplacementWord(const std::wstring& filter);
	std::wstring GetExpressionForRegex(const std::wstring& filter);
	std::wstring GetExpressionOfLettersToIgnore();
	bool CanReplace(const std::wsmatch& m);
	bool IsEveryLetterSame(const std::wstring& match_result);
};