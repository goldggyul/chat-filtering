#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Filter
{
public:
	Filter(std::wstring filter) : word_(filter) {}
	static void SetLettersToIgnore(std::wstring letters_to_ignore)
	{
		letters_to_ignore_.append(letters_to_ignore);
	}
	std::wstring Filtering(std::wstring input);

private:
	static const wchar_t REPLACEMENT_LETTER = '*';
	static std::wstring letters_to_ignore_;

	std::wstring GetExpressionForRegex();
	std::wstring GetExpressionOfLettersToIgnore();

	bool CanReplace(const std::wsmatch& m);
	bool IsEveryLetterSame(const std::wstring& match_result);

	std::wstring word_;
};

