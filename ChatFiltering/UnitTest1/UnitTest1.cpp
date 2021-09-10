#include "pch.h"
#include "CppUnitTest.h"
#include "../ChatFiltering/main.cpp"
#include "../ChatFiltering/Filter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			// �⺻ ���͸�
			Chat chat;
			chat.AddFilter(L"puppy");

			std::wstring output = chat.Filtering(L"������");
			std::wstring expected = L"***";
			Assert::AreEqual(output, expected);

			output = chat.Filtering(L"puppy");
			expected=L"*****";
			Assert::AreEqual(output, expected);

			output = chat.Filtering(L"�� ������ �� ��");
			expected = L"�� *** �� ��";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod2)
		{
			// �⺻ ���͸�
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"��@��@��  p   upp    y �� ��@�� d  og d#o#g");
			std::wstring expected = L"***  ***** �� ��@�� *** ***";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod3)
		{
			// �⺻ ���͸�
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"��##��@@@�� !@#!#% p^^^^u@@pp!!y");
			std::wstring expected = L"��##��@@@�� !@#!#% p^^^^u@@pp!!y";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(TestMethod4)
		{
			// �⺻ ���͸�
			Chat chat;
			chat.AddFilter(L"puppy");
			chat.AddFilter(L"dog");
			chat.AddLettersToIgnore(L"\\s");
			chat.AddLettersToIgnore(L"!@#$%^&*\\s");

			std::wstring output = chat.Filtering(L"��##��@@@�� !@#!#% p^^^^u@@pp!!y ��@@��@@@�� ");
			std::wstring expected = L"��##��@@@�� !@#!#% p^^^^u@@pp!!y *** ";
			Assert::AreEqual(output, expected);
		}

	};
}
