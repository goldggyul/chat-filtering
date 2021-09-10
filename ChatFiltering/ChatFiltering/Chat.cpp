#include "Chat.h"


std::wstring Chat::Filtering(const std::wstring& original_input)
{
	std::wstring input = original_input;
	for (Filter& filter : filters_)
		input = filter.Filtering(input);
	return input;
}
