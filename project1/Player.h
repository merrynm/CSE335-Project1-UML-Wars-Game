/**
 * \file Player.h
 *
 * \author Team Zuse
 *
 * Class that implements the player.
 *
 */

#pragma once
#include <memory>
#include "ImageObject.h"
#include "Pens.h"

class CScreen;

/** Class for Player object
*/
class CPlayer : public CImageObject
{
public:
	/// Constructor
	CPlayer(CScreen* screen);
	
	/// Default constructor (disabled)
	CPlayer() = delete;

	/// Copy constructor (disabled)
	CPlayer(const CPlayer&) = delete;

	/// Rotate Harold and Pen
	void RotateImage(CPoint point);

	/// Shoot pen
	void ShootPen();

	/// Update Player on left mouse click
	void Update(double elapsed) override;

	/// Accept a visitor
	/// \param visitor The visitor for this object
	void Accept(CVisitor* visitor) { visitor->VisitPlayer(this); }
	
	/// Function that generates the pen
	/// \param pen the pen we are regenerating
	void Regenerate(std::shared_ptr<CPens> pen);

	/// True if Player has no pen in his hand
	/// \return bool If the player is empty handed
	bool IsEmptyHanded() { return mEmptyHanded; }

	/// Updates to whether or not Player has pen in hand
	void SetHandedness() { mEmptyHanded = false; }

	/// Gets time that has elapsed
	/// \return double The time that has elapsed
	double GetElapsedTime() { return mElapsed; }

	/// Sets time that has elapsed
	void SetElapsedTime() { mElapsed = 0; }

	/// Getter for hold
	/// \return std::shared_ptr<CPens> The pen the player is holding
	std::shared_ptr<CPens> GetHold() { return mHold; }

private:
	/// The game screen
	CScreen* screen;

	/// The Pen in player's hand
	std::shared_ptr<CPens> mPen = std::make_shared<CPens>(screen);

	///Hold
	std::shared_ptr<CPens> mHold = nullptr;

	/// Time that has elapsed
	double mElapsed = 0;

	/// Is player empty handed?
	bool mEmptyHanded = false;

};

