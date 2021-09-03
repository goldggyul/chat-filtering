#include <iostream>
#include <string>
#include <vector>

const int MIN_ASCII = 0;
const int MAX_ASCII = 127;

class Chat
{
private:
	std::vector<std::string>* filters_;
public:
	Chat() :filters_(new std::vector<std::string>)
	{
		addFilter("강아지"); // 기본 필터링 단어 추가
	}

	~Chat()
	{
		delete filters_;
	}

	void addFilter(std::string filter)
	{
		filters_->push_back(filter);
	}

	bool isAscii(const char& letter)
	{
		return letter >= MIN_ASCII && letter <= MAX_ASCII;
	}

	std::string handleKoreanFilter(const std::string& input, const std::string& filtered_input);
	std::string filterInputWithSpace(std::string& input);
	std::string filterInput(std::string& input);
	void play();
};

int main()
{
	Chat chat;
	chat.addFilter("cat");
	chat.play();

	return 0;
}

std::string Chat::handleKoreanFilter(const std::string& input, const std::string& filtered_input)
{
	int input_size = input.size();
	std::string output;
	for (int i = 0; i < input_size; i++)
	{
		output.push_back(filtered_input[i]);
		if (filtered_input[i] == '*' && !isAscii(input[i]))
			i++;
	}
	return output;
}

std::string Chat::filterInputWithSpace(std::string& input)
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

		// 필터링 필요한 경우
		int filter_size = filter.size();
		while (no_space_pos != std::string::npos)
		{
			for (int i = 0; i < filter_size; i++)
			{
				filtered_input[letter_pos[no_space_pos + i]] = '*';
			}
			no_space_pos = input_no_space.find(filter, no_space_pos + 1);
		}
	}
	return handleKoreanFilter(input, filtered_input);
}

std::string Chat::filterInput(std::string& input)
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
				filtered_input[pos + i] = '*';
			}
			pos = input.find(filter, pos + 1);
		}
	}
	return handleKoreanFilter(input, filtered_input);
}

void Chat::play()
{
	std::cout << "q 입력 시 종료" << std::endl;
	while (true)
	{
		std::cout << "> 입력: ";
		std::string input;
		getline(std::cin, input);

		if (input == "q")
			return;

		std::string output = filterInputWithSpace(input);
		//std::string output = filterInput(input);
		std::cout << "출력: " << output << std::endl;
	}
}