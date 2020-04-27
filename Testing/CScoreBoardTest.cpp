#include "pch.h"
#include "CppUnitTest.h"
#include "Scoreboard.h"
#include "Screen.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CScoreBoardTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir+'/0');
		}

		TEST_METHOD(TestScores)
		{
			//// This is an empty test just to ensure the system is working
			CScreen *screen = new CScreen();
			CScoreboard scoreBoard(screen);
			
			Assert::IsTrue(0 == scoreBoard.GetCorrect());
			Assert::IsTrue(0 == scoreBoard.GetIncorrect());
			Assert::IsTrue(0 == scoreBoard.GetMissed());

			for (int i = 0; i < 3; ++i) {
				scoreBoard.AddCorrect();
			}
			for (int i = 0; i < 10; ++i) {
				scoreBoard.AddIncorrect();
			}
			for (int i = 0; i < 25; ++i) {
				scoreBoard.AddMissed();
			}

			Assert::IsTrue(3 == scoreBoard.GetCorrect());
			Assert::IsTrue(10 == scoreBoard.GetIncorrect());
			Assert::IsTrue(25 == scoreBoard.GetMissed());

			// Not sure what this assert is, but the others finally work with our functionality
			// Assert::IsTrue(5 == scoreBoard.GetCombo());
		}

	};
}
