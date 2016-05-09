#if !defined(AFX_CVDIP_H__18FCE162_19B5_49F3_9E8E_8E5DEA8447C8__INCLUDED_)
#define AFX_CVDIP_H__18FCE162_19B5_49F3_9E8E_8E5DEA8447C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CvDIP.h : header file
//

#include "MyDib.h"
#include "cv.h"
#include "highgui.h"
/////////////////////////////////////////////////////////////////////////////
// CCvDIP window

class CCvDIP : public MyDib
{
// Construction
public:
	CCvDIP();
	
// Attributes
public:
	//IplImage* m_curImg;
	//IplImage* m_cvImg;
// Operations
public:
	void LoadFileFromOpenCV(LPCTSTR lpszPath);//OpenCV加载图像
	bool SaveFileBasedOpenCV(LPCTSTR lpszPath);//OpenCV保存图像
	IplImage* cvCreateDataImage(int,int,char*,int,int flag =1);//根据已有数据创建IplImage图像
	IplImage* cvBmpToIplImage(int,int flag = 1);//将bmp图像转换成IplImage图像
	void cvDataToBmp(IplImage*,int flag = 1);//将IplImage图像中的数据传到bmp图像中
	IplImage* cvFaceDec(IplImage*,int*);//人脸检测
	IplImage* cvFaceDecYuShiQi(IplImage*,int*);
	void PcFaceDetection(int*);//笔记本摄像头人脸检测1
	void PcFaceDetectionYuShiQi(int*);//笔记本摄像头人脸检测1
	IplImage* cvCornerDetection(IplImage*,int*);//角点检测
	IplImage* cvSobelEdge(IplImage*);//Sobel边缘检测
	IplImage* cvLaplacianEdge(IplImage*);//Laplacian边缘检测
	void cvMySplit(IplImage*);//获取彩色颜色分量

public:
	virtual ~CCvDIP();
};
#endif // !defined(AFX_CVDIP_H__18FCE162_19B5_49F3_9E8E_8E5DEA8447C8__INCLUDED_)
