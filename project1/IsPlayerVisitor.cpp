/**
 * \file IsPlayerVisitor.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "IsPlayerVisitor.h"

/*
* Visits a CPlayer object
*/
void CIsPlayerVisitor::VisitPlayer(CPlayer* player)
{
	mIsPlayer = true;
}
