/**
 * \file Scoreboard.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include <sstream>
#include "Scoreboard.h"
#include "Screen.h"

using namespace Gdiplus;
using namespace std;

/// strings to display the scoreboard along with the actual scores
/// \return string
const FontFamily fontFamily(L"Arial");

/// Text for Correct score
/// \return string
const wstring cScoreText = L"Correct";

/// Text for Unfair score
/// \return string
const wstring icScoreText = L"Unfair";

/// Text for Missed score
/// \return string
const wstring mScoreText = L"Missed";


/* Constructor for Scoreboard objects
* \param screen the screen object that this scoreboard is a part of */
CScoreboard::CScoreboard(CScreen* screen) : CTextObject(screen, ScreenLayers::TextLayer, L"", 25)
{
	mCorrect = 0;
	mIncorrect = 0;
	mMissed = 0;
}

/* Draws the scoreboard on the parameter graphical display
* \param graphics the gdi+ graphics object to display to */
void CScoreboard::Draw(Gdiplus::Graphics* graphics)
{
	SetLocation(Gdiplus::REAL(-260), Gdiplus::REAL(50));
	//// get the text to print out
	//// the string
	std::wostringstream ss;
	ss << cScoreText << "\t   " << icScoreText << "\t    " << mScoreText << endl;
	ss << "    " << mCorrect << "\t        " << mIncorrect << "\t         " << mMissed;
	wstring output = ss.str();
	CTextObject::SetText(output);
	CTextObject::Draw(graphics);
}
