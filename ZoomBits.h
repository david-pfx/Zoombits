// ZoomBits.h : main header file for the ZoomBits application
//

#if !defined(AFX_ZoomBits_H__A091A1D7_14B5_11D1_A76B_00000100782D__INCLUDED_)
#define AFX_ZoomBits_H__A091A1D7_14B5_11D1_A76B_00000100782D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CZoomBitsApp:
// See ZoomBits.cpp for the implementation of this class
//

class CZoomBitsApp : public CWinApp
{
public:
	CZoomBitsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomBitsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZoomBitsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZoomBits_H__A091A1D7_14B5_11D1_A76B_00000100782D__INCLUDED_)
