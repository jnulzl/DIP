// DlgTran.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgTran.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTran dialog


CDlgTran::CDlgTran(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTran::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTran)
	m_horOff = 50;
	m_verOff = 50;
	//}}AFX_DATA_INIT

}


void CDlgTran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTran)
	DDX_Text(pDX, IDC_hor, m_horOff);
	DDV_MinMaxInt(pDX, m_horOff, -500, 500);
	DDX_Text(pDX, IDC_ver, m_verOff);
	DDV_MinMaxInt(pDX, m_verOff, -500, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTran, CDialog)
	//{{AFX_MSG_MAP(CDlgTran)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTran message handlers
BOOL CDlgTran::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//获取微调控件句柄
	CSpinButtonCtrl *pHorSpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_HOR_SPIN);
	CSpinButtonCtrl *pVerSpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_VER_SPIN);
	
	//设置伙伴窗口
	pHorSpinCtrl->SetBuddy(GetDlgItem(IDC_hor));
	pVerSpinCtrl->SetBuddy(GetDlgItem(IDC_ver));
	//设置变换范围
	pHorSpinCtrl->SetRange(-500,500);
	pVerSpinCtrl->SetRange(-500,500);
	//设置初始位置(没有也可)
	//pHorSpinCtrl->SetPos(50);//设置旋转按钮位置
	//pVerSpinCtrl->SetPos(50);//设置旋转按钮位置

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





