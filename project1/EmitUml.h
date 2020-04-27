/**
 * \file EmitUml.h
 *
 * \author Team Zuse
 *
 * UML emitter class.
 */

#pragma once

#include <memory>
#include "UmlBadAttribute.h"
#include <algorithm>
#include <vector>

/// Game screen class
class CScreen;

/** Class to emit the UML every 2 seconds
*/
class CEmitUml 
{
public:
	/// default constructor (disabled)
	CEmitUml() = delete;

	/// Copy constructor (disabled)
	CEmitUml (const CEmitUml&) = delete;

	/// Constructor
	CEmitUml(CScreen* screen);
	
	/// Updates UML emission
	void Update(double elapsed);


	//std::vector<UmlBadAttribute> GetAttribute() { return mAttribute; }

private:
	/// Used to keep track of the time
	double mTime = 0;

	/// The screen to draw the uml
	CScreen* mScreen;
	
	/// Current state of pause in the game
	bool mPause = false;

	/// the bad attribute
	std::vector<UmlBadAttribute>  mAttribute;

};

