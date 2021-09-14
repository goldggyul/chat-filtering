#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "IHandler.h"

using uint = unsigned int;

class LetterColoring :public IHandler
{
public:
	LetterColoring(std::wstring text) : text_(text) {}
	LetterColoring(std::wstring text, std::wstring color) : text_(text), color_(color) {}

	static void SetDefaultColor(const std::wstring& color)
	{
		std::map<std::wstring, std::wstring>& color_codes = GetColorCodes();
		if (color_codes.find(color) == color_codes.end())
		{
			std::wcout << color<<" color is undefined" << std::endl;
			return;
		}
		std::wstring& default_color = GetDefaultColor();
		default_color = color;
		std::wcout << "default color: "<<color<< std::endl;
	}

	std::wstring Process(const std::wstring& msg);

private:
	static std::map<std::wstring, std::wstring>& GetColorCodes()
	{
		static std::map<std::wstring, std::wstring>* color_codes = new std::map<std::wstring, std::wstring>{
			{L"red",L"\033[31m"}, {L"green",L"\033[32m"},{L"yellow",L"\033[33m"},{L"blue",L"\033[34m"},{L"magenta",L"\033[35m"},{L"white",L"\033[97m"}
		};
		return *color_codes;
	}
	
	static std::wstring& GetDefaultColor()
	{
		static std::shared_ptr<std::wstring> default_color( new std::wstring(L"green") );
		return *default_color;
	}

	std::wstring DoColoring(const std::wstring& msg);
	std::wstring GetColorCode();

	std::wstring text_;
	std::wstring color_;
};

