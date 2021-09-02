#include <iostream>
#include <string>
#include <vector>

class Chat
{
private:
	std::string filter_;

public:
	// 초기 설정 
	Chat() :filter_("강아지") {}
	Chat(std::string filter) :filter_(filter) {}

	const std::string& get_filter() { return filter_; }

	std::string GetFilteredWord(const std::string& filter);
	std::string GetSpaceOutput(const std::string& input);
	std::string GetOutput(const std::string& input);
	void play();
};

int main()
{
	Chat chat;
	chat.play();

	return 0;
}

std::string Chat::GetFilteredWord(const std::string& filter)
{
	std::string filter_word = "";
	// 필터링 단어가 한글인 경우
	for (int i = 0; i < filter.size() / 2; i++)
	{
		filter_word.push_back('*');
	}
	return filter_word;
}

std::string Chat::GetSpaceOutput(const std::string& input)
{
	const std::string& filter = get_filter();
	std::string output = input;
	std::string input_no_space = input;
	std::string::iterator it = std::remove(input_no_space.begin(), input_no_space.end(), ' ');
	input_no_space.erase(it, input_no_space.end());

	std::string::size_type no_space_pos = input_no_space.find(filter);
	if (no_space_pos != std::string::npos)
	{
		std::vector<int> space_count(input.size(), 0);
		for (int i = 1; i < input.size(); i++)
		{
			if (input[i - 1] == ' ')
				space_count[i] = space_count[i - 1] + 1;
			else
				space_count[i] = space_count[i - 1];
		}

		std::string::size_type pos = output.find("강");
		while (pos != std::string::npos)
		{
			if (pos == no_space_pos + space_count[pos])
			{
				output[pos] = '*';
				output.erase(pos + 1, 1);
				pos = output.find("아", pos + 1);
				output[pos] = '*';
				output.erase(pos + 1, 1);
				pos = output.find("지", pos + 1);
				output[pos] = '*';
				output.erase(pos + 1, 1);
				break;
			}
			pos = output.find("강", pos + 1);
		}
	}
	return output;
}

std::string Chat::GetOutput(const std::string& input)
{
	std::string::size_type pos = input.find(get_filter());
	std::string output = input;

	if (pos != std::string::npos)
	{
		output.replace(pos, get_filter().size(), GetFilteredWord(get_filter()));
	}
	else
	{
		output = GetSpaceOutput(input);
	}
	return output;
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

		std::string output = GetOutput(input);
		std::cout << "출력: " << output << std::endl;
	}
}