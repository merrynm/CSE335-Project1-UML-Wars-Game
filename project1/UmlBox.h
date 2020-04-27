/**
 * \file UmlBox.h
 *
 * \author Team Zuse
 *
 * Class that displays the UML box.
 *
 */

#pragma once


#include "Screen.h"
#include <algorithm> 
#include "ScreenObject.h"
#include "LoadUml.h"
#include <memory>

/// Time box remains on the screen after being hit
const double hitStopTime = 1;

/** Class that describes UML boxes
*/
class CUmlBox : public CTextObject
{
public:
	/// delete default constructor
	CUmlBox() = delete;

	/// delete constructor 
	CUmlBox(const CUmlBox&) = delete;

	/// Constructor
	CUmlBox(CScreen* screen);

	/// draws the draw to the graphics passed as a parameter
	void Draw(Gdiplus::Graphics* graphics);

	/// Updates the time elapsed
	virtual void Update(double elapsed) override;

	/// Set graphics
	void SetGdiplus(Gdiplus::Graphics* graphics);

	/// Handle rotation for animation
	/// \param point system point of mouse on screen
	virtual void RotateImage(CPoint point) {}

	/// Sets speed in X and Y direction
	/// \param x the x value
	/// \param y the y value
	void SetSpeed(double x, double y) { mSpeedX = x, mSpeedY = y; }

	/// Gets box height
	/// \return height of box
	double GetHeight() override { return mBoxHeight; }

	/// Gets box width
	/// \return width of box
	double GetWidth() override { return mBoxWidth; }

	/// Accepts the visitor
	/// \param visitor a uml visitor
	virtual void Accept(CVisitor* visitor) override { visitor->VisitUml(this); }

	/// Pause uml
	virtual void PauseObject(bool pause) override;

	/// Return string attribute of bad
	/// \return wstring bad attribute
	wstring GetBad();

	/// Tells whether this UML box was hit by the pen
	/// \return bool whether it has been hit
	bool IsOld() { return mTimeSinceHit > hitStopTime; }

	/// Tells the UML to stop moving for a set amount of time and then remove itself
	void SetHit() { PauseObject(true); mHit = true; mTimeSinceHit = 0; }
	//CLoadUml loaduml;

private:
	/// Bad attribute
	UmlBadAttribute mAttribute;

	/// Bad operation
	UmlBadAttribute mOperation;

	/// The Game screen
	CScreen* mScreen;
	
	/// UML box speed in the X direction
	double mSpeedX;
	
	/// UML box speed in the Y direction
	double mSpeedY;

	/// Speed multiplier. Set to 0 when game is paused, otherwise set to 1.
	double mModifier = 1.0;

	/// Stores previous value of modifier if we pause the game
	double mPrevModifier;

	/// Current Pause State
	bool mPause = false;

	/// Current hit state
	bool mHit = false;

	/// Amount of time that has passed since being hit
	double mTimeSinceHit = 0;

	/// height of the box
	int mBoxHeight = 0;

	/// Width of UML box
	int mBoxWidth = 0;

	///Height of name
	int mNameHeight;

	/// Width of name
	int mNameWidth;

	/// Height of attribute
	int mAttributeHeight;

	/// Width of attribute
	int mAttributesWidth;

	/// Height of operation
	int mOperationHeight;

	/// Width of operation
	int mOperationsWidth;

	/// If item drawn
	bool mDraw = false;

	/// The first three attributes that go inside our UML boxes
	std::vector<UmlBadAttribute> mAtt;

	/// The first three operations that go inside our UML boxes
	std::vector<UmlBadAttribute> mOper;

	/// The first three names that go inside our UML boxes
	std::vector<UmlBadAttribute> mName;
	
	/// Create a pointer to a load uml which is empty now
	std::shared_ptr<CLoadUml> mLoadUml = std::make_shared<CLoadUml>();

	/// amount of bad UML that spawns
	static int mAmountBadModifier;
};

