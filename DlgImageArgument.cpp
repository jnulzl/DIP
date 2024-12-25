// DlgImageArgument.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "DlgImageArgument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageArgument dialog


CDlgImageArgument::CDlgImageArgument(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageArgument::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImageArgument)
	m_ImageHeight = 480;
	m_ImageWidth = 640;
	m_ImageNBIts = 8;
	m_filePath = _T("H:\\img\\newImage.bmp");
	//}}AFX_DATA_INIT
}


void CDlgImageArgument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImageArgument)
	DDX_Text(pDX, IDC_IMAGEHEIGHT, m_ImageHeight);
	DDV_MinMaxUInt(pDX, m_ImageHeight, 0, 2000);
	DDX_Text(pDX, IDC_IMAGEWIDTH, m_ImageWidth);
	DDV_MinMaxUInt(pDX, m_ImageWidth, 0, 2000);
	DDX_Text(pDX, IDC_NBITS, m_ImageNBIts);
	DDV_MinMaxUInt(pDX, m_ImageNBIts, 0, 32);
	DDX_Text(pDX, IDC_FILEPATH, m_filePath);
	DDV_MaxChars(pDX, m_filePath, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImageArgument, CDialog)
	//{{AFX_MSG_MAP(CDlgImageArgument)
	ON_BN_CLICKED(IDC_BUTTONSCAN, OnButtonScan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageArgument message handlers

void CDlgImageArgument::OnButtonScan() 
{
	// TODO: Add your control notification handler code here
	//��������ļ�����
	UpdateData(TRUE); 
	static char filePath[] = "BMP�ļ�(*.bmp)|*.bmp|PNG�ļ�(*.png)|*.png|PPM�ļ�(*.ppm)|*.ppm|PGM�ļ�(*.pgm)|*.pgm|PBM�ļ�(*.pbm)|*.pbm|JPG�ļ�(*.jpg)|*.jpg|FITS�ļ�(*.fits)|*.fits|JPEG�ļ�(*.jpeg)|*.jpeg|TIFF�ļ�(*.tiff)|*.tiff|TIF�ļ�(*.tif)|*.tif|ȫ���ļ�(*.*)|*.*|";
	//�����ļ��Ի������
	CFileDialog dlg(TRUE,"bmp","newImage",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "�½�ͼ��";	
	//�����ļ�·��+�ļ���
	CString fileName;
	//���д��ļ��Ի���
	int ret = dlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		fileName = dlg.GetPathName();
		m_filePath = fileName;
	}
	UpdateData(FALSE); 
}
