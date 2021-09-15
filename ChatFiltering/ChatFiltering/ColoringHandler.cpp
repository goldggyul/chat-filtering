#include "ColoringHandler.h"

std::wstring ColoringHandler::Process(const std::wstring& msg)
{
	std::wstring colored = msg;
	// default color
	for (const auto& text : texts_)
	{
		colored = DoColoring(text, color_codes_[default_color_], msg);
	}
	for (const auto& text_color : text_with_color_)
	{
		colored = DoColoring(text_color.first, color_codes_[text_color.second], colored);
	}
	return colored;
}

std::wstring ColoringHandler::DoColoring(const std::wstring& text, const std::wstring& color_code, const std::wstring& msg)
{
	std::wstring output;
	size_t color_start = msg.find(text);
	size_t msg_start = 0;
	while (color_start != std::wstring::npos)
	{
		size_t prefix_count = color_start - msg_start;
		output.append(msg, msg_start, prefix_count);
		// ANSI color + text_color + ANSI color default
		output.append(color_code);
		output.append(text);
		output.append(L"\033[0m");

		msg_start = color_start + text.length();
		color_start = msg.find(text, color_start + 1);
	}
	output.append(msg, msg_start, msg.length() - msg_start);
	return output;
}
