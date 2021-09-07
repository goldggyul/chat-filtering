#include "Chat.h"

int main()
{
	Chat chat;

	chat.AddFilter("puppy");
	chat.AddFilter("dog");
	chat.Play();

	return 0;
}