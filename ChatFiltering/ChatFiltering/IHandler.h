#pragma once
#include <string>

class IHandler
{
public:
	virtual ~IHandler() {};
	virtual std::wstring Process(const std::wstring& msg) = 0;
};

