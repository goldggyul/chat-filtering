#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/main.cpp"
#include "../ChatFiltering/Chat.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// 기본 필터링
			Chat chat;
			chat.AddFilter(L"puppy");

			std::wstring output = chat.Filtering(L"강아지");
			std::wstring expected = L"***";
			Assert::AreEqual(output, expected);

			output = chat.Filtering(L"puppy");
			expected=L"*****";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod2)
		{
			// 기본 필터링
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"강@아@지  p   upp    y 강 아@지 d  og d#o#g");
			std::wstring expected = L"***  ***** 강 아@지 *** ***";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod3)
		{
			// 기본 필터링
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y");
			std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod4)
		{
			// 기본 필터링
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"강##아@@@지 !@#!#% p^^^^u@@pp!!y 강@@아@@@지 ");
			std::wstring expected = L"강##아@@@지 !@#!#% p^^^^u@@pp!!y *** ";
			Assert::AreEqual(output, expected);
		}

	};
}
