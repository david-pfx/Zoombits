// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A091A1DB_14B5_11D1_A76B_00000100782D__INCLUDED_)
#define AFX_MAINFRM_H__A091A1DB_14B5_11D1_A76B_00000100782D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ChildWindow.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CChildWindow m_childwindow;
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

   void SetStatusTextWidth (int ndx, CString cs);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileGrab();
	afx_msg void OnUpdateFileGrab(CCmdUI* pCmdUI);
	afx_msg void OnMagnification1();
	afx_msg void OnUpdateMagnification1(CCmdUI* pCmdUI);
	afx_msg void OnMagnification2();
	afx_msg void OnUpdateMagnification2(CCmdUI* pCmdUI);
	afx_msg void OnMagnification4();
	afx_msg void OnUpdateMagnification4(CCmdUI* pCmdUI);
	afx_msg void OnMagnification8();
	afx_msg void OnUpdateMagnification8(CCmdUI* pCmdUI);
	afx_msg void OnMagnification16();
	afx_msg void OnUpdateMagnification16(CCmdUI* pCmdUI);
	afx_msg void OnMagnification32();
	afx_msg void OnUpdateMagnification32(CCmdUI* pCmdUI);
	afx_msg void OnFileOntop();
	afx_msg void OnUpdateFileOntop(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOptionFixCentre();
	afx_msg void OnUpdateOptionFixCentre(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
        afx_msg void OnUpdateStatusGrab(CCmdUI *pCmdUI);
        afx_msg void OnUpdateStatusMagnification(CCmdUI *pCmdUI);
        afx_msg void OnUpdateStatusPosition(CCmdUI *pCmdUI);
        afx_msg void OnUpdateStatusColor(CCmdUI *pCmdUI);
        afx_msg void OnUpdateStatusSpot(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A091A1DB_14B5_11D1_A76B_00000100782D__INCLUDED_)
