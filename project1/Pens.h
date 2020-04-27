/**
 * \file Pens.h
 *
 * \author Team Zuse
 *
 * Pen object class.
 */

#pragma once

#include "ImageObject.h"
#include "Screen.h"
#include <memory>

 /** Class that describes a pen object.
 */
class CPens : public CImageObject
{
public:
	/// Constructor
	CPens(CScreen* screen);

	/// Default constructor (disabled)
	CPens() = delete;

	/// Copy constructor (disabled)
	CPens(const CPens&) = delete;

	/// Update Pen on left mouse click
	void Update(double elapsed) override;

	/// Set Shot for pen
	void SetShot() { mShot = true; }

	/// Get Shot for pen
	/// \return bool Whether or not the pen has been shot
	bool GetShot(){ return mShot; } // override

	/// Getter for pen speed
	/// \return int The pen's speed
	double GetSpeed() { return mSpeed; };

	/// Setter for pen speed
	/// \param newSpeed the new speed we want the pen to have
	void SetSpeed(double newSpeed) { mSpeed = newSpeed; };

	/// Setter for pen shoot angle
	/// \param angle The angle we are shooting
	void SetShootAngle(double angle) { mShootAngle = angle; }
	
	/// Accept a visitor
	/// \param visitor The visitor it is accepting
	virtual void Accept(CVisitor* visitor) override { visitor->VisitPen(this); }

	/// Sets pause state of the game
	/// \param paused Pause state of the game
	void SetPaused(bool paused) { mPaused = paused; }

	/// Pauses the pen object
	virtual void PauseObject( bool paused) override;

private:
	/// Pen speed
	double mSpeed = 700; // changed from const because we will need to be able to change it for pause/difficulty

	/// Pen shot
	bool mShot = false;

	/// Pen velocity vector
	CVector mV;

	/// Angle at which to shoot pen
	double mShootAngle;

	///if the game is paused
	bool mPaused = false;
};

