// DlgLinear.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgLinear.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinear dialog


CDlgLinear::CDlgLinear(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinear::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLinear)
	m_a = -1.f;
	m_b = 255;
	//}}AFX_DATA_INIT
}


void CDlgLinear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLinear)
	DDX_Text(pDX, IDC_A, m_a);
	DDV_MinMaxFloat(pDX, m_a, -1.f, 1.f);
	DDX_Text(pDX, IDC_B, m_b);
	DDV_MinMaxFloat(pDX, m_b, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLinear, CDialog)
	//{{AFX_MSG_MAP(CDlgLinear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinear message handlers

BOOL CDlgLinear::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��ȡ΢���ؼ����
	CSpinButtonCtrl *pASpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_A_SPIN);
	CSpinButtonCtrl *pBSpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_B_SPIN);
	
	//���û�鴰��
	pASpinCtrl->SetBuddy(GetDlgItem(IDC_A));
	pBSpinCtrl->SetBuddy(GetDlgItem(IDC_B));
	//���ò���
	UDACCEL pAccel;
	pAccel.nSec = 1;
	pAccel.nInc = 1;
	pASpinCtrl->SetAccel(1,&pAccel);
	//���ñ任��Χ
	pASpinCtrl->SetRange(-10,10);
	pBSpinCtrl->SetRange(-255,255);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
