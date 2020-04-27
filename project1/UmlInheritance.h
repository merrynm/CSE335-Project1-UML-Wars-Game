#pragma once

#include "pch.h"
#include "Umlbox.h"
#include <sstream>
#include "Scoreboard.h"
#include "Screen.h"
#include "Player.h"
using namespace Gdiplus;
using namespace std;

/// Class for inheritance cases of Uml

class CUmlInheritance :
	public CUmlBox
{

public:
	///// Default constructor (disabled)
	//CUmlInheritance() = delete;

	///// Copy constructor (disabled)
	//CUmlInheritance(const CUmlInheritance&) = delete;

	/// Constructor
	/// \param play pointer to screen
	CUmlInheritance(CScreen* play) : CUmlBox(play) {}

	/// Sets the uml is bad and the reason why it is
	//void SetBad(bool isGood, std::wstring badReason);

	/// set the base
	/// \param base
	void SetBase(std::shared_ptr<CUmlBox> base) { mBase = base; }
	
	/// set the derivative
	/// \param derived
	void SetDerived(std::shared_ptr<CUmlBox> derived) { mDerived = derived; }

	/// set the direction
	/// \param direct The direction
	void SetDirection(bool direct) { mDirection = direct; }

	/// draw inheritance
	void Draw(Gdiplus::Graphics* graphics);

	/// hit test for inheritance
	virtual bool HitTest(int x, int y);

private:
	/// pointer to screen
	CScreen* mScreen;

	/// base pointer to box
	std::shared_ptr<CUmlBox> mBase;

	/// derived pointer to box
	std::shared_ptr<CUmlBox> mDerived;

	/// direction
	bool mDirection; 

	/// height
	double mHeight = 10;

	/// width
	double mWidth = 10;

	/// velocity vector
	CVector mV;

	/// Image for inheritance
	std::unique_ptr<Gdiplus::Bitmap> mUmlInheritanceImage;

};
