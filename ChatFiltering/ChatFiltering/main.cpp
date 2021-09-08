#include <iostream>
#include<string>
#include<vector>
#include<regex>

const int MIN_ASCII = 0;
const int MAX_ASCII = 127;
const char REPLACEMENT = '*';

class Chat
{
private:
	std::vector<std::string>* filters_;
	std::vector<char>* letters_to_ignore_;

public:
	Chat() :filters_(new std::vector<std::string>), letters_to_ignore_(new std::vector<char>)
	{
		// #1
		AddFilter("강아지");
	}

	~Chat()
	{
		delete filters_;
		delete letters_to_ignore_;
	}

	void AddFilter(std::string filter)
	{
		filters_->push_back(filter);
	}

	void AddLettersToIgnore(std::string letters_to_ignore)
	{
		for (int i = 0; i < letters_to_ignore.size(); i++)
		{
			letters_to_ignore_->push_back(letters_to_ignore[i]);
		}
	}

	bool IsAscii(const char& letter)
	{
		return letter >= MIN_ASCII && letter <= MAX_ASCII;
	}

	void Play();
	std::string Filter(std::string& original_input);
	std::string GetReplacementWord(const std::string& filter);
	std::string GetExpression(const std::string& filter, const std::string& mask);
};

int main()
{
	Chat chat;

	// #2
	chat.AddFilter("puppy");
	chat.AddFilter("dog");

	// #2.5 !@#$%(^)&*(\s)
	chat.AddLettersToIgnore("!@#$%\\^&*\\s");

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

std::string Chat::Filter(std::string& original_input)
{
	std::string filtered_input = original_input;
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);

		std::string replacement_word = GetReplacementWord(filter);
		
		for (int l = 0; l < letters_to_ignore_->size(); l++)
		{
			std::string mask;
			mask.append("[");
			mask.push_back(letters_to_ignore_->at(l));
			if (letters_to_ignore_->at(l) == '\\')
				mask.push_back(letters_to_ignore_->at(++l));
			mask.append("]*");

			std::string expression = GetExpression(filter, mask);

			original_input = regex_replace(original_input, std::regex(expression), replacement_word);
		}
	}
	return original_input;
}

std::string Chat::GetReplacementWord(const std::string& filter)
{
	std::string replacement_word;
	for (int f = 0; f < filter.size(); f++)
	{
		replacement_word.push_back(REPLACEMENT);
		if (!IsAscii(filter[f]))
			f++;
	}
	return replacement_word;
}

std::string Chat::GetExpression(const std::string& filter, const std::string& mask)
{
	std::string expression;
	for (int f = 0; f < filter.size(); f++)
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