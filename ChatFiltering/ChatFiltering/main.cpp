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
		AddFilter("강아지"); // 기본 필터링 단어 추가
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
	chat.AddFilter("고양이");
	chat.Play();

	return 0;
}

void Chat::EraseLetter(std::string& input, std::string::size_type& pos, const std::string& filter)
{
	// 위치 찾음 -> 나머지 필터링하면 완료
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
			// 더 이상 필터링 할 단어 없음
			continue;
		}
		// 나머지 단어 처리
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
			// 공백 포함된 상태의 필터링 단어 있는 지 확인
			GetSpaceOutput(input);
			continue;
		}
		// 나머지 단어 처리
		GetOutput(input);
		continue;
	}
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

		std::string output = input;
		GetOutput(output);
		std::cout << "출력: " << output << std::endl;
	}
}