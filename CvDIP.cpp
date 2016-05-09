// CvDIP.cpp : implementation file
//

#include "stdafx.h"
#include "DIP1.h"
#include "CvDIP.h"

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
	IplImage* imgOrigin = cvLoadImage(fileName);
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
	OpenCV�Դ����������
*/
IplImage* CCvDIP::cvFaceDec(IplImage* image,int* faceNum)
{
	static CvHaarClassifierCascade* cascade = 0;
	static CvMemStorage* storage = 0;
	const char* cascade_name = "D:\\Program Files\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt.xml";

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
	pResults = facedetect_multiview_reinforce((unsigned char*)(gray->imageData), gray->width, 
												gray->height, gray->widthStep,1.3f, 4, 24);
	//��¼��⵽����������
	*faceNum = (pResults ? *pResults : 0);//pResults(�ֽ����):1|6|6|6��
										  //��1���ֽڱ�ʾ��⵽��������Ŀ
	
	//��������
	CvFont font = cvFont(1.5);
	CString str1;
	const char* temp;
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+6*i;
		int x = p[0];//�����������Ͻ�x����
		int y = p[1];//�����������Ͻ�y����
		int w = p[2];//�������εĿ��
		int h = p[3];//�������εĸ߶�
		int neighbors = p[4];
		int angle = p[5];//�����Ƕ�
		
		CvPoint center;
		int radius;
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		cvCircle(Color, center, radius, colors[i%8], 3, 8, 0 );
		//��ͼ������ʾ�����ĽǶ�

		str1.Format("Angle:%d",angle);
		temp = (LPSTR)(LPCSTR)str1;		
		cvPutText(Color,temp,cvPoint(x - w*0.2,y),&font,colors[7-i%8]);
// 		str1.Format("Neighbors:%d",neighbors);
//		temp = (LPSTR)(LPCSTR)str1;	
//		cvPutText(Color,temp,cvPoint(x - w*0.2,y),&font,colors[7-i%8]);
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
	//����ͼ��
	IplImage *sobel=cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,1);
	//Sobel��Ե���
	cvSobel(img,sobel,1,0,3);
	//�Դ�����ͼ������ȡ����ֵ
	IplImage *sobel8u=cvCreateImage(cvGetSize(sobel),IPL_DEPTH_8U,1);
	cvConvertScaleAbs(sobel,sobel8u,1,0);
	cvReleaseImage(&sobel);
	return sobel8u;
}


/*���ܣ�
	OpenCV Laplacian��Ե���
*/
IplImage* CCvDIP::cvLaplacianEdge(IplImage* img)
{
	//************************������һ������*********************
	//	SavePreImage();
	//************************������һ������*********************  
	IplImage *LaplaceX=cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,1);
	//Laplace��Ե���
	cvLaplace(img,LaplaceX,3);
	//�Դ�����ͼ������ȡ����ֵ
	IplImage *Laplace8u=cvCreateImage(cvGetSize(LaplaceX),IPL_DEPTH_8U,1);
	cvConvertScaleAbs(LaplaceX,Laplace8u,1,0);
	//������ʱ����
	cvReleaseImage(&img);
	cvReleaseImage(&LaplaceX);
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
	
    rImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    gImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    bImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
	cvSplit(pImg,bImg,gImg,rImg,0);  
    
	const char* RName = "R����";
	const char* GName = "G����";
	const char* BName = "B����";
	cvNamedWindow(RName,0);
	cvShowImage(RName,rImg);
	
	cvNamedWindow(GName,0);
	cvShowImage(GName,gImg);
	
	cvNamedWindow(BName,0);
	cvShowImage(BName,bImg);
	
	cvWaitKey(0);
	cvDestroyWindow(RName);
	cvReleaseImage(&rImg);
	cvDestroyWindow(GName);
	cvReleaseImage(&gImg);
	cvDestroyWindow(BName);
	cvReleaseImage(&bImg);
//    cvImShow(rImg,"R����",0);
//	cvImShow(gImg,"G����",0);  
//     cvImShow(bImg,"B����",0); 	
}
