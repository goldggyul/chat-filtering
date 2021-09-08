#include <iostream>
#include <string>
#include <vector>
#include <regex>

const int MIN_ASCII = 0;
const int MAX_ASCII = 127;
const char REPLACEMENT_LETTER = '*';

class Chat
{
private:
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

	bool IsAscii(const char& letter)
	{
		return letter >= MIN_ASCII && letter <= MAX_ASCII;
	}

	void Play();
	std::string Filter(const std::string& original_input);
	std::string GetReplacementWord(const std::string& filter);
	std::string GetExpression(const std::string& mask);
	std::string GetMask();
	bool IsAppropriateToFilter(const std::smatch& m);
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

		std::string output = Filter(input);
		std::cout << ">> " << output << std::endl;
	}
}

std::string Chat::Filter(const std::string& original_input)
{
	std::string input = original_input;

	int filters_size = filters_.size();
	for (int i = 0; i < filters_size; i++)
	{
		const std::string& filter = filters_.at(i);

		std::string replacement_word = GetReplacementWord(filter);
		std::string expression = GetExpression(filter);
		std::smatch m;
		std::string search_output = "";
		while (regex_search(input, m, std::regex(expression)))
		{
			search_output.append(m.prefix());
			if (IsAppropriateToFilter(m))
				search_output.append(replacement_word);
			else
				search_output.append(m.str());
			input = m.suffix();
		}
		input = search_output.append(input);
	}
	return input;
}

std::string Chat::GetReplacementWord(const std::string& filter)
{
	std::string replacement_word;
	int filter_size = filter.size();
	for (int f = 0; f < filter_size; f++)
	{
		replacement_word.push_back(REPLACEMENT_LETTER);
		if (!IsAscii(filter[f]))
			f++;
	}
	return replacement_word;
}

std::string Chat::GetExpression(const std::string& filter)
{
	std::string mask = GetMask();
	std::string expression;
	int filter_size = filter.size();
	for (int f = 0; f < filter_size; f++)
	{
		expression.push_back(filter[f]);
		if (!IsAscii(filter[f]))
			expression.push_back(filter[++f]);
		if (f == filter.size() - 1)
			break;
		expression.append(mask);
	}
	return expression;
}

std::string Chat::GetMask()
{
	std::string mask;
	mask.append("([");
	mask.append(letters_to_ignore_);
	mask.append("]*)");
	return mask;
}

bool Chat::IsAppropriateToFilter(const std::smatch& m)
{
	std::string match_result;
	int m_size = m.size();
	for (int i = 1; i < m_size; i++)
	{
		match_result.append(m[i].str());
	}
	return IsEveryLetterSame(match_result);
}

bool Chat::IsEveryLetterSame(const std::string& match_result)
{
	int match_result_size = match_result.size();
	for (int i = 1; i < match_result_size; i++)
	{
		if (match_result[i] != match_result[i - 1])
		{
			return false;
		}
	}
	return true;
}