/**
* \file Visitor.h
*
* \author Team Zuse
*
* Visitor Base Class
*/

#pragma once

// Objects we need a visitor for
class CPens;
class CUmlBox;
//DO NOT DELETE
class CPlayer;

/** Visitor base class*/
class CVisitor
{
public:
	/// destructor
	virtual ~CVisitor() {};

	/** Visit a CPens object
	* \param pen Pen we are visiting*/
	virtual void VisitPen(CPens* pen) {};

	/** Visit a CUml object
	* \param uml UML box we are visiting*/
	virtual void VisitUml(CUmlBox* uml) {};

	/** Visit a CPlayer object
	* \param player the Player we are visiting*/
	virtual void VisitPlayer(CPlayer* player) {};

	/// Resets all data for the visitor
	virtual void Reset() = 0;
};

