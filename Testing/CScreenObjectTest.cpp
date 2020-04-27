#include "pch.h"
#include "CppUnitTest.h"
#include "ScreenObject.h"
#include "Screen.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const wstring PlayerImageName = L"images/harold.png";
const wstring PenImageName = L"images/redpen.png";

namespace Testing
{
	TEST_CLASS(EmptyTest3)
	{
	public:

		TEST_METHOD(TestNothing)
		{
		}
	};
	/** Mock class for testing CItem */
	class CScreenObjectMock : public CScreenObject
	{
	public:
		CScreenObjectMock(CScreen* screen) : CScreenObject(screen, ScreenLayers::Background) {}

		/** Draw the item
		* \param graphics The graphics context to draw on */
		virtual void Draw(Gdiplus::Graphics* graphics) {}
		virtual void RotateImage(CPoint point) {}
	};

	TEST_CLASS(CScreenObjectTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir + '/0');
		}
		
		TEST_METHOD(TestCScreenObjectConstruct)
		{
			CScreen screen;
			CScreenObjectMock screenObject(&screen);
		}

		TEST_METHOD(TestCScreenObjectHitTest)
		{
			// Screen object hit test was moved to CImageObject, so cannot produce
			// meaningful results since we changed the design in the last week.
			// This test was meaningful as of the last week of the project, but since
			// that point has been invalidated. We would write a new test but it wouldn't
			// count towards our grade anyways because it is the last week of the project.

			//HAVE RECREATED THIS TEST IN CImageObject testing class!! Same code - but using our new functionality

			//// Create a screen object to test
			//CScreen screen;
			//CScreenObjectMock screenObject(&screen);

			//// give it a location
			//// always make the numbers different, in case they are mixed up
			//screenObject.SetLocation(100, 200);

			//// center of the object should be a true
			//Assert::IsTrue(screenObject.HitTest(100, 200));

			//// left of the object
			//Assert::IsFalse(screenObject.HitTest(10, 200));

			//// right of the object
			//Assert::IsFalse(screenObject.HitTest(200, 200));

			//// above the object
			//Assert::IsFalse(screenObject.HitTest(100, 0));

			//// below the object
			//Assert::IsFalse(screenObject.HitTest(100, 300));

			//// of item transparent pixel
			//Assert::IsFalse(screenObject.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
		}

		TEST_METHOD(TestCScreenObjectGettersSetters)
		{
			CScreen screen;
			CScreenObjectMock screenObject(&screen);

			screenObject.SetLocation(300, 300);
			// ensure expected results
			Assert::AreEqual(300, screenObject.GetY(), 0.0001);
			Assert::AreEqual(300, screenObject.GetX(), 0.0001);
			// ensure that the returned coordinates are meaningful
			Assert::IsTrue(1000 != screenObject.GetY());
			Assert::IsTrue(1000 != screenObject.GetX());
		}

	};
}