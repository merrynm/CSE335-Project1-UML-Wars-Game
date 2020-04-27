/**
* \file Pens.cpp
*
* \author Team Zuse
*/

#include "pch.h"
#include "Pens.h"
#include <memory>

using namespace std;
using namespace Gdiplus;

/// Pen filename 
const wstring PenImageName = L"images/redpen.png";

/** Constructor
 * \param screen The screen this is a member of
*/
CPens::CPens(CScreen* screen) : CImageObject(screen, PenImageName, ScreenLayers::PenLayer)
{
}

/**
 * Update our pen location
 * \param elapsed time elapsed
 */
void CPens::Update(double elapsed)
{
	if (mShot)
	{
		mV.SetX(mSpeed * cos(-mShootAngle-1.078));
		mV.SetY(mSpeed * sin(-mShootAngle-1.078));

		CVector currP;
		currP.SetX(GetX());
		currP.SetY(GetY());

		CVector newP = currP + mV * elapsed;

		SetLocation(newP.X(), newP.Y());
	}
}

/**
 * Freeze pen on pause
 * \param paused if screen paused
 */
void CPens::PauseObject(bool paused)
{
	if (paused)
	{
		mSpeed = 0;
	}

	else
	{
		mSpeed = 700;
	}
}
