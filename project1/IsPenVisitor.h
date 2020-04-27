/**
* \file IsPenVisitor.h
*
* \author Team Zuse
*
* Class that visits pens
*/

#pragma once
#include "Visitor.h"

/**
 * Class that visits pens
 */
class CIsPenVisitor : public CVisitor
{
public:
	/// Constructor
	CIsPenVisitor() { mIsPen = false; mIsShot = false; }

	/** Visit pen object
	* \param pen the pen we're looking at */
	virtual void VisitPen(CPens* pen) override;

	/** Checks if visitor is pen visitor
	* \return bool mIsPen */
	bool IsPenVisitor() { return mIsPen; }

	/** Checks if the visited object is a pen and has been shot
	* \return bool whether the visited object is both a pen and has been shot*/
	bool VisitedShotPen() { return mIsPen && mIsShot; }

	/// Resets member data
	void Reset() override { mIsPen = false; }

private:
	/// bool of whether object is a pen
	bool mIsPen = false;
	/// bool of whether the pen has been shot if the visited object is a pen.
	bool mIsShot = false;
};

