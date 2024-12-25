
#include "afx.h"
#include "Dib.h"
#include "PinYuLuBoDib.h"
#ifndef _MyDib_
#define _MyDib_



class MyDib:public PinYuLuBoDib
{
public:
		LONG GetShowWidth();
		LONG GetShowHeight();
		void SetShowWidth(LONG showWidth);
		void SetShowHeight(LONG showHeight);
		void SaveOriginImage();
		void ShowOriginImage();
		void SavePreImage();
		void ShowPreImage();
public:
		void ImageThreshold(int threshold);//ͼ����ֵ������
		void ImageContrary();//ͼ��ת
		void ImageLinear(float a,int b);//ͼ�����Ի�
		void RobertEdge();//Robert��Ե���
		void SobelEdge();//Sobel��Ե���
		void PreWittEdge();//PreWitt��Ե���
		void Laplacian();//������˹��Ե���
		void Guasslaplacian();//��˹������˹��Ե���
		void KrischEdge();//Krisch��Ե���
		void ImageTranslation(int horOff,int verOff);//ͼ��ƽ��
		void ImageRotate(float alpha);//ͼ����ת
		void ImageMirror();//ˮƽ����
		void ImageMirror1(int flagSavePreData = 1 );//��ֱ����,flag=1Ĭ�ϱ�����һ��������
		void ImageZoom(float ZoomX,float ZoomY);//ͼ������
		void ImageTranspose();//ͼ��ת��
		void ImageWindowTranslation(int low,int high);//���ڱ任
		void ImageLog(float);//�����任
		void ImagePower(float,float);//�ݴα任
		void ImageAreaAverage(int);//����ƽ��
		void ImageWeightAverage();//��Ȩƽ��
		void ImageMedianFilter(int,int,int);//�˲���������������ʾ�˲�����
		void ImagePlusMedianFilter(int,int);//ʮ������ֵ�˲�
		void AddRandNoise(float);//�����������
		void AddSaltPepperNoise(float);//���ӽ�������
		void ImageProfileDetect();//ͼ���������
		void RgbAddColor(int,int,int);//��ɫͼ����ɫ����
		void ChangeBright(int);//���ȸı�
		void Mosaic(int,int);//������ЧӦ
		void GetRGBComponent(int);//��ȡRGB����
	/*	void RColor();//��ͼR����
		void GColor();//��ͼG����
		void BColor();*///��ͼB���� 
		void ToDownScan(CDC*,CPoint,CSize);//����ɨ��
		void ToUpScan(CDC*,CPoint,CSize);//����ɨ��
		void ToRightScan(CDC*,CPoint,CSize);//����ɨ��
		void ToLeftScan(CDC*,CPoint,CSize);//����ɨ��
		void HistogramEqualization();//ֱ��ͼ���⻯
		double* GetImageHist(int,int);//��ͼ��ֱ��ͼ
		void RgbToHSI();//RGB�ռ�ת��ΪHSI�ռ�
		bool OutPutImageData(CString);
		void ImageFourier();//���ٸ���Ҷ�任
		void OtusThreshold();//��󷽲���ֵ�ָ�
		void AdaptiveThreshold();//����Ӧ��ֵ�ָ�
		BOOL LoadFitsFile(LPCTSTR lpszPath);//����FITSͼ��
		void ImageErosion(int Structure[3][3]);//ͼ��ʴ����
		void ImageDilation(int Structure[3][3]);//ͼ�����Ͳ���
private:
		void Connv2(LPBYTE m_pdata,float *Template,int tempH,int tempW,double fCoef);
		int GetMedian(int*,int,int);
		void Histogram(LPBYTE,double*);
		void Equalization(LPBYTE,int,int);
		double ImageHistogram[256];
		LONG showWidth;
		LONG showHeight;
		LONG preShowWidth;
		LONG preShowHeight;
		LPBYTE originImageData;
		bool originImageIsRgb;
		LPBYTE preImageData;
		bool preImageIsRgb;
};
#endif
