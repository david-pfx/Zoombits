#if !defined(AFX_CHILDWINDOW_H__A091A203_14B5_11D1_A76B_00000100782D__INCLUDED_)
#define AFX_CHILDWINDOW_H__A091A203_14B5_11D1_A76B_00000100782D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChildWindow.h : header file
//

class CSpy;

/////////////////////////////////////////////////////////////////////////////
// CChildWindow window

class CChildWindow : public CWnd
{
// Construction
public:
   CChildWindow();

// Attributes
public:
   bool m_captured;
   bool m_timer;
   bool m_ontop;
   bool m_grab;		   // allowed to grab - update display from screen
   bool m_grabbing;	   // actually grabbing
   bool m_gotfocus;	   // actually have focus now
   CRect m_status_rect;	   // rectangle for status display
   CPoint m_status_base;   // base spot for status display
   CPoint m_status_spot;   // centre spot for status display
   COLORREF m_status_rgb;  // color of pixel for status display
   CRect m_findbut;
   CSpy* m_spy;
   HCURSOR m_hcursor;
   HCURSOR m_holdcursor;
   enum edraw { DR_START, DR_CONT, DR_STOP };
   CRect m_grabrect;	   // where grab rectangle now is

// Operations
public:
   void Nudge (CSize sz);
   void StartSpy ();
   void EndSpy ();
   void SpyMove ();
   void SpyInit();
   void SpyPause ();
   void SpyExit ();
   void SpyDraw (edraw draw, CPoint newpt);	 // draw at this new point
   void SpyRender (CDC* pwindc, CDC* pdispdc);
   void SpyRender (CDC* pwindc);
   void SpyRender ();
   void SpyTick ();
   void SetBase (CPoint pos);			// reference for spot
   void SetSpot (CPoint pos);			// status is for this point
   void DrawGrabRect (bool on);
   void GotFocus (bool yes);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildWindow)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI);
	//}}AFX_MSG
	BOOL OnTooltipNeedText(UINT id, NMHDR*  pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSpy - object with info about what we're spying on

class CSpy {
// Attributes
public:
   int m_scale;		   // magnification factor
   int m_linewidth;
   bool m_fix_centre;	   // true if centre is fixed on re-size
   CRect m_rect;	   // current spied upon rectangle
   CSize m_size;	   // next spied upon size
   CPoint m_pos;	   // focal point
   CPoint m_spot;	   // location on status bar
// Construction
public:
   CSpy () { m_scale = 4; m_linewidth = 1; m_fix_centre = false;
	     m_rect = CRect (0, 0, 0, 0); m_pos = CPoint (0, 0);
	     m_size = CSize (0, 0);  
   }
   void SetScale (int scale) { 
      SetSize (CSize (m_size.cx * m_scale / scale, m_size.cy * m_scale / scale));
      m_scale = scale; 
   }
   void SetSize (CSize size) { 
      m_size = size; 
      if (m_fix_centre) {
	 m_rect = CRect (m_pos - CSize (m_size.cx/2, m_size.cy/2), m_size); 
      } else {
	 m_rect = CRect (m_rect.TopLeft (), size);
	 m_pos = m_rect.CenterPoint ();
      }
   }
   void SetPos (CPoint pos)  { 
      m_pos = pos; 
      m_rect = CRect (m_pos - CSize (m_size.cx/2, m_size.cy/2), m_size); 
   }

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDWINDOW_H__A091A203_14B5_11D1_A76B_00000100782D__INCLUDED_)
