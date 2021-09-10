#include "Chat.h"

int main()
{
	Chat chat;

	// #2
	chat.AddFilter(L"puppy");
	chat.AddFilter(L"dog");
	chat.AddLettersToIgnore(L"\\s");

	// #2.5: !@#$%^&*(\s)
	chat.AddLettersToIgnore(L"!@#$%^&*\\s");

	std::wcout << "q 입력 시 종료" << std::endl;
	while (true)
	{
		std::wcout << "입력: ";
		std::wstring input;
		getline(std::wcin, input);

		if (input == L"q")
			break;

		std::wstring output = chat.Filtering(input);
		std::wcout << ">> " << output << std::endl;
	}

	return 0;
}
