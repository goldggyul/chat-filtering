#pragma once
#include "IHandler.h"
#include <list>

class Chat
{
public:

	void AddHandler(IHandler* handler)
	{
		Handlers_.push_back(handler);
	}

	// BackColoring

	// AutoCompletion

	std::wstring DoChat(const std::wstring& original_msg);

private:
	std::list<IHandler*> Handlers_;
};

std::wstring Chat::DoChat(const std::wstring& original_msg)
{
	std::wstring msg = original_msg;
	for (IHandler* handler : Handlers_)
		msg = handler->Process(msg);
	return msg;
}