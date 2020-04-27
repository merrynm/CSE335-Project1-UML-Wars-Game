/**
 * \file IsPlayerVisitor.h
 *
 * \author Team Zuse
 *
 * Visitor to the player
 */

#pragma once
#include "Visitor.h"

 /**
  * Class that visits Player object
  */
class CIsPlayerVisitor : public CVisitor
{
public:
	/// Constructor
	CIsPlayerVisitor() { mIsPlayer = false; }

	/** Visit Player object
	* \param player the player we're looking at */
	virtual void VisitPlayer(CPlayer* player) override;

	/** Checks if visitor is player visitor
	* \return bool mIsPlayer */
	bool IsPlayerVisitor() { return mIsPlayer; }

	/// Resets member data
	void Reset() override { mIsPlayer = false; }

private:
	/// bool of whether visited object is the player
	bool mIsPlayer = false;
};

