﻿#include <iostream>
#include <string>
#include <vector>
#include <regex>

class Chat
{
private:
	static const int MIN_KOREAN = 0;
	static const int MAX_KOREAN = 127;
	static const char REPLACEMENT_LETTER = '*';

	std::vector<std::string> filters_;
	std::string letters_to_ignore_;

public:
	Chat()
	{
		letters_to_ignore_ = "";
		// #1
		AddFilter("강아지");
	}

	void AddFilter(std::string filter)
	{
		filters_.push_back(filter);
	}

	void AddLettersToIgnore(std::string letters_to_ignore)
	{
		letters_to_ignore_.append(letters_to_ignore);
	}

	bool IsKorean(const char& letter)
	{
		// 유니코드 한글 2진수 범위 : 1010 1100 0000 0000 ~ 1101 0111 1010 0011
		// 앞에 8비트가 모두 1로 시작 -> 0x80 & 한글 == 1
		return letter & 0x80;
	}

	void Play();
	std::string Filtering(const std::string& original_input);
	std::string FilteringUsingOneFilter(const std::string& input, const std::string& filter);
	std::string GetReplacementWord(const std::string& filter);
	std::string GetExpressionForRegex(const std::string& filter);
	std::string GetExpressionOfLettersToIgnore();
	bool CanReplace(const std::smatch& m);
	bool IsEveryLetterSame(const std::string& match_result);
};

int main()
{
	Chat chat;

	// #2
	chat.AddFilter("puppy");
	chat.AddFilter("dog");
	chat.AddLettersToIgnore("\\s");

	// #2.5: !@#$%^&*(\s)
	chat.AddLettersToIgnore("!@#$%^&*\\s");

	chat.Play();

	return 0;
}

void Chat::Play()
{
	std::cout << "q 입력 시 종료" << std::endl;
	while (true)
	{
		std::cout << "입력: ";
		std::string input;
		getline(std::cin, input);

		if (input == "q")
			return;

		std::string output = Filtering(input);
		std::cout << ">> " << output << std::endl;
	}
}

std::string Chat::Filtering(const std::string& original_input)
{
	std::string input = original_input;
	for (const std::string& filter:filters_)
		input = FilteringUsingOneFilter(input, filter);
	return input;
}

std::string Chat::FilteringUsingOneFilter(const std::string& input, const std::string& filter)
{
	std::string replacement_word = GetReplacementWord(filter);
	std::string expression = GetExpressionForRegex(filter);
	std::string filtered = "";

	std::string not_filtered = input;
	std::smatch match_result;
	std::regex rgx(expression);
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
			not_filtered = "";
		}
	}
	return filtered;
}

std::string Chat::GetReplacementWord(const std::string& filter)
{
	std::string replacement_word;
	for (size_t f = 0; f < filter.size(); f++)
	{
		replacement_word.push_back(REPLACEMENT_LETTER);
		if (IsKorean(filter[f]))
			f++;
	}
	return replacement_word;
}

std::string Chat::GetExpressionForRegex(const std::string& filter)
{
	std::string expression_to_ignore = GetExpressionOfLettersToIgnore();
	std::string expression;
	
	// 필터링 단어의 글자 사이사이에 '무시할 문자들의 정규식'을 삽입하여 최종 정규식 생성
	// 무시할 문자들의 정규식: [!@#$%^&*\\s]*
	// []안에 문자 중 하나가 0개 이상 있을 경우 match된다.
	// 따라서 모두 다른 종류든 같은 종류든 위의 경우에 해당한다면 모두 match된다.
	for (size_t f = 0; f < filter.size(); f++)
	{
		expression.push_back(filter[f]);
		if (IsKorean(filter[f]))
			expression.push_back(filter[++f]);
		if (f == filter.size() - 1)
			break;
		expression.append(expression_to_ignore);
	}
	return expression;
}

std::string Chat::GetExpressionOfLettersToIgnore()
{
	std::string expression;
	expression.append("([");
	expression.append(letters_to_ignore_);
	expression.append("]*)");
	return expression;
}

bool Chat::CanReplace(const std::smatch& m)
{
	std::string match_result;
	for (size_t i = 1; i < m.size(); i++)
		match_result.append(m[i].str());
	return IsEveryLetterSame(match_result);
}

bool Chat::IsEveryLetterSame(const std::string& match_result)
{
	for (size_t i = 1; i < match_result.size(); i++)
		if (match_result[i] != match_result[i - 1])
			return false;
	return true;
}