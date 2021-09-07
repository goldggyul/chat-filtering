#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<regex>

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
		AddFilter("강아지"); // 기본 필터링 단어 추가
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
};

