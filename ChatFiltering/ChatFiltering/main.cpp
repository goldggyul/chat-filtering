﻿#include "Chat.h"

int main()
{
	std::locale::global(std::locale("kor")); // Resets the default locale for the program
	std::wcout.imbue(std::locale("kor")); // Changes the locale of stream
	std::wcin.imbue(std::locale("kor"));
	
	Chat chat;

	// #1
	chat.AddHandler(new Filter(L"강아지"));

	// #2
	chat.AddHandler(new Filter(L"puppy"));
	chat.AddHandler(new Filter(L"dog"));
	chat.AddLettersToIgnore(L" ");

	// #2.5: !@#$%^&*(\s)
	chat.AddLettersToIgnore(L"!@#$%^&* \t");

	std::wcout << L"q 입력 시 종료" << std::endl;
	while (true)
	{
		std::wcout << L"입력: ";
		std::wstring input;
		getline(std::wcin, input);

		if (input == L"q")
			break;

		std::wstring output = chat.DoChat(input);
		std::wcout << L">> " << output << std::endl;
	}
	return 0;
}
