/**
 * \file Pause.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "Pause.h"

using namespace Gdiplus;
using namespace std;

///the pause screen image
const static wstring PauseScreenImage = L"images/PauseScreen.png";

/**
* Constructor
* \param screen Screen this Pause is a member of
*/
CPause::CPause(CScreen* screen) : CImageObject(screen, PauseScreenImage, ScreenLayers::TextLayer)
{
	SetLocation(0, 500);
}
