#pragma once
#include "Filter.h"
#include <list>

class Chat
{
public:
	//TODO
	//~Chat()
	//{
	//	for (auto* handler : Handlers_)
	//	{
	//		delete(handler);
	//	}
	//}
	void AddHandler(IHandler* handler)
	{
		Handlers_.push_back(handler);
	}

	void AddLettersToIgnore(const std::wstring& ignorable_letters)
	{
		Filter::AddLettersToIgnore(ignorable_letters);
	}

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