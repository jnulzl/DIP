
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
		void ImageThreshold(int threshold);//图像阈值化处理
		void ImageContrary();//图像反转
		void ImageLinear(float a,int b);//图像线性化
		void RobertEdge();//Robert边缘检测
		void SobelEdge();//Sobel边缘检测
		void PreWittEdge();//PreWitt边缘检测
		void Laplacian();//拉普拉斯边缘检测
		void Guasslaplacian();//高斯拉普拉斯边缘检测
		void KrischEdge();//Krisch边缘检测
		void ImageTranslation(int horOff,int verOff);//图像平移
		void ImageRotate(float alpha);//图像旋转
		void ImageMirror();//水平镜像
		void ImageMirror1(int flagSavePreData = 1 );//垂直镜像,flag=1默认保存上一步的数据
		void ImageZoom(float ZoomX,float ZoomY);//图像缩放
		void ImageTranspose();//图像转置
		void ImageWindowTranslation(int low,int high);//窗口变换
		void ImageLog(float);//对数变换
		void ImagePower(float,float);//幂次变换
		void ImageAreaAverage(int);//邻域平均
		void ImageWeightAverage();//加权平均
		void ImageMedianFilter(int,int,int);//滤波，第三个参数表示滤波类型
		void ImagePlusMedianFilter(int,int);//十字形中值滤波
		void AddRandNoise(float);//增加随机噪声
		void AddSaltPepperNoise(float);//增加椒盐噪声
		void ImageProfileDetect();//图像轮廓检测
		void RgbAddColor(int,int,int);//彩色图象着色处理
		void ChangeBright(int);//亮度改变
		void Mosaic(int,int);//马赛克效应
		void GetRGBComponent(int);//提取RGB分量
	/*	void RColor();//彩图R分量
		void GColor();//彩图G分量
		void BColor();*///彩图B分量 
		void ToDownScan(CDC*,CPoint,CSize);//向下扫描
		void ToUpScan(CDC*,CPoint,CSize);//向上扫描
		void ToRightScan(CDC*,CPoint,CSize);//向右扫描
		void ToLeftScan(CDC*,CPoint,CSize);//向右扫描
		void HistogramEqualization();//直方图均衡化
		double* GetImageHist(int,int);//画图像直方图
		void RgbToHSI();//RGB空间转化为HSI空间
		bool OutPutImageData(CString);
		void ImageFourier();//快速傅里叶变换
		void OtusThreshold();//最大方差阈值分割
		void AdaptiveThreshold();//自适应阈值分割
		BOOL LoadFitsFile(LPCTSTR lpszPath);//加载FITS图像
		void ImageErosion(int Structure[3][3]);//图像腐蚀操作
		void ImageDilation(int Structure[3][3]);//图像膨胀操作
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
