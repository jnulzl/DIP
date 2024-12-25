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
	void LoadFileFromOpenCV(LPCTSTR lpszPath);//OpenCV����ͼ��	
	bool SaveFileBasedOpenCV(LPCTSTR lpszPath);//OpenCV����ͼ��
	IplImage* cvCreateDataImage(int,int,char*,int,int flag =1);//�����������ݴ���IplImageͼ��
	IplImage* cvBmpToIplImage(int,int flag = 1);//��bmpͼ��ת����IplImageͼ��
	void cvDataToBmp(IplImage*,int flag = 1);//��IplImageͼ���е����ݴ���bmpͼ����
	IplImage* cvFaceDec(IplImage*,int*);//�������
	IplImage* cvFaceDecYuShiQi(IplImage*,int*);
	void PcFaceDetection(int*);//�ʼǱ�����ͷ�������1
	void PcFaceDetectionYuShiQi(int*);//�ʼǱ�����ͷ�������1
	IplImage* cvCornerDetection(IplImage*,int*);//�ǵ���
	IplImage* cvSobelEdge(IplImage*);//Sobel��Ե���
	IplImage* cvCannyEdge(IplImage*);//Canny��Ե���
	IplImage* cvLaplacianEdge(IplImage*);//Laplacian��Ե���
	void cvMySplit(IplImage*);//��ȡ��ɫ��ɫ����
	IplImage* cvSmoothBlur(IplImage*,int,int,int);//OpenCVͼ���˲�
	IplImage* plotGrayHistogram(IplImage*,CvScalar color = cvScalar(125,125,125));//���ƻҶ�ͼ��ֱ��ͼ
	void plotColorHistogram(IplImage*);//���Ʋ�ɫͼ��ֱ��ͼ
	void plotHistogram(IplImage*);//����ͼ��ֱ��ͼ
	IplImage* HistEqualize(IplImage*);//ֱ��ͼ���⻯

private:
	bool vicar2png(LPCTSTR lpszPath);//��IMGͼ��ת����pngͼ��
	BOOL system_hide(char* CommandLine);//�������������������ʾ�����д���  

public:
	virtual ~CCvDIP();
};


#endif // !defined(AFX_CVDIP_H__18FCE162_19B5_49F3_9E8E_8E5DEA8447C8__INCLUDED_)
