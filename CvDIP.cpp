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

/*功能：
	利用OpenCV函数打开图像
*/
void CCvDIP::LoadFileFromOpenCV(LPCTSTR lpszPath)
{
	//1、获取图像路径
	char *fileName  = (LPSTR)lpszPath;
	//2、打开图像		
	IplImage* imgOrigin;
	std::string path = fileName;//图像完整路径
	std::string extName = path.substr(path.find_last_of('.') + 1);//图像扩展名
	if (("IMG" == extName) || ("img" == extName))
	{
		//图像名
		std::string imgN = path.substr(path.find_last_of('\\') + 1, path.find_last_of('.') - path.find_last_of('\\') - 1);
		std::string imgName = path.substr(0, path.find_last_of('\\')) + "\\" + imgN + ".png";
		//如果该IMG图像对应的png图像不存在将其换为png图像
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
	将IMG图像转换成png图像
*/
bool CCvDIP::vicar2png(LPCTSTR lpszPath)
{
	if (!PathFileExists(lpszPath))
	{
		AfxMessageBox("文件不存在");
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
/*功能：
	调用命令行命令而不显示命令行窗口(12.16晚，暂未成功)
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
	OpenCV人脸检测
*/
IplImage* CCvDIP::cvFaceDec(IplImage* image,int* faceNum)
{
	static CvHaarClassifierCascade* cascade = 0;
	static CvMemStorage* storage = 0;
	const char* cascade_name = "E:\\Program Files (x86)\\OpenCV\\data\\haarcascades\\haarcascade_frontalface_alt.xml";

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
	pResults = facedetect_multiview_reinforce((unsigned char*)(gray->imageData), gray->width, gray->height, gray->widthStep,
											   1.3f, 4, 24);
	//记录检测到的人脸个数
	*faceNum = (pResults ? *pResults : 0);

	//输出检测结果
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
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,img->nChannels);
	//Sobel边缘检测
	cvSobel(img,Gray,1,0);
	//对处理后的图像数据取绝对值
	IplImage *Laplace8u=cvCreateImage(cvGetSize(Gray),IPL_DEPTH_8U,img->nChannels);
	cvConvertScaleAbs(Gray,Laplace8u);
	cvReleaseImage(&Gray);

	return Laplace8u;
}

/*
功能：
	OpenCV Canny边缘检测；
参数：
	img必须是灰度图
*/
IplImage* CCvDIP::cvCannyEdge(IplImage *img)
{
	//************************保存上一步数据*********************
	//	SavePreImage();
	//************************保存上一步数据*********************
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//Sobel边缘检测
	cvCanny(img,Gray,50,150);
	return Gray;
}
		

/*功能：
	OpenCV Laplacian边缘检测
*/
IplImage* CCvDIP::cvLaplacianEdge(IplImage* img)
{
	//************************保存上一步数据*********************
	//	SavePreImage();
	//************************保存上一步数据*********************  
	IplImage *Gray = cvCreateImage(cvGetSize(img),IPL_DEPTH_16S,img->nChannels);
	//Laplace边缘检测
	cvLaplace(img,Gray);
	//对处理后的图像数据取绝对值
	IplImage *Laplace8u=cvCreateImage(cvGetSize(Gray),IPL_DEPTH_8U,img->nChannels);
	cvConvertScaleAbs(Gray,Laplace8u);
	cvReleaseImage(&Gray);

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
	const char* RWindowName = "R分量";
	const char* GWindowName = "G分量";
	const char* BWindowName = "B分量";
    rImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    bImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
    gImg=cvCreateImage(cvSize(pImg->width,pImg->height),pImg->depth,1);  
	cvSplit(pImg,bImg,gImg,rImg,0);  
        
	cvNamedWindow(RWindowName,0);
	cvNamedWindow(GWindowName,0);
	cvNamedWindow(BWindowName,0);
	//显示图像
	cvShowImage(RWindowName,rImg);
	cvShowImage(GWindowName,gImg);
	cvShowImage(BWindowName,bImg);
	//改变窗口尺寸
	cvResizeWindow(RWindowName,pImg->width,pImg->height);
	cvResizeWindow(GWindowName,pImg->width,pImg->height);
	cvResizeWindow(BWindowName,pImg->width,pImg->height);
	//程序暂停
	cvWaitKey();
	//释放图像
	cvReleaseImage(&rImg);
	cvReleaseImage(&bImg);
	cvReleaseImage(&gImg);
	cvDestroyWindow(RWindowName);
	cvDestroyWindow(GWindowName);
	cvDestroyWindow(BWindowName);
}
/*
功能：
	OpenCV 图像滤波
参数：
	img(彩色或者灰度图)
*/
IplImage* CCvDIP::cvSmoothBlur(IplImage *img,int smoothType,int templateWidth,int templateHeight)
{
	IplImage *smoothImg = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,img->nChannels);
    cvSmooth(img,smoothImg,smoothType,templateWidth,templateHeight);
	return smoothImg;
}

/*
功能：
	OpenCV 绘制灰度图像直方图
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
功能：
	OpenCV 绘制彩色图像直方图
*/
void CCvDIP::plotColorHistogram(IplImage* colorImage)
{
	IplImage *rImg,*bImg,*gImg;   
	const char* RWindowName = "R分量直方图";
	const char* GWindowName = "G分量直方图";
	const char* BWindowName = "B分量直方图";
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
	//释放图像
	cvReleaseImage(&rImg);
	cvReleaseImage(&bImg);
	cvReleaseImage(&gImg);
	cvDestroyWindow(RWindowName);
	cvDestroyWindow(GWindowName);
	cvDestroyWindow(BWindowName);	
}

/*
功能：
	OpenCV 绘制图像直方图
*/
void CCvDIP::plotHistogram(IplImage* Image)
{
	if(1 == Image->nChannels)
		cvImShow(plotGrayHistogram(Image),"灰度直方图",0);
	else
		plotColorHistogram(Image);
}

/*
功能：
	OpenCV 直方图均衡化
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
		
		//对分量进行直方图均衡化
		cvEqualizeHist(rImg,rImg);
		cvEqualizeHist(gImg,gImg);
		cvEqualizeHist(bImg,bImg);
				
		cvMerge(bImg,gImg,rImg,0,Image);

		//释放图像
		cvReleaseImage(&rImg);
		cvReleaseImage(&bImg);
		cvReleaseImage(&gImg);

	}
	return Image;	
}
