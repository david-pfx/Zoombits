// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ZoomBits.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDW_CHILD 1

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_GRAB, OnFileGrab)
	ON_UPDATE_COMMAND_UI(ID_FILE_GRAB, OnUpdateFileGrab)
	ON_COMMAND(ID_MAGNIFICATION_1, OnMagnification1)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_1, OnUpdateMagnification1)
	ON_COMMAND(ID_MAGNIFICATION_2, OnMagnification2)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_2, OnUpdateMagnification2)
	ON_COMMAND(ID_MAGNIFICATION_4, OnMagnification4)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_4, OnUpdateMagnification4)
	ON_COMMAND(ID_MAGNIFICATION_8, OnMagnification8)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_8, OnUpdateMagnification8)
	ON_COMMAND(ID_MAGNIFICATION_16, OnMagnification16)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_16, OnUpdateMagnification16)
	ON_COMMAND(ID_MAGNIFICATION_32, OnMagnification32)
	ON_UPDATE_COMMAND_UI(ID_MAGNIFICATION_32, OnUpdateMagnification32)
	ON_COMMAND(ID_FILE_ONTOP, OnFileOntop)
	ON_UPDATE_COMMAND_UI(ID_FILE_ONTOP, OnUpdateFileOntop)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_OPTION_FIX_CENTRE, OnOptionFixCentre)
	ON_UPDATE_COMMAND_UI(ID_OPTION_FIX_CENTRE, OnUpdateOptionFixCentre)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP

	//ON_COMMAND(ID_TOOLBAR_TARGET, OnToolbarTarget)
	//ON_UPDATE_COMMAND_UI(ID_TOOLBAR_TARGET, OnUpdateToolbarTarget)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_GRAB, OnUpdateStatusGrab)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MAGNIFICATION, OnUpdateStatusMagnification)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_POSITION, OnUpdateStatusPosition)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COLOR, OnUpdateStatusColor)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SPOT, OnUpdateStatusSpot)

        //ON_NOTIFY_EX(NM_CLICK, 0, OnNotifyClick)
END_MESSAGE_MAP()

static UINT indicators[] =
{
//	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_GRAB,
	ID_INDICATOR_MAGNIFICATION,
	ID_INDICATOR_SPOT,
	ID_INDICATOR_COLOR,
	ID_INDICATOR_POSITION,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

   EnableToolTips (TRUE);
   if (!m_childwindow.CreateEx (WS_EX_CLIENTEDGE, NULL, "", WS_CHILD | WS_VISIBLE, 
	 CRect (0, 0, 0, 0), this, IDW_CHILD)) { 
      TRACE0 ("Failed to create child window\n");
      return -1;      // fail to create
   }
   RecalcLayout ();
   m_childwindow.InvalidateRect (NULL);
   return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::RecalcLayout(BOOL bNotify) 
{
   CFrameWnd::RecalcLayout(bNotify);
   CRect rc;
   RepositionBars (0, 0xffff, IDW_CHILD, reposQuery, &rc);
   if (IsWindow (m_childwindow.GetSafeHwnd ())) {
      m_childwindow.MoveWindow (&rc, FALSE);
   }
   InvalidateRect (NULL);
}

void CMainFrame::OnFileGrab() 
{
   m_childwindow.m_grab = !m_childwindow.m_grab;
}

void CMainFrame::OnUpdateFileGrab(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck (m_childwindow.m_grab);	
}

void CMainFrame::OnMagnification1() {  m_childwindow.m_spy->SetScale (1); }
void CMainFrame::OnUpdateMagnification1(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 1); 
   InvalidateRect (NULL);
}
void CMainFrame::OnMagnification2() {  m_childwindow.m_spy->SetScale (2); }
void CMainFrame::OnUpdateMagnification2(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 2); 
   InvalidateRect (NULL);
}
void CMainFrame::OnMagnification4() {  m_childwindow.m_spy->SetScale (4); }
void CMainFrame::OnUpdateMagnification4(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 4); 
   InvalidateRect (NULL);
}
void CMainFrame::OnMagnification8() {  m_childwindow.m_spy->SetScale (8); }
void CMainFrame::OnUpdateMagnification8(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 8); 
   InvalidateRect (NULL);
}
void CMainFrame::OnMagnification16() {  m_childwindow.m_spy->SetScale (16); }
void CMainFrame::OnUpdateMagnification16(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 16); 
   InvalidateRect (NULL);
}
void CMainFrame::OnMagnification32() {  m_childwindow.m_spy->m_scale = 32; }
void CMainFrame::OnUpdateMagnification32(CCmdUI* pCmdUI) { 
		    pCmdUI->SetRadio (m_childwindow.m_spy->m_scale == 32); 
   InvalidateRect (NULL);
}

void CMainFrame::OnZoomIn() {
   m_childwindow.m_spy->SetScale (m_childwindow.m_spy->m_scale * 2);	
   InvalidateRect (NULL);
}

// Toolbar Zoom in and Zoom out buttons
void CMainFrame::OnUpdateZoomIn(CCmdUI* pCmdUI) {
   pCmdUI->Enable (m_childwindow.m_spy->m_scale < 32);	
}
void CMainFrame::OnZoomOut() {
   m_childwindow.m_spy->SetScale (m_childwindow.m_spy->m_scale / 2);	
   InvalidateRect (NULL);
}
void CMainFrame::OnUpdateZoomOut(CCmdUI* pCmdUI) {
   pCmdUI->Enable (m_childwindow.m_spy->m_scale > 1);	
}

// Toolbar always-on-top button
void CMainFrame::OnFileOntop() {
   m_childwindow.m_ontop = !m_childwindow.m_ontop;
   SetWindowPos ((m_childwindow.m_ontop) ? &wndTopMost : &wndNoTopMost, 
      0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
void CMainFrame::OnUpdateFileOntop(CCmdUI* pCmdUI) {
   pCmdUI->SetCheck (m_childwindow.m_ontop);	
}

// Toolbar fixed centre button
void CMainFrame::OnOptionFixCentre() {
   m_childwindow.m_spy->m_fix_centre = !m_childwindow.m_spy->m_fix_centre;
}
void CMainFrame::OnUpdateOptionFixCentre(CCmdUI* pCmdUI) {
   pCmdUI->SetCheck (m_childwindow.m_spy->m_fix_centre);	
}

// Status bar indicators
void CMainFrame::SetStatusTextWidth (int ndx, CString cs) {
   CClientDC dc (this);
   CSize sz = dc.GetOutputTextExtent(cs);
   UINT nID, nStyle;
   int cxWidth;
   m_wndStatusBar.GetPaneInfo (ndx, nID, nStyle, cxWidth);
   //m_wndStatusBar.SetPaneInfo (ndx, nID, nStyle, sz.cx);
}

void CMainFrame::OnUpdateStatusGrab(CCmdUI *pCmdUI) {
   pCmdUI->SetText ("Grab");
   pCmdUI->Enable (m_childwindow.m_grabbing);	
}
void CMainFrame::OnUpdateStatusMagnification(CCmdUI *pCmdUI) {
   CString cs;
   cs.Format ("x %d", m_childwindow.m_spy->m_scale);
   pCmdUI->SetText (cs);
   SetStatusTextWidth (pCmdUI->m_nIndex, cs);
}
void CMainFrame::OnUpdateStatusPosition(CCmdUI *pCmdUI) {
   CString fmt = (GetKeyState (VK_CONTROL) < 0) ? "%02X-%02X %02X-%02X" 
						: "(%d,%d)-(%d-%d)";
   CString cs;
   cs.Format (fmt, 
      m_childwindow.m_status_rect.left, m_childwindow.m_status_rect.top, 
      m_childwindow.m_status_rect.right, m_childwindow.m_status_rect.bottom);
   pCmdUI->SetText (cs);
   SetStatusTextWidth (pCmdUI->m_nIndex, cs);
}
void CMainFrame::OnUpdateStatusSpot(CCmdUI *pCmdUI) {
   CString fmt = (GetKeyState (VK_CONTROL) < 0) ? "%02X %02X" : "(%d,%d)";
   CString cs;
   cs.Format (fmt, 
      m_childwindow.m_status_spot.x - m_childwindow.m_status_base.x, 
      m_childwindow.m_status_spot.y - m_childwindow.m_status_base.y);
   pCmdUI->SetText (cs);
   SetStatusTextWidth (pCmdUI->m_nIndex, cs);
}
void CMainFrame::OnUpdateStatusColor(CCmdUI *pCmdUI) {
   CString fmt = (GetKeyState (VK_CONTROL) < 0) ? "%02X %02X %02X" : "%d,%d,%d";
   CString cs;
   cs.Format (fmt, GetRValue (m_childwindow.m_status_rgb),
		   GetGValue (m_childwindow.m_status_rgb),
		   GetBValue (m_childwindow.m_status_rgb));
   pCmdUI->SetText (cs);
   SetStatusTextWidth (pCmdUI->m_nIndex, cs);
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   switch (nChar) {
   case VK_LEFT:
      m_childwindow.Nudge (CSize (-1, 0));
      break;
   case VK_RIGHT:
      m_childwindow.Nudge (CSize (1, 0));
      break;
   case VK_UP:
      m_childwindow.Nudge (CSize (0, -1));
      break;
   case VK_DOWN:
      m_childwindow.Nudge (CSize (0, 1));
      break;
   case VK_NEXT:
      m_childwindow.Nudge (CSize (0, 10));
      break;
   case VK_PRIOR:
      m_childwindow.Nudge (CSize (0, -10));
      break;
   default: ;
      CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
   }
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
   GetCursorPos (&point);	 // easy way to get screen coords
   CDC cdc;
   cdc.CreateDC ("DISPLAY", "", "", 0);
   m_childwindow.m_status_rgb = cdc.GetPixel (point);
   CFrameWnd::OnMouseMove(nFlags, point);
}

#if 0
/* problems.
   1. original method, start capture in Update, no longer works. Some aspect
      of the capture logic changed, so capture cannot get outside main window.
   2. check box fails: not activated until button up.
   3. attempt to capture NOTIFY for KEYDOWN failed. Dunno why.
*/
void CMainFrame::OnToolbarTarget() {
   m_childwindow.StartSpy ();
}

void CMainFrame::OnUpdateToolbarTarget(CCmdUI* pCmdUI) {
   if (!m_childwindow.m_captured && 
       m_wndToolBar.GetToolBarCtrl().IsButtonPressed (ID_TOOLBAR_TARGET)) {
      m_childwindow.StartSpy ();
      Beep (1000,50);
   }
   //m_wndToolBar.GetToolBarCtrl().SetButtonStyle (ID_TOOLBAR_TARGET, TBBS_CHECKBOX);
   TBBUTTONINFO tbbi = { sizeof(tbbi), TBIF_STYLE, 0};
   m_wndToolBar.GetToolBarCtrl().GetButtonInfo(ID_TOOLBAR_TARGET, &tbbi);
   if (!(tbbi.fsStyle & TBSTYLE_CHECK)) {
      tbbi.fsStyle |= TBSTYLE_CHECK;
      m_wndToolBar.GetToolBarCtrl().SetButtonInfo(ID_TOOLBAR_TARGET, &tbbi);
   }
   pCmdUI->Enable (!m_childwindow.m_captured);
}
BOOL CMainFrame::OnNotifyClick(UINT id, NMHDR* pTTTStruct, LRESULT* pResult) {
   Beep (1000,50);
   return 0;
}
#endif

void CMainFrame::OnSetFocus(CWnd* pOldWnd) {
   CFrameWnd::OnSetFocus(pOldWnd);
   m_childwindow.GotFocus(true);
}

void CMainFrame::OnKillFocus(CWnd* pNewWnd) {
   CFrameWnd::OnKillFocus(pNewWnd);
   m_childwindow.GotFocus(false);
}
