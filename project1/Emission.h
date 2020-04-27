/**
 * \file Emission.h
 *
 * \author Tianrui Liu
 *
 * Class describing an emission
 */

#pragma once

#include <memory>
#include<vector>
#include "Vector.h"

using namespace std;

/** Class that describes an emission object.
 */
class CEmission
{
public:
	/// Getter for X position
	/// \return int
	double GetX() const { return mPos.X(); }
	
	/// Getter for Y position
	/// \return int
	double GetY() const { return mPos.Y(); }
	
	/// Draw graphics
	/// \param graphics GDI+ graphics
	virtual void Draw(Gdiplus::Graphics* graphics);
	
	///Draws the emissions
	/// \param graphics the gdi+ graphics object to display to
	/// \param width width of emission
	/// \param height height of emission
	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

private:
	/// The game this is contained in 
	CEmission* mEmission;

	CVector mPos;			///< Position 

	/// The image
	std::unique_ptr<Gdiplus::Bitmap> mImage;
public:
	///Getter for width
	/// \return int
	int GetWidth() const { return Width; }

	///Getter for height
	/// \return int
	int GetHeight() const { return Height; }

	/// On click
	/// \param x pos x
	/// \param y pos y
	void OnLButtonDown(int x, int y);

	/// Add emission to items
	/// \param emission to add to items
	void Add(std::shared_ptr<CEmission> emission);

private:
	/// Width const
	const static int Width = 1250;

	/// Game area height in virtual pixels
	const static int Height = 1000;

	/// Scale of the window
	double mScale;
	/// XOffset
	double mXset;
	/// YOffset
	double mYset;

	/// Constant ratio to convert radians to degrees
	//const double RtoD = 57.295779513;

	///Emission items
	std::vector<std::shared_ptr<CEmission> > mItemsEmission;
};

