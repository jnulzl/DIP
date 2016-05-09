// DlgChangeBright.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgChangeBright.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright dialog


CDlgChangeBright::CDlgChangeBright(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeBright::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangeBright)
	m_bright = 60;
	//}}AFX_DATA_INIT
}


void CDlgChangeBright::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeBright)
	DDX_Text(pDX, IDC_BRIGHTCHANGE, m_bright);
	DDV_MinMaxInt(pDX, m_bright, 0, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeBright, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeBright)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright dialog


CDlgChangeBright::CDlgChangeBright(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeBright::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangeBright)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgChangeBright::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeBright)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeBright, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeBright)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright dialog


CDlgChangeBright::CDlgChangeBright(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeBright::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChangeBright)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgChangeBright::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangeBright)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangeBright, CDialog)
	//{{AFX_MSG_MAP(CDlgChangeBright)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeBright message handlers
