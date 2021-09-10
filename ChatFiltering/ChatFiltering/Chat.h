#pragma once
#include "Filter.h"

class Chat
{
public:
	Chat()
	{
		// #1
		AddFilter(L"°­¾ÆÁö");
	}

	void AddFilter(std::wstring filter)
	{
		filters_.push_back(Filter(filter));
	}

	void AddLettersToIgnore(std::wstring letters_to_ignore)
	{
		Filter::SetLettersToIgnore(letters_to_ignore);
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