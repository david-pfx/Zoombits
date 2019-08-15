// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A091A1D9_14B5_11D1_A76B_00000100782D__INCLUDED_)
#define AFX_STDAFX_H__A091A1D9_14B5_11D1_A76B_00000100782D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE // vs8:C4996
//#define WINVER 0x400		 //vs8
//#define _WIN32_IE 0x400		 // vs9
#define WINVER 0x501		 // vs11
#define _WIN32_WINNT 0x501	 // vs11
#define _WIN32_IE 0x501		 // vs11

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A091A1D9_14B5_11D1_A76B_00000100782D__INCLUDED_)
