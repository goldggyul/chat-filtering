#pragma once
#include "Filter.h"
#include <list>

class Chat
{
public:

	void AddFilter(std::wstring word)
	{
		filters_.push_back(Filter(word));
	}

	void AddLettersToIgnore(const std::wstring& ignorable_letters)
	{
		Filter::AddLettersToIgnore(ignorable_letters);
	}

	std::wstring DoChat(const std::wstring& original_msg);

private:
	std::list <Filter> filters_;
};

std::wstring Chat::DoChat(const std::wstring& original_msg)
{
	std::wstring msg = original_msg;
	for (Filter& filter : filters_)
		msg = filter.DoFilter(msg);
	return msg;
}