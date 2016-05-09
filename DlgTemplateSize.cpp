// DlgTemplateSize.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgTemplateSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplateSize dialog


CDlgTemplateSize::CDlgTemplateSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemplateSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemplateSize)
	m_template_size = 3;
	//}}AFX_DATA_INIT
}


void CDlgTemplateSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemplateSize)
	DDX_Text(pDX, IDC_TEMPLATE_SIZE, m_template_size);
	DDV_MinMaxFloat(pDX, m_template_size, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemplateSize, CDialog)
	//{{AFX_MSG_MAP(CDlgTemplateSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplateSize message handlers

BOOL CDlgTemplateSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	//设置滚动范围为：获取微调控件句柄
	CSpinButtonCtrl *pTemplateSizeSpinCtrl=(CSpinButtonCtrl*)GetDlgItem(IDC_TEMPLATESIZE_SPIN);
	
	//设置伙伴窗口
	pTemplateSizeSpinCtrl->SetBuddy(GetDlgItem(IDC_TEMPLATE_SIZE));
	//设置变换范围
	pTemplateSizeSpinCtrl->SetRange(1,100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
