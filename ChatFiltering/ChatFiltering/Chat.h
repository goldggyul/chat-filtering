﻿#pragma once
#include "IHandler.h"
#include <memory>
#include <list>

class Chat
{
public:
	void AddHandler(IHandler* handler)
	{
		Handlers_.push_back(std::shared_ptr<IHandler>(handler));
	}

	// BackColoring

	// AutoCompletion

	std::wstring DoChat(const std::wstring& original_msg);

private:
	std::list<std::shared_ptr<IHandler>> Handlers_;
};

std::wstring Chat::DoChat(const std::wstring& original_msg)
{
	std::wstring msg = original_msg;
	for (auto& handler : Handlers_)
		msg = handler->Process(msg);
	return msg;
}