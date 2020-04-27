/**
* \file IsUmlVisitor.h
*
* \author Team Zuse
*
* Class that visits uml
*/

#pragma once
#include "Visitor.h"

/**Class that visits road tiles to fix them
 */
class CIsUmlVisitor : public CVisitor
{
public:
	/// Constructor
	CIsUmlVisitor() { mIsUml = false; mIsOld = false; }

	/** Visit uml object
	*/
	virtual void VisitUml(CUmlBox* uml) override;

	/** Checks if visitor is uml visitor
	* \return bool mIsUml */
	bool IsUmlVisitor() { return mIsUml; }

	/** Checks whether the UML is old
	* \return bool mIsUml
	* \return bool mIsOld */
	bool IsOldUml() { return mIsUml && mIsOld; }

	/// Resets member data
	void Reset() override { mIsUml = false; }

private:
	/// bool of whether the visited object is an uml box
	bool mIsUml = false;

	/// bool of whether the UML is hit and old
	bool mIsOld = false;
};

