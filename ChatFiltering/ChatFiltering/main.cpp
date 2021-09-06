#include <iostream>
#include <string>
#include <vector>

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

	std::string HandleKoreanFilter(const std::string& input, const std::string& filtered_input);
	std::string FilterConsideringBlank(std::string& input);
	std::string FilterNotConsideringBlank(std::string& input);
	void Play();
};

int main()
{
	Chat chat;
	chat.AddFilter("cat");
	chat.Play();

	return 0;
}

std::string Chat::HandleKoreanFilter(const std::string& input, const std::string& filtered_input)
{
	int input_size = input.size();
	std::string output;
	for (int i = 0; i < input_size; i++)
	{
		output.push_back(filtered_input[i]);
		if (filtered_input[i] == REPLACEMENT && !IsAscii(input[i]))
			i++;
	}
	return output;
}

std::string Chat::FilterConsideringBlank(std::string& input)
{
	std::string input_no_space;
	std::vector<int> letter_pos;
	int input_size = input.size();
	for (int i = 0; i < input_size; i++)
	{
		if (input[i] != ' ')
		{
			input_no_space.push_back(input[i]);
			letter_pos.push_back(i);
		}
	}

	std::string filtered_input = input;
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		std::string::size_type no_space_pos = input_no_space.find(filter);

		int filter_size = filter.size();
		while (no_space_pos != std::string::npos)
		{
			for (int i = 0; i < filter_size; i++)
			{
				filtered_input[letter_pos[no_space_pos + i]] = REPLACEMENT;
			}
			no_space_pos = input_no_space.find(filter, no_space_pos + 1);
		}
	}
	return HandleKoreanFilter(input, filtered_input);
}

std::string Chat::FilterNotConsideringBlank(std::string& input)
{
	std::string filtered_input = input;
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		int filter_size = filter.size();
		std::string::size_type pos = input.find(filter);
		while (pos != std::string::npos)
		{
			for (int i = 0; i < filter_size; i++)
			{
				filtered_input[pos + i] = REPLACEMENT;
			}
			pos = input.find(filter, pos + 1);
		}
	}
	return HandleKoreanFilter(input, filtered_input);
}

void Chat::Play()
{
	std::cout << "q 입력 시 종료" << std::endl;
	while (true)
	{
		std::cout << "> 입력: ";
		std::string input;
		getline(std::cin, input);

		if (input == "q")
			return;

		std::string output = FilterConsideringBlank(input);
		std::cout << "출력: " << output << std::endl;
	}
}