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
	if(m_dib.IsValid())//�ж��Ƿ�ɹ�����λͼ
	{
		//��ȡͼ��Ŀ�͸�
		int SWidth = m_dib.GetShowWidth();
		int SHeight = m_dib.GetShowHeight();
		//ͼ�������ʾ
		CRect rect;
		GetWindowRect(&rect);
		int topLeftX = (rect.Width()-m_dib.GetShowWidth())/2;//ͼ����ʾλ�����Ͻ�X����
		int topLeftY = (rect.Height()-m_dib.GetShowHeight())/2;//ͼ����ʾλ�����Ͻ�Y����
		//�����ʾͼ������Ͻ������Ƿ�С��0
		if(topLeftX<0)
			topLeftX = 0;
		if(topLeftY<0)
			topLeftY = 0;
		//��ʾͼ��
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
//��ʾ��Ϣ����
int CDIP1View::alert(int temp)
{
	switch(temp)
	{
		case 1:
		{
			if(!m_dib.IsValid())//�ж�ͼ���Ƿ��Ѵ�
			{
				AfxMessageBox("ͼ��δ�򿪣����ȴ�ͼ��");
				return 1;
			}
			else 
				return 0;
		}
		break;
		case 2:
		{
			if(!m_dib.IsValid())//�ж�ͼ���Ƿ��Ѵ�
			{
				AfxMessageBox("ͼ��δ�򿪣����ȴ�ͼ��");
				return 1;
			}
			else if(24 == m_dib.GetBitCount())//�ж�ͼ���Ƿ��ǻҶ�ͼ��
			{
				AfxMessageBox("���Ƚ�ԭͼ��ת��Ϊ�Ҷ�ͼ��");
				return 1;
			}
			else 
				return 0;
		}
		break;
		case 3:
		{
			if(!m_dib.IsValid())//�ж�ͼ���Ƿ��Ѵ�
			{
				AfxMessageBox("ͼ��δ�򿪣����ȴ�ͼ��");
				return 1;
			}
			else if(8 == m_dib.GetBitCount())//�ж�ͼ���Ƿ��ǲ�ɫͼ��
			{
				AfxMessageBox("��ǰͼ�����Ϊ��ɫͼ��");
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
	��ͼ��
*/
void CDIP1View::OnOpenImage() 
{
	// TODO: Add your command handler code here

	//��������ļ�����
	static char filePath[] = "BMP�ļ�(*.bmp)|*.bmp|PNG�ļ�(*.png)|*.png|PPM�ļ�(*.ppm)|*.ppm|PGM�ļ�(*.pgm)|*.pgm|PBM�ļ�(*.pbm)|*.pbm|JPG�ļ�(*.jpg)|*.jpg|FITS�ļ�(*.fits)|*.fits|IMG�ļ�(*.IMG)|*.IMG|JPEG�ļ�(*.jpeg)|*.jpeg|TIFF�ļ�(*.tiff)|*.tiff|TIF�ļ�(*.tif)|*.tif|ȫ���ļ�(*.*)|*.*|";
	//�����ļ��Ի������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "��ͼ��";
	//�����ļ�·��+�ļ���
	CString fileName;
	//���д��ļ��Ի���
	int ret = dlg.DoModal();

	if(IDOK == ret)
	{
		//��ȡ��ѡ��ͼ��·��
		fileName = dlg.GetPathName();
		//��ȡ��ѡ��ͼ�����չ��
		CString ExtName = dlg.GetFileExt();
		if(ExtName == "fits")//����ͼ��������ر���
			m_dib.LoadFitsFile(fileName);
		else
			//m_dib.LoadFromFile(fileName);
			m_dib.LoadFileFromOpenCV(fileName);

		if(!m_dib.IsValid())
		{
			AfxMessageBox("ͼ���ʧ��!");
			return;
		}
		//������ʾͼ��Ŀ��
		m_dib.SetShowWidth(m_dib.GetWidth());
		//������ʾͼ��ĸ߶�
		m_dib.SetShowHeight(m_dib.GetHeight());
		//����ԭʼ����
		m_dib.SaveOriginImage();
		//***********************��ʵ�þ���Բ�Ҫ**********************
		//������һ��ͼ������
		m_dib.SavePreImage();//��ʵ�þ���Բ�Ҫ������
		//***********************��ʵ�þ���Բ�Ҫ**********************
		//��ʼ����ȫ����ʾ
	//	m_dib.isFullScreen = false;
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	����ͼ��
*/
void CDIP1View::OnSaveImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//��������ļ�����
	static char filePath[] = "BMP�ļ�(*.bmp)|*.bmp|PNG�ļ�(*.png)|*.png|PPM�ļ�(*.ppm)|*.ppm|PGM�ļ�(*.pgm)|*.pgm|PBM�ļ�(*.pbm)|*.pbm|JPG�ļ�(*.jpg)|*.jpg|JPEG�ļ�(*.jpeg)|*.jpeg|TIFF�ļ�(*.tiff)|*.tiff|TIF�ļ�(*.tif)|*.tif|ȫ���ļ�(*.*)|*.*|";
	//�����ļ��Ի������
	LPCTSTR imgName = m_dib.GetFileName();
	//AfxMessageBox(imgName);
	CFileDialog dlg(FALSE,"bmp",imgName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filePath);
	dlg.m_ofn.lpstrTitle = "ͼ�����Ϊ";
	CString fileName;
	//���д��ļ��Ի���
	int ret = dlg.DoModal();
	if(IDOK == ret)
	{
		//��ȡ��ѡ��ͼ��·��
		fileName = dlg.GetPathName();
		if(!m_dib.SaveFileBasedOpenCV(fileName))
		{
			AfxMessageBox("ͼ�񱣴�ʧ��!");
			return;
		}
		/*if(!m_dib.SaveToFile(fileName))
		{
			AfxMessageBox("ͼ�񱣴�ʧ��!");
			return;
		}*/
	}
	//ˢ����Ļ
	Invalidate(1);
}

/*
	ͼ��ƽ��
*/
void CDIP1View::OnImageTranslation() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgTran Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int horOff = Mydlg.m_horOff;
		int verOff = Mydlg.m_verOff;
		m_dib.ImageTranslation(horOff,verOff);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ����ֵ������
*/
void CDIP1View::OnImageThreshold() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgThre Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int threshold = Mydlg.m_threshold;
		m_dib.ImageThreshold(threshold);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ��ҶȻ�
*/
void CDIP1View::OnRgb2Gray() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.SavePreImage();
	m_dib.RgbToGrade();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ���ɫ��
*/
void CDIP1View::OnGray2Rgb() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//if(!m_dib.originImageIsRgb)
	
	m_dib.GradeToRgb();

	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ��ת
*/
void CDIP1View::OnImageContrary() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageContrary();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	��˹��������Ե���
*/
void CDIP1View::OnGaussLapEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.Guasslaplacian();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	PreWitt��Ե���
*/
void CDIP1View::OnPreWittEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.PreWittEdge();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	Robert��Ե���
*/
void CDIP1View::OnRobertEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.RobertEdge();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	Sobel��Ե���
*/
void CDIP1View::OnSobelEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.SobelEdge();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	Krisch��Ե���
*/
void CDIP1View::OnKrischEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.KrischEdge();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	Laplacian��Ե���
*/
void CDIP1View::OnLaplacianEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.Laplacian();
	//ˢ����Ļ
	Invalidate(1);
}


/*
	ͼ�����Ա任
*/
void CDIP1View::OnImageLinear() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgLinear Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float a = Mydlg.m_a;
		int b = Mydlg.m_b;
		m_dib.ImageLinear(a,b);
	}
	//ˢ����Ļ
	Invalidate(1);
}


/*
	ͼ��ˮƽ����
*/
void CDIP1View::OnImageMirrorhor() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageMirror();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ��ֱ����
*/
void CDIP1View::OnImageMirrorver() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageMirror1();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ������
*/
void CDIP1View::OnImageZoom() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgZoom Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float a = Mydlg.m_zoomX;
		float b = Mydlg.m_zoomY;
		m_dib.ImageZoom(a,b);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ��Ŵ�
*/
void CDIP1View::OnImageBig() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageZoom(1.25,1.25);
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ����С
*/
void CDIP1View::OnImageSmall() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageZoom(0.75,0.75);
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ͼ��ת��
*/
void CDIP1View::OnImageTranspose() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageTranspose();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	���ڱ任
*/
void CDIP1View::OnWindowTranslation() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgWindowTranslation Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		UINT a = Mydlg.m_Low;
		UINT b = Mydlg.m_High;
		m_dib.ImageWindowTranslation(a,b);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	�����任
*/
void CDIP1View::OnImageLog() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgLog Mydlg;
	int ret = Mydlg.DoModal();
	
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float a = Mydlg.m_logCoeff;
		m_dib.ImageLog(a);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	�ݴα任
*/
void CDIP1View::OnPower() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgPower Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float a = Mydlg.m_C;
		float b = Mydlg.m_Gamma;
		m_dib.ImagePower(a,b);
	}
	//ˢ����Ļ
	Invalidate(1);
}

/*
	����ƽ��
*/
void CDIP1View::OnAreaAverage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgTemplateSize Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int size = Mydlg.m_template_size;
		m_dib.ImageAreaAverage(size);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	��Ȩƽ��
*/
void CDIP1View::OnWeightAverage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ImageWeightAverage();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	��ֵ�˲�
*/
void CDIP1View::OnMedianFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,2);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	���ֵ�˲�
*/
void CDIP1View::OnMaxFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,3);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	��Сֵ�˲�
*/
void CDIP1View::OnMinFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImageMedianFilter(Height,Width,1);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	ʮ������ֵ�˲�
*/
void CDIP1View::OnPlusMedianFilter() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		m_dib.ImagePlusMedianFilter(Height,Width);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	�����������
*/
void CDIP1View::OnImageRandNoise() 
{
	// TODO: Add your command handler code here
		if(alert(1))
		return;
	CDlgAddNoiseRadio Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float radio = Mydlg.m_noise_radio;
		m_dib.AddRandNoise(radio);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	���ӽ�������
*/
void CDIP1View::OnImageSaltpepper() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CDlgAddNoiseRadio Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		float radio = Mydlg.m_noise_radio;
		m_dib.AddSaltPepperNoise(radio);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
	�������
*/
void CDIP1View::OnProfileDetect() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.ImageProfileDetect();
	//ˢ����Ļ
	Invalidate(1);
}
/*
	��ʾԭͼ��
*/
void CDIP1View::OnShowOriginImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ShowOriginImage();
	//ˢ����Ļ
	Invalidate(1);
}

/*
	��ʾ��һ��ͼ��
*/

void CDIP1View::OnShowPreimage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.ShowPreImage();
	//ˢ����Ļ
	Invalidate(1);
}



/*
���ܣ�
	��ɫͼ����ɫ
*/
void CDIP1View::OnRgbAddColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgAdColor Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int mR = Mydlg.m_R;
		int mG = Mydlg.m_G;
		int mB = Mydlg.m_B;
		m_dib.RgbAddColor(mR,mG,mB);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	�ı�ͼ������
*/
void CDIP1View::OnBrightChange() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgBrightChange Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int radio = Mydlg.m_bright;
		m_dib.ChangeBright(radio);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	������ЧӦ
*/
void CDIP1View::OnMosaic() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	CDlgMosaic Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int width = Mydlg.m_widht;
		int height = Mydlg.m_height;
		m_dib.Mosaic(width,height);
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	ʵ������Ҽ�����
*/
void CDIP1View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu; //�˵��������˵����Ӳ˵�
	CMenu *pSubMenu;//�Ҽ��˵�

	//�������˵���Դ��menu������
	menu.LoadMenu(IDR_MOUSE_RIGHT);

	//��Ϊ�Ҽ��ǵ���ʽ�˵������������˵�������ȡ�Ӳ˵�[����ȡ���ǵ�һ��(0)�Ӳ˵�]
		
	pSubMenu = menu.GetSubMenu(0);

	
	//������ֵ�ɿͻ�����ת��Ϊ��Ļ����
	ClientToScreen(&point);
	//����ʽ�Ҽ��˵����˵������point.x����ֵ����
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	CScrollView::OnRButtonDown(nFlags, point);
}


/*
���ܣ�
	��ȡR����
*/
void CDIP1View::OnRColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(2);//��������ǰ�B��G��R�洢���ص�
	//ˢ����Ļ
	Invalidate(1);
}

/*
���ܣ�
	��ȡG����
*/
void CDIP1View::OnGColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(1);//��������ǰ�B��G��R�洢���ص�
	//ˢ����Ļ
	Invalidate(1);
}

/*
���ܣ�
	��ȡB����
*/
void CDIP1View::OnBColor() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.GetRGBComponent(0);//��������ǰ�B��G��R�洢���ص�
	//ˢ����Ļ
	Invalidate(1);
}

/*
���ܣ�
	ͼ��������ʾ��Ч
*/
void CDIP1View::OnToDownScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************ˢ����Ļ******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//�ð�ɫ�����Ļ
	pDC->FillRect(&rect,&brush);
	//******************************ˢ����Ļ******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//�ж��Ƿ�ɹ�����λͼ
	{
		//��ȡͼ��Ŀ�͸�
		int SWidth = m_dib.GetShowWidth();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//ͼ����ʾλ�����Ͻ�X����
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//ͼ����ʾλ�����Ͻ�Y����
		//��ʾͼ��
		m_dib.ToDownScan(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,1));
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	ͼ��������ʾ��Ч
*/
void CDIP1View::OnToUpscan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************ˢ����Ļ******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//�ð�ɫ�����Ļ
	pDC->FillRect(&rect,&brush);
	//******************************ˢ����Ļ******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//�ж��Ƿ�ɹ�����λͼ
	{
		//��ȡͼ��Ŀ�͸�
		int SWidth = m_dib.GetShowWidth();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//ͼ����ʾλ�����Ͻ�X����
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//ͼ����ʾλ�����Ͻ�Y����
		//��ʾͼ��
		m_dib.ToUpScan(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,1));
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	ͼ��������ʾ��Ч
*/
void CDIP1View::OnTorightScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************ˢ����Ļ******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//�ð�ɫ�����Ļ
	pDC->FillRect(&rect,&brush);
	//******************************ˢ����Ļ******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//�ж��Ƿ�ɹ�����λͼ
	{
		//��ȡͼ��Ŀ�͸�
		int SHeight = m_dib.GetShowHeight();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//ͼ����ʾλ�����Ͻ�X����
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//ͼ����ʾλ�����Ͻ�Y����
		//��ʾͼ��
		m_dib.ToRightScan(pDC,CPoint(topLeftX,topLeftY),CSize(1,SHeight));
	}
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	ͼ��������ʾ��Ч
*/
void CDIP1View::OnToleftScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************ˢ����Ļ******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//�ð�ɫ�����Ļ
	pDC->FillRect(&rect,&brush);
	//******************************ˢ����Ļ******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//�ж��Ƿ�ɹ�����λͼ
	{
		//��ȡͼ��Ŀ�͸�
		int SHeight = m_dib.GetShowHeight();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//ͼ����ʾλ�����Ͻ�X����
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//ͼ����ʾλ�����Ͻ�Y����
		//��ʾͼ��
		m_dib.ToLeftScan(pDC,CPoint(topLeftX,topLeftY),CSize(1,SHeight));
	}
	//ˢ����Ļ
	Invalidate(1);
}

/*
���ܣ�
	ͼ��ֱ��ͼ���⻯
*/
void CDIP1View::OnImageHistogramEqualization() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	m_dib.HistogramEqualization();
	//ˢ����Ļ
	Invalidate(1);
}
/*
���ܣ�
	ͼ�����ݱ���
*/
void CDIP1View::OnSaveData() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	CFileDialog dlg(FALSE,"txt","imgData",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"TXT�ļ�(*.txt)|*.txt|ȫ���ļ�(*.*)|*.*|");
	dlg.m_ofn.lpstrTitle = "����ͼ������Ϊ";
	
	//���д��ļ��Ի���
	if(IDOK == dlg.DoModal())
	{
		//��ȡ��ѡ��ͼ��·��
		CString	fileName = dlg.GetPathName();
		if(!m_dib.OutPutImageData(fileName))
		{
			AfxMessageBox("ͼ�����ݱ���ʧ��!");
			return;
		}
	}
}

/*
���ܣ�
	��ͼ����и���Ҷ�任
*/
void CDIP1View::OnImageFourier() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.ImageFourier();
	AfxMessageBox("Ŀǰֻ�ܴ��������2���������ݵ�ͼ��");
	//ˢ����Ļ
	Invalidate(1);
}

/*
���ܣ�
	RGB�ռ�תHSI�ռ�
*/
void CDIP1View::OnRgb2Hsi() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	m_dib.RgbToHSI();
	//ˢ����Ļ
	Invalidate(1);
}

/*
����:
	���Ҷ�ͼ��ֱ��ͼ
*/
void CDIP1View::OnGrayHist() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;

	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(1,0);//��ȡ�Ҷ�ͼ��ֱ��ͼ
	pDlg->SetWindowText("�Ҷ�ͼ��ֱ��ͼ");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
����:
	����ɫͼ��R����ֱ��ͼ
*/
void CDIP1View::OnRHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//��ģ̬�Ի���
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,2);//��ȡ��ͼR����ֱ��ͼ,������ǰ�BGR�洢��
	pDlg->SetWindowText("R����ֱ��ͼ");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
����:
	����ɫͼ��G����ֱ��ͼ
*/
void CDIP1View::OnGHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//��ģ̬�Ի���
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,1);//��ȡ��ͼG����ֱ��ͼ
	pDlg->SetWindowText("G����ֱ��ͼ");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}
/*
����:
	����ɫͼ��B����ֱ��ͼ
*/
void CDIP1View::OnBHist() 
{
	// TODO: Add your command handler code here
	if(alert(3))
		return;
	//��ģ̬�Ի���
	CDlgHist *pDlg = new CDlgHist;
	pDlg->Create(IDD_HIST_DIALOG,this);
	
	double* Hist = m_dib.GetImageHist(3,0);//��ȡ��ͼB����ֱ��ͼ,������ǰ�BGR�洢��
	pDlg->SetWindowText("B����ֱ��ͼ");
	for(int i=0;i<256;i++)
		pDlg->m_fIntensity[i] = Hist[i];
	pDlg->ShowWindow(SW_SHOW);
}

//=======================================================
// �������ܣ� ��󷽲���ֵ�ָ�
// ��������� ��
// ����ֵ��   ��
//=======================================================
void CDIP1View::OnOtsu() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.OtusThreshold();
	//ˢ����Ļ
	Invalidate(1);
}


//=======================================================
// �������ܣ� ����Ӧ��ֵ�ָ�
// ��������� ��
// ����ֵ��   ��
//=======================================================
void CDIP1View::OnApaptiveThreshold() 
{
	// TODO: Add your command handler code here
	if(alert(2))
		return;
	m_dib.AdaptiveThreshold();
	//ˢ����Ļ
	Invalidate(1);
}

/*
����:
	ͼ��ʴ����
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ��ˮƽ��ʴ����
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ��ֱ��ʴ����
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ�񶫱������ϸ�ʴ����
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ�����������ϸ�ʴ����
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
 	//ˢ����Ļ
 	Invalidate(1);
}

/*
����:
	ͼ�����Ͳ���
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ��ˮƽ���Ͳ���
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ��ֱ���Ͳ���
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ�񶫱����������Ͳ���
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
 	//ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	ͼ���������������Ͳ���
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
 	//ˢ����Ļ
 	Invalidate(1);
}

//*******************************�����õ���OpenCV�еĺ���*******************************

/*
����:
	����OpenCV
*/
void CDIP1View::OnTestOpenCV() 
{
	// TODO: Add your command handler code here
	if(alert(2))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	AfxMessageBox("����OpenCV�Ĳ��԰�ť��"); 
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǻҶ�ͼ
	IplImage *temp = m_dib.cvBmpToIplImage(1);

	//2��������ʱͼ��
	IplImage *CannyGray = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);

	//****************************3����ʼͼ����**************************
	cvCanny(temp,CannyGray,50,150,3);
	//****************************3����ʼͼ����**************************

	//4����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(CannyGray);

	//5���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	cvReleaseImage(&CannyGray);//�ͷ�CannyGray
	
	 //ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	OpenCV�������
*/
void CDIP1View::OnCvFaceDetection() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǻҶ�ͼ
	IplImage *temp = m_dib.cvBmpToIplImage(3);

	//2����ʼͼ����
	int faceNum;
	//����OpenCV1.0�Դ���������⺯��
	//temp = m_dib.cvFaceDec(temp,&faceNum);
	//���������������������⺯��
	temp = m_dib.cvFaceDecYuShiQi(temp,&faceNum);
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);
	//�����������
	CString  str; 
	if(faceNum>0)
	{
		str.Format("����⵽:%d��������",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("δ��⵽������"); 

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}

/*
����:
	OpenCV�ǵ���
*/
void CDIP1View::OnCvCornerDetectipn() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǻҶ�ͼ
	IplImage *temp = m_dib.cvBmpToIplImage(3);

	//2����ʼͼ����
	int count = 5000;
	temp = m_dib.cvCornerDetection(temp,&count);
	
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);
	//����ǵ����
	CString  str; 
	str.Format("��⵽:%d���ǵ㣡",count); 
	AfxMessageBox(str);  
	
	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}


/*
����:
	OpenCVͼ������
*/
void CDIP1View::OnCvErode() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	//2����ʼͼ����
	cvDilate(temp,temp);
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);
	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	OpenCVͼ��ʴ
*/
void CDIP1View::OnCvDilate() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	//2����ʼͼ����
	cvErode(temp,temp);
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);
	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}

/*
����:
	OpenCV Sobel��Ե���
*/
void CDIP1View::OnCvSobelEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	temp = m_dib.cvSobelEdge(temp);
	
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	OpenCV Canny��Ե���
*/
void CDIP1View::OnCvCannyEdge() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);
	
	//2����ʼͼ����
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
	
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
	
}
/*
����:
	OpenCV Laplacian��Ե���
*/
void CDIP1View::OnCvLaplacian() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	temp = m_dib.cvLaplacianEdge(temp);
	
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp	
	
	 //ˢ����Ļ
 	Invalidate(1);
}
/*
����:
	OpenCV ��ɫ������ȡ
*/
void CDIP1View::OnCvSplit() 
{
	// TODO: Add your command handler code here
	if(alert(3))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǻҶ�ͼ
	IplImage *temp = m_dib.cvBmpToIplImage(3);
	
	//2��������ʱͼ��

	//3����ʼͼ����
	m_dib.cvMySplit(temp);
	
	//4����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//5���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}

//����ͷ�������
void CDIP1View::OnCvPcFaceDetection() 
{
	// TODO: Add your command handler code here
	int faceNum;//��¼��⵽����������
	m_dib.PcFaceDetection(&faceNum);
	//���������Ŀ
	/*CString  str; 
	if(faceNum>0)
	{
		str.Format("����⵽:%d��������",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("δ��⵽������"); */
}
//������������ͷ�������
void CDIP1View::OnFaceDetectionYushiqi() 
{
	// TODO: Add your command handler code here
	int faceNum;//��¼��⵽����������
	m_dib.PcFaceDetectionYuShiQi(&faceNum);
	//���������Ŀ
	/*CString  str; 
	if(faceNum>0)
	{
		str.Format("����⵽:%d��������",faceNum); 
		AfxMessageBox(str); 
	}
	else
		AfxMessageBox("δ��⵽������"); */
}

//��������ģ��

//���˲�
void CDIP1View::OnCvSimpleBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		temp = m_dib.cvSmoothBlur(temp,CV_BLUR,Width,Height);
	}
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}

//��˹�˲�
void CDIP1View::OnCvGaussianBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	temp = m_dib.cvSmoothBlur(temp,CV_GAUSSIAN,5,5);
	
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}

//��ֵ�˲�
void CDIP1View::OnCvMedianBlur() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	CDlgMedianFilter Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		int Height = Mydlg.m_temp_height;
		int Width = Mydlg.m_temp_width;
		temp = m_dib.cvSmoothBlur(temp,CV_MEDIAN,Width,Height);
	}
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}


//OpenCV���ƻҶ�ͼ��ֱ��ͼ
void CDIP1View::OnCvPlotHist() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	m_dib.plotHistogram(temp);
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}

void CDIP1View::OnCvHistEqualize() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	//**************************OpenCVͼ������Ҫ����*****************************
	
	//0���жϵ�ǰͼ���ǲ�ͼ���ǻҶ�ͼ
	int GrayOrColor;
	if(m_dib.IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//1���ѵ�ǰbmpͼ��ת��ΪIplImageͼ��1����ʾ��ǰbmpͼ���ǻҶ�ͼ��3����ʾ��ǰbmpͼ���ǲ�ɫͼ
	IplImage *temp = m_dib.cvBmpToIplImage(GrayOrColor);

	//2����ʼͼ����
	m_dib.HistEqualize(temp);
	//3����������ͼ��(һ��ָ��2��������ͼ��)���ݸ���bmpͼ������
	m_dib.cvDataToBmp(temp);

	//4���ͷ�ǰ����������IplImageͼ��
	cvReleaseImage(&temp);//�ͷ�temp
	
	 //ˢ����Ļ
 	Invalidate(1);
}

/*
���ܣ�
	�½�ͼ��
*/
void CDIP1View::OnNewImage() 
{
	// TODO: Add your command handler code here
	CDlgImageArgument Mydlg;
	int ret = Mydlg.DoModal();
	if(IDOK == ret)//�ж��Ƿ�������ȷ����ť
	{
		UINT width = Mydlg.m_ImageWidth;
		UINT height = Mydlg.m_ImageHeight;
		UINT nBits = Mydlg.m_ImageNBIts;
		CString fileName = Mydlg.m_filePath;
		//****************����ͼ�񲢽��䱣�浽�ļ�fileName**************
		if(m_dib.CreateDIB((LPSTR)(LPCTSTR)fileName,width,height,nBits))
		{
			//***********************������ʾ�½�ͼ�����ز���***********************	
			if(!m_dib.IsValid())
			{
				AfxMessageBox("�½�ͼ��ʧ��!");
				return;
			}
			//������ʾͼ��Ŀ��
			m_dib.SetShowWidth(m_dib.GetWidth());
			//������ʾͼ��ĸ߶�
			m_dib.SetShowHeight(m_dib.GetHeight());
			//����ԭʼ����
			m_dib.SaveOriginImage();
			//***********************��ʵ�þ���Բ�Ҫ**********************
			//������һ��ͼ������
			m_dib.SavePreImage();//��ʵ�þ���Բ�Ҫ������
			//***********************��ʵ�þ���Բ�Ҫ**********************
			//��ʼ����ȫ����ʾ
			//	m_dib.isFullScreen = false;	
			//***********************������ʾ�½�ͼ�����ز���***********************
		}
	}	
	//ˢ����Ļ
 	Invalidate(1);
}
/*
���ܣ�
	���ͼ��
*/
void CDIP1View::OnClearImage() 
{
	// TODO: Add your command handler code here
	if(alert(1))
 		return;
	m_dib.Empty();
	//ˢ����Ļ
 	Invalidate(1);
}
