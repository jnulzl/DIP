// DlgPower.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPower dialog


CDlgPower::CDlgPower(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPower::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPower)
	m_C = 1.0f;
	m_Gamma = 1.0f;
	//}}AFX_DATA_INIT
}


void CDlgPower::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPower)
	DDX_Text(pDX, IDC_POWER_C, m_C);
	DDV_MinMaxFloat(pDX, m_C, 0.f, 20.f);
	DDX_Text(pDX, IDC_POWER_GAMMA, m_Gamma);
	DDV_MinMaxFloat(pDX, m_Gamma, 0.f, 20.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPower, CDialog)
	//{{AFX_MSG_MAP(CDlgPower)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPower message handlers
