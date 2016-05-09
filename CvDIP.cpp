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

/*功能：
	利用OpenCV函数打开图像

*/
void CCvDIP::LoadFileFromOpenCV(LPCTSTR lpszPath)
{
	//1、获取图像路径
	char *fileName  = (LPSTR)lpszPath;
	//2、打开图像
	IplImage* imgOrigin = cvLoadImage(fileName);
	//3、获取图像数据
	int* m_pData = (int*)(imgOrigin->imageData);
	//4、获取图像的宽度
	long imgWidth = imgOrigin->width;
	//5、获取图像的高度
	long imgHeight = imgOrigin->height;
	//6、获取图像的通道数
	int imgChannels = imgOrigin->nChannels;
	
	CreateDIB(fileName,m_pData,imgWidth,imgHeight,8*imgChannels);
	ImageMirror1(0);//垂直镜像,其中的0表示不保存上一步的数据
	return;
}

/*功能：
	利用OpenCV函数打开图像
*/
bool CCvDIP::SaveFileBasedOpenCV(LPCTSTR lpszPath)
{
	//1、获取图像路径
	char *fileName  = (LPSTR)lpszPath;
	//2、判断当前图像是灰色还是彩色
	int GrayOrColor;
	if(IsGrade())
		GrayOrColor = 1;
	else
		GrayOrColor = 3;
	//3、将当前bmp图像转化为IplImage格式的图像
	IplImage *img = cvBmpToIplImage(GrayOrColor);
	ImageMirror1(0);//垂直镜像,其中的1表示保存上一步的数据
	//4、保存当前图像到路径lpszPath
	cvSaveImage(fileName,img);
	//5、释放图像img
	cvReleaseImage(&img);
	return TRUE;
}
/*功能：
	根据现有图像数据创建图像
*/
IplImage* CCvDIP::cvCreateDataImage(int width,int height,char *data,int channels,int flag)
{
	//创建一幅灰度图像
	CvSize imgSize;
	imgSize.width = width;
	imgSize.height = height;
	IplImage* m_curImg = cvCreateImage(imgSize,IPL_DEPTH_8U,channels);
	//为图像赋值
	//第一种方法
	if(1 == flag)
	{
		ImageMirror1(1);//垂直镜像,其中的1表示保存上一步的数据
		memcpy(m_curImg->imageData,data,m_curImg->widthStep*m_curImg->height);
	}
	//第二种方法
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
功能：
	根据现有图像数据创建IplImage图像
参数：
	channels：图像的通道数，1：表示灰度图，3：表示彩色图
	flag：表示传递图像数据的一种方式，1：传递速度快，其他：传递速度慢，默认flag=1
*/
IplImage* CCvDIP::cvBmpToIplImage(int channels,int flag)
{
	return cvCreateDataImage(GetWidth(),GetHeight(),(char *)GetData(),channels,flag);
}

/*功能：
	把IplImage中的数据赋给Bmp
*/
void CCvDIP::cvDataToBmp(IplImage *m_curImg,int flag)
{
	BYTE* temp = (unsigned char *)(m_curImg->imageData);
	BYTE* m_pdata = GetData();
	//void *memcpy(void *dest, const void *src, size_t n)
	//解释：从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
	//第一种
	if(1 == flag)
	{
		memcpy(m_pdata,temp,GetLineByte()*GetHeight());//可能有问题
		ImageMirror1(0);//垂直镜像,其中的0表示不保存上一步的数据
	}
	//第二种
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

/*功能：
	OpenCV自带的人脸检测
*/
IplImage* CCvDIP::cvFaceDec(IplImage* image,int* faceNum)
{
	static CvHaarClassifierCascade* cascade = 0;
	static CvMemStorage* storage = 0;
	const char* cascade_name = "D:\\Program Files\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt.xml";

	//加载人脸检测所用的分类器
	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0 );   
	if( !cascade )
	{
		AfxMessageBox("不能加载分类器！" );
		return 0;
	}
	//动态存储结构，用来存储人脸在图像中的位置
	storage = cvCreateMemStorage(0);
	return 	detect_and_draw(image,storage,cascade,faceNum);
}
/*功能：
	深大于仕琪人脸检测
*/
IplImage* CCvDIP::cvFaceDecYuShiQi(IplImage* Color,int* faceNum)
{

	//创建一幅灰度图像
	IplImage* gray = cvCreateImage(cvGetSize(Color),Color->depth,1);
	
	//彩图转为灰度图
	cvCvtColor(Color, gray, CV_BGR2GRAY );
	if(!gray)
	{
		fprintf(stderr, "图像加载失败！\n");
		return 0;
	}
	int *pResults = NULL; 
	//!!! 输入图像必须是一幅灰度图像(单通道图像)
	//!!! 不要释放结果pResults !!!
	pResults = facedetect_multiview_reinforce((unsigned char*)(gray->imageData), gray->width, 
												gray->height, gray->widthStep,1.3f, 4, 24);
	//记录检测到的人脸个数
	*faceNum = (pResults ? *pResults : 0);//pResults(字节组成):1|6|6|6，
										  //第1个字节表示检测到的人脸数目
	
	//输出检测结果
	CvFont font = cvFont(1.5);
	CString str1;
	const char* temp;
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+6*i;
		int x = p[0];//人脸矩形左上角x坐标
		int y = p[1];//人脸矩形左上角y坐标
		int w = p[2];//人脸矩形的宽度
		int h = p[3];//人脸矩形的高度
		int neighbors = p[4];
		int angle = p[5];//人脸角度
		
		CvPoint center;
		int radius;
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		cvCircle(Color, center, radius, colors[i%8], 3, 8, 0 );
		//在图像中显示人脸的角度

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
功能：
	用OpenCV1.0自带的人脸检测函数进行视频中的人脸检测
*/
void CCvDIP::PcFaceDetection(int* faceNum)
{
	CvCapture *capture = NULL;
	IplImage *frame = NULL;
	//加载摄像头
	capture = cvCreateCameraCapture(0);
	if(!capture)
	{
		AfxMessageBox("对不起，未检测到摄像头或摄像头加载失败！"); 
		return;
	}
	cvNamedWindow("Camera",0);
	while(1)
	{
		frame = cvQueryFrame(capture);
		cvFaceDec(frame,faceNum);
		//显示检测到的人脸个数
		/*CString  str; 
		if(*faceNum>0)
		{
			str.Format("共检测到:%d个人脸！",*faceNum); 
			AfxMessageBox(str); 
		}
		else
			AfxMessageBox("未检测到人脸！"); */
		cvShowImage("Camera",frame);
		char c = cvWaitKey(30);
		if(c == 27) 
			break;
	}
	cvReleaseCapture(&capture);
	cvDestroyWindow("Camera");
}

/*	
功能：
	用深大于仕琪的人脸检测库进行视频中的人脸检测
*/
void CCvDIP::PcFaceDetectionYuShiQi(int* faceNum)
{
	CvCapture *capture = NULL;
	IplImage *frame = NULL;

	capture = cvCreateCameraCapture(0);
	if(!capture)
	{
		AfxMessageBox("对不起，未检测到摄像头或摄像头加载失败！"); 
		return;
	}
	cvNamedWindow("Camera",0);
	while(1)
	{
		frame = cvQueryFrame(capture);
		cvFaceDecYuShiQi(frame,faceNum);
		//显示检测到的人脸个数
		/*CString  str; 
		if(*faceNum>0)
		{
			str.Format("共检测到:%d个人脸！",*faceNum); 
			AfxMessageBox(str); 
		}
		else
			AfxMessageBox("未检测到人脸！"); */
		cvShowImage("Camera",frame);
		char c = cvWaitKey(30);
		if(c == 27) 
			break;
	}
		cvReleaseCapture(&capture);
		cvDestroyWindow("Camera");
}
/*功能：
	OpenCV角点检测
*/
IplImage* CCvDIP::cvCornerDetection(IplImage* img,int *count)
{
	assert( NULL != img ) ;
	IplImage* img_gray = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);

	// 创建临时图像
	IplImage* img_temp = cvCreateImage(cvGetSize(img), 32, 1);
	IplImage* img_eigen = cvCreateImage(cvGetSize(img), 32, 1);

	// 创建数组存储角点
	//int count = 1000;
	CvPoint2D32f* corners = new CvPoint2D32f[*count];

	// 寻找角点
	cvGoodFeaturesToTrack(img_gray, img_eigen, img_temp, corners, count, 0.1, 10);

	// 将找到的角点画到原图像上
	for(int i=0;i<*count;i++)
		cvLine(img, cvPoint((int)corners[i].x, (int)corners[i].y), cvPoint((int)corners[i].x,(int)corners[i].y), CV_RGB(255,0,0), 5);
	return img;
}
/*功能：
	OpenCV Sobel边缘检测
*/
IplImage* CCvDIP::cvSobelEdge(IplImage *img)
{
	//************************保存上一步数据*********************
	//	SavePreImage();
	//************************保存上一步数据*********************
	//加载图像
	IplImage *sobel=cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,1);
	//Sobel边缘检测
	cvSobel(img,sobel,1,0,3);
	//对处理后的图像数据取绝对值
	IplImage *sobel8u=cvCreateImage(cvGetSize(sobel),IPL_DEPTH_8U,1);
	cvConvertScaleAbs(sobel,sobel8u,1,0);
	cvReleaseImage(&sobel);
	return sobel8u;
}


/*功能：
	OpenCV Laplacian边缘检测
*/
IplImage* CCvDIP::cvLaplacianEdge(IplImage* img)
{
	//************************保存上一步数据*********************
	//	SavePreImage();
	//************************保存上一步数据*********************  
	IplImage *LaplaceX=cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,1);
	//Laplace边缘检测
	cvLaplace(img,LaplaceX,3);
	//对处理后的图像数据取绝对值
	IplImage *Laplace8u=cvCreateImage(cvGetSize(LaplaceX),IPL_DEPTH_8U,1);
	cvConvertScaleAbs(LaplaceX,Laplace8u,1,0);
	//销毁临时变量
	cvReleaseImage(&img);
	cvReleaseImage(&LaplaceX);
	return Laplace8u;
}

/*功能：
	OpenCV 彩色图像分量提取
*/
void CCvDIP::cvMySplit(IplImage *pImg)
{
	//************************保存上一步数据*********************
	//	SavePreImage();
	//************************保存上一步数据*********************   
    IplImage *rImg,*bImg,*gImg;   
	
    rImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    gImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    bImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
	cvSplit(pImg,bImg,gImg,rImg,0);  
    
	const char* RName = "R分量";
	const char* GName = "G分量";
	const char* BName = "B分量";
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
//    cvImShow(rImg,"R分量",0);
//	cvImShow(gImg,"G分量",0);  
//     cvImShow(bImg,"B分量",0); 	
}
