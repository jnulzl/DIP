// DlgZoom.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgZoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZoom dialog


CDlgZoom::CDlgZoom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgZoom)
	m_zoomX = 1.0f;
	m_zoomY = 1.0f;
	//}}AFX_DATA_INIT
}


void CDlgZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZoom)
	DDX_Text(pDX, IDC_ZOOMX, m_zoomX);
	DDV_MinMaxFloat(pDX, m_zoomX, 0.f, 10.f);
	DDX_Text(pDX, IDC_ZOOMY, m_zoomY);
	DDV_MinMaxFloat(pDX, m_zoomY, 0.f, 10.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZoom, CDialog)
	//{{AFX_MSG_MAP(CDlgZoom)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZoom message handlers
