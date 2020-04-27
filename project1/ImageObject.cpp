/**
 * \file ImageObject.cpp
 *
 * \author Jonathan Skidmore
 */

#include "pch.h"
#include "ImageObject.h"

using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

 /** Constructor
 * \param screen the screen this item is a member of
 * \param filename The filename of the image this object will use
 */
CImageObject::CImageObject(CScreen* screen, const std::wstring& filename, ScreenLayers layer) : CScreenObject::CScreenObject(screen, layer)
{
	mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mItemImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}

/*
* Draws the image object on the graphics
* \param graphics the graphics to draw to
*/
void CImageObject::Draw(Gdiplus::Graphics* graphics)
{
	double x = GetX();
	double y = GetY();
	double angle = GetAngle();

	float wid = (float)mItemImage->GetWidth();
	float hit = (float)mItemImage->GetHeight();

	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform(float(-angle * RtoD));
	graphics->DrawImage(mItemImage.get(), -wid / 2, -hit / 2, wid, hit);
	graphics->Restore(state);
}

/**
 *  Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CImageObject::HitTest(int x, int y)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image.
	// Subtracting the center makes x, y relative to the center of 
	// the image. Adding half the size makes x, y relative to the top 
	// corner of the image.
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}

	// Test to see if x, y are in the drawn part of the image
	auto format = mItemImage->GetPixelFormat();
	if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
	{
		// This image has an alpha map, which implements the 
		// transparency. If so, we should check to see if we
		// clicked on a pixel where alpha is not zero, meaning
		// the pixel shows on the screen.
		Color color;
		mItemImage->GetPixel((int)testX, (int)testY, &color);
		return color.GetAlpha() != 0;
	}
	else {
		return true;
	}
}