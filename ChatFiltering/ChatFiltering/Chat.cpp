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
	// ���Խ��� �̿��Ͽ� �� �̻� ��ġ���� ���� ������ ���͸�
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

	// ���͸� �ܾ��� ���� ���̻��̿� '������ ���ڵ��� ���Խ�'�� �����Ͽ� ���� ���Խ� ����
	// ������ ���ڵ��� ���Խ�: [!@#$%^&*\\s]*
	// []�ȿ� ���� �� �ϳ��� 0�� �̻� ���� ��� match�ȴ�.
	// ���� ��� �ٸ� ������ ���� ������ ���� ��쿡 �ش��Ѵٸ� ��� match�ȴ�.
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