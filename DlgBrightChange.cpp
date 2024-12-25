// DlgBrightChange.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgBrightChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBrightChange dialog


CDlgBrightChange::CDlgBrightChange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBrightChange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBrightChange)
	m_bright = 60;
	//}}AFX_DATA_INIT
}


void CDlgBrightChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBrightChange)
	DDX_Control(pDX, IDC_HOR_SCROLLBAR, m_HorScrollBar);
	DDX_Text(pDX, IDC_BRIGHTCHANGE, m_bright);
	DDV_MinMaxInt(pDX, m_bright, 0, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBrightChange, CDialog)
	//{{AFX_MSG_MAP(CDlgBrightChange)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBrightChange message handlers

BOOL CDlgBrightChange::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// ����ˮƽ�������Ĺ�����ΧΪ1��100   
    m_HorScrollBar.SetScrollRange(1, 1000);   
    // ����ˮƽ�������ĳ�ʼλ��Ϊ20   
    m_HorScrollBar.SetScrollPos(60);   
    // �ڱ༭������ʾ60   
    SetDlgItemInt(IDC_BRIGHTCHANGE, 60);   

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgBrightChange::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int pos = m_HorScrollBar.GetScrollPos();    // ��ȡˮƽ��������ǰλ��   
  
    switch (nSBCode)    
    {    
        // ����������һ�У���pos��1   
        case SB_LINEUP:    
            pos -= 1;    
            break;    
        // ������ҹ���һ�У���pos��1   
        case SB_LINEDOWN:    
            pos  += 1;    
            break;    
        // ����������һҳ����pos��10   
        case SB_PAGEUP:    
            pos -= 10;    
            break;    
        // ������ҹ���һҳ����pos��10   
        case SB_PAGEDOWN:    
            pos  += 10;    
            break;    
        // �������������ˣ���posΪ1   
        case SB_TOP:    
            pos = 1;    
            break;    
        // ������������Ҷˣ���posΪ100   
        case SB_BOTTOM:    
            pos = 1000;    
            break;      
        // ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ   
        case SB_THUMBPOSITION:    
            pos = nPos;    
            break;    
        // �����m_horiScrollbar.SetScrollPos(pos);ִ��ʱ��ڶ��ν���˺���������ȷ��������λ�ã����һ�ֱ�ӵ�default��֧�������ڴ˴����ñ༭������ʾ��ֵ   
        default:    
            SetDlgItemInt(IDC_BRIGHTCHANGE, pos);   
            return;    
    }    
  
    // ���ù�����λ��   
    m_HorScrollBar.SetScrollPos(pos); 
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
