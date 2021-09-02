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
	// 필터링 단어가 한글이므로 2로 나눔
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

	// 공백 제거
	std::string::iterator it = std::remove(input_no_space.begin(), input_no_space.end(), ' ');
	input_no_space.erase(it, input_no_space.end());

	// 공백 제거한 문자열에서 필터링할 단어 있는 지 확인
	std::string::size_type no_space_pos = input_no_space.find(filter);

	// 필터링 필요한 경우
	if (no_space_pos != std::string::npos)
	{
		// 공백 제거한 문자열이 아닌, 원래 문자열에서 위치 찾기 위해 공백 수 세기
		std::vector<int> space_count(input.size(), 0);
		for (int i = 1; i < input.size(); i++)
		{
			if (input[i - 1] == ' ')
				space_count[i] = space_count[i - 1] + 1;
			else
				space_count[i] = space_count[i - 1];
		}

		// 필터링 단어 첫번째 글자 기준으로 찾기
		std::string filter_first_letter;

		// 필터링 단어가 한글이므로 2바이트 필요
		filter_first_letter.push_back(filter[0]);
		filter_first_letter.push_back(filter[1]);
		std::string::size_type pos = output.find(filter_first_letter);
		while (pos != std::string::npos)
		{
			if (pos == no_space_pos + space_count[pos])
			{
				// 위치 찾음 -> 나머지 필터링하면 완료
				for (int i = 0; i < filter.size(); i += 2)
				{
					output[pos] = '*';
					output.erase(pos + 1, 1);
					if (i + 2 >= filter.size())
						break;
					pos = output.find(filter[i + 2], pos + 1);
				}
				break;
			}
			pos = output.find(filter_first_letter, pos + 1);
		}
	}
	return output;
}

std::string Chat::GetOutput(const std::string& input)
{
	const std::string& filter = get_filter();
	std::string::size_type pos = input.find(filter);
	std::string output = input;

	if (pos != std::string::npos)
	{
		output.replace(pos, filter.size(), GetFilteredWord(filter));
	}
	else
	{
		// 공백 포함된 상태의 필터링 단어 있는 지 확인
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