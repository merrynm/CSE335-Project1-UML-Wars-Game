#include "pch.h"
#include "UmlInheritance.h"

using namespace Gdiplus;


/** Draw function that draws UML boxes on our screen
 * \param graphics
*/
void CUmlInheritance::Draw(Gdiplus::Graphics* graphics)
{
	Gdiplus::RectF size;
	Gdiplus::FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 10);
	Gdiplus::SolidBrush redBrush(Gdiplus::Color(255, 0, 0));
	Gdiplus::SolidBrush Brush(Gdiplus::Color(0, 128, 0));

	int width = (int)mBase->GetWidth() - (int)mDerived->GetWidth();
	mBase->SetLocation(GetX(), GetY());
	mBase->Draw(graphics);

	int triPointX = (int)GetX() + (int)mBase->GetWidth() / 2;
	int triPointY = (int)GetY() + (int)mBase->GetHeight();

	if (mDirection)
	{
		Pen pen(Color(0, 0, 0), 2);
		graphics->DrawLine(&pen, triPointX - 10, triPointY + 15, triPointX + 10, triPointY + 15);
		graphics->DrawLine(&pen, triPointX - 10, triPointY + 15, triPointX, triPointY);
		graphics->DrawLine(&pen, triPointX, triPointY, triPointX + 10, triPointY + 15);
		graphics->DrawLine(&pen, triPointX, triPointY + 15, triPointX, triPointY + 35);
	}
	else
	{
		Pen pen(Color(0, 0, 0), 2);
		graphics->DrawLine(&pen, triPointX, triPointY, triPointX, triPointY + 20);
		graphics->DrawLine(&pen, triPointX - 10, triPointY + 20, triPointX + 10, triPointY + 20);
		graphics->DrawLine(&pen, triPointX - 10, triPointY + 20, triPointX, triPointY + 35);
		graphics->DrawLine(&pen, triPointX, triPointY + 35, triPointX + 10, triPointY + 20);
	}

	mDerived->SetLocation(GetX() + (width / 2), GetY() + mBase->GetHeight() + 35);
	mDerived->Draw(graphics);

	if (mBase->GetWidth() > mDerived->GetWidth())
	{
		mWidth = mBase->GetWidth();
	}
	else
	{
		mWidth = mDerived->GetWidth();
	}

	mHeight = mBase->GetHeight() + mDerived->GetHeight() + 35;

	//if (true)
	//{
	//	Gdiplus::Font font(&fontFamily, 20);
	//	int wid;
	//	graphics->MeasureString(L"Unfair!", -1, &font, Gdiplus::PointF(0.0f, 0.0f), &size);
	//	double textWidth = (double)size.Width;

	//	graphics->DrawString(L"Unfair!", -1, &font,
	//		Gdiplus::PointF(triPointX - textWidth / 2, triPointY), &redBrush);
	//}

}

/** Test interitence hit test
* \param x X location
* \param y Y location
* \return bool of hit
*/
bool CUmlInheritance::HitTest(int x, int y)
{
	double wid = mWidth;
	double hit = mHeight;

	double testX = x - GetX();
	double testY = y - GetY();

	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit) { return false; }
	else { return true; }
}
