#include "Chat.h"
#include "FilterHandler.h"
#include "ColoringHandler.h"
#include <iostream>

Chat GetChat()
{
	Chat chat;

	FilterHandler* filter_handler = new FilterHandler;
	filter_handler->AddFilter(L"강아지");
	filter_handler->AddFilter(L"puppy");
	filter_handler->AddFilter(L"dog");
	filter_handler->AddLettersToIgnore(L"!@#$%^&* \t");
	chat.AddHandler(filter_handler);

	ColoringHandler* coloring_handler = new ColoringHandler;
	coloring_handler->SetDefaultColor(L"yellow");
	coloring_handler->AddText(L"고양이");
	coloring_handler->AddTextAndColor(L"cat", L"red");
	chat.AddHandler(coloring_handler);

	return chat;
}

int main()
{
	std::locale::global(std::locale("kor")); // Resets the default locale for the program
	std::wcout.imbue(std::locale("kor")); // Changes the locale of stream
	std::wcin.imbue(std::locale("kor"));
	
	Chat chat=GetChat();

	std::wcout << L"q 입력 시 종료" << std::endl;
	while (true)
	{
		std::wcout << L"입력: ";
		std::wstring input;
		getline(std::wcin, input);

		if (input == L"q")
		{
			break;
		}

		std::wstring output = chat.DoChat(input);
		std::wcout << L">> " << output << std::endl;
	}
	return 0;
}
