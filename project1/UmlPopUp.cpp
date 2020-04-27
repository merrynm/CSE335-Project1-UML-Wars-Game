/**
 * \file UmlPopUp.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "UmlPopUp.h"
#include <sstream>
#include "Screen.h"

using namespace Gdiplus;
using namespace std;

/// strings to display the scoreboard along with the actual scores
/// \return string
const FontFamily fontFamily(L"Times New Roman");

/* Constructor for Uml Pop up objects
* \param screen the screen object that this scoreboard is a part of */
CUmlPopUp::CUmlPopUp(CScreen* screen) : CTextObject(screen, ScreenLayers::TextLayer, L"", 25)
{
}

/* Draws the scoreboard on the parameter graphical display
* \param graphics the gdi+ graphics object to display to */
void CUmlPopUp::Draw(Gdiplus::Graphics* graphics)
{
	Gdiplus::Font font(&fontFamily, 20);
	// get a brush to write in
	SolidBrush red(Color(200, 15, 15));
	SolidBrush green(Color(15, 200, 15));
	// get the text to print out
	std::wostringstream ss;
	if (mBadAtt==L"")
	{
		ss << "Unfair!";
		SetBrush(&red);
	}
	else
	{
		ss << mBadAtt;
		SetBrush(&green);
	}
	SetText((ss.str()).c_str());
	CTextObject::Draw(graphics);
}
