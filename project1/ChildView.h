/**
 * \file ChildView.h
 *
 * \author Team Zuse
 *
 * Class that implements the child window our program draws in.
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#pragma once

#include "Screen.h"
#include "Player.h"
#include "Pens.h"
#include "Pause.h"
#include "UmlBox.h"

/** Class for ChildView
*/
class CChildView : public CWnd
{
// Construction
public:
	/// constructor
	CChildView();

// Attributes
public:
	///Possible levels to choose from
	enum Levels{Easy, Normal, Hard};

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	///deconstructor
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private: 
	/// if it's the first time drawing the screen
	bool mFirstDraw = true;
	double mTimeFreq;   ///<Rate the timer updates
	long long mLastTime; ///<Last time we read the timer

	/// An object that describes our screen
	CScreen  mScreen;

	///sets mPause to current value of Screen's pause member
	bool mPause = mScreen.GetPause();

	/// An object that describes our pen
	std::shared_ptr<CPens> mPen = std::make_shared<CPens>(&mScreen);

	/// An object that describes Pause screen object
	std::shared_ptr<CPause> mPauseScreen = std::make_shared<CPause>(&mScreen);

	/// The currently selected level.
	Levels mLevel = Normal;

public:

	afx_msg void OnFilePause();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	/// Check box handler for pause
	/// \param pCmdUI Check box
	afx_msg void OnUpdateFilePause(CCmdUI* pCmdUI);

	/// Check box handler for Easy difficulty
	/// \param pCmdUI Check box
	afx_msg void OnUpdateDifficultyEasy(CCmdUI* pCmdUI);

	/// Check box handler for Normal difficulty
	/// \param pCmdUI Check box
	afx_msg void OnUpdateDifficultyNormal(CCmdUI* pCmdUI);

	/// Checkbox handler for Hard difficulty
	/// \param pCmdUI Check box
	afx_msg void OnUpdateDifficultyHard(CCmdUI* pCmdUI);

	/// Handler for when Easy difficulty is selected
	afx_msg void OnDifficultyEasy();

	/// Handler for when Normal difficulty is selected
	afx_msg void OnDifficultyNormal();

	/// Handler for when Hard difficulty is selected
	afx_msg void OnDifficultyHard();
};

