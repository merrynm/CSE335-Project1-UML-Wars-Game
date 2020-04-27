/**
 * \file IsUmlVisitor.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "UmlBox.h"
#include "IsUmlVisitor.h"

/**
 * Visits the UML object
 * \param uml The UML object
 */
void CIsUmlVisitor::VisitUml(CUmlBox* uml)
{
	mIsUml = true;
	mIsOld = uml->IsOld();
}
