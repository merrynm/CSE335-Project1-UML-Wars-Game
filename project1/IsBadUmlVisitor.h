/**
* \file IsBadUmlVisitor.h
*
* \author Team Zuse
*
* Class that visits uml and also can tell if they are bad
*/

#pragma once
#include "IsUmlVisitor.h"
#include <string>

/**
 * Class that visits UML boxes and determines if they are bad
 */
class CIsBadUmlVisitor : public CIsUmlVisitor
{
public:
	/// Constructor
	CIsBadUmlVisitor() : CIsUmlVisitor::CIsUmlVisitor() { mIsBad = false; }

	/** Visit UML object
	* \param uml the UML box we're looking at */
	virtual void VisitUml(CUmlBox* uml) override;

	/** Returns whether the visited Uml was bad
	* \return mIsBad bool of whether the uml visited was bad */
	bool GetIsBad() { return mIsBad; }

	/** Returns bad attribute of uml
	* \return mBadAtt of uml */
	std::wstring GetBadAtt() { return mBadAtt; }

private:
	/// True if UML is bad
	bool mIsBad;

	/// Bad attribute
	std::wstring mBadAtt;
};