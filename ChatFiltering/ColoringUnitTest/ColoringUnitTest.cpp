#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/Chat.h"
#include "../ChatFiltering/Filter.cpp"
#include "../ChatFiltering/LetterColoring.cpp"
#include "../ChatFiltering/IHandler.h"
#include "../ChatFiltering/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColoringUnitTest
{
	TEST_CLASS(ColoringUnitTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// default: yellow
			// ����� -> default
			// cat -> red
			Chat chat = GetChat();

			std::wstring output = chat.DoChat(L"�����");
			std::wstring expected = L"\033[33m�����\033[0m";
			Assert::AreEqual(output, expected);

			output = chat.DoChat(L"cat");
			expected = L"\033[31mcat\033[0m";
			Assert::AreEqual(output, expected);

			for (int i = 0; i < 100000; i++)
			{
				LetterColoring::SetDefaultColor(L"green");
				std::wstring output = chat.DoChat(L"�����");
				std::wstring expected = L"\033[32m�����\033[0m";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"cat");
				expected = L"\033[31mcat\033[0m";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"�� ������ ����� �� ��");
				expected = L"�� *** \033[32m�����\033[0m �� ��";
				Assert::AreEqual(output, expected);
			}
		}
	};
}
