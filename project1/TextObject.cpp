/**
 * \file TextObject.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include <memory>
#include <sstream>
#include "TextObject.h"
#include "Screen.h"

using namespace std;
using namespace Gdiplus;

/* Constructor for CTextObject objects
* \param screen the screen this will use
* \param fontFamily the font to use
* \param text the text to display defaults to empty string
* \param size the font size to use, defaults to 12 pt font
*/
CTextObject::CTextObject(CScreen* screen, ScreenLayers layer, wstring text = L"", double size = 12)
	: CScreenObject::CScreenObject(screen, layer)
{
	// member variable to hold the text to display
	mText = text.c_str();
	// create a font for the text from the parameter font family and size
	FontFamily fontFamily(L"Times New Roman");
	mFont = new Gdiplus::Font(&fontFamily, Gdiplus::REAL(size));
	// default the color of the text to black
	mBrush = new Gdiplus::SolidBrush(Color(15, 15, 15));
}

/* Draws text
* \param graphics the display to draw to
*/
void CTextObject::Draw(Gdiplus::Graphics* graphics)
{
	// get the text to print out
	std::wostringstream ss;
	ss << mText.c_str();
	wstring output = ss.str();
	// draw the text to the parameter graphics
	graphics->DrawString(output.c_str(), -1, mFont, PointF(Gdiplus::REAL(GetX()), Gdiplus::REAL(GetY())), mBrush);
}
