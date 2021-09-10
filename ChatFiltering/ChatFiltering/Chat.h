#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Filter.h"

class Chat
{
public:
	Chat()
	{
		// #1
		AddFilter(L"������");
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