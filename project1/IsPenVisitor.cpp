/**
 * \file IsPenVisitor.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "Pens.h"
#include "IsPenVisitor.h"

/*
* Visits the pen object
* \param pen The pen object
*/
void CIsPenVisitor::VisitPen(CPens* pen)
{
	mIsPen = true;
	mIsShot = pen->GetShot();
}
