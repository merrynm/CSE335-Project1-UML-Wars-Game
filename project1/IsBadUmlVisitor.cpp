/**
 * \file IsBadUmlVisitor.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "IsBadUmlVisitor.h"
#include "UmlBox.h"

void CIsBadUmlVisitor::VisitUml(CUmlBox* uml)
{
	CIsUmlVisitor::VisitUml(uml);
	mIsBad = uml->GetBad().c_str() == L"" ? true : false;
	mBadAtt = uml->GetBad();
}
