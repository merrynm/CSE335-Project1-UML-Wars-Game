
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChildView.h"
/** Mainframe class
*/
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	/// PreCreate Window
	/// \param cs Create structure
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	/// On Command Message
	/// \param nID
	/// \param nCode
	/// \param pExtra
	/// \param pHandlerInfo
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	/// Toolbar
	CToolBar          m_wndToolBar;

	/// Status bar
	CStatusBar        m_wndStatusBar;

	/// View
	CChildView    m_wndView;

// Generated message map functions
protected:
	/// On create
	/// \param lpCreateStruct
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	/// on set focus
	/// \param pOldWnd
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

};


