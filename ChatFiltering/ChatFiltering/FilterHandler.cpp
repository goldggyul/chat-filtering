#include "FilterHandler.h"

std::wstring FilterHandler::Process(const std::wstring& msg)
{
	std::wstring filtered = msg;
	for (const auto& text : texts_)
	{
		filtered = DoFilter(text, filtered);
	}
	return filtered;
}

std::wstring FilterHandler::DoFilter(const std::wstring& text, const std::wstring& msg) {
	std::queue<FilterScope> q;
	for (uint i = 0; i < msg.length(); i++)
	{
		if (msg[i] == text[0])
		{
			uint last_index = GetLastIndexToFilter(text,msg, i);
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
		// { #1 | #2 | #3 } : #2�� ��ü ����(*)�� ���͸� �Ǵ� �κ�, #1�� #3�� �״�� ��µǴ� �κ�
		uint count = filter_scope.start - msg_start;
		output.append(msg, msg_start, count); // #1
		output.append(text.length(), REPLACEMENT_LETTER); // #2
		msg_start = filter_scope.end + 1;
	}
	output.append(msg, msg_start, msg.length()); // #3
	return output;
}

/*
	<��� �Լ�>
	���� �ε����� ��ġ��, ���� �ε��� �˻� �ʿ�

	F: ���͸� �ܾ��� ���� �ε��� ����
	I: �Է� ���ڿ��� ���� �ε��� ����

	1. ���� �Ϸ� ����
		1-1. ���͸� �ܾ� ������ ���� - ����
		1-2. �Է� ���ڿ��� ���� - ����
	2. ���� ���� Ȯ��
		2-1. F+1�� I+1�� ����
		2-2. F+1�� ����,!,@,#,$,%,^,&,* �� �ϳ�
			�� ���� �� �ϳ��� �̹� �� �� �����°�?
			1) ó�� ����
			2) �̹� ���� - ������ ���ڿ� �� ���ڿ� ����
	3. �� �� - ����
*/
uint FilterHandler::GetLastIndexToFilter(const std::wstring& text, const std::wstring& msg, uint msg_idx)
{
	return _GetLastIndexToFilterImpl(text, msg, msg_idx, 0, L'\0');
}

// GetLastIndexToFIlter�Լ��� ���ؼ��� ������ ��
uint FilterHandler::_GetLastIndexToFilterImpl(const std::wstring& text, const std::wstring& msg, uint msg_idx, uint text_idx, wchar_t ignorable_letter)
{
	if (text_idx == text.length() - 1)
	{
		return msg_idx;
	}
	if (msg_idx == msg.length() - 1)
	{
		return FAIL;
	}

	wchar_t next_text = text[text_idx + 1LL];
	wchar_t next_msg = msg[msg_idx + 1LL];

	if (next_text == next_msg)
	{
		return _GetLastIndexToFilterImpl(text, msg, msg_idx + 1, text_idx + 1, ignorable_letter);
	}
	if (IsIgnorableLetter(next_msg))
	{
		if (ignorable_letter == '\0')
		{
			return _GetLastIndexToFilterImpl(text, msg, msg_idx + 1, text_idx, next_msg);
		}
		else if (next_msg == ignorable_letter)
		{
			return _GetLastIndexToFilterImpl(text, msg, msg_idx + 1, text_idx, ignorable_letter);
		}
	}
	return FAIL;
}

bool FilterHandler::IsIgnorableLetter(wchar_t letter)
{
	auto it = ignorable_letters_.find(letter);
	if (it != ignorable_letters_.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
