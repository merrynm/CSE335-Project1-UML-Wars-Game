#include "pch.h"
//#include "PensTest.h"
#include "CppUnitTest.h"
#include "Pens.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPenTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCPenConstruct)
		{
			CScreen screen;
			//CPens pen(&screen);
		}
	};
}
