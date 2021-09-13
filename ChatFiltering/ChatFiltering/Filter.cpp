﻿#include "Filter.h"
#include <queue>

// 입력 문자열의 필터링 해야 하는 범위 [start,end]  
struct FilterScope
{
	uint start;
	uint end;
};

std::wstring Filter::DoFilter(const std::wstring& msg) {
	std::queue<FilterScope> q;
	for (uint i = 0; i < msg.length(); i++)
	{
		if (msg[i] == text_[0])
		{
			uint last_index = GetLastIndexToFilter(msg, i, 0, L'\0');
			if (last_index != FAIL)
			{
				q.push(FilterScope{ i,last_index });
				i = last_index;
			}
		}
	}

	std::wstring output;
	uint msg_start = 0;
	while (!q.empty())
	{
		FilterScope filter_scope = q.front(); q.pop();
		// { #1 | #2 | #3 } : #2는 대체 문자(*)로 필터링 되는 부분, #1과 #3은 그대로 출력되는 부분
		uint count = filter_scope.start - msg_start;
		output.append(msg, msg_start, count); // #1
		output.append(text_.length(), REPLACEMENT_LETTER); // #2
		msg_start = filter_scope.end + 1;
	}
	output.append(msg, msg_start, msg.length()); // #3
	return output;
}

/*
	<재귀 함수>
	현재 인덱스는 일치함, 다음 인덱스 검사 필요

	F: 필터링 단어의 현재 인덱스 글자
	I: 입력 문자열의 현재 인덱스 글자

	1. 현재 완료 여부
		1-1. 필터링 단어 마지막 글자 - 성공
		1-2. 입력 문자열이 끝남 - 실패
	2. 다음 문자 확인
		2-1. F+1과 I+1이 동일
		2-2. F+1이 공백,!,@,#,$,%,^,&,* 중 하나
			위 문자 중 하나가 이미 한 번 쓰였는가?
			1) 처음 쓰임
			2) 이미 쓰임 - 쓰였던 문자와 위 문자와 동일
	3. 그 외 - 실패
*/
uint Filter::GetLastIndexToFilter(const std::wstring& msg, uint msg_idx, uint text_idx, wchar_t ignorable_letter)
{
	if (text_idx == text_.length() - 1)
		return msg_idx;	
	if (msg_idx == msg.length() - 1)
		return FAIL;

	wchar_t next_text = text_[text_idx + 1];
	wchar_t next_msg = msg[msg_idx + 1];

	if (next_text == next_msg)
		return GetLastIndexToFilter(msg, msg_idx + 1, text_idx + 1, ignorable_letter);

	if (IsIgnorableLetter(next_msg))
		if (ignorable_letter == '\0')
			return GetLastIndexToFilter(msg, msg_idx + 1, text_idx, next_msg);
		else if (next_msg == ignorable_letter)
			return GetLastIndexToFilter(msg, msg_idx + 1, text_idx, ignorable_letter);

	return FAIL;
}

bool Filter::IsIgnorableLetter(wchar_t letter)
{
	std::set<wchar_t>& ignorable_letters = Filter::GetIgnorableLetters();
	auto it = ignorable_letters.find(letter);
	if (it != ignorable_letters.end())
		return true;
	else
		return false;
}
