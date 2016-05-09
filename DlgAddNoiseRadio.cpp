// DlgAddNoiseRadio.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgAddNoiseRadio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddNoiseRadio dialog


CDlgAddNoiseRadio::CDlgAddNoiseRadio(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddNoiseRadio::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddNoiseRadio)
	m_noise_radio = 0.1f;
	//}}AFX_DATA_INIT
}


void CDlgAddNoiseRadio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddNoiseRadio)
	DDX_Text(pDX, IDC_NOISE_DADIO, m_noise_radio);
	DDV_MinMaxFloat(pDX, m_noise_radio, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddNoiseRadio, CDialog)
	//{{AFX_MSG_MAP(CDlgAddNoiseRadio)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddNoiseRadio message handlers
