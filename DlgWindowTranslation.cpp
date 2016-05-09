// DlgWindowTranslation.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgWindowTranslation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWindowTranslation dialog


CDlgWindowTranslation::CDlgWindowTranslation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWindowTranslation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWindowTranslation)
	m_High = 50;
	m_Low = 180;
	//}}AFX_DATA_INIT
}


void CDlgWindowTranslation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWindowTranslation)
	DDX_Text(pDX, IDC_HIGH, m_High);
	DDV_MinMaxUInt(pDX, m_High, 0, 255);
	DDX_Text(pDX, IDC_LOW, m_Low);
	DDV_MinMaxUInt(pDX, m_Low, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWindowTranslation, CDialog)
	//{{AFX_MSG_MAP(CDlgWindowTranslation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWindowTranslation message handlers
