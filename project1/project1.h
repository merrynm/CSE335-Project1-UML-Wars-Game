

// project1.h : main header file for the project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cproject1App:
// See project1.cpp for the implementation of this class
//

/** Project 1 Application Class
*/
class Cproject1App : public CWinApp
{
public:
	/// constructor
	Cproject1App() noexcept;


// Overrides
public:
	/// bool virtual
	/// \return bool
	virtual BOOL InitInstance();

	/// int virtual
	/// \return int
	virtual int ExitInstance();

// Implementation

public:
	/// App details
	afx_msg void OnAppAbout();
	/// message map declaration
	DECLARE_MESSAGE_MAP()

private:
	/// gdi startup input
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	/// gdi plus token
	ULONG_PTR gdiplusToken = 0;
};

extern Cproject1App theApp;
