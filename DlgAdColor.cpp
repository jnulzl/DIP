// DlgAdColor.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgAdColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAdColor dialog


CDlgAdColor::CDlgAdColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAdColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAdColor)
	m_R = 100;
	m_G = 255;
	m_B = 100;
	//}}AFX_DATA_INIT
}


void CDlgAdColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAdColor)
	DDX_Text(pDX, IDC_R, m_R);
	DDV_MinMaxInt(pDX, m_R, 0, 255);
	DDX_Text(pDX, IDC_G, m_G);
	DDV_MinMaxInt(pDX, m_G, 0, 255);
	DDX_Text(pDX, IDC_B, m_B);
	DDV_MinMaxInt(pDX, m_B, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAdColor, CDialog)
	//{{AFX_MSG_MAP(CDlgAdColor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAdColor message handlers
