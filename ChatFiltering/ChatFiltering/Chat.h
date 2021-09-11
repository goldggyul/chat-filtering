#pragma once
#include "Filter.h"

class Chat
{
public:
	Chat()
	{
		// #1
		AddFilter(L"강아지");
	}

	void AddFilter(std::wstring word)
	{
		filters_.push_back(Filter(word));
	}

	void AddLettersToIgnore(std::wstring letters_to_ignore)
	{
		Filter::AddLettersToIgnore(letters_to_ignore);
	}

	std::wstring Filtering(const std::wstring& original_input);

private:
	std::vector<Filter> filters_;
};

std::wstring Chat::Filtering(const std::wstring& original_input)
{
	std::wstring input = original_input;
	for (Filter& filter : filters_)
		input = filter.Filtering(input);
	return input;
}