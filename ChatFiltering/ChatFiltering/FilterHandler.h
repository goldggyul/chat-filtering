#pragma once
#include "IHandler.h"
#include <list>
#include <set>
#include <queue>

using uint = unsigned int;

// 입력 문자열의 필터링 해야 하는 범위 [start,end]  
struct FilterScope
{
	uint start;
	uint end;
};

class FilterHandler :public IHandler
{
public:
	FilterHandler() = default;
	FilterHandler(const std::wstring& ignorable_letters)
	{
		AddLettersToIgnore(ignorable_letters);
	}

	void AddLettersToIgnore(const std::wstring& ignorable_letters)
	{
		for (wchar_t letter : ignorable_letters)
		{
			ignorable_letters_.insert(letter);
		}
	}
	void AddFilter(const std::wstring& text)
	{
		texts_.push_back(text);
	}

	std::wstring Process(const std::wstring& msg);

private:
	static const wchar_t REPLACEMENT_LETTER = '*';
	static const uint FAIL = 0xffffffff;

	std::wstring DoFilter(const std::wstring& text, const std::wstring& msg);
	uint GetLastIndexToFilter(const std::wstring& text, const std::wstring& msg, uint msg_idx);
	uint _GetLastIndexToFilterImpl(const std::wstring& text, const std::wstring& msg, uint msg_idx, uint word_idx, wchar_t ignorable_letter);
	bool IsIgnorableLetter(wchar_t letter);

	std::list<std::wstring> texts_;
	std::set<wchar_t> ignorable_letters_;
};