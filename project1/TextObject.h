/**
 * \file TextObject.h
 * 
 *\author Team Zuse
 *
 * Class for screen objects which have no image but display formatted text
 */

#pragma once
#include "pch.h"
#include "ScreenObject.h"

/** Class for screenObjects which include text
*/
class CTextObject :	public CScreenObject
{
public:
	/// draws the text object
	/// \param graphics
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// default constructor (disabled)
	CTextObject() = delete;

	/// copy constructor (disabled)
	CTextObject(const CTextObject&) = delete;

	/// Rotate function for pause
	/// \param point Vector of mouse location
	void RotateImage(CPoint point) { SetAngle(0); };

protected:
	/// constructs a text object
	/// \param screen the screen we are playing on
	/// \param text the text written on the screen
	/// \param size the size of the text on the screen
	/// \param layer the layer the image is in
	CTextObject(CScreen* screen, ScreenLayers layer, wstring text, double size);

	/// Sets the text to display
	/// \param newText
	void SetText(const wstring newText) { mText = newText; }

	/// Set brush color
	/// \param newBrush the new brush
	void SetBrush(Gdiplus::SolidBrush *newBrush) { mBrush = newBrush; }
private:
	/// text to use when drawing
	wstring mText;
	/// font to use when drawing
	Gdiplus::Font *mFont;
	/// brush to use when drawing
	Gdiplus::SolidBrush *mBrush;
};