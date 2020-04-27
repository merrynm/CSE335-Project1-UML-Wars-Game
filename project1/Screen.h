/**
 * \file Screen.h
 *
 * \author Team Zuse
 *
 * Class that displays the main game screen.
 *
 */

#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "Scoreboard.h"
#include "ScreenObject.h"
#include "UmlBadAttribute.h"
#include "Player.h"
#include "EmitUml.h"
#include "Pause.h"
#include "UmlBox.h"
#include "UmlPopUp.h"
#include "LoadUml.h"
#include "ScreenLayers.h"

/// Classes to include
class CUmlBox;

/**Class for the Game Screen
*/
class CScreen
{
public:

	/// Game area in virtual pixels
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

	CScreen(); ///< Constructor

	void Load(); ///< Load the uml

	virtual ~CScreen(); ///< Destructor

	CScreen(const CScreen&) = delete; ///< Deleted constructor

	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return Width; }

	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return Height; }

	/// Get the number of screenObjects on the screen
	/// \returns the number of screenObjects
	int GetScreenObjectCount() const { return (int)mScreenObjects.size(); }

	/// Sets screen background to pause state
	void SetPause() { mPause = !mPause; }

	/// Getter for pause bool
	/// \return bool
	bool GetPause() { return mPause; }

	/// Draws the screen
	void Draw(Gdiplus::Graphics* graphics, int width, int height);

	/// Adds a screen object
	/// \param newScreenObject new screen object item
	void AddScreenObject(std::shared_ptr<CScreenObject> newScreenObject);

	/// Removes a screen object
	/// \param target existing screen object item
	void RemoveScreenObject(std::shared_ptr<CScreenObject> target);

	/// Hit test for screen
	bool HitTest(int x, int y);

	// Updates the time elapsed for UML
	void Update(double elapsed);

	/// Rotate Screen Objects
	/// \param point system point x/y
	void RotateScreenObjects(CPoint point);

	/// Sorts screen objects by their screen layer
	void SortScreenObjects();

	/// Shoot pen & set timer to regenerate
	void Shoot();

	/// Scales the mouse position to the screen size
	/// \param point to scale
	/// \return CPoint the point
	CPoint FixMouseCoordinates(CPoint& point);

	/// Determines if two screen items collided
	void Collision();
	
	///Getter for Screen X value
	/// \return double X value of screen
	double GetScreenX() { return mScreenX; }

	///Getter for Screen Y value
	/// \return double Y value of screen
	double GetScreenY() { return mScreenY; }

	/// On screen paused
	void OnPause();

	/// Add screen object to vector
	/// \param item screen object item
	void Add(std::shared_ptr<CScreenObject> item);
	
	///Setter for new box speed
	/// \param speed
	void SetNewSpeed(double speed) { mNewSpeed = speed; }

	/// Getter for new box speed
	/// \return new speed
	double GetNewSpeed() { return mNewSpeed; }
	
private:
	///The scale
	float mScale = 1;

	/// X offset
	float mXOffset = Width/2;

	///Y offset
	float mYOffset = Height/2;

	/// Screen pixels X value
	double mScreenX = mVirtualX * mScale + mXOffset;

	/// Screen pixels X value
	double mScreenY = mVirtualY * mScale + mYOffset;

	/// Virtual pixels X value
	double mVirtualX = (mScreenX - mXOffset) / mScale;

	/// Virtual pixels Y value
	double mVirtualY = (mScreenY - mYOffset) / mScale;

	/// turn on pause state if true
	bool mPause = false;

	/// X location of the pen
	double mPenX = 0;

	/// Y location of the pen
	double mPenY = 700;

	/// All of the items to populate our Screen
	std::vector<std::shared_ptr<CScreenObject> > mScreenObjects;

	/// The Scoreboard
	CScoreboard *mScoreboard;

	/// The Pop Up
	std::shared_ptr<CUmlPopUp> mPopUp = std::make_shared<CUmlPopUp>(this);

	/// The Player
	std::shared_ptr<CPlayer> mPlayer = std::make_shared<CPlayer>(this);

	///Make a uml box
	std::shared_ptr<CUmlBox> mUmlbox = std::make_shared<CUmlBox>(this);

	///Emit UML box
	std::shared_ptr<CEmitUml> mEmitUml = std::make_shared<CEmitUml>(this);

	///Make a pointer to load the uml class
	std::shared_ptr<CLoadUml> mLoadUml = std::make_shared<CLoadUml>();

	///Elapsed time
	double mElapsed;

	/// default box speed multiplier
	double mNewSpeed = 1.0;

	/// check if pop up exists now
	bool mPopUpExists = false;


};


