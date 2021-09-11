#include "Filter.h"
#include <queue>

// 입력 문자열의 필터링 해야 하는 범위[from,to]  
struct FilterScope
{
	int from;
	int to;
};

std::wstring Filter::Filtering(const std::wstring& msg) {
	std::queue<FilterScope> q;
	for (auto i = 0; i < msg.length(); i++)
	{
		if (msg[i] == text_[0])
		{
			// 현재 문장에서부터 search, 아직 ignorable letter는 없음
			int last_index = GetLastIndexToFilter(msg, i, 0, L'\0');
			if (last_index != FAIL)
				q.push(FilterScope{ i,last_index });
		}
	}

	std::wstring output;
	int msg_start = 0;
	while (!q.empty())
	{
		FilterScope filter_scope = q.front(); q.pop();
		// { #1 | #2 | #3 } : #2는 대체 문자(*)로 필터링 되는 부분, #1과 #3은 그대로 출력되는 부분
		int count = filter_scope.from - msg_start;
		output.append(msg, msg_start, count); // #1
		output.append(text_.length(), REPLACEMENT_LETTER); // #2
		msg_start = filter_scope.to + 1;
	}
	output.append(msg, msg_start, msg.length()); // #3
	return output;
}

// 현재 인덱스는 일치함, 다음 인덱스 검사 필요
int Filter::GetLastIndexToFilter(const std::wstring& msg, int msg_idx, int text_idx, wchar_t ignorable_letter)
{
	// match 성공
	if (text_idx == text_.length() - 1)
		return msg_idx;
	// 더 이상 match 시도할 문자열이 없음
	if (msg_idx == msg.length() - 1)
		return FAIL;

	wchar_t next_text = text_[text_idx + 1LL];
	wchar_t next_msg = msg[msg_idx + 1LL];

	if (next_text == next_msg)
		return GetLastIndexToFilter(msg, msg_idx + 1, text_idx + 1, ignorable_letter);
	// 무시 문자 '후보'군에 있음
	if (IsIgnorableLetter(next_msg))
		// 무시 문자 처음 나와서 세팅
		if (ignorable_letter == '\0')
			return GetLastIndexToFilter(msg, msg_idx + 1, text_idx, next_msg);
		// 무시 문자 세팅되어 있으며 + 일치함
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
