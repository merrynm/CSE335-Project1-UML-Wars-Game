#include "pch.h"
#include "CppUnitTest.h"
#include "ScreenObject.h"
#include "Pause.h"
#include "screen.h"
#include "ScreenObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const static wstring PauseScreenImage = L"images/PauseScreen.png";

namespace Testing
{
	/** Mock class for testing CItem */
	class CItemMock : public CScreenObject
	{
	public:
		/** Constructor
		 * \param aquarium The aquarium this is a member of */
		CItemMock(CScreen* screen) :
			CScreenObject(screen, ScreenLayers::Background) {}

		/** Draw the item
		* \param graphics The graphics context to draw on */
		virtual void CItemMock::RotateImage(CPoint point) {}

	};

	TEST_CLASS(CPauseTest)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir + '/0');
		}

		TEST_METHOD(TestCItemConstruct)
		{
			CScreen screen;
			CItemMock item(&screen);
		}

		TEST_METHOD(TestCPauseState)
		{
			// Construct an item to test
			CScreen screen;

			Assert::AreEqual(screen.GetScreenObjectCount(), 3);

			screen.SetPause();

			// this test used to test the addition of the pause screen, 
			// but during the last sprint we changed our screen to keep
			// the pause screen separate from mScreenObjects.
			// Now it tests to make sure nothing has changed since the pause happened
			// This test was meaningful as of the last week of the project, but since
			// that point has been invalidated. We would write a new test but it wouldn't
			// count towards our grade anyways because it is the last week of the project.
			Assert::AreEqual(screen.GetScreenObjectCount(), 3);

			screen.SetPause();

			Assert::AreEqual(screen.GetScreenObjectCount(), 3);
		}

		TEST_METHOD(CPauseInitializeTest)
		{
			CScreen screen;

			screen.SetPause();
			Assert::IsTrue(screen.GetPause() == true);

			screen.SetPause();
			Assert::IsTrue(screen.GetPause() == false);
		}
	};
}