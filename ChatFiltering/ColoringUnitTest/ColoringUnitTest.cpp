#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/main.cpp"
#include "../ChatFiltering/FilterHandler.cpp"
#include "../ChatFiltering/ColoringHandler.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColoringUnitTest
{
	TEST_CLASS(ColoringUnitTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Chat chat;
			FilterHandler* filter_handler = new FilterHandler;
			filter_handler->AddFilter(L"강아지");
			chat.AddHandler(filter_handler);

			// default: yellow
			// 고양이 -> default
			// cat -> red
			ColoringHandler* coloring_handler = new ColoringHandler;
			coloring_handler->SetDefaultColor(L"yellow");
			coloring_handler->AddText(L"고양이");
			coloring_handler->AddTextAndColor(L"cat", L"red");

			chat.AddHandler(coloring_handler);

			std::wstring output = chat.DoChat(L"고양이");
			std::wstring expected = L"\033[33m고양이\033[0m";
			Assert::AreEqual(output, expected);

			output = chat.DoChat(L"cat");
			expected = L"\033[31mcat\033[0m";
			Assert::AreEqual(output, expected);

			for (int i = 0; i < 100000; i++)
			{
				coloring_handler->SetDefaultColor(L"green");
				std::wstring output = chat.DoChat(L"고양이");
				std::wstring expected = L"\033[32m고양이\033[0m";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"cat");
				expected = L"\033[31mcat\033[0m";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"저 강아지 고양이 좀 봐");
				expected = L"저 *** \033[32m고양이\033[0m 좀 봐";
				Assert::AreEqual(output, expected);
			}
		}
	};
}
