#pragma once
#include <iostream>
#include<string>
#include<vector>

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
		AddFilter("������"); // �⺻ ���͸� �ܾ� �߰�
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

	void Play();
	std::string Filter(std::string& original_input);
	std::string RemoveReplacementDuplication(const std::string& original_input, const std::string& filtered_input);
};

