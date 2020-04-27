/**
 * \file Player.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include <string>
#include "Player.h"

using namespace Gdiplus;
using namespace std;

/// Player filename
const wstring PlayerImageName = L"images/harold.png";

/**
* Constructor
* \param screen Screen this Player is a member of
*/
CPlayer::CPlayer(CScreen* screen) : CImageObject(screen, PlayerImageName, ScreenLayers::PlayerLayer)
{
	screen->AddScreenObject(mPen);
	mPen->SetLocation(GetX() + 29, GetY() - 54);
	mPen->SetAngle(-1.078);
}

/**
 * Rotate our Player
 * \param point Vector of mouse location
 */
void CPlayer::RotateImage(CPoint point)
{
	double constant = point.x * (1.2 / 600);
	SetAngle(-constant);
	if (!mPen->GetShot())
	{
		mPen->SetAngle(-1 - constant);
		mPen->SetLocation(61.3 * cos(constant - 1.078), 850 + 61.3 * sin(constant - 1.078));
	}
}

/**
 * Shoot the pen in Player's hand
 */
void CPlayer::ShootPen()
{
	if (!mEmptyHanded)
	{
		mPen->SetShootAngle(GetAngle());
		mPen->SetShot();
		mEmptyHanded = true;
	}
}

/**
 * Track time since pen shot
 * \param elapsed time elapsed
 */
void CPlayer::Update(double elapsed)
{
	if (mEmptyHanded)
	{
		mElapsed += elapsed;
	}
}

/**
 * Generate new pen
 */
void CPlayer::Regenerate(std::shared_ptr<CPens> pen)
{
	mHold = mPen;
	mPen = pen;
	mPen->SetAngle(-1 + GetAngle());
	mPen->SetLocation(61.3 * cos(-GetAngle() - 1.078), 850 + 61.3 * sin(-GetAngle() - 1.078));
	mEmptyHanded = false;
	mElapsed = 0;
}



