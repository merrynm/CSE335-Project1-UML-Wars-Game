/**
 * \file ImageObject.h
 *
 * \author Team Zuse
 *
 * intermediate classes for ScreenObjects that have attatched images.
 */

#pragma once
#include "pch.h"
#include "ScreenObject.h"

/** Class for screen objects with an attatched image
*/
class CImageObject : public CScreenObject
{
public:
	/// Draws the image object to the parameter graphics
	/// \param graphics the graphics to draw to
	void Draw(Gdiplus::Graphics *graphics) override;
	
	/// Test if the x and y coords are within the image object
	bool HitTest(int x, int y) override;

	/// Sets the image of this screen object
	/// \param filename the filename of the image to load
	void SetImage(const WCHAR* filename) { mItemImage->FromFile(filename); }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	void Accept(CVisitor* visitor) override {};

protected:
	/// Image object constructor
	/// \param layer layer of the object
	CImageObject(CScreen* screen, const std::wstring& filename, ScreenLayers layer);

private:
	/// The image for this screenObject
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;
};

