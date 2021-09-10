#include "Chat.h"

std::wstring Chat::Filtering(const std::wstring& original_input)
{
	std::wstring input = original_input;
	for (const std::wstring& filter : filters_)
		input = FilteringUsingOneFilter(input, filter);
	return input;
}

std::wstring Chat::FilteringUsingOneFilter(const std::wstring& input, const std::wstring& filter)
{
	std::wstring replacement_word = GetReplacementWord(filter);
	std::wstring expression = GetExpressionForRegex(filter);
	std::wstring filtered = L"";

	std::wstring not_filtered = input;
	std::wsmatch match_result;
	std::wregex rgx(expression);
	// 정규식을 이용하여 더 이상 일치하지 않을 때까지 필터링
	while (!not_filtered.empty())
	{
		bool is_matched = regex_search(not_filtered, match_result, rgx);
		if (is_matched)
		{
			filtered.append(match_result.prefix());
			if (CanReplace(match_result))
				filtered.append(replacement_word);
			else
				filtered.append(match_result.str());
			not_filtered = match_result.suffix();
		}
		else
		{
			filtered.append(not_filtered);
			not_filtered = L"";
		}
	}
	return filtered;
}

std::wstring Chat::GetReplacementWord(const std::wstring& filter)
{
	std::wstring replacement_word;
	for (size_t f = 0; f < filter.size(); f++)
		replacement_word.push_back(REPLACEMENT_LETTER);
	return replacement_word;
}

std::wstring Chat::GetExpressionForRegex(const std::wstring& filter)
{
	std::wstring expression_to_ignore = GetExpressionOfLettersToIgnore();
	std::wstring expression;

	// 필터링 단어의 글자 사이사이에 '무시할 문자들의 정규식'을 삽입하여 최종 정규식 생성
	// 무시할 문자들의 정규식: [!@#$%^&*\\s]*
	// []안에 문자 중 하나가 0개 이상 있을 경우 match된다.
	// 따라서 모두 다른 종류든 같은 종류든 위의 경우에 해당한다면 모두 match된다.
	for (size_t f = 0; f < filter.size(); f++)
	{
		expression.push_back(filter[f]);
		if (f == filter.size() - 1)
			break;
		expression.append(expression_to_ignore);
	}
	return expression;
}

std::wstring Chat::GetExpressionOfLettersToIgnore()
{
	std::wstring expression;
	expression.append(L"([");
	expression.append(letters_to_ignore_);
	expression.append(L"]*)");
	return expression;
}

bool Chat::CanReplace(const std::wsmatch& m)
{
	std::wstring match_result;
	for (size_t i = 1; i < m.size(); i++)
		match_result.append(m[i].str());
	return IsEveryLetterSame(match_result);
}

bool Chat::IsEveryLetterSame(const std::wstring& match_result)
{
	for (size_t i = 1; i < match_result.size(); i++)
		if (match_result[i] != match_result[i - 1])
			return false;
	return true;
}