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
	//定义过滤文件类型
	UpdateData(TRUE); 
	static char filePath[] = "BMP文件(*.bmp)|*.bmp|PNG文件(*.png)|*.png|PPM文件(*.ppm)|*.ppm|PGM文件(*.pgm)|*.pgm|PBM文件(*.pbm)|*.pbm|JPG文件(*.jpg)|*.jpg|FITS文件(*.fits)|*.fits|JPEG文件(*.jpeg)|*.jpeg|TIFF文件(*.tiff)|*.tiff|TIF文件(*.tif)|*.tif|全部文件(*.*)|*.*|";
	//定义文件对话框对象
	CFileDialog dlg(TRUE,"bmp","newImage",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "新建图像";	
	//定义文件路径+文件名
	CString fileName;
	//运行打开文件对话框
	int ret = dlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		fileName = dlg.GetPathName();
		m_filePath = fileName;
	}
	UpdateData(FALSE); 
}
