// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DIP1.h"

#include "MainFrm.h"
#include <iostream>
#include <strstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "DIP1View.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
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
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	/*m_wndStatusBarCtrl = new CStatusBarCtrl();
	RECT rec;
	GetWindowRect(&rec);
	rec.top = rec.bottom - 20;
	m_wndStatusBarCtrl->Create(WS_BORDER | WS_VISIBLE | CBRS_BOTTOM, rec, this, 3);
	int nparts[4] = { 100, 200, 300, -1 };
	m_wndStatusBarCtrl->SetParts(4, nparts);
	m_wndStatusBarCtrl->SetText("第一个", 0, 0);
	m_wndStatusBarCtrl->SetText("第二个", 1, 0);*/

	//创建状态栏
	//
	//if (!m_wndStatusBar.Create(this) /*||
	//	!m_wndStatusBar.SetIndicators(indicators,
	//	sizeof(indicators) / sizeof(UINT))*/)
	//{
	//	TRACE0("Failed to create status bar\n");
	//	return -1;      // fail to create
	//}
	//int nparts[4] = { 100, 200, 300, -1};
	////CPoint point = CDIP1View::getPixel();
	//std::strstream ss;
	//std::string s;
	//ss << point.x;
	//s = ss.str();
	//std::string X = "X = " + s;	
	//ss << point.y;
	//s = ss.str();	
	//std::string Y = "Y = " + s;
	//m_wndStatusBar.GetStatusBarCtrl().SetParts(4, nparts);
	//m_wndStatusBar.GetStatusBarCtrl().SetText(X.c_str(), 0, 0);
	//m_wndStatusBar.GetStatusBarCtrl().SetText(Y.c_str(), 3, 0);
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.style=WS_SYSMENU|WS_OVERLAPPED|WS_MINIMIZEBOX;
	m_strTitle = " 数字图像处理 "; 
	//cs.x=cs.y=0; //置于屏幕左上角
	//cs.cx=GetSystemMetrics(SM_CXMAXIMIZED); //最大化并显示状态栏
	//cs.cy=GetSystemMetrics(SM_CYMAXIMIZED); 
	cs.style &= ~FWS_ADDTOTITLE ;//防止MFC在窗口标题栏上添加文档名
 
	return CFrameWnd::PreCreateWindow(cs); 
	//return TRUE;
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







