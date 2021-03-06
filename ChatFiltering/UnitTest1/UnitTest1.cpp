#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/main.cpp"
#include "../ChatFiltering/FilterHandler.cpp"
#include "../ChatFiltering/ColoringHandler.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// 기본 필터링
			Chat chat = GetChat();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.DoChat(L"강아지");
				std::wstring expected = L"***";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"puppy");
				expected = L"*****";
				Assert::AreEqual(output, expected);

				output = chat.DoChat(L"저 강아지 좀 봐");
				expected = L"저 *** 좀 봐";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod2)
		{
			// 기본 필터링
			Chat chat = GetChat();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.DoChat(L"강@아@지  p   upp    y 강 아@지 d  og d#o#g");
				std::wstring expected = L"***  ***** 강 아@지 *** ***";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod3)
		{
			// 기본 필터링
			Chat chat = GetChat();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.DoChat(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y");
				std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod4)
		{
			// 기본 필터링
			Chat chat = GetChat();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.DoChat(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y 강@@아@@@지 ");
				std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y *** ";
				Assert::AreEqual(output, expected);
			}

		}
	};
}
