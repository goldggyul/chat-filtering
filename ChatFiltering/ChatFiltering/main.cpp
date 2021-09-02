#include <iostream>
#include <string>

class Chat
{
private:
	std::string filter;

public:

	// 초기 설정 
	Chat() :filter("강아지") {}
	Chat(std::string filter) :filter(filter) {}

	std::string GetFilteredWord(std::string filter)
	{
		std::string filter_word = "";
		// 필터링 단어가 한글인 경우
		for (int i = 0; i < filter.size() / 2; i++)
		{
			filter_word.push_back('*');
		}
		return filter_word;
	}

	void play()
	{
		std::cout << "q 입력 시 종료" << std::endl;
		while (true)
		{
			std::cout << "입력: ";
			std::string input;
			getline(std::cin, input);
			
			if (input == "q")
				return;

			std::string::size_type pos = input.find(filter);
			std::string output = input;

			if (pos != std::string::npos)
			{
				output.replace(pos, filter.size(), GetFilteredWord(filter));
			}
			std::cout << "출력: " << output << std::endl;
		}
	}
};

int main()
{
	Chat chat;
	chat.play();

	return 0;
}