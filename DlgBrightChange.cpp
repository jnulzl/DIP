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
	// 设置水平滚动条的滚动范围为1到100   
    m_HorScrollBar.SetScrollRange(1, 1000);   
    // 设置水平滚动条的初始位置为20   
    m_HorScrollBar.SetScrollPos(60);   
    // 在编辑框中显示60   
    SetDlgItemInt(IDC_BRIGHTCHANGE, 60);   

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgBrightChange::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int pos = m_HorScrollBar.GetScrollPos();    // 获取水平滚动条当前位置   
  
    switch (nSBCode)    
    {    
        // 如果向左滚动一列，则pos减1   
        case SB_LINEUP:    
            pos -= 1;    
            break;    
        // 如果向右滚动一列，则pos加1   
        case SB_LINEDOWN:    
            pos  += 1;    
            break;    
        // 如果向左滚动一页，则pos减10   
        case SB_PAGEUP:    
            pos -= 10;    
            break;    
        // 如果向右滚动一页，则pos加10   
        case SB_PAGEDOWN:    
            pos  += 10;    
            break;    
        // 如果滚动到最左端，则pos为1   
        case SB_TOP:    
            pos = 1;    
            break;    
        // 如果滚动到最右端，则pos为100   
        case SB_BOTTOM:    
            pos = 1000;    
            break;      
        // 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值   
        case SB_THUMBPOSITION:    
            pos = nPos;    
            break;    
        // 下面的m_horiScrollbar.SetScrollPos(pos);执行时会第二次进入此函数，最终确定滚动块位置，并且会直接到default分支，所以在此处设置编辑框中显示数值   
        default:    
            SetDlgItemInt(IDC_BRIGHTCHANGE, pos);   
            return;    
    }    
  
    // 设置滚动块位置   
    m_HorScrollBar.SetScrollPos(pos); 
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
