#include <iostream>
#include <string>
#include <vector>

class Chat
{
private:
	std::vector<std::string>* filters_;

public:
	Chat() :filters_(new std::vector<std::string>)
	{
		AddFilter("������"); // �⺻ ���͸� �ܾ� �߰�
	}

	~Chat()
	{
		delete filters_;
	}

	const std::vector<std::string>& get_filters() { return *filters_; }
	void AddFilter(std::string filter) { filters_->push_back(filter); }

	void EraseLetter(std::string& input, std::string::size_type& pos, const std::string& filter);
	void GetSpaceOutput(std::string& input);
	void GetOutput(std::string& input);
	void Play();
};

int main()
{
	Chat chat;
	chat.AddFilter("�����");
	chat.Play();

	return 0;
}

void Chat::EraseLetter(std::string& input, std::string::size_type& pos, const std::string& filter)
{
	// ��ġ ã�� -> ������ ���͸��ϸ� �Ϸ�
	for (int i = 0; i < filter.size(); i += 2)
	{
		input[pos] = '*';
		input.erase(pos + 1, 1);
		if (i + 2 >= filter.size())
			break;
		pos = input.find(filter[i + 2], pos + 1);
	}
}

void Chat::GetSpaceOutput(std::string& input)
{
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		std::string input_no_space = input;

		// ���� ����
		std::string::iterator it = std::remove(input_no_space.begin(), input_no_space.end(), ' ');
		input_no_space.erase(it, input_no_space.end());

		// ���� ������ ���ڿ����� ���͸��� �ܾ� �ִ� �� Ȯ��
		std::string::size_type no_space_pos = input_no_space.find(filter);

		// ���͸� �ʿ��� ���
		if (no_space_pos != std::string::npos)
		{
			// ���� ������ ���ڿ��� �ƴ�, ���� ���ڿ����� ��ġ ã�� ���� ���� �� ����
			std::vector<int> space_count(input.size(), 0);
			for (int i = 1; i < input.size(); i++)
			{
				if (input[i - 1] == ' ')
					space_count[i] = space_count[i - 1] + 1;
				else
					space_count[i] = space_count[i - 1];
			}

			// ���͸� �ܾ� ù��° ���� �������� ã��
			std::string filter_first_letter;

			// ���͸� �ܾ �ѱ��̹Ƿ� 2����Ʈ �ʿ�
			filter_first_letter.push_back(filter[0]);
			filter_first_letter.push_back(filter[1]);
			std::string::size_type pos = input.find(filter_first_letter);
			while (pos != std::string::npos)
			{
				if (pos == no_space_pos + space_count[pos])
				{
					EraseLetter(input, pos, filter);
					break;
				}
				pos = input.find(filter_first_letter, pos + 1);
			}
		}
		else
		{
			// �� �̻� ���͸� �� �ܾ� ����
			continue;
		}
		// ������ �ܾ� ó��
		GetSpaceOutput(input);
		continue;
	}
}

void Chat::GetOutput(std::string& input)
{
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		std::string::size_type pos = input.find(filter);
		if (pos != std::string::npos)
		{
			EraseLetter(input, pos, filter);
		}
		else
		{
			// ���� ���Ե� ������ ���͸� �ܾ� �ִ� �� Ȯ��
			GetSpaceOutput(input);
			continue;
		}
		// ������ �ܾ� ó��
		GetOutput(input);
		continue;
	}
}

void Chat::Play()
{
	std::cout << "q �Է� �� ����" << std::endl;
	while (true)
	{
		std::cout << "> �Է�: ";
		std::string input;
		getline(std::cin, input);

		if (input == "q")
			return;

		std::string output = input;
		GetOutput(output);
		std::cout << "���: " << output << std::endl;
	}
}