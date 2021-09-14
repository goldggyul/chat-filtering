#pragma once
#include <iostream>
#include <string>
#include <set>
#include <queue>
#include "IHandler.h"

using uint = unsigned int;

// 입력 문자열의 필터링 해야 하는 범위 [start,end]  
struct FilterScope
{
	uint start;
	uint end;
};

class Filter:public IHandler
{
public:
	Filter(std::wstring text) : text_(text) {}

	static void AddLettersToIgnore(const std::wstring& ignorable_letters)
	{
		std::set<wchar_t>& ignorable_letters_ = GetIgnorableLetters();
		for (wchar_t letter : ignorable_letters)
			ignorable_letters_.insert(letter);
	}

	std::wstring Process(const std::wstring& msg);
	
private:
	static std::set<wchar_t>& GetIgnorableLetters()
	{
		static std::set<wchar_t>* ignorable_letters = new std::set<wchar_t>();
		return *ignorable_letters;
	}
	static const wchar_t REPLACEMENT_LETTER = '*';
	static const uint FAIL = 0xffffffff;

	std::wstring DoFilter(const std::wstring& msg);
	uint GetLastIndexToFilter(const std::wstring& msg, uint msg_idx);
	uint _GetLastIndexToFilterImpl(const std::wstring& msg, uint msg_idx, uint word_idx, wchar_t ignorable_letter);
	bool IsIgnorableLetter(wchar_t letter);
	std::wstring text_;
};

