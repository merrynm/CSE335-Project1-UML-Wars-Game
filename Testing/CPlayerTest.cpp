#include "pch.h"
#include "CppUnitTest.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPlayerTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir + '/0');
		}
		
		TEST_METHOD(TestCPlayerConstruct)
		{
			CScreen screen;
			CPlayer player(&screen);
		}
	};
}