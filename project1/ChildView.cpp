/**
 * \file ChildView.cpp
 *
 * \author Team Zuse
 */

#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "ChildView.h"
#include "Screen.h"
#include "DoubleBufferDC.h"
#include "Pens.h"
#include "UmlBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/* 
* Constructor
*/
CChildView::CChildView()
{
	//Generates random constructors for the uml speed
	srand((unsigned int)time(nullptr));
}

/*
* Deconstructor
*/
CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_PAUSE, &CChildView::OnFilePause)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_FILE_PAUSE, &CChildView::OnUpdateFilePause)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_EASY, &CChildView::OnUpdateDifficultyEasy)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_NORMAL, &CChildView::OnUpdateDifficultyNormal)
	ON_UPDATE_COMMAND_UI(ID_DIFFICULTY_HARD, &CChildView::OnUpdateDifficultyHard)
	ON_COMMAND(ID_DIFFICULTY_EASY, &CChildView::OnDifficultyEasy)
	ON_COMMAND(ID_DIFFICULTY_NORMAL, &CChildView::OnDifficultyNormal)
	ON_COMMAND(ID_DIFFICULTY_HARD, &CChildView::OnDifficultyHard)
END_MESSAGE_MAP()

// CChildView message handlers

/** This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/** This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint() 
{
	if (mFirstDraw)
	{
		//mScreen.AddScreenObject(mPen);
		mFirstDraw = false;

		//starts the timer
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

	//	mScreen.Load();
	}
	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	//if (mPen->GetShot())
	//{
		//if (mScreen.Regenerate(elapsed)) // Make new pen if elapsed time > 1000ms
		//{
		//	mScreen.AddScreenObject(mPen2);
		//}
	//}

	mScreen.Update(elapsed); //Update the animation

	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC);
	Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

	CRect rect;
	GetClientRect(&rect);

	mScreen.Draw(&graphics, rect.Width(), rect.Height());
	//Pen pen(Color(0, 0, 0), 3);
	//SolidBrush brush(Color(255, 255, 193));
	//graphics.FillRectangle(&brush, 200, 125, 300, 200);
	////Draws the rectangle in yellow
	//graphics.DrawRectangle(&pen, 200, 125, 300, 200);
	//HatchBrush hBrush(HatchStyleHorizontal, Color(0, 0, 0),
	//	Color(255, 255, 193));
	//graphics.FillRectangle(&hBrush, 100, 125, 200,250);
	//graphics.DrawRectangle(&pen, 100, 125, 200, 250);
	//

	/*CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");  // Filter
	if (dlg.DoModal() != IDOK)
		return;
	wstring filename = dlg.GetPathName();
	mScreen.UMLLoad(filename);*/
}


/** This function is called to pause the window
*
* This function is called in response to a pause message
* It is responsible for changing the window to a pause screen & saving state of the game.
*/
void CChildView::OnFilePause()
{
	mPause = !mPause; //check or uncheck pause option
	mScreen.OnPause();

	if (mPause == true)
	{
		//draw pause image
		mScreen.AddScreenObject(mPauseScreen);	
	}

	if (mPause == false)
	{
		//get rid of pause image
		mScreen.RemoveScreenObject(mPauseScreen);
	}
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**
 * Set Harold's angle according to mouse x position
 *
 * \param nFlags device flags
 * \param point vector mouse position
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	point = mScreen.FixMouseCoordinates(point);
	mScreen.RotateScreenObjects(point);
}

/**
 * Redraw screen on timer - state driven program
 *
 * \param nIDEvent device event
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}

/**
 * Shoot pen on left button click
 *
 * \param nFlags device flags
 * \param point vector mouse position
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mScreen.Shoot();
}

/*
* Updates the menu check box if pause option is selected
*/
void CChildView::OnUpdateFilePause(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mPause);
}

/*
* Sets check if user selects Easy difficulty
*/
void CChildView::OnUpdateDifficultyEasy(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mLevel == Easy);
}

/*
* Sets check if user selects Normal difficulty. This is the default difficulty.
*/
void CChildView::OnUpdateDifficultyNormal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mLevel == Normal);
}

/*
* Sets check if user selects Hard difficulty
*/
void CChildView::OnUpdateDifficultyHard(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mLevel == Hard);
}

/*
* Handler for Easy difficulty
*/
void CChildView::OnDifficultyEasy()
{
	mLevel = Easy;
	mScreen.SetNewSpeed(0.3);
}

/*
* Handler for Normal difficulty
*/
void CChildView::OnDifficultyNormal()
{
	mLevel = Normal;
	mScreen.SetNewSpeed(1.0);
}

/*
* Handler for Hard difficulty
*/
void CChildView::OnDifficultyHard()
{
	mLevel = Hard;
	mScreen.SetNewSpeed(2.5);
}
