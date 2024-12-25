// DIP1View.cpp : implementation of the CDIP1View class
//

#include "stdafx.h"
#include "DIP1.h"

#include "DIP1Doc.h"
#include "DIP1View.h"

//**************************************************************************
#include "cv.h"
#include "highgui.h"
//**************************************************************************

//////////////////////////////////////////////////////////////////////////
#include "DlgTran.h"
#include "DlgThre.h"
#include "DlgLinear.h"
#include "DlgZoom.h"
#include "DlgWindowTranslation.h"
#include "DlgLog.h"
#include "DlgPower.h"
#include "DlgMedianFilter.h"
#include "DlgAddNoiseRadio.h"
#include "DlgTemplateSize.h"
#include "DlgAdColor.h"
#include "DlgBrightChange.h"
#include "DlgMosaic.h"
#include "DlgHist.h"
#include "DlgImageArgument.h"
//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIP1View

IMPLEMENT_DYNCREATE(CDIP1View, CScrollView)

BEGIN_MESSAGE_MAP(CDIP1View, CScrollView)
	//{{AFX_MSG_MAP(CDIP1View)
	ON_COMMAND(ID_OPEN_IMAGE, OnOpenImage)
	ON_COMMAND(ID_SAVE_IMAGE, OnSaveImage)
	ON_COMMAND(ID_IMAGE_TRANSLATION, OnImageTranslation)
	ON_COMMAND(ID_IMAGE_THRESHOLD, OnImageThreshold)
	ON_COMMAND(ID_RGB2_GRAY, OnRgb2Gray)
	ON_COMMAND(ID_IMAGE_CONTRARY, OnImageContrary)
	ON_COMMAND(ID_Gauss_Lap_Edge, OnGaussLapEdge)
	ON_COMMAND(ID_PreWitt_Edge, OnPreWittEdge)
	ON_COMMAND(ID_Robert_Edge, OnRobertEdge)
	ON_COMMAND(ID_Sobel_Edge, OnSobelEdge)
	ON_COMMAND(ID_IMAGE_LINEAR, OnImageLinear)
	ON_COMMAND(ID_IMAGE_MIRRORHOR, OnImageMirrorhor)
	ON_COMMAND(ID_IMAGE_MIRRORVER, OnImageMirrorver)
	ON_COMMAND(ID_IMAGE_ZOOM, OnImageZoom)
	ON_COMMAND(ID_IMAGE_BIG, OnImageBig)
	ON_COMMAND(ID_IMAGE_SMALL, OnImageSmall)
	ON_COMMAND(ID_IMAGE_TRANSPOSE, OnImageTranspose)
	ON_COMMAND(ID_WINDOW_TRANSLATION, OnWindowTranslation)
	ON_COMMAND(ID_IMAGE_LOG, OnImageLog)
	ON_COMMAND(ID_POWER, OnPower)
	ON_COMMAND(ID_AREA_AVERAGE, OnAreaAverage)
	ON_COMMAND(ID_WEIGHT_AVERAGE, OnWeightAverage)
	ON_COMMAND(ID_MEDIAN_FILTER, OnMedianFilter)
	ON_COMMAND(ID_MAX_FILTER, OnMaxFilter)
	ON_COMMAND(ID_MIN_FILTER, OnMinFilter)
	ON_COMMAND(ID_PLUS_MEDIANFilter, OnPlusMedianFilter)
	ON_COMMAND(ID_IMAGE_SALTPEPPER, OnImageSaltpepper)
	ON_COMMAND(ID_PROFILE_DETECT, OnProfileDetect)
	ON_COMMAND(ID_SHOW_ORIGIN_IMAGE, OnShowOriginImage)
	ON_COMMAND(ID_GRAY2_RGB, OnGray2Rgb)
	ON_COMMAND(ID_SHOW_PREIMAGE, OnShowPreimage)
	ON_COMMAND(ID_KRISCH_EDGE, OnKrischEdge)
	ON_COMMAND(ID_RGB_ADDCOLOR, OnRgbAddColor)
	ON_COMMAND(ID_BRIGHT_CHANGE, OnBrightChange)
	ON_COMMAND(ID_MOSAIC, OnMosaic)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_IMAGE_RANDNOISE, OnImageRandNoise)
	ON_COMMAND(ID_R_COLOR, OnRColor)
	ON_COMMAND(ID_B_COLOR, OnBColor)
	ON_COMMAND(ID_G_COLOR, OnGColor)
	ON_COMMAND(ID_TO_DOWNSCAN, OnToDownScan)
	ON_COMMAND(ID_TO_UPSCAN, OnToUpscan)
	ON_COMMAND(ID_TORIGHTSCAN, OnTorightScan)
	ON_COMMAND(ID_TOLEFTSCAN, OnToleftScan)
	ON_COMMAND(ID_IMAGE_HistogramEqualization, OnImageHistogramEqualization)
	ON_COMMAND(ID_SAVE_DATA, OnSaveData)
	ON_COMMAND(ID_IMAGE_FOURIER, OnImageFourier)
	ON_COMMAND(ID_RGB2_HSI, OnRgb2Hsi)
	ON_COMMAND(ID_GRAY_HIST, OnGrayHist)
	ON_COMMAND(ID_B_HIST, OnBHist)
	ON_COMMAND(ID_R_HIST, OnRHist)
	ON_COMMAND(ID_G_HIST, OnGHist)
	ON_COMMAND(ID_LAPLACIAN_EDGE, OnLaplacianEdge)
	ON_COMMAND(ID_OTSU, OnOtsu)
	ON_COMMAND(ID_APAPTIVE_THRESHOLD, OnApaptiveThreshold)
	ON_COMMAND(ID_SHUIPING_EROSION, OnShuiPingErosion)
	ON_COMMAND(ID_CHUIZHI_EROSION, OnChuiZhiErosion)
	ON_COMMAND(ID_SHUIPING_DILATION, OnShuiPingDilation)
	ON_COMMAND(ID_CHUIZHI_DILATION, OnChuiZhiDilation)
	ON_COMMAND(ID_DONGXI_EROSION, OnDongXiErosion)
	ON_COMMAND(ID_XIDONG_EROSION, OnXiDongErosion)
	ON_COMMAND(ID_DONGXI_DILATION, OnDongXiDilation)
	ON_COMMAND(ID_XIDONG_DILATION, OnXiDongDilation)
	ON_COMMAND(ID_IMAGE_EROSION, OnImageErosion)
	ON_COMMAND(ID_IMAGE_DILATION, OnImageDilation)
	ON_COMMAND(ID_TEST_OPENCV, OnTestOpenCV)
	ON_COMMAND(ID_CV_FACEDETECTION, OnCvFaceDetection)
	ON_COMMAND(ID_CV_ERODE, OnCvErode)
	ON_COMMAND(ID_CV_DILATE, OnCvDilate)
	ON_COMMAND(ID_CV_CORNERDETECTIPN, OnCvCornerDetectipn)
	ON_COMMAND(ID_CV_SOBELEDGE, OnCvSobelEdge)
	ON_COMMAND(ID_CV_CANNY_EDGE, OnCvCannyEdge)
	ON_COMMAND(ID_CV_SPLIT, OnCvSplit)
	ON_COMMAND(ID_CV_LAPLACIAN, OnCvLaplacian)
	ON_COMMAND(ID_CV_PCFACEDETECTION, OnCvPcFaceDetection)
	ON_COMMAND(ID_FACE_DETECTIONYUSHIQI, OnFaceDetectionYushiqi)
	ON_COMMAND(ID_CV_SIMPLEBLUR, OnCvSimpleBlur)
	ON_COMMAND(ID_CVMEDIANBLUR, OnCvMedianBlur)
	ON_COMMAND(ID_CVGAUSSIANBLUR, OnCvGaussianBlur)
	ON_COMMAND(ID_CVPLOTHIST, OnCvPlotHist)
	ON_COMMAND(CD_CVHISTEqualize, OnCvHistEqualize)
	ON_COMMAND(ID_NEW_IMAGE, OnNewImage)
	ON_COMMAND(ID_CLEAR_IMAGE, OnClearImage)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIP1View construction/destruction

CDIP1View::CDIP1View()
{
	// TODO: add construction code here
}

CDIP1View::~CDIP1View()
{
}

BOOL CDIP1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDIP1View drawing

void CDIP1View::OnDraw(CDC* pDC)
{
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SWidth = m_dib.GetShowWidth();
		int SHeight = m_dib.GetShowHeight();
		//图像居中显示
		CRect rect;
		GetWindowRect(&rect);
		int topLeftX = (rect.Width()-m_dib.GetShowWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetShowHeight())/2;//图像显示位置左上角Y坐标
		//检查显示图像的左上角坐标是否小于0
		if(topLeftX<0)
			topLeftX = 0;
		if(topLeftY<0)
			topLeftY = 0;
		//显示图像
		m_dib.Draw(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,SHeight));
		SetScrollSizes(MM_TEXT, CSize(SWidth, SHeight));
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIP1View printing

BOOL CDIP1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDIP1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDIP1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDIP1View diagnostics

#ifdef _DEBUG
void CDIP1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDIP1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDIP1Doc* CDIP1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIP1Doc)));
	return (CDIP1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIP1View message handlers

//CPoint CDIP1View::getxy()
//{
//	CPoint p;
//	GetCursorPos(&p);
//	return p;
//}
//int CDIP1View::getPixel()
//{
//	return 0;
//}

void CDIP1View::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();	
	// TODO: Add your specialized code here and/or call the base class
	CRect windowsSize;
	GetWindowRect(&windowsSize);
	SetScrollSizes(MM_TEXT, CSize(windowsSize.Width(), windowsSize.Height()));			
	//SetScrollSizes(MM_TEXT, CSize(windowsSize.Height(), windowsSize.Width()));	
}
//提示消息函数
int CDIP1View::alert(int temp)
{
	switch(temp)
	{
		case 1:
		{
			if(!m_dib.IsValid())//判断图像是否已打开
			{
				AfxMessageBox("图像未打开，请先打开图像！");
				return 1;
			}
			else 
				return 0;
		}
		break;
		case 2:
		{
			if(!m_dib.IsValid())//判断图像是否已打开
			{
				AfxMessageBox("图像未打开，请先打开图像！");
				return 1;
			}
			else if(24 == m_dib.GetBitCount())//判断图像是否是灰度图像
			{
				AfxMessageBox("请先将原图像转化为灰度图像！");
				return 1;
			}
			else 
				return 0;
		}
		break;
		case 3:
		{
			if(!m_dib.IsValid())//判断图像是否已打开
			{
				AfxMessageBox("图像未打开，请先打开图像！");
				return 1;
			}
			else if(8 == m_dib.GetBitCount())//判断图像是否是彩色图像
			{
				AfxMessageBox("当前图像必须为彩色图像！");
				return 1;
			}
			else 
				return 0;
		}
		break;
	}
	return 0;
}
/*
	打开图像
*/
void CDIP1View::OnOpenImage() 
{
	// TODO: Add your command handler code here

	//定义过滤文件类型
	static char filePath[] = "BMP文件(*.bmp)|*.bmp|PNG文件(*.png)|*.png|PPM文件(*.ppm)|*.ppm|PGM文件(*.pgm)|*.pgm|PBM文件(*.pbm)|*.pbm|JPG文件(*.jpg)|*.jpg|FITS文件(*.fits)|*.fits|IMG文件(*.IMG)|*.IMG|JPEG文件(*.jpeg)|*.jpeg|TIFF文件(*.tiff)|*.tiff|TIF文件(*.tif)|*.tif|全部文件(*.*)|*.*|";
	//定义文件对话框对象
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "打开图像";
	//定义文件路径+文件名
	CString fileName;
	//运行打开文件对话框
	int ret = dlg.DoModal();

	if(IDOK == ret)
	{
		//获取所选择图像路径
		fileName = dlg.GetPathName();
		//获取所选择图像的扩展名
		CString ExtName = dlg.GetFileExt();
		if(ExtName == "fits")//加载图像并设置相关变量
			m_dib.LoadFitsFile(fileName);
		else
			//m_dib.LoadFromFile(fileName);
			m_dib.LoadFileFromOpenCV(fileName);

		if(!m_dib.IsValid())
		{
			AfxMessageBox("图像打开失败!");
			return;
		}
		//设置显示图像的宽度
		m_dib.SetShowWidth(m_dib.GetWidth());
		//设置显示图像的高度
		m_dib.SetShowHeight(m_dib.GetHeight());
		//保存原始数据
		m_dib.SaveOriginImage();
		//***********************其实该句可以不要**********************
		//保存上一步图像数据
		m_dib.SavePreImage();//其实该句可以不要！！！
		//***********************其实该句可以不要**********************
		//初始化非全屏显示
	//	m_dib.isFullScreen = false;
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	保存图像
*/
void CDIP1View::OnSaveImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//定义过滤文件类型
	static char filePath[] = "BMP文件(*.bmp)|*.bmp|PNG文件(*.png)|*.png|PPM文件(*.ppm)|*.ppm|PGM文件(*.pgm)|*.pgm|PBM文件(*.pbm)|*.pbm|JPG文件(*.jpg)|*.jpg|JPEG文件(*.jpeg)|*.jpeg|TIFF文件(*.tiff)|*.tiff|TIF文件(*.tif)|*.tif|全部文件(*.*)|*.*|";
	//定义文件对话框对象
	LPCTSTR imgName = m_dib.GetFileName();
	//AfxMessageBox(imgName);
	CFileDialog dlg(FALSE,"bmp",imgName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "图像另存为";
	CString fileName;
	//运行打开文件对话框
	int ret = dlg.DoModal();
	if(IDOK == ret)
	{
		//获取所选择图像路径
		fileName = dlg.GetPathName();
		if(!m_dib.SaveFileBasedOpenCV(fileName))
		{
			AfxMessageBox("图像保存失败!");
			return;
		}
		/*if(!m_dib.SaveToFile(fileName))
		{
			AfxMessageBox("图像保存失败!");
			return;
		}*/
	}
	//刷新屏幕
	Invalidate(1);
}

/*
	图像平移
*/
void CDIP1View::OnImageTranslation() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgTran Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int horOff = Mydlg.m_horOff;
		int verOff = Mydlg.m_verOff;
		m_dib.ImageTranslation(horOff,verOff);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	图像阈值化处理
*/
void CDIP1View::OnImageThreshold() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgThre Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int threshold = Mydlg.m_threshold;
		m_dib.ImageThreshold(threshold);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	图像灰度化
*/
void CDIP1View::OnRgb2Gray() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.SavePreImage();
	m_dib.RgbToGrade();
	//刷新屏幕
	Invalidate(1);
}
/*
	图像彩色化
*/
void CDIP1View::OnGray2Rgb() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//if(!m_dib.originImageIsRgb)
	
	m_dib.GradeToRgb();

	//刷新屏幕
	Invalidate(1);
}
/*
	图像反转
*/
void CDIP1View::OnImageContrary() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageContrary();
	//刷新屏幕
	Invalidate(1);
}
/*
	高斯拉普拉边缘检测
*/
void CDIP1View::OnGaussLapEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.Guasslaplacian();
	//刷新屏幕
	Invalidate(1);
}
/*
	PreWitt边缘检测
*/
void CDIP1View::OnPreWittEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.PreWittEdge();
	//刷新屏幕
	Invalidate(1);
}
/*
	Robert边缘检测
*/
void CDIP1View::OnRobertEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.RobertEdge();
	//刷新屏幕
	Invalidate(1);
}
/*
	Sobel边缘检测
*/
void CDIP1View::OnSobelEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.SobelEdge();
	//刷新屏幕
	Invalidate(1);
}
/*
	Krisch边缘检测
*/
void CDIP1View::OnKrischEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.KrischEdge();
	//刷新屏幕
	Invalidate(1);
}
/*
	Laplacian边缘检测
*/
void CDIP1View::OnLaplacianEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.Laplacian();
	//刷新屏幕
	Invalidate(1);
}


/*
	图像线性变换
*/
void CDIP1View::OnImageLinear() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgLinear Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float a = Mydlg.m_a;
		int b = Mydlg.m_b;
		m_dib.ImageLinear(a,b);
	}
	//刷新屏幕
	Invalidate(1);
}


/*
	图像水平镜像
*/
void CDIP1View::OnImageMirrorhor() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageMirror();
	//刷新屏幕
	Invalidate(1);
}
/*
	图像垂直镜像
*/
void CDIP1View::OnImageMirrorver() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageMirror1();
	//刷新屏幕
	Invalidate(1);
}
/*
	图像缩放
*/
void CDIP1View::OnImageZoom() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgZoom Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float a = Mydlg.m_zoomX;
		float b = Mydlg.m_zoomY;
		m_dib.ImageZoom(a,b);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	图像放大
*/
void CDIP1View::OnImageBig() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageZoom(1.25,1.25);
	//刷新屏幕
	Invalidate(1);
}
/*
	图像缩小
*/
void CDIP1View::OnImageSmall() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageZoom(0.75,0.75);
	//刷新屏幕
	Invalidate(1);
}
/*
	图像转置
*/
void CDIP1View::OnImageTranspose() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageTranspose();
	//刷新屏幕
	Invalidate(1);
}
/*
	窗口变换
*/
void CDIP1View::OnWindowTranslation() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgWindowTranslation Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		UINT a = Mydlg.m_Low;
		UINT b = Mydlg.m_High;
		m_dib.ImageWindowTranslation(a,b);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	对数变换
*/
void CDIP1View::OnImageLog() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgLog Mydlg;
	int ret = Mydlg.DoModal();
	
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float a = Mydlg.m_logCoeff;
		m_dib.ImageLog(a);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	幂次变换
*/
void CDIP1View::OnPower() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgPower Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float a = Mydlg.m_C;
		float b = Mydlg.m_Gamma;
		m_dib.ImagePower(a,b);
	}
	//刷新屏幕
	Invalidate(1);
}

/*
	邻域平均
*/
void CDIP1View::OnAreaAverage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgTemplateSize Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int size = Mydlg.m_template_size;
		m_dib.ImageAreaAverage(size);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	加权平均
*/
void CDIP1View::OnWeightAverage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageWeightAverage();
	//刷新屏幕
	Invalidate(1);
}
/*
	中值滤波
*/
void CDIP1View::OnMedianFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,2);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	最大值滤波
*/
void CDIP1View::OnMaxFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,3);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	最小值滤波
*/
void CDIP1View::OnMinFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,1);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	十字型中值滤波
*/
void CDIP1View::OnPlusMedianFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImagePlusMedianFilter(Height,Width);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	增加随机噪声
*/
void CDIP1View::OnImageRandNoise() 
{
	// TODO: Add your command handler code here
		if(alert(1))
		return;
	CDlgAddNoiseRadio Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float radio = Mydlg.m_noise_radio;
		m_dib.AddRandNoise(radio);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	增加椒盐噪声
*/
void CDIP1View::OnImageSaltpepper() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgAddNoiseRadio Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		float radio = Mydlg.m_noise_radio;
		m_dib.AddSaltPepperNoise(radio);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
	轮廓检测
*/
void CDIP1View::OnProfileDetect() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.ImageProfileDetect();
	//刷新屏幕
	Invalidate(1);
}
/*
	显示原图像
*/
void CDIP1View::OnShowOriginImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ShowOriginImage();
	//刷新屏幕
	Invalidate(1);
}

/*
	显示上一步图像
*/

void CDIP1View::OnShowPreimage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ShowPreImage();
	//刷新屏幕
	Invalidate(1);
}



/*
功能：
	彩色图像着色
*/
void CDIP1View::OnRgbAddColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgAdColor Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int mR = Mydlg.m_R;
		int mG = Mydlg.m_G;
		int mB = Mydlg.m_B;
		m_dib.RgbAddColor(mR,mG,mB);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	改变图像亮度
*/
void CDIP1View::OnBrightChange() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgBrightChange Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int radio = Mydlg.m_bright;
		m_dib.ChangeBright(radio);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	马赛克效应
*/
void CDIP1View::OnMosaic() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgMosaic Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int width = Mydlg.m_widht;
		int height = Mydlg.m_height;
		m_dib.Mosaic(width,height);
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	实现鼠标右键功能
*/
void CDIP1View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu; //菜单包含主菜单和子菜单
	CMenu *pSubMenu;//右键菜单

	//加载主菜单资源到menu对象中
	menu.LoadMenu(IDR_MOUSE_RIGHT);

	//因为右键是弹出式菜单，不包含主菜单，所以取子菜单[这里取得是第一个(0)子菜单]
		
	pSubMenu = menu.GetSubMenu(0);

	
	//将坐标值由客户坐标转换为屏幕坐标
	ClientToScreen(&point);
	//弹出式右键菜单，菜单左侧与point.x坐标值对齐
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	CScrollView::OnRButtonDown(nFlags, point);
}


/*
功能：
	获取R分量
*/
void CDIP1View::OnRColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(2);//计算机中是按B、G、R存储像素的
	//刷新屏幕
	Invalidate(1);
}

/*
功能：
	获取G分量
*/
void CDIP1View::OnGColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(1);//计算机中是按B、G、R存储像素的
	//刷新屏幕
	Invalidate(1);
}

/*
功能：
	获取B分量
*/
void CDIP1View::OnBColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(0);//计算机中是按B、G、R存储像素的
	//刷新屏幕
	Invalidate(1);
}

/*
功能：
	图像向下显示特效
*/
void CDIP1View::OnToDownScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************刷新屏幕******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//用白色填充屏幕
	pDC->FillRect(&rect,&brush);
	//******************************刷新屏幕******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SWidth = m_dib.GetShowWidth();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//图像显示位置左上角Y坐标
		//显示图像
		m_dib.ToDownScan(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,1));
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	图像向上显示特效
*/
void CDIP1View::OnToUpscan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************刷新屏幕******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//用白色填充屏幕
	pDC->FillRect(&rect,&brush);
	//******************************刷新屏幕******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SWidth = m_dib.GetShowWidth();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//图像显示位置左上角Y坐标
		//显示图像
		m_dib.ToUpScan(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,1));
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	图像向右显示特效
*/
void CDIP1View::OnTorightScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************刷新屏幕******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//用白色填充屏幕
	pDC->FillRect(&rect,&brush);
	//******************************刷新屏幕******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SHeight = m_dib.GetShowHeight();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//图像显示位置左上角Y坐标
		//显示图像
		m_dib.ToRightScan(pDC,CPoint(topLeftX,topLeftY),CSize(1,SHeight));
	}
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	图像向左显示特效
*/
void CDIP1View::OnToleftScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************刷新屏幕******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//用白色填充屏幕
	pDC->FillRect(&rect,&brush);
	//******************************刷新屏幕******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SHeight = m_dib.GetShowHeight();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//图像显示位置左上角Y坐标
		//显示图像
		m_dib.ToLeftScan(pDC,CPoint(topLeftX,topLeftY),CSize(1,SHeight));
	}
	//刷新屏幕
	Invalidate(1);
}

/*
功能：
	图像直方图均衡化
*/
void CDIP1View::OnImageHistogramEqualization() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.HistogramEqualization();
	//刷新屏幕
	Invalidate(1);
}
/*
功能：
	图像数据保存
*/
void CDIP1View::OnSaveData() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CFileDialog dlg(FALSE,"txt","imgData",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"TXT文件(*.txt)|*.txt|全部文件(*.*)|*.*|");
	dlg.m_ofn.lpstrTitle = "保存图像数据为";
	
	//运行打开文件对话框
	if(IDOK == dlg.DoModal())
	{
		//获取所选择图像路径
		CString	fileName = dlg.GetPathName();
		if(!m_dib.OutPutImageData(fileName))
		{
			AfxMessageBox("图像数据保存失败!");
			return;
		}
	}
}

/*
功能：
	对图像进行傅里叶变换
*/
void CDIP1View::OnImageFourier() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.ImageFourier();
	AfxMessageBox("目前只能处理宽、高是2的整数次幂的图像！");
	//刷新屏幕
	Invalidate(1);
}

/*
功能：
	RGB空间转HSI空间
*/
void CDIP1View::OnRgb2Hsi() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.RgbToHSI();
	//刷新屏幕
	Invalidate(1);
}

/*
功能:
	画灰度图像直方图
*/
void CDIP1View::OnGrayHist() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;

	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(1,0);//获取灰度图像直方图
	pDlg->SetWindowText("灰度图像直方图");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
功能:
	画彩色图像R分量直方图
*/
void CDIP1View::OnRHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//非模态对话框
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,2);//获取彩图R分量直方图,计算机是按BGR存储的
	pDlg->SetWindowText("R分量直方图");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
功能:
	画彩色图像G分量直方图
*/
void CDIP1View::OnGHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//非模态对话框
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,1);//获取彩图G分量直方图
	pDlg->SetWindowText("G分量直方图");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
功能:
	画彩色图像B分量直方图
*/
void CDIP1View::OnBHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//非模态对话框
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,0);//获取彩图B分量直方图,计算机是按BGR存储的
	pDlg->SetWindowText("B分量直方图");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}

//=======================================================
// 函数功能： 最大方差阈值分割
// 输入参数： 无
// 返回值：   无
//=======================================================
void CDIP1View::OnOtsu() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.OtusThreshold();
	//刷新屏幕
	Invalidate(1);
}


//=======================================================
// 函数功能： 自适应阈值分割
// 输入参数： 无
// 返回值：   无
//=======================================================
void CDIP1View::OnApaptiveThreshold() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.AdaptiveThreshold();
	//刷新屏幕
	Invalidate(1);
}

/*
功能:
	图像腐蚀操作
*/
void CDIP1View::OnImageErosion() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 1;
 	m_dib.ImageErosion(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像水平腐蚀操作
*/
void CDIP1View::OnShuiPingErosion() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[1][0] = 1;
 	Structure[1][1] = 1;
 	Structure[1][2] = 1;
 	m_dib.ImageErosion(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像垂直腐蚀操作
*/
void CDIP1View::OnChuiZhiErosion() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][1] = 1;
 	Structure[1][1] = 1;
 	Structure[2][1] = 1;
 	m_dib.ImageErosion(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像东北—西南腐蚀操作
*/
void CDIP1View::OnDongXiErosion() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][0] = 1;
 	Structure[1][1] = 1;
 	Structure[2][2] = 1;
 	m_dib.ImageErosion(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像西北—东南腐蚀操作
*/
void CDIP1View::OnXiDongErosion() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][2] = 1;
 	Structure[1][1] = 1;
 	Structure[2][0] = 1;
 	m_dib.ImageErosion(Structure);
 	//刷新屏幕
 	Invalidate(1);
}

/*
功能:
	图像膨胀操作
*/
void CDIP1View::OnImageDilation() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 1;
 	m_dib.ImageDilation(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像水平膨胀操作
*/
void CDIP1View::OnShuiPingDilation() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[1][0] = 1;
 	Structure[1][1] = 1;
 	Structure[1][2] = 1;
 	m_dib.ImageDilation(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像垂直膨胀操作
*/
void CDIP1View::OnChuiZhiDilation() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][1] = 1;
 	Structure[1][1] = 1;
 	Structure[2][1] = 1;
 	m_dib.ImageDilation(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像东北—西南膨胀操作
*/
void CDIP1View::OnDongXiDilation() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][0] = 1;
 	Structure[1][1] = 1;
 	Structure[2][2] = 1;
 	m_dib.ImageDilation(Structure);
 	//刷新屏幕
 	Invalidate(1);
}
/*
功能:
	图像西北—东南膨胀操作
*/
void CDIP1View::OnXiDongDilation() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
 	int Structure[3][3];
 	for(int i=0;i<3;i++)
 		for(int j=0;j<3;j++)
 			Structure[i][j] = 0;
 	Structure[0][2] = 1;
 	Structure[1][1] = 1;
 	Structure[2][0] = 1;
 	m_dib.ImageDilation(Structure);
 	//刷新屏幕
 	Invalidate(1);
}

//*******************************以下用的是OpenCV中的函数*******************************

/*
功能:
	测试OpenCV
*/
void CDIP1View::OnTestOpenCV() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	AfxMessageBox("这是OpenCV的测试按钮！"); 
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是灰度图
	IplImage *temp = m_dib.cvBmpToIplImage(1);

	//2、创建临时图像
	IplImage *CannyGray = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);

	//****************************3、开始图像处理**************************
	cvCanny(temp,CannyGray,50,150,3);
	//****************************3、开始图像处理**************************

	//4、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(CannyGray);

	//5、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	cvReleaseImage(&CannyGray);//释放CannyGray
	
	 //刷新屏幕
 	Invalidate(1);
}
/*
功能:
	OpenCV人脸检测
*/
void CDIP1View::OnCvFaceDetection() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是灰度图
	IplImage *temp = m_dib.cvBmpToIplImage(3);

	//2、开始图像处理
	int faceNum;
	//调用OpenCV1.0自带的人脸检测函数
	//temp = m_dib.cvFaceDec(temp,&faceNum);
	//调用深大于仕琪的人脸检测函数
	temp = m_dib.cvFaceDecYuShiQi(temp,&faceNum);
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);
	//输出人脸个数
	CString  str; 
	if(faceNum>0)
	{
		str.Format("共检测到:%d个人脸！",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("未检测到人脸！"); 

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}

/*
功能:
	OpenCV角点检测
*/
void CDIP1View::OnCvCornerDetectipn() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是灰度图
	IplImage *temp = m_dib.cvBmpToIplImage(3);

	//2、开始图像处理
	int count = 5000;
	temp = m_dib.cvCornerDetection(temp,&count);
	
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);
	//输出角点个数
	CString  str; 
	str.Format("检测到:%d个角点！",count); 
	AfxMessageBox(str);  
	
	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}


/*
功能:
	OpenCV图像膨胀
*/
void CDIP1View::OnCvErode() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	//2、开始图像处理
	cvDilate(temp,temp);
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);
	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}
/*
功能:
	OpenCV图像腐蚀
*/
void CDIP1View::OnCvDilate() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	//2、开始图像处理
	cvErode(temp,temp);
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);
	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}

/*
功能:
	OpenCV Sobel边缘检测
*/
void CDIP1View::OnCvSobelEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	temp = m_dib.cvSobelEdge(temp);
	
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}
/*
功能:
	OpenCV Canny边缘检测
*/
void CDIP1View::OnCvCannyEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	
	//2、开始图像处理
	if(1 == GrayOrColor)
		temp = m_dib.cvCannyEdge(temp);
	else
	{
			IplImage *tempB = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);
			IplImage *tempG = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);
			IplImage *tempR = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);
			cvSplit(temp,tempB,tempG,tempR,0);
			cvMerge(m_dib.cvCannyEdge(tempB),m_dib.cvCannyEdge(tempG),m_dib.cvCannyEdge(tempR),0,temp);			
			cvReleaseImage(&tempB);
			cvReleaseImage(&tempG);
			cvReleaseImage(&tempR);
	}
	
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
	
}
/*
功能:
	OpenCV Laplacian边缘检测
*/
void CDIP1View::OnCvLaplacian() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	temp = m_dib.cvLaplacianEdge(temp);
	
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp	
	
	 //刷新屏幕
 	Invalidate(1);
}
/*
功能:
	OpenCV 彩色分量提取
*/
void CDIP1View::OnCvSplit() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是灰度图
	IplImage *temp = m_dib.cvBmpToIplImage(3);
	
	//2、创建临时图像

	//3、开始图像处理
	m_dib.cvMySplit(temp);
	
	//4、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//5、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}

//摄像头人脸检测
void CDIP1View::OnCvPcFaceDetection() 
{
	// TODO: Add your command handler code here
	int faceNum;//记录检测到的人脸个数
	m_dib.PcFaceDetection(&faceNum);
	//输出人脸数目
	/*CString  str; 
	if(faceNum>0)
	{
		str.Format("共检测到:%d个人脸！",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("未检测到人脸！"); */
}
//基于深大的摄像头人脸检测
void CDIP1View::OnFaceDetectionYushiqi() 
{
	// TODO: Add your command handler code here
	int faceNum;//记录检测到的人脸个数
	m_dib.PcFaceDetectionYuShiQi(&faceNum);
	//输出人脸数目
	/*CString  str; 
	if(faceNum>0)
	{
		str.Format("共检测到:%d个人脸！",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("未检测到人脸！"); */
}

//简单无缩放模糊

//简单滤波
void CDIP1View::OnCvSimpleBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		temp = m_dib.cvSmoothBlur(temp,CV_BLUR,Width,Height);
	}
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}

//高斯滤波
void CDIP1View::OnCvGaussianBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	temp = m_dib.cvSmoothBlur(temp,CV_GAUSSIAN,5,5);
	
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}

//中值滤波
void CDIP1View::OnCvMedianBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		temp = m_dib.cvSmoothBlur(temp,CV_MEDIAN,Width,Height);
	}
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}


//OpenCV绘制灰度图像直方图
void CDIP1View::OnCvPlotHist() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	m_dib.plotHistogram(temp);
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}

void CDIP1View::OnCvHistEqualize() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCV图像处理主要步骤*****************************
	
	//0、判断当前图像是彩图还是灰度图
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1、把当前bmp图像转化为IplImage图像。1：表示当前bmp图像是灰度图；3：表示当前bmp图像是彩色图
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2、开始图像处理
	m_dib.HistEqualize(temp);
	//3、将处理后的图像(一般指第2步创建的图像)数据赋到bmp图像数据
	m_dib.cvDataToBmp(temp);

	//4、释放前两步创建的IplImage图像
	cvReleaseImage(&temp);//释放temp
	
	 //刷新屏幕
 	Invalidate(1);
}

/*
功能：
	新建图像
*/
void CDIP1View::OnNewImage() 
{
	// TODO: Add your command handler code here
	CDlgImageArgument Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//判断是否点击的是确定按钮
	{
		UINT width = Mydlg.m_ImageWidth;
		UINT height = Mydlg.m_ImageHeight;
		UINT nBits = Mydlg.m_ImageNBIts;
		CString fileName = Mydlg.m_filePath;
		//****************创建图像并将其保存到文件fileName**************
		if(m_dib.CreateDIB((LPSTR)(LPCTSTR)fileName,width,height,nBits))
		{
			//***********************设置显示新建图像的相关参数***********************	
			if(!m_dib.IsValid())
			{
				AfxMessageBox("新建图像失败!");
				return;
			}
			//设置显示图像的宽度
			m_dib.SetShowWidth(m_dib.GetWidth());
			//设置显示图像的高度
			m_dib.SetShowHeight(m_dib.GetHeight());
			//保存原始数据
			m_dib.SaveOriginImage();
			//***********************其实该句可以不要**********************
			//保存上一步图像数据
			m_dib.SavePreImage();//其实该句可以不要！！！
			//***********************其实该句可以不要**********************
			//初始化非全屏显示
			//	m_dib.isFullScreen = false;	
			//***********************设置显示新建图像的相关参数***********************
		}
	}	
	//刷新屏幕
 	Invalidate(1);
}
/*
功能：
	清空图像
*/
void CDIP1View::OnClearImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	m_dib.Empty();
	//刷新屏幕
 	Invalidate(1);
}
