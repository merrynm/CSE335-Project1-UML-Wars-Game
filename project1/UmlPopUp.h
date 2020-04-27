/**
 * \file UmlPopUp.h
 *
 * \author Team Zuse
 *
 * header file for the uml pop up class
 */

#pragma once

#include "TextObject.h"
class CScreen;

/// Class to track and display the score
class CUmlPopUp : public CTextObject
{
public:
	/// default constructor (disabled)
	CUmlPopUp() = delete;

	/// copy constructor (disabled)
	CUmlPopUp(const CUmlPopUp&) = delete;

	// constructor
	/// \param screen the screen we are playing on
	CUmlPopUp(CScreen* screen);

	/// draws the scoreboard to the graphics passed as a parameter
	/// \param graphics GDI+ graphics
	void Draw(Gdiplus::Graphics* graphics) override;

	/// Rotate function for pause
	/// \param point Vector of mouse location
	void RotateImage(CPoint point) { SetAngle(0); }

	/// Set the bad attribute
	/// \param att bad uml attribute
	void SetBad(std::wstring att) { mBadAtt = att; }

private:
	/// Bad attribute string
	wstring mBadAtt = L"";
};

