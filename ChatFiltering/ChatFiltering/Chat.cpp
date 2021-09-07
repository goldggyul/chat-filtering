#include "Chat.h"

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
	std::string input_removed_space;
	std::vector<int> letter_offset;
	for (int i = 0; i < original_input.size(); i++)
	{
		if (original_input[i] != ' ')
		{
			input_removed_space.push_back(original_input[i]);
			letter_offset.push_back(i);
		}
	}

	std::string filtered_input = original_input;
	for (int i = 0; i < filters_->size(); i++)
	{
		const std::string& filter = filters_->at(i);
		std::string::size_type pos = input_removed_space.find(filter);
		while (pos != std::string::npos)
		{
			for (int i = 0; i < filter.size(); i++)
			{
				int letter_index = letter_offset[pos + i];
				filtered_input[letter_index] = REPLACEMENT;
			}
			pos = input_removed_space.find(filter, pos + 1);
		}
	}
	return RemoveReplacementDuplication(original_input, filtered_input);
}

std::string Chat::RemoveReplacementDuplication(const std::string& original_input, const std::string& filtered_input)
{
	std::string input_removed_duplication;
	for (int i = 0; i < original_input.size(); i++)
	{
		input_removed_duplication.push_back(filtered_input[i]);
		if (filtered_input[i] == REPLACEMENT && !IsAscii(original_input[i]))
			i++;
	}
	return input_removed_duplication;
}
