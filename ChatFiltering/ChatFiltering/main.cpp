#include <iostream>
#include <string>

class Chat
{
private:
	std::string filter;

public:

	// �ʱ� ���� 
	Chat() :filter("������") {}
	Chat(std::string filter) :filter(filter) {}

	std::string GetFilteredWord(std::string filter)
	{
		std::string filter_word = "";
		// ���͸� �ܾ �ѱ��� ���
		for (int i = 0; i < filter.size() / 2; i++)
		{
			filter_word.push_back('*');
		}
		return filter_word;
	}

	void play()
	{
		std::cout << "q �Է� �� ����" << std::endl;
		while (true)
		{
			std::cout << "�Է�: ";
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
			std::cout << "���: " << output << std::endl;
		}
	}
};

int main()
{
	Chat chat;
	chat.play();

	return 0;
}