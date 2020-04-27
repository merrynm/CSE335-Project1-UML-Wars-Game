#include "pch.h"
#include "CppUnitTest.h"
#include "Screen.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const unsigned int RandomSeed = 1234567890;

namespace Testing
{
	TEST_CLASS(CScreenTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir+'\0');
		}
		
		// Test the constructor
		TEST_METHOD(TestCScreenConstruct)
		{
			CScreen screen;
		}

		TEST_METHOD(TestCScreenHitTest)
		{
			CScreen screen;
			/// Ensure hit test returns false outside of the screen
			Assert::IsFalse(screen.HitTest(-1, 0));
			Assert::IsFalse(screen.HitTest(0, -1));
			Assert::IsFalse(screen.HitTest(-1, -1));
			Assert::IsFalse(screen.HitTest(2000, 100));
			Assert::IsFalse(screen.HitTest(100, 2000));
			Assert::IsFalse(screen.HitTest(2000, 2000));

			/// Esure that hit test returns true within the screen
			Assert::IsTrue(screen.HitTest(500, 500));
		}

		TEST_METHOD(TestCScreenAddObject)
		{
			CScreen screen;

			//TestPopulation(0, &screen);
			Populate(3, &screen);
			TestPopulation(3, &screen);
		}

		TEST_METHOD(TestCScreenEmpty)
		{
			CScreen screen;

			TestPopulation(0, &screen);
		}

		TEST_METHOD(TestCScreenPointConversion)
		{
			CScreen screen;

			// find expected result
			int x = -1250 / 2;
			int y = -1000 / 2;

			TestCoordinateConversion(0, 0, x, y, &screen);
		}

		void Populate(int num, CScreen *screen)
		{
			for (int i = 0; i < num; i++)
			{
				srand(RandomSeed);
				shared_ptr<CPens> obj = make_shared<CPens>(screen);
				obj->SetLocation(100, 200);
				screen->AddScreenObject(obj);
			}
		}

		void TestPopulation(int expected, CScreen *screen)
		{
			int count = screen->GetScreenObjectCount();
			// add 3 because of items on every screen (player, pen, scoreboard)
			Assert::AreEqual(count, expected + 3);
		}

		void TestCoordinateConversion(int x, int y, int actualX, int actualY, CScreen *screen)
		{
			CPoint p1(x, y);
			CPoint p2(actualX, actualY);
			screen->FixMouseCoordinates(p1);
			Assert::AreEqual(p1.x, p2.x);
			Assert::AreEqual(p1.y, p2.y);
		}
	};
}