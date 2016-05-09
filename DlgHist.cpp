// DlgHist.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgHist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHist dialog


CDlgHist::CDlgHist(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHist::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHist)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHist, CDialog)
	//{{AFX_MSG_MAP(CDlgHist)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHist message handlers

void CDlgHist::OnOK() 
{
	// TODO: Add extra validation here
	//if(AfxMessageBox("��ȷ��Ҫ�˳���",MB_YESNO)==IDYES)
	//�����ȡ���ù��ܾ�ע�͸���
	//CDialog::OnOK();
}

void CDlgHist::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(AfxMessageBox("��ȷ��Ҫ�˳���",MB_YESNO)==IDYES)
	//���ٶԻ��� 
	DestroyWindow();//�μ������Σ�p227-p228
	//�����ȡ���ù��ܾ�ע�͸���
	//CDialog::OnCancel();
}

void CDlgHist::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;//�μ������Σ�p227-p228
	CDialog::PostNcDestroy();
}


void CDlgHist::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// �ַ���
	CString str;
	
	// ѭ������
	int i;
	
	// ������
	float fMaxIntensity = 0;
	
	// �豸������
	CPaintDC dc(this);
	
	// ��ȡ��������ľ�̬��
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	pDC->Rectangle(0,0,330,300);
	
	// �������ʶ���
	CPen* pPenRed = new CPen;
	
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	
	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	
	// ����������
	pDC->MoveTo(10,10);
	
	// ��ֱ��
	pDC->LineTo(10,280);
	
	// ˮƽ��
	pDC->LineTo(320,280);
	
	// ����X���ͷ
	pDC->MoveTo(315,275);
	pDC->LineTo(320,280);
	pDC->LineTo(315,285);
	
	// ����Y���ͷ
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);

	// дx��̶�ֵ
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);
	
	// ����X��̶�
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}
	
	// ����������ֵ
	for (i = 0; i < 256; i ++)
	{
		// �ж��Ƿ���ڵ�ǰ���ֵ
		if (m_fIntensity[i] > fMaxIntensity)
		{
			// �������ֵ
			fMaxIntensity = (float)m_fIntensity[i];
		}
	}
	
	// ���������ֵ
 	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%f", fMaxIntensity);
	pDC->TextOut(11, 26, str); 
	
	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);	
	
	// �ж��Ƿ��м���
	if (fMaxIntensity > 0)
	{
		// ����ֱ��ͼ
		for (i = 0; i < 256; i ++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int) (m_fIntensity[i] * 256 / fMaxIntensity));
		}
	}
	
	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	
	
	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	// Do not call CDialog::OnPaint() for painting messages
}



