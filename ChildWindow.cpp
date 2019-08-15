// ChildWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ZoomBits.h"
#include "ChildWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWindow

BEGIN_MESSAGE_MAP(CChildWindow, CWnd) 
	//{{AFX_MSG_MAP(CChildWindow)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnTooltipNeedText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChildWindow::CChildWindow() {
   m_captured = false;
   m_timer = false;
   m_grab = true;
   m_grabbing = false;
   m_ontop = false;
   m_gotfocus = false;
   m_holdcursor = NULL;
   m_status_rgb = 0;
   m_status_rect = CRect (0, 0, 0, 0);
   m_spy = new CSpy ();
   VERIFY (m_hcursor = AfxGetApp ()->LoadCursor (IDC_CURSOR_TARGET));
}

CChildWindow::~CChildWindow() {
}

/////////////////////////////////////////////////////////////////////////////
// 

inline int divup (int n, int f) {
   return (n + f - 1) / f;
}

inline int roundup (int n, int f) {
   return divup (n, f) * f;
}

void CChildWindow::SpyInit() {
   m_timer = false;
   CRect clrc;
   GetClientRect (&clrc);
   m_spy->SetSize (CSize (divup (clrc.Width (), m_spy->m_scale), 
			  divup (clrc.Height (), m_spy->m_scale)));
   GetDesktopWindow ()->GetWindowRect (&clrc);
   m_spy->SetPos (CPoint (clrc.Width() / 2, clrc.Height () / 2));
   SetBase (CPoint (0, 0));
   SetSpot (CPoint (clrc.Width() / 2, clrc.Height () / 2));
   CPoint point;
   GetCursorPos (&point);
   SpyDraw (DR_START, point);
}

void CChildWindow::SpyExit () {
   SpyDraw (DR_STOP, CPoint (0, 0));
}

void CChildWindow::SpyPause () {
   SpyDraw (DR_STOP, CPoint (0, 0));
}

// set the current target spot and other status variables
void CChildWindow::SetBase (CPoint pos)  { 
   m_status_base = pos;
}

// set the current target spot and other status variables
void CChildWindow::SetSpot (CPoint pos)  { 
   m_status_spot = pos;
   CDC cdc;
   cdc.CreateDC ("DISPLAY", "", "", 0);
   m_status_rgb = cdc.GetPixel (pos);
}

// move the target window to where the cursor now is and re-draw
void CChildWindow::SpyMove () {
   CPoint point;
   GetCursorPos (&point);
   SetBase (CPoint (0, 0));
   SetSpot (point);
   SpyDraw (DR_CONT, point);
}

// draw or undraw the dotted target rectangle 
// DrawDragRect will replace rc1 by rc2 (either may be null), but first
// expand them to include the line width
void CChildWindow::DrawGrabRect (bool on) {
   if (on && m_grabrect == m_spy->m_rect) 
      ;	 // nothing: already on and didn't move
   else if (!on && m_grabrect.IsRectEmpty ()) 
      ;	 // nothing: already off
   else {
      //Beep (on ? 1100 : 2100, 50);
      //Beep (m_grabrect.IsRectEmpty () ? 1000 : 2000, 50);
      int lw = m_spy->m_linewidth;
      CRect rc1 = m_grabrect + CRect (lw, lw, lw, lw);	 // old
      CRect rc2 = (!on) ? CRect (0, 0, 0, 0)	 // new
	        : m_spy->m_rect + CRect (lw, lw, lw, lw);
      CSize sz = CSize (lw, lw);
      CDC cdc;
      cdc.CreateDC ("DISPLAY", "", "", 0);
      if (m_grabrect.IsRectEmpty ())
	 cdc.DrawDragRect (rc2, sz, NULL, sz);
      else 
	 cdc.DrawDragRect (rc2, sz, rc1, sz);
      m_grabrect = (on) ? m_spy->m_rect : CRect (0, 0, 0, 0);
   }
}

// draw everything - the target window (if necessary) and the view
void CChildWindow::SpyDraw (edraw draw, CPoint newpt) {
#if 1
   if (draw == DR_STOP)
      DrawGrabRect (false);
   else {
      m_spy->SetPos (newpt);
      DrawGrabRect (true);
   }
   SpyRender ();
#else
   CDC cdc;
   cdc.CreateDC ("DISPLAY", "", "", 0);
   CRect oldrc = m_spy->m_rect;
   if (draw != DR_STOP)
      m_spy->SetPos (newpt);
   CRect newrc = m_spy->m_rect;
   CRect rc1 = (draw == DR_START) ? NULL	 // old
	     : oldrc + CRect (lw, lw, lw, lw);
   CRect rc2 = (draw == DR_STOP) ? CRect (0, 0, 0, 0)	 // new
	     : newrc + CRect (lw, lw, lw, lw);
   CSize sz = CSize (lw, lw);
   cdc.DrawDragRect (rc2, sz, rc1, sz);
   CClientDC windc (this);
   SpyRender (&windc, &cdc);
#endif
}

void CChildWindow::SpyTick () {
   CPoint pt;
   GetCursorPos (&pt);
   CRect clrc;
   GetWindowRect (&clrc);
   // grab if enabled and either mouse outside window, or not active window
   if (this == GetActiveWindow())
      Beep (1100, 50);
   m_grabbing = m_grab && (!clrc.PtInRect (pt) || !m_gotfocus);
   if (m_grabbing) {
      SpyRender ();
      DrawGrabRect (false);
   } else 
      DrawGrabRect (true);
}

// called when main window gets or loses focus
void CChildWindow::GotFocus(bool yes) {
   m_gotfocus = yes;
}

// render the contents of the view window
void CChildWindow::SpyRender () {
   CClientDC windc (this);
   SpyRender (&windc);
}

void CChildWindow::SpyRender (CDC* pwindc) {
   CDC dispdc;
   VERIFY (dispdc.CreateDC ("DISPLAY", "", "", 0));
   SpyRender (pwindc, &dispdc);
}

void CChildWindow::SpyRender (CDC* pwindc, CDC* pdispdc) {
   CBitmap bitmap;
   VERIFY (bitmap.CreateCompatibleBitmap (pwindc, 
      m_spy->m_size.cx, m_spy->m_size.cy));
   CDC memdc;
   VERIFY (memdc.CreateCompatibleDC (pwindc));
   CBitmap* oldbm = memdc.SelectObject (&bitmap);
   memdc.BitBlt (0, 0, m_spy->m_rect.Width (), m_spy->m_rect.Height (), 
   		 pdispdc, m_spy->m_rect.left, m_spy->m_rect.top, SRCCOPY);
   int scale = m_spy->m_scale;
   // the offset within the target on screen 
   CPoint spot (m_spy->m_size.cx/2, m_spy->m_size.cy/2);
   // the centre focus area
   CPoint spotx (spot.x * scale, spot.y * scale);
   TRACE ("spot: x=%d y=%d spotx: x=%d y=%d\n", spot.x, spot.y, spotx.x, spotx.y);
   pwindc->StretchBlt (0, 0, m_spy->m_size.cx * scale, m_spy->m_size.cy * scale, 
		       &memdc, 0, 0, m_spy->m_size.cx, m_spy->m_size.cy, SRCCOPY);
   pwindc->StretchBlt (spotx.x-2, spotx.y-2, scale+4,  scale+4, 
		       &memdc, 0, 0, 0, 0, BLACKNESS);
   pwindc->StretchBlt (spotx.x, spotx.y, scale,  scale, 
		       &memdc, spot.x, spot.y, 1, 1, SRCCOPY);
   memdc.SelectObject (oldbm);
   memdc.DeleteDC ();
   CRect clrc;
   GetClientRect (&clrc);
   m_status_rect = CRect (m_spy->m_rect.TopLeft (), 
      CSize (clrc.right / m_spy->m_scale, clrc.bottom / m_spy->m_scale));
   SetBase (CPoint (0, 0));
   SetSpot (m_spy->m_pos);
}

void CChildWindow::Nudge (CSize sz) {
   CPoint point;
   if (m_captured) {
      GetCursorPos (&point);
      SetCursorPos (point.x + sz.cx, point.y + sz.cy);
   } else if (m_grab) {
      m_spy->SetPos (m_spy->m_pos + sz);
      InvalidateRect (NULL);
   }
}

void CChildWindow::StartSpy () {
   if (!m_captured) {
      SetCapture ();
      if (m_timer)
	 KillTimer (1);
      SpyInit ();
      VERIFY (m_holdcursor = SetCursor (m_hcursor));
      m_captured = true;
      m_grab = true;
   }
}

void CChildWindow::EndSpy () {
   if (m_captured) {
      ReleaseCapture ();
      m_captured = false;
      SpyPause ();
      SetTimer (1, 100, NULL);
      m_timer = true;
      VERIFY (SetCursor (m_holdcursor));
   }
}

/////////////////////////////////////////////////////////////////////////////
// CChildWindow message handlers

int CChildWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) {
   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   int x = lpCreateStruct->cx;
   int y = lpCreateStruct->cy;
   //SpyInit ();
   EnableToolTips (TRUE);
   SetTimer (1, 100, NULL);
   m_timer = true;
   return 0;
}

void CChildWindow::OnPaint() {
   CPaintDC dc(this); // device context for painting
   SpyRender (&dc);
}

void CChildWindow::OnMouseMove(UINT nFlags, CPoint point) {
   if (m_captured) {
      SpyMove ();
   } else {
      SetSpot (m_spy->m_rect.TopLeft () + 
	 CSize (point.x / m_spy->m_scale, point.y / m_spy->m_scale));
   }
}

void CChildWindow::OnLButtonDblClk(UINT nFlags, CPoint point) {
   StartSpy ();
}

void CChildWindow::OnLButtonUp(UINT nFlags, CPoint point) {
   EndSpy ();
}

void CChildWindow::OnTimer(UINT nIDEvent) {
   SpyTick ();
}

void CChildWindow::OnSize(UINT nType, int cx, int cy) {
   //CWnd::OnSize(nType, cx, cy);
   //CRect rc;
   //GetWindowRect (rc);
   //ScreenToClient (rc);
   //InvalidateRect (rc);
   //CClientDC cdc (this);
   //cdc.Rectangle (0, 0, cx, cy);
   m_spy->SetSize (CSize (divup (cx, m_spy->m_scale)+1, divup (cy, m_spy->m_scale)+1));
   //CClientDC windc (this);
   SpyRender ();
}

BOOL CChildWindow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
   SetCursor (LoadCursor (NULL, IDC_CROSS));
   return TRUE;
}

void CChildWindow::OnLButtonDown(UINT nFlags, CPoint point) {
   SetBase (m_status_spot);
//   if (m_findbut.PtInRect (point)) {
//      MessageBeep (0);
//   }
}


BOOL CChildWindow::OnEraseBkgnd(CDC* pDC) {
   return CWnd::OnEraseBkgnd(pDC);
   //return true;
}

int CChildWindow::OnToolHitTest(CPoint point, TOOLINFO* pTI) {
   return -1;
}

BOOL CChildWindow::OnTooltipNeedText(UINT id, NMHDR*  pNMHDR, LRESULT* pResult) {
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT*)pNMHDR;
    UINT nID =pNMHDR->idFrom;
    sprintf (pTTT->szText, "xxx");
    return TRUE;
    //if (pTTT->uFlags & TTF_IDISHWND) {
    //    nID = ::GetDlgCtrlID((HWND)nID);
    //    if(nID)
    //    {
    //        pTTT->lpszText = MAKEINTRESOURCE(nID);
    //        pTTT->hinst = AfxGetResourceHandle();
    //        return(TRUE);
    //    }
    //}
    //return(FALSE);
}
