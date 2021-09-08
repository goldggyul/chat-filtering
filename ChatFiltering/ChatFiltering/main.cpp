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
public:
	Chat() :filters_(new std::vector<std::string>)
	{
		AddFilter("강아지"); // 기본 필터링 단어 추가
	}

	~Chat()
	{
		delete filters_;
	}

	void AddFilter(std::string filter)
	{
		filters_->push_back(filter);
	}

	bool IsAscii(const char& letter)
	{
		return letter >= MIN_ASCII && letter <= MAX_ASCII;
	}

	void Play();
	std::string Filter(std::string& original_input);
};

int main()
{
	Chat chat;

	chat.AddFilter("puppy");
	chat.AddFilter("dog");
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

		std::string expression;
		for (int j = 0; j < filter.size(); j++)
		{
			expression.push_back(filter[j]);
			if (j == filter.size() - 1)
				break;
			expression.append("\\s*");
		}

		std::string replacement_word;
		for (int j = 0; j < filter.size(); j++)
		{
			replacement_word.push_back(REPLACEMENT);
			if (!IsAscii(filter[j]))
				j++;
		}

		std::regex rgx(expression);
		original_input = regex_replace(original_input, rgx, replacement_word);
	}
	return original_input;
}

