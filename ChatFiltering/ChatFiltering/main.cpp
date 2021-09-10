#include "Chat.h"

void multibyte_setting()
{
	std::locale::global(std::locale("kor"));
	std::wcout.imbue(std::locale("kor"));
	std::wcin.imbue(std::locale("kor"));
}

int main()
{
	multibyte_setting();

	Chat chat;

	// #2
	chat.AddFilter(L"puppy");
	chat.AddFilter(L"dog");
	chat.AddLettersToIgnore(L"\\s");

	// #2.5: !@#$%^&*(\s)
	chat.AddLettersToIgnore(L"!@#$%^&*\\s");

	std::wcout << L"q 입력 시 종료" << std::endl;
	while (true)
	{
		std::wcout << L"입력: ";
		std::wstring input;
		getline(std::wcin, input);

		if (input == L"q")
			break;

		std::wstring output = chat.Filtering(input);
		std::wcout << L">> " << output << std::endl;
	}
	return 0;
}
