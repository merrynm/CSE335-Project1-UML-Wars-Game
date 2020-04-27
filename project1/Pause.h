/**
 * \file Pause.h
 *
 * \author Team Zuse
 *
 * Class that implements the pause screen.
 *
 */

#pragma once
#include <memory>
#include "Screen.h"
#include "ImageObject.h"

/** The Class that implements Pause
*/
class CPause : public CImageObject
{
public:
	/// Constructor
	CPause(CScreen* screen);

	/// Default constructor (disabled)
	CPause() = delete;

	/// Copy constructor (disabled)
	CPause(const CPause&) = delete;

};

