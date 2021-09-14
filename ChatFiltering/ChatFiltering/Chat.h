#pragma once
#include "IHandler.h"
#include <memory>
#include <list>

class Chat
{
public:
	void AddHandler(IHandler* handler)
	{
		handlers_.push_back(std::shared_ptr<IHandler>(handler));
	}

	std::wstring DoChat(const std::wstring& original_msg);

private:
	std::list<std::shared_ptr<IHandler>> handlers_;
};

std::wstring Chat::DoChat(const std::wstring& original_msg)
{
	std::wstring msg = original_msg;
	for (auto& handler : handlers_)
	{
		msg = handler->Process(msg);
	}
	return msg;
}