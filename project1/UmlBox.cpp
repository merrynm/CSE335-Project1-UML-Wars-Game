/**
 * \file UmlBox.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "UmlBox.h"
#include <algorithm>
#include <memory>
#include "Screen.h"
#include "LoadUml.h"
#include "TextObject.h"

using namespace Gdiplus;
using namespace std;

/// Maximum speed in the Y direction in pixels per second
const double MaxSpeedY = 100;

/// Minimum allowed Y value
const double MinSpeedY = 50;

/// How long the box stops before deleting after being hit
const double StopOnDelete = 1;

/// maximum attributes on a uml box
const int MaxAttributes = 3;
/// maximum operations on a uml box
const int MaxOperations = 3;
/// total number of attributes to choose from
const int MaxAttIndex = 15;
/// total number of operations to choose from
const int MaxOperIndex = 10;

int CUmlBox::mAmountBadModifier = 0;

/** Constructor
 * \param screen The screen this is a member of
*/
CUmlBox::CUmlBox(CScreen* screen) : CTextObject(screen, ScreenLayers::UmlLayer, L"", 12)
{
	mScreen = screen;

	//Call set speed

	SetLocation(-550 + ((double)rand() / RAND_MAX) * 650, 0);

	SetSpeed(((double)rand() / RAND_MAX) * 70 * 2 - 80, 90 + ((double)rand() / RAND_MAX) * 100);

	auto att = mLoadUml->Name(0);

	int startPos = mAmountBadModifier +(int)(((double)rand() / RAND_MAX) * 7);
	//int startPos = 1;
	
	//Make it go from 1 instead of 0 as doesn't index it properly.
	int nameAmount = startPos + 1;

	//int operationAmount = startPos + 1;
	int operationAmount = startPos + 1 + (int)(((double)rand() / RAND_MAX) * MaxOperations);
	operationAmount = operationAmount < MaxOperIndex ? operationAmount : MaxOperIndex;

	//int attributeAmount = startPos + 1;
	int attributeAmount = startPos + 1 + (int)(((double)rand() / RAND_MAX) * MaxAttributes);
	attributeAmount = attributeAmount < MaxAttIndex ? attributeAmount : MaxAttIndex;

	//randomize the vector
	mLoadUml->Attribute();

	for (int i = startPos; i < nameAmount; i++)
	{
		mName.push_back(mLoadUml->Name(i));
	}
	for (int j = startPos; j < attributeAmount; j++)
	{
		mAtt.push_back(mLoadUml->Att(j));
	}
	for (int k = startPos; k < operationAmount; k++)
	{
		mOper.push_back(mLoadUml->Op(k));
	}

	//for (int y = mAmountBadModifier; y < attributeAmount; y++) {
	//	mOper.push_back(mLoadUml->Op(y));

	//}
	//for (int i = mAmountBadModifier; i < nameAmount; i++) {

	//	//push back a load uml attribute
	//	auto att = mLoadUml->Att(i);
	//	mAtt.push_back(att);

	//	mName.push_back(mLoadUml->Name(i));
	//}
	
}


/** Draw function that draws UML boxes on our screen
 * \param graphics
*/
void CUmlBox::Draw(Gdiplus::Graphics* graphics)
{
	std::vector<UmlBadAttribute> value;
	if (mBoxHeight == 0)
		SetGdiplus(graphics);

	Gdiplus::RectF size;
	Gdiplus::PointF origin(0.0f, 0.0f);

	double yOffset = GetY() + mNameHeight;

	Pen pen(Color(0, 0, 0), 3);
	SolidBrush black(Color(0, 0, 0));
	SolidBrush yellow(Color(255, 255, 193));

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 13);

	auto save = graphics->Save();

	Gdiplus::Rect rect(int(GetX()), int(GetY()), mBoxWidth, mBoxHeight);
	graphics->FillRectangle(&yellow, rect);
	graphics->DrawRectangle(&pen, rect);

	
	graphics->DrawString(mName[0].GetName().c_str(), -1, &font, PointF(Gdiplus::REAL(GetX() + (mBoxWidth - mNameWidth) / 2), Gdiplus::REAL(GetY())), &black);
	graphics->DrawLine(&pen, PointF(Gdiplus::REAL(GetX()), Gdiplus::REAL(GetY() + mNameHeight)), PointF(Gdiplus::REAL(GetX() + mBoxWidth), Gdiplus::REAL(GetY() + mNameHeight)));

	for (auto item : mAtt) {
		graphics->DrawString(item.GetName().c_str(), -1, &font, PointF(Gdiplus::REAL(GetX()), Gdiplus::REAL(yOffset)), &black);
		graphics->MeasureString(item.GetName().c_str(), -1, &font, origin, &size);
		yOffset += (int)size.Height;
	}
	graphics->DrawLine(&pen, PointF(Gdiplus::REAL(GetX()), Gdiplus::REAL(yOffset)), PointF(Gdiplus::REAL(GetX() + mBoxWidth), Gdiplus::REAL(yOffset)));

	for (auto item : mOper) {
		graphics->DrawString(item.GetName().c_str(), -1, &font, PointF(Gdiplus::REAL(GetX()), Gdiplus::REAL(yOffset)), &black);
		graphics->MeasureString(item.GetName().c_str(), -1, &font, origin, &size);
		yOffset += (int)size.Height;
	}

	graphics->Restore(save);
}

/** Update
 * \param elapsed The elapsed time
*/
void CUmlBox::Update(double elapsed)
{
	if (!mPause)
	{
		mModifier = mScreen->GetNewSpeed();
	}

	if (mHit)
	{
		mTimeSinceHit += elapsed;
	}
	else
	{
		SetLocation(GetX() + mSpeedX * elapsed * mModifier,
			GetY() + mSpeedY * elapsed * mModifier);
	}
}


/** Set GDI Plus
 * \param graphics
*/
void CUmlBox::SetGdiplus(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 13);
	Gdiplus::RectF size;
	Gdiplus::PointF origin(0.0f, 0.0f);
	

	graphics->MeasureString(mName[0].GetName().c_str(), -1, &font, origin, &size);
	mNameHeight = ((int)size.Height > 1) ? (int)size.Height : 25;
	mNameWidth = (int)size.Width;
	mBoxHeight += mNameHeight;
	mBoxWidth = (int)size.Width;

	for (UmlBadAttribute attribute : mAtt)
	{
		graphics->MeasureString(attribute.GetName().c_str(), -1, &font, origin, &size);
		mBoxHeight += (int)size.Height;
		mAttributeHeight += (int)size.Height;

		if ((int)size.Width > mBoxWidth)
			mBoxWidth = (int)size.Width;
		if ((int)size.Width > mAttributesWidth)
			mAttributesWidth = (int)size.Width;
	}

	for (UmlBadAttribute operation : mOper)
	{
		graphics->MeasureString(operation.GetName().c_str(), -1, &font, origin, &size);
		mBoxHeight += (int)size.Height;
		mOperationHeight += (int)size.Height;

		if ((int)size.Width > mBoxWidth)
			mBoxWidth = (int)size.Width;
		if ((int)size.Width > mOperationsWidth)
			mOperationsWidth = (int)size.Width;
	}

	if (mBoxHeight == 0)
		mBoxHeight = 10;

	if (mBoxWidth == mNameHeight)
		mBoxWidth += 50;
}


/** Pause functionality for the UML boxes on the screen
 * \param pause The current pause state of the game
*/
void CUmlBox::PauseObject(bool pause)
{
	mPause = pause;

	if (pause)
	{
		mPrevModifier = mModifier;
		mModifier = 0.0;
	}

	else
	{
		mModifier = mPrevModifier;
	}
}

/* Gets a string which is the reason this uml is bad, or the empty string if it is good
* \return wstring the reason this uml is bad if it is bad */
wstring CUmlBox::GetBad()
{
	wstring reason = L"";
	for (auto i : mAtt)
	{
		reason = i.GetBad() != L"" ? i.GetBad() : reason;
	}
	for (auto j : mName)
	{
		reason = j.GetBad() != L"" ? j.GetBad() : reason;
	}
	for (auto k : mOper)
	{
		reason = k.GetBad() != L"" ? k.GetBad() : reason;
	}
	return reason;
}


