#include "Chat.h"
#include "Filter.h"
#include "LetterColoring.h"

Chat GetChat()
{
	Chat chat;

	Filter::AddLettersToIgnore(L"!@#$%^&* \t");

	chat.AddHandler(new Filter(L"강아지"));
	chat.AddHandler(new LetterColoring(L"cat", L"red"));

	LetterColoring::SetDefaultColor(L"yellow");

	chat.AddHandler(new LetterColoring(L"고양이"));
	chat.AddHandler(new Filter(L"puppy"));
	chat.AddHandler(new Filter(L"dog"));

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
