// DlgLog.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLog dialog


CDlgLog::CDlgLog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLog)
	m_logCoeff = 15.0f;
	//}}AFX_DATA_INIT
}


void CDlgLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLog)
	DDX_Text(pDX, IDC_LOG_COEFF, m_logCoeff);
	DDV_MinMaxFloat(pDX, m_logCoeff, 0.f, 20.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLog, CDialog)
	//{{AFX_MSG_MAP(CDlgLog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLog message handlers
