#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/main.cpp"
#include "../ChatFiltering/Filter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	private:
		Chat setting()
		{
			Chat chat;
			chat.AddFilter(L"강아지");
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L" ");
			chat.AddLettersToIgnore(L"!@#$%^&* ");
			return chat;
		}

	public:
		TEST_METHOD(TestMethod1)
		{
			// 기본 필터링
			Chat chat = setting();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.Filtering(L"강아지");
				std::wstring expected = L"***";
				Assert::AreEqual(output, expected);

				output = chat.Filtering(L"puppy");
				expected = L"*****";
				Assert::AreEqual(output, expected);

				output = chat.Filtering(L"저 강아지 좀 봐");
				expected = L"저 *** 좀 봐";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod2)
		{
			// 기본 필터링
			Chat chat = setting();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.Filtering(L"강@아@지  p   upp    y 강 아@지 d  og d#o#g");
				std::wstring expected = L"***  ***** 강 아@지 *** ***";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod3)
		{
			// 기본 필터링
			Chat chat = setting();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.Filtering(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y");
				std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y";
				Assert::AreEqual(output, expected);
			}

		}

		TEST_METHOD(TestMethod4)
		{
			// 기본 필터링
			Chat chat = setting();

			for (int i = 0; i < 100000; i++)
			{
				std::wstring output = chat.Filtering(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y 강@@아@@@지 ");
				std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y *** ";
				Assert::AreEqual(output, expected);
			}

		}
	};
}
