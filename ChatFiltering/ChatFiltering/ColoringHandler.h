#pragma once
#include "IHandler.h"
#include <list>
#include <map>

class ColoringHandler :public IHandler
{
public:
	ColoringHandler() :default_color_(L"green"){}
	ColoringHandler(const std::wstring& color):default_color_(color) { }

	void AddText(const std::wstring& text)
	{
		texts_.push_back(text);
	}
	void SetDefaultColor(const std::wstring& color)
	{
		default_color_ = color;
	}
	void AddTextAndColor(const std::wstring& text, const std::wstring& color)
	{
		text_with_color_.insert({ text, color });
	}

	std::wstring Process(const std::wstring& msg);

private:
	std::wstring DoColoring(const std::wstring& text, const std::wstring& color_code, const std::wstring& msg);
	
	std::list<std::wstring> texts_;
	std::wstring default_color_;

	std::map<std::wstring, std::wstring> text_with_color_;
	std::map<std::wstring, std::wstring> color_codes_ = {
		{L"red",L"\033[31m"}, {L"green",L"\033[32m"},{L"yellow",L"\033[33m"},{L"blue",L"\033[34m"},{L"magenta",L"\033[35m"},{L"white",L"\033[97m"}
	};
};

