// DlgMosaic.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgMosaic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMosaic dialog


CDlgMosaic::CDlgMosaic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMosaic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMosaic)
	m_widht = 3;
	m_height = 3;
	//}}AFX_DATA_INIT
}


void CDlgMosaic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMosaic)
	DDX_Text(pDX, IDC_HEIGHT, m_widht);
	DDV_MinMaxInt(pDX, m_widht, 3, 1000);
	DDX_Text(pDX, IDC_WIDTH, m_height);
	DDV_MinMaxInt(pDX, m_height, 3, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMosaic, CDialog)
	//{{AFX_MSG_MAP(CDlgMosaic)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMosaic message handlers
