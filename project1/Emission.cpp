/**
* \file Emission.cpp
*
* \author Tianrui Liu
*/

#include "pch.h"
#include "Emission.h"

using namespace std;
using namespace Gdiplus;

/* Constructor for Emission objects
* \param graphics the gdi+ graphics object to display to */
void CEmission::Draw(Gdiplus::Graphics* graphics)
{
	double wid = mImage->GetWidth();
	double hit = mImage->GetHeight();

	graphics->DrawImage(mImage.get(),
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)mImage->GetWidth(), (float)mImage->GetHeight());
}

/* Draws the emissions
* \param graphics the gdi+ graphics object to display to
* \param width width of emission
* \param height height of emission
*/
void CEmission::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
	SolidBrush brush(Color::LavenderBlush);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXset = width / 2.0f;
	mYset = 0;
	if (height > Height * mScale) {
		mYset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform(float(mXset), float(mYset));
	graphics->ScaleTransform(float(mScale), float(mScale));

}

/* Changes x and y locations on left button down
* \param x x-axis location
* \param y y-axis location
*/
void CEmission::OnLButtonDown(int x, int y)
{
	double oX = (x - mXset) / mScale;
	double oY = (y - mYset) / mScale;

}

/* Adds emission to items
* \param emission item to add to emissions vector
*/
void CEmission::Add(std::shared_ptr<CEmission> emission)
{
	mItemsEmission.push_back(emission);
}
