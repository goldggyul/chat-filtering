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

	chat.Play();

	return 0;
}
