/**
 * \file ScreenObject.h
 *
 * \author Team Zuse
 *
 * Header file for ScreenObject
 */

#pragma once

#include <memory>
#include <string>
#include "Emission.h"
#include "Visitor.h"
#include "ScreenLayers.h"

class CScreen;

/** Base Class for a Screen Object
 */
class CScreenObject
{
public:
	/// default constructor (disabled)
	CScreenObject() = delete;

	/// copy constructor (disabled)
	CScreenObject(const CScreenObject&) = delete;

	/// destructor
	virtual ~CScreenObject();

	/// Tells the screen object to draw itself at (mX, mY) on the parameter graphics
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Returns adjustment for X direction
	/// \return mAdjust the adjustment for x direction
	virtual double GetXAdjust() { return mAdjust; }

	/// Tests if the screen object has a pixel in the specified coordinate
	virtual bool HitTest(int x, int y);

	/// Getter for the width of the screen object
	/// \returns width of this screen object
	virtual double GetWidth() { return 1.0; }

	/// Getter for the height of the screen object
	/// \returns height of this screen object
	virtual double GetHeight() { return 1.0; }

	/// Getter for the x position of the object
	/// \returns x, the x position
	double GetX() { return mX; }

	/// Getter for the y position of the object
	/// \returns y, the y position
	double GetY() { return mY; }

	/// Getter for the angle of the object
	/// \returns angle
	double GetAngle() { return mA; }

	/// Sets the location of this screen object to the parameter coordinates
	/// \param x the x position to move to
	/// \param y the y position to move to
	virtual void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Sets the angle of the image on screen
	/// \param angle the angle to rotate to
	virtual void SetAngle(double angle) { mA = angle; }

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}

	/// Allows us to tell if it is a shot pen (will only be called on pen objects)
	//virtual bool GetShot() { return false; } <- DO NOT USE. Causes the pen to not shoot.

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CVisitor* visitor) {};

	/// Base function for pausing 
	/// \param pause if screen paused
	virtual void PauseObject(bool pause) {};

	/// Function to tell an object it was hit with the pen
	virtual void SetHit() {};

	/// Get layer to draw image on
	/// \return the object layer number
	virtual ScreenLayers GetScreenLayer() { return mObjectLayer; };

	/// Compare two image layers to determine which is on top
	/// \param obj1 first item
	/// \param obj2 second item
	/// \return comparison
	static bool CompareLayer(std::shared_ptr<CScreenObject> obj1, std::shared_ptr<CScreenObject> obj2) { return ((int)obj1->GetScreenLayer() < (int)obj2->GetScreenLayer()); }

protected:
	/// Constructor for screen objects
	/// \param layer the layer of the image
	CScreenObject(CScreen* screen, ScreenLayers layer);

private:
	/// X position of this ScreenObject's Image
	double mX = 0;
	/// Y position of this ScreenObject's Image
	double mY = 850;
	
	/// angle of this ScreenObject's Image
	double mA = 0;

	/// Screen that this screen object is part of
	CScreen* mScreen;

	/// Adjustment value
	double mAdjust;

	/// layer to draw the screenObject on
	ScreenLayers mObjectLayer;
};

