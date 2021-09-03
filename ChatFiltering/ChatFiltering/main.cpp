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

	void FIlterOnce(std::string& input, std::string::size_type& pos, const std::string& filter);
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

void Chat::GetSpaceOutput(std::string& input)
{
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		int size = filter.size()/2;
		std::string input_no_space = input;

		// ���� ������ ���ڿ��� �ƴ�, ���� ���ڿ����� ��ġ ã�� ���� ���� �� ����
		std::vector<int> space_count(input.size(), 0);
		for (int i = 1; i < input.size(); i++)
		{
			if (input[i - 1] == ' ')
				space_count[i] = space_count[i - 1] + 1;
			else
				space_count[i] = space_count[i - 1];
		}

		// ���� ����
		std::string::iterator it = std::remove(input_no_space.begin(), input_no_space.end(), ' ');
		input_no_space.erase(it, input_no_space.end());

		// ���� ������ ���ڿ����� ���͸��� �ܾ� �ִ� �� Ȯ��
		std::string::size_type no_space_pos = input_no_space.find(filter);
	
		int erase_count = 0;
		// ���͸� �ʿ��� ���
		while (no_space_pos != std::string::npos)
		{
			std::string::size_type pos = input.find(filter[0]);
			while (pos != std::string::npos)
			{
				if (pos == no_space_pos - (erase_count*size)+ space_count[pos])
				{
					for (int i = 0; i < size; i++)
					{
						input[pos] = '*';
						input.erase(pos + 1, 1);
						space_count.erase(space_count.begin() + pos + 1);
						if (i == size-1)
							break;
						pos = input.find(filter[(i+1)*2], pos + 1);
					}
					++erase_count;
					break;
				}
				pos = input.find(filter[0], pos + 1);
			}
			no_space_pos = input_no_space.find(filter, no_space_pos+1);
		}
	}
}

void Chat::GetOutput(std::string& input)
{
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		int size = filter.size();
		std::string::size_type pos = input.find(filter);
		while (pos != std::string::npos)
		{
			for (int i = 0; i < size/2; i++)
			{
				input[pos+i] = '*';
				input.erase(pos+i + 1, 1);
			}
			pos = input.find(filter, pos+1);
		}
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
		//GetOutput(output);
		GetSpaceOutput(output);
		std::cout << "���: " << output << std::endl;
	}
}