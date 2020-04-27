/**
 * \file ScreenObject.cpp
 *
 * \author Team Zuse
 */

#include <memory>
#include "pch.h"
#include "ScreenObject.h"
#include "ScreenLayers.h"

using namespace Gdiplus;
using namespace std;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/** Constructor
* \param screen the screen this item is a member of
*/
CScreenObject::CScreenObject(CScreen* screen, ScreenLayers layer) : mScreen(screen), mObjectLayer(layer)
{
}

/**
 * Destructor
 */
CScreenObject::~CScreenObject()
{
}

/**
 * Draw our player
 * \param graphics The graphics context to draw on, move it to an intermeditae class, pure virtual function
 */
void CScreenObject::Draw(Gdiplus::Graphics* graphics)
{
}

/**
 *  Test to see if we hit this object at a point, most classes are unhittable and will simply return false.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CScreenObject::HitTest(int x, int y)
{
	return false;
}