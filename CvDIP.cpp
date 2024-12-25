// CvDIP.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "CvDIP.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "cv.h"
#include "highgui.h"
#include  "InterfaceFuc.h"
#include "facedetect-dll.h"
/////////////////////////////////////////////////////////////////////////////
// CCvDIP

CCvDIP::CCvDIP()
{
}

CCvDIP::~CCvDIP()
{
}

/*���ܣ�
	����OpenCV������ͼ��
*/
void CCvDIP::LoadFileFromOpenCV(LPCTSTR lpszPath)
{
	//1����ȡͼ��·��
	char *fileName  = (LPSTR)lpszPath;
	//2����ͼ��		
	IplImage* imgOrigin;
	std::string path = fileName;//ͼ������·��
	std::string extName = path.substr(path.find_last_of('.') + 1);//ͼ����չ��
	if (("IMG" == extName) || ("img" == extName))
	{
		//ͼ����
		std::string imgN = path.substr(path.find_last_of('\\') + 1, path.find_last_of('.') - path.find_last_of('\\') - 1);
		std::string imgName = path.substr(0, path.find_last_of('\\')) + "\\" + imgN + ".png";
		//�����IMGͼ���Ӧ��pngͼ�񲻴��ڽ��任Ϊpngͼ��
		if (!PathFileExists(imgName.c_str()))			
		{
			if (vicar2png(lpszPath))			
				imgOrigin = cvLoadImage(imgName.c_str());
		}
		else
			imgOrigin = cvLoadImage(imgName.c_str());

	}
	else
		imgOrigin = cvLoadImage(fileName);
	
	//3����ȡͼ������
	int* m_pData = (int*)(imgOrigin->imageData);
	//4����ȡͼ��Ŀ��
	long imgWidth = imgOrigin->width;
	//5����ȡͼ��ĸ߶�
	long imgHeight = imgOrigin->height;
	//6����ȡͼ���ͨ����
	int imgChannels = imgOrigin->nChannels;
	
	CreateDIB(fileName,m_pData,imgWidth,imgHeight,8*imgChannels);
	ImageMirror1(0);//��ֱ����,���е�0��ʾ��������һ��������
	return;
}
/*���ܣ�
	��IMGͼ��ת����pngͼ��
*/
bool CCvDIP::vicar2png(LPCTSTR lpszPath)
{
	if (!PathFileExists(lpszPath))
	{
		AfxMessageBox("�ļ�������");
		return false;
	}
	std::string temp = "vicar2png -f ";
	std::string imgPath = temp + (LPSTR)lpszPath;	

	//AfxMessageBox(imgPath.c_str());		
	//ShellExecute(NULL, NULL, "vicar2png", imgPath.c_str(), NULL, SW_HIDE|SW_SHOWNORMAL);
	
	//WinExec(_T("vicar2png -f C:\\Users\\jnulzl\\Desktop\\res\\N1715984373_1.IMG"), SW_MINIMIZE);

	//if (system_hide(const_cast<char*>(imgPath.c_str())))
	//	return true;
	//else
	//	return false;
	
	system(imgPath.c_str());
	
}
/*���ܣ�
	�������������������ʾ�����д���(12.16����δ�ɹ�)
*/
BOOL CCvDIP::system_hide(char* CommandLine)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_HIDE;
	//si.dwFlags = STARTF_USESHOWWINDOW;
	si.dwFlags = STARTF_USESHOWWINDOW;	
	if (CreateProcess(NULL, CommandLine, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		return   true;
	else
		return false;
}
/*���ܣ�
	����OpenCV������ͼ��
*/
bool CCvDIP::SaveFileBasedOpenCV(LPCTSTR lpszPath)
{
	//1����ȡͼ��·��
	char *fileName  = (LPSTR)lpszPath;
	//2���жϵ�ǰͼ���ǻ�ɫ���ǲ�ɫ
	int GrayOrColor;
	if(IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//3������ǰbmpͼ��ת��ΪIplImage��ʽ��ͼ��
	IplImage *img = cvBmpToIplImage(GrayOrColor);
	ImageMirror1(0);//��ֱ����,���е�1��ʾ������һ��������
	//4�����浱ǰͼ��·��lpszPath
	cvSaveImage(fileName,img);
	//5���ͷ�ͼ��img
	cvReleaseImage(&img);
	return TRUE;
}
/*���ܣ�
	��������ͼ�����ݴ���ͼ��
*/
IplImage* CCvDIP::cvCreateDataImage(int width,int height,char *data,int channels,int flag)
{
	//����һ���Ҷ�ͼ��
	CvSize imgSize;
	imgSize.width = width;
	imgSize.height = height;
	IplImage* m_curImg = cvCreateImage(imgSize,IPL_DEPTH_8U,channels);
	//Ϊͼ��ֵ
	//��һ�ַ���
	if(1 == flag)
	{
		ImageMirror1(1);//��ֱ����,���е�1��ʾ������һ��������
		memcpy(m_curImg->imageData,data,m_curImg->widthStep*m_curImg->height);
	}
	//�ڶ��ַ���
	else
	{
		for(int i=0;i<imgSize.height;i++)
			for(int j=0;j<imgSize.width;j++)
			{
				if(1 == channels)
					m_curImg->imageData[m_curImg->widthStep*i + j]= data[m_curImg->widthStep*(imgSize.height-i) + j];
				else if(3 == channels)
				{
					m_curImg->imageData[m_curImg->widthStep*i + 3*j]= data[m_curImg->widthStep*(imgSize.height-i) + 3*j];
					m_curImg->imageData[m_curImg->widthStep*i + 3*j + 1]= data[m_curImg->widthStep*(imgSize.height-i) + 3*j + 1];
					m_curImg->imageData[m_curImg->widthStep*i + 3*j + 2]= data[m_curImg->widthStep*(imgSize.height-i) + 3*j + 2];
				}
			}
	}
	return m_curImg;
}

/*
���ܣ�
	��������ͼ�����ݴ���IplImageͼ��
������
	channels��ͼ���ͨ������1����ʾ�Ҷ�ͼ��3����ʾ��ɫͼ
	flag����ʾ����ͼ�����ݵ�һ�ַ�ʽ��1�������ٶȿ죬�����������ٶ�����Ĭ��flag=1
*/
IplImage* CCvDIP::cvBmpToIplImage(int channels,int flag)
{
	return cvCreateDataImage(GetWidth(),GetHeight(),(char *)GetData(),channels,flag);
}

/*���ܣ�
	��IplImage�е����ݸ���Bmp
*/
void CCvDIP::cvDataToBmp(IplImage *m_curImg,int flag)
{
	BYTE* temp = (unsigned char *)(m_curImg->imageData);
	BYTE* m_pdata = GetData();
	//void *memcpy(void *dest, const void *src, size_t n)
	//���ͣ���Դsrc��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n���ֽڵ�Ŀ��dest��ָ���ڴ��ַ����ʼλ����
	//��һ��
	if(1 == flag)
	{
		memcpy(m_pdata,temp,GetLineByte()*GetHeight());//����������
		ImageMirror1(0);//��ֱ����,���е�0��ʾ��������һ��������
	}
	//�ڶ���
	else
	{
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
				if(IsGrade())
					m_pdata[m_curImg->widthStep*i + j]= temp[m_curImg->widthStep*(GetHeight()-i) + j];
				else
				{	
					m_pdata[m_curImg->widthStep*i + 3*j]= temp[m_curImg->widthStep*(GetHeight()-i) + 3*j];
					m_pdata[m_curImg->widthStep*i + 3*j + 1]= temp[m_curImg->widthStep*(GetHeight()-i) + 3*j + 1];
					m_pdata[m_curImg->widthStep*i + 3*j + 2]= temp[m_curImg->widthStep*(GetHeight()-i) + 3*j + 2];
				}
			}
	}
}

/*���ܣ�
	OpenCV�������
*/
IplImage* CCvDIP::cvFaceDec(IplImage* image,int* faceNum)
{
	static CvHaarClassifierCascade* cascade = 0;
	static CvMemStorage* storage = 0;
	const char* cascade_name = "E:\\Program Files (x86)\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt.xml";

	//��������������õķ�����
	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0 );   
	if( !cascade )
	{
		AfxMessageBox("���ܼ��ط�������" );
		return 0;
	}
	//��̬�洢�ṹ�������洢������ͼ���е�λ��
	storage = cvCreateMemStorage(0);
	return 	detect_and_draw(image,storage,cascade,faceNum);
}
/*���ܣ�
	����������������
*/
IplImage* CCvDIP::cvFaceDecYuShiQi(IplImage* Color,int* faceNum)
{

	//����һ���Ҷ�ͼ��
	IplImage* gray = cvCreateImage(cvGetSize(Color),Color->depth,1);
	
	//��ͼתΪ�Ҷ�ͼ
	cvCvtColor(Color, gray, CV_BGR2GRAY );
	if(!gray)
	{
		fprintf(stderr, "ͼ�����ʧ�ܣ�\n");
		return 0;
	}
	int *pResults = NULL; 
	//!!! ����ͼ�������һ���Ҷ�ͼ��(��ͨ��ͼ��)
	//!!! ��Ҫ�ͷŽ��pResults !!!
	pResults = facedetect_multiview_reinforce((unsigned char*)(gray->imageData), gray->width, gray->height, gray->widthStep,
											   1.3f, 4, 24);
	//��¼��⵽����������
	*faceNum = (pResults ? *pResults : 0);

	//��������
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+6*i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		int angle = p[5];
		
		CvPoint center;
		int radius;
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		cvCircle(Color, center, radius, colors[i%8], 3, 8, 0 );
	}
	return Color;
}
/*	
���ܣ�
	��OpenCV1.0�Դ���������⺯��������Ƶ�е��������
*/
void CCvDIP::PcFaceDetection(int* faceNum)
{
	CvCapture *capture = NULL;
	IplImage *frame = NULL;
	//��������ͷ
	capture = cvCreateCameraCapture(0);
	if(!capture)
	{
		AfxMessageBox("�Բ���δ��⵽����ͷ������ͷ����ʧ�ܣ�"); 
		return;
	}
	cvNamedWindow("Camera",0);
	while(1)
	{
		frame = cvQueryFrame(capture);
		cvFaceDec(frame,faceNum);
		//��ʾ��⵽����������
		/*CString  str; 
		if(*faceNum>0)
		{
			str.Format("����⵽:%d��������",*faceNum); 
			AfxMessageBox(str); 
		}
		else
			AfxMessageBox("δ��⵽������"); */
		cvShowImage("Camera",frame);
		char c = cvWaitKey(30);
		if(c == 27) 
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Camera");
}

/*	
���ܣ�
	��������������������������Ƶ�е��������
*/
void CCvDIP::PcFaceDetectionYuShiQi(int* faceNum)
{
	CvCapture *capture = NULL;
	IplImage *frame = NULL;

	capture = cvCreateCameraCapture(0);
	if(!capture)
	{
		AfxMessageBox("�Բ���δ��⵽����ͷ������ͷ����ʧ�ܣ�"); 
		return;
	}
	cvNamedWindow("Camera",0);
	while(1)
	{
		frame = cvQueryFrame(capture);
		cvFaceDecYuShiQi(frame,faceNum);
		//��ʾ��⵽����������
		/*CString  str; 
		if(*faceNum>0)
		{
			str.Format("����⵽:%d��������",*faceNum); 
			AfxMessageBox(str); 
		}
		else
			AfxMessageBox("δ��⵽������"); */
		cvShowImage("Camera",frame);
		char c = cvWaitKey(30);
		if(c == 27) 
			break;
	}
		cvReleaseCapture(&capture);
		cvDestroyWindow("Camera");
}
/*���ܣ�
	OpenCV�ǵ���
*/
IplImage* CCvDIP::cvCornerDetection(IplImage* img,int *count)
{
	assert( NULL != img ) ;
	IplImage* img_gray = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);

	// ������ʱͼ��
	IplImage* img_temp = cvCreateImage(cvGetSize(img), 32, 1);
	IplImage* img_eigen = cvCreateImage(cvGetSize(img), 32, 1);

	// ��������洢�ǵ�
	//int count = 1000;
	CvPoint2D32f* corners = new CvPoint2D32f[*count];

	// Ѱ�ҽǵ�
	cvGoodFeaturesToTrack(img_gray, img_eigen, img_temp, corners, count, 0.1, 10);

	// ���ҵ��Ľǵ㻭��ԭͼ����
	for(int i=0;i<*count;i++)
		cvLine(img, cvPoint((int)corners[i].x, (int)corners[i].y), cvPoint((int)corners[i].x,(int)corners[i].y), CV_RGB(255,0,0), 5);
	return img;
}
/*���ܣ�
	OpenCV Sobel��Ե���
*/
IplImage* CCvDIP::cvSobelEdge(IplImage *img)
{
	//************************������һ������*********************
	//	SavePreImage();
	//************************������һ������*********************
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,img->nChannels);
	//Sobel��Ե���
	cvSobel(img,Gray,1,0);
	//�Դ�����ͼ������ȡ����ֵ
	IplImage *Laplace8u=cvCreateImage(cvGetSize(Gray),IPL_DEPTH_8U,img->nChannels);
	cvConvertScaleAbs(Gray,Laplace8u);
	cvReleaseImage(&Gray);

	return Laplace8u;
}

/*
���ܣ�
	OpenCV Canny��Ե��⣻
������
	img�����ǻҶ�ͼ
*/
IplImage* CCvDIP::cvCannyEdge(IplImage *img)
{
	//************************������һ������*********************
	//	SavePreImage();
	//************************������һ������*********************
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//Sobel��Ե���
	cvCanny(img,Gray,50,150);
	return Gray;
}
		

/*���ܣ�
	OpenCV Laplacian��Ե���
*/
IplImage* CCvDIP::cvLaplacianEdge(IplImage* img)
{
	//************************������һ������*********************
	//	SavePreImage();
	//************************������һ������*********************  
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,img->nChannels);
	//Laplace��Ե���
	cvLaplace(img,Gray);
	//�Դ�����ͼ������ȡ����ֵ
	IplImage *Laplace8u=cvCreateImage(cvGetSize(Gray),IPL_DEPTH_8U,img->nChannels);
	cvConvertScaleAbs(Gray,Laplace8u);
	cvReleaseImage(&Gray);

	return Laplace8u;
}

/*���ܣ�
	OpenCV ��ɫͼ�������ȡ
*/
void CCvDIP::cvMySplit(IplImage *pImg)
{
	//************************������һ������*********************
	//	SavePreImage();
	//************************������һ������*********************   
    IplImage *rImg,*bImg,*gImg;   
	const char* RWindowName = "R����";
	const char* GWindowName = "G����";
	const char* BWindowName = "B����";
    rImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    bImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    gImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
	cvSplit(pImg,bImg,gImg,rImg,0);  
        
	cvNamedWindow(RWindowName,0);
	cvNamedWindow(GWindowName,0);
	cvNamedWindow(BWindowName,0);
	//��ʾͼ��
	cvShowImage(RWindowName,rImg);
	cvShowImage(GWindowName,gImg);
	cvShowImage(BWindowName,bImg);
	//�ı䴰�ڳߴ�
	cvResizeWindow(RWindowName,pImg->width,pImg->height);
	cvResizeWindow(GWindowName,pImg->width,pImg->height);
	cvResizeWindow(BWindowName,pImg->width,pImg->height);
	//������ͣ
	cvWaitKey();
	//�ͷ�ͼ��
	cvReleaseImage(&rImg);
	cvReleaseImage(&bImg);
	cvReleaseImage(&gImg);
	cvDestroyWindow(RWindowName);
	cvDestroyWindow(GWindowName);
	cvDestroyWindow(BWindowName);
}
/*
���ܣ�
	OpenCV ͼ���˲�
������
	img(��ɫ���߻Ҷ�ͼ)
*/
IplImage* CCvDIP::cvSmoothBlur(IplImage *img,int smoothType,int templateWidth,int templateHeight)
{
	IplImage *smoothImg = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,img->nChannels);
    cvSmooth(img,smoothImg,smoothType,templateWidth,templateHeight);
	return smoothImg;
}

/*
���ܣ�
	OpenCV ���ƻҶ�ͼ��ֱ��ͼ
*/
IplImage* CCvDIP::plotGrayHistogram(IplImage* grayImage,CvScalar color)
{

	int size=256;
	float maxPixelValue=0;	
	CvHistogram* hist=cvCreateHist(1,&size,CV_HIST_ARRAY);
	cvCalcHist(&grayImage,hist,0,NULL);	
	cvGetMinMaxHistValue(hist,NULL,&maxPixelValue,NULL,NULL);
	IplImage* dst=cvCreateImage(cvSize(400,300),8,3);
	cvSet(dst,cvScalarAll(255),0);
	double bin_width=(double)dst->width/size;
	double bin_unith=(double)dst->height/maxPixelValue;
	for(int i=0;i <256;i++)
	{
		CvPoint p0=cvPoint(i*bin_width,dst->height);
		CvPoint p1=cvPoint((i+1)*bin_width,dst->height-cvGetReal1D(hist->bins,i)*bin_unith);
		cvRectangle(dst,p0,p1,color,-1);
	}
	return dst;
}

/*
���ܣ�
	OpenCV ���Ʋ�ɫͼ��ֱ��ͼ
*/
void CCvDIP::plotColorHistogram(IplImage* colorImage)
{
	IplImage *rImg,*bImg,*gImg;   
	const char* RWindowName = "R����ֱ��ͼ";
	const char* GWindowName = "G����ֱ��ͼ";
	const char* BWindowName = "B����ֱ��ͼ";
    rImg=cvCreateImage(cvSize(colorImage->width,colorImage->height),colorImage->depth,1);  
    bImg=cvCreateImage(cvSize(colorImage->width,colorImage->height),colorImage->depth,1);  
    gImg=cvCreateImage(cvSize(colorImage->width,colorImage->height),colorImage->depth,1);  
	cvSplit(colorImage,bImg,gImg,rImg,0);  

	cvNamedWindow(RWindowName,0);
	cvNamedWindow(GWindowName,0);
	cvNamedWindow(BWindowName,0);
	cvShowImage(RWindowName,plotGrayHistogram(rImg,cvScalar(0,0,255)));
	cvShowImage(GWindowName,plotGrayHistogram(gImg,cvScalar(0,255,0)));
	cvShowImage(BWindowName,plotGrayHistogram(bImg,cvScalar(255,0,0)));
	cvWaitKey();
	//�ͷ�ͼ��
	cvReleaseImage(&rImg);
	cvReleaseImage(&bImg);
	cvReleaseImage(&gImg);
	cvDestroyWindow(RWindowName);
	cvDestroyWindow(GWindowName);
	cvDestroyWindow(BWindowName);	
}

/*
���ܣ�
	OpenCV ����ͼ��ֱ��ͼ
*/
void CCvDIP::plotHistogram(IplImage* Image)
{
	if(1 == Image->nChannels)
		cvImShow(plotGrayHistogram(Image),"�Ҷ�ֱ��ͼ",0);
	else
		plotColorHistogram(Image);
}

/*
���ܣ�
	OpenCV ֱ��ͼ���⻯
*/
IplImage* CCvDIP::HistEqualize(IplImage *Image)
{
	//IplImage* dst = cvCreateImage(cvGetSize(grayImage),IPL_DEPTH_8U,1);

	if(1 == Image->nChannels)
		cvEqualizeHist(Image,Image);
	else
	{
		IplImage *rImg,*bImg,*gImg;   
	
		rImg=cvCreateImage(cvSize(Image->width,Image->height),Image->depth,1);  
		bImg=cvCreateImage(cvSize(Image->width,Image->height),Image->depth,1);  
		gImg=cvCreateImage(cvSize(Image->width,Image->height),Image->depth,1);  
		cvSplit(Image,bImg,gImg,rImg,0);  
		
		//�Է�������ֱ��ͼ���⻯
		cvEqualizeHist(rImg,rImg);
		cvEqualizeHist(gImg,gImg);
		cvEqualizeHist(bImg,bImg);
				
		cvMerge(bImg,gImg,rImg,0,Image);

		//�ͷ�ͼ��
		cvReleaseImage(&rImg);
		cvReleaseImage(&bImg);
		cvReleaseImage(&gImg);

	}
	return Image;	
}
