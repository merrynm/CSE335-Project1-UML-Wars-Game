/**
 * \file Screen.cpp
 *
 * \author Merryn Marderosian, Becky Henning, Ruchika Gupta, Jonathan Skidmore, Tianrui Liu
 */

#include "pch.h"
#include "Screen.h"
#include "ScreenObject.h"
#include "XmlNode.h"
#include "UmlBadAttribute.h"
#include <memory>
#include "Player.h"
#include <algorithm>
#include "UmlBox.h"
#include "IsPenVisitor.h"
#include "IsUmlVisitor.h"
#include "IsPlayerVisitor.h"
#include "IsBadUmlVisitor.h"

using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

/// Filename for the pause screen image
const static wstring UmlFilename = L"images/uml.xml";

/// 1 second has passed
const int sec = 1;

/// A Pen object Visitor
CIsPenVisitor penVisitor;

/// A UML object Visitor
CIsUmlVisitor umlVisitor;

/// A Player object Visitor
CIsPlayerVisitor playerVisitor;

/// A Bad UML object Visitor
CIsBadUmlVisitor badUmlVisitor;

/** Game Screen Constructor
 */
CScreen::CScreen()
{
	mScreenObjects.push_back(mUmlbox);
	mScreenObjects.push_back(mPlayer);
	mScoreboard = new CScoreboard(this);
}

void CScreen::Load() {
	mLoadUml->UMLLoad(UmlFilename.c_str());
}

CScreen::~CScreen()
{
}

/**
 * Draw the game area
 * \param graphics The GDI+ graphics context to draw on
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CScreen::Draw(Gdiplus::Graphics* graphics, int width, int height)
{
	// Sort screen objects by screen layer
	SortScreenObjects();

	// Fill the background with black
	Color backgroundColor = Color(255, 25, 250, 250); // color of background, we are using white for now
	SolidBrush brush(backgroundColor);
	graphics->FillRectangle(&brush, 0, 0, width, height);

	//
	// Automatic Scaling
	//
	float scaleX = float(width) / float(Width);
	float scaleY = float(height) / float(Height);
	mScale = min(scaleX, scaleY);

	mXOffset = width / 2.0f;
	mYOffset = 0;
	if (height > Height * mScale) {
		mYOffset = (float)((height - Height * mScale) / 2);
	}

	graphics->TranslateTransform(mXOffset, mYOffset);
	graphics->ScaleTransform(mScale, mScale);

	// From here on you are drawing virtual pixels
	// Currently not working correctly? Debugging in progress. 

	for (auto i : mScreenObjects)
	{
		i->Draw(graphics);
	}

	// tell the scoreboard to draw itself
	if (mScoreboard != nullptr)
		mScoreboard->Draw(graphics);
	else
		mScoreboard = new CScoreboard(this);

}

/* Adds a ScreenObject to this screen
* \param newScreenObject the screen object to add*/
void CScreen::AddScreenObject(std::shared_ptr<CScreenObject> newScreenObject)
{
	mScreenObjects.push_back(newScreenObject);
}

/* Removes a ScreenObject from this screen
* \param target the screen object to remove*/
void CScreen::RemoveScreenObject(std::shared_ptr<CScreenObject> target)
{
	int index = 0;
	for (auto i : mScreenObjects)
	{
		if (i == target)
		{
			mScreenObjects.erase(mScreenObjects.begin() + index);
		}
		index++;
	}
}

/** Test an x,y click location to see if it clicked
* on some item in the aquarium.
* \param x X location
* \param y Y location
* \returns boolean whether the x and y coordinates are within the screen.
*/
bool CScreen::HitTest(int x, int y)
{
	if ((x >= 0 && x <= (mXOffset * 2)) && (y >= 0 && y <= (mYOffset * 2)))
		return true;
	return false;
}


/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CScreen::Update(double elapsed)
{
	for (auto item : mScreenObjects)
	{
		item->Update(elapsed);

		item->Accept(&penVisitor);

		if (penVisitor.IsPenVisitor())
		{
			mPenX = item->GetX();
			mPenY = item->GetY();
		}
		penVisitor.Reset();
	}

	Collision();

	if (mPlayer->IsEmptyHanded() && mPlayer->GetElapsedTime() > sec)
	{
		if (mPlayer->GetHold() != nullptr)
		{
			RemoveScreenObject(mPlayer->GetHold());
		}
		shared_ptr<CPens> mPen = std::make_shared<CPens>(this);

		mPen->SetPaused(mPause);

		if (!mPause)
		{
			AddScreenObject(mPen);
			mPlayer->Regenerate(mPen);
		}
	}

	// delete old hit UML
	vector<shared_ptr<CScreenObject>> oldUml;
	for (auto i : mScreenObjects)
	{
		if (i != nullptr)
		{
			i->Accept(&umlVisitor);
		}
		if (umlVisitor.IsOldUml())
		{
			i->SetLocation(0, 0);
			oldUml.push_back(i);
			if (mPopUpExists)
			{
				RemoveScreenObject(mPopUp);
				mPopUpExists = false;
			}
		}
		umlVisitor.Reset();
	}
	for (auto j : oldUml)
	{
		RemoveScreenObject(j);
	}

	//Calls the update on the object
	mEmitUml->Update(elapsed);

}

/* Rotates screen objects
*/
void CScreen::RotateScreenObjects(CPoint point)
{
	if (!mPause)
	{
		mPlayer->RotateImage(point);
	}
}

/* Function to sort screen objects by their screen layer
*/
void CScreen::SortScreenObjects()
{
	std::sort(mScreenObjects.begin(), mScreenObjects.end(), CScreenObject::CompareLayer);
}

void CScreen::Shoot()
{
	if (!mPause)
	{
		mPlayer->ShootPen();
	}
}

CPoint CScreen::FixMouseCoordinates(CPoint& point)
{
	point.x = long((point.x - mXOffset) / mScale);
	point.y = long((point.y - mYOffset) / mScale);
	return point;
}

/*
* Determines if two screen objects have collided. If collision occurs,
*  calls function in screen object to deal with collision
*/
void CScreen::Collision()
{

	for (unsigned int index = 0; index < mScreenObjects.size()-1; index++)
	{
		auto object = mScreenObjects[index];

		object->Accept(&penVisitor);
		object->Accept(&umlVisitor);
		object->Accept(&playerVisitor);
		if (penVisitor.IsPenVisitor())
		{
			if (HitTest(int(object->GetX()), int(object->GetY()))) //&& object->GetShot())
			{
				mPenX = object->GetX();
				mPenY = object->GetY();
			}
		}
		else if (umlVisitor.IsUmlVisitor() && !umlVisitor.IsOldUml())
		{
			object->Accept(&badUmlVisitor);

			double minX = object->GetX();
			double maxX = object->GetX() + object->GetWidth();
			double minY = object->GetY();
			double maxY = object->GetY() + object->GetHeight();

			if ((mPenX >= minX && mPenX <= maxX) && (mPenY >= minY && mPenY <= maxY) && mPlayer->IsEmptyHanded())
			{
				//delete the pen on hit:
				for (auto x : mScreenObjects)
				{
					penVisitor.Reset();
					x->Accept(&penVisitor);
					/// Need some way to tell apart pens that have been shot then 
					// this can be completed so that pens delete on impact
					if (penVisitor.VisitedShotPen() && x->GetX() == mPenX && x->GetY() == mPenY)
					{
						AddScreenObject(mPopUp);
						mPopUpExists = true;
						mPopUp->SetBad(badUmlVisitor.GetBadAtt());
						mPopUp->SetLocation(object->GetX(), object->GetY());

						if (badUmlVisitor.GetBadAtt() != L"")
						{
							mScoreboard->AddCorrect();
						}
						else
						{
							mScoreboard->AddIncorrect();
						}

						RemoveScreenObject(x);
						object->SetHit();
						index--;
						index--;
						break;
					}
				}

			}

			if (minY >= Height)
			{
				if (badUmlVisitor.GetBadAtt() != L"")
				{
					mScoreboard->AddMissed();
				}
				RemoveScreenObject(object);
				index--;
			}

		}

		badUmlVisitor.Reset();
		penVisitor.Reset();
		umlVisitor.Reset();
		playerVisitor.Reset();
	}
}

void CScreen::OnPause()
{
	mPause = !mPause;
	for (auto object : mScreenObjects)
	{
		object->PauseObject(mPause);
	}

}

void CScreen::Add(std::shared_ptr<CScreenObject> item)
{
	mScreenObjects.push_back(item);
}
