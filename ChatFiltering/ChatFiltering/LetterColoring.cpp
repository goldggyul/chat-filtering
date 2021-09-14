#include "LetterColoring.h"

std::wstring LetterColoring::Process(const std::wstring& msg)
{
	return DoColoring(msg);
}

std::wstring LetterColoring::DoColoring(const std::wstring& msg)
{
	std::wstring color_code=GetColorCode();
	std::wstring output;
	size_t color_start = msg.find(text_);
	size_t msg_start = 0;
	while (color_start != std::wstring::npos)
	{
		size_t prefix_count = color_start - msg_start;
		output.append(msg, msg_start, prefix_count);
		// ANSI color + text + ANSI color default
		output.append(color_code);
		output.append(text_);
		output.append(L"\033[0m"); 

		msg_start = color_start + text_.length();
		color_start = msg.find(text_, color_start + 1);
	}
	output.append(msg, msg_start, msg.length() - msg_start);
	return output;
}

std::wstring LetterColoring::GetColorCode()
{
	std::map<std::wstring, std::wstring>& color_codes = GetColorCodes();
	if (color_.empty())
	{
		return color_codes[GetDefaultColor()];
	}
	if (color_codes.find(color_) == color_codes.end())
	{
		return color_codes[L"white"];
	}
	else
	{
		return color_codes[color_];
	}
}