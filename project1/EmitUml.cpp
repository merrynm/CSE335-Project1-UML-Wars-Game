/**
 * \file EmitUml.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "EmitUml.h"
#include "UmlBox.h"
#include <algorithm>
#include "string"
#include <memory>
#include "UmlBadAttribute.h"
#include <vector>

using namespace Gdiplus;
using namespace std;

 /** Constructor
 * \param screen the screen this item is a member of
 */
CEmitUml::CEmitUml(CScreen* screen)
{
	//Update(double elapsed);
	//scren information stored in the mScreen member variable
	mScreen = screen;
}

/** Update function - adds more UML after elapsed time
* \param elapsed The time that has elapsed
*/
void CEmitUml::Update(double elapsed)
{
	// Update current pause state
	mPause = mScreen->GetPause();

	// If paused = false
	if (!mPause)
	{
		//The last time since you called update
		mTime += elapsed;
		if (mTime > 2) {
			std::shared_ptr<CUmlBox> umlbox = std::make_shared<CUmlBox>(mScreen);

			//mAttribute = mScreen->GetAttributes();
			//auto value = mScreen->GetAttributes();
		//	random_shuffle(mAttribute.begin(), mAttribute.end());
			//Adds the uml box to it
			mScreen->Add(umlbox);
			//Set the time back to 0 after you add it back
			mTime = 0;
		}
	}
}
