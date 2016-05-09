// DlgThre.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgThre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThre dialog


CDlgThre::CDlgThre(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThre::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThre)
	m_threshold = 125;
	//}}AFX_DATA_INIT
}


void CDlgThre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThre)
	DDX_Text(pDX, IDC_Threshold, m_threshold);
	DDV_MinMaxInt(pDX, m_threshold, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThre, CDialog)
	//{{AFX_MSG_MAP(CDlgThre)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThre message handlers

BOOL CDlgThre::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//获取微调控件句柄
	CSpinButtonCtrl *pThresholdSpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_THRESHOLD_SPIN);
	
	//设置伙伴窗口
	pThresholdSpinCtrl->SetBuddy(GetDlgItem(IDC_Threshold));
	//设置变换范围
	pThresholdSpinCtrl->SetRange(1,255);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
