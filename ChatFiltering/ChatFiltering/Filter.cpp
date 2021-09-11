#include "Filter.h"
#include<queue>

void Filter::AddLettersToIgnore(std::wstring letters_to_ignore)
{
	std::set<wchar_t>& letters_to_ignore_ = Filter::GetLettersToIgnore();
	for (wchar_t letter : letters_to_ignore)
		letters_to_ignore_.insert(letter);
}

std::wstring Filter::Filtering(std::wstring input) {
	std::queue<size_t> q;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == word_[0])
		{
			int last_index = GetLastIndexIfReplaceable(input, i, 0, true, L'\0');
			if (last_index == FAIL)
				continue;
			q.push(i);
			q.push(last_index);
		}
	}

	std::wstring output;
	size_t first = 0;
	while (!q.empty())
	{
		size_t last = q.front(); q.pop();
		output.append(input.begin() + first, input.begin() + last);
		output.append(word_.length(), REPLACEMENT_LETTER);
		first = q.front() + 1; q.pop();
	}
	output.append(input, first, input.length());
	return output;
}

int Filter::GetLastIndexIfReplaceable(const std::wstring& input, int input_idx, int word_idx, bool isFirstCapture, wchar_t ignore_letter)
{
	if (word_idx == word_.length() - 1) // 마지막 단어 -> 즉 정답
		return input_idx;
	if (input_idx == input.length() - 1) // 입력 끝, 더 이상 못찾음
		return FAIL;
	if (word_[word_idx + 1] == input[input_idx + 1]) // 다음 글자 일치
		return GetLastIndexIfReplaceable(input, input_idx + 1, word_idx + 1, isFirstCapture, ignore_letter);
	if (IsIgnoreLetter(input[input_idx + 1]))
		if (isFirstCapture)
			return GetLastIndexIfReplaceable(input, input_idx + 1, word_idx, !isFirstCapture, input[input_idx + 1]);
		else if (input[input_idx + 1] == ignore_letter)
			return GetLastIndexIfReplaceable(input, input_idx + 1, word_idx, isFirstCapture, ignore_letter);
	return FAIL;
}

bool Filter::IsIgnoreLetter(wchar_t letter)
{
	std::set<wchar_t>& letters_to_ignore_ = Filter::GetLettersToIgnore();
	auto it = letters_to_ignore_.find(letter);
	if (it != letters_to_ignore_.end())
		return true;
	else
		return false;
}
