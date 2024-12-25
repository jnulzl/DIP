// DlgMedianFilter.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgMedianFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilter dialog


CDlgMedianFilter::CDlgMedianFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMedianFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMedianFilter)
	m_temp_height = 3;
	m_temp_width = 3;
	//}}AFX_DATA_INIT
}


void CDlgMedianFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMedianFilter)
	DDX_Text(pDX, IDC_TEMP_HEIGHT, m_temp_height);
	DDV_MinMaxInt(pDX, m_temp_height, 0, 99);
	DDX_Text(pDX, IDC_TEMP_WIDTH, m_temp_width);
	DDV_MinMaxInt(pDX, m_temp_width, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMedianFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgMedianFilter)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilter message handlers
