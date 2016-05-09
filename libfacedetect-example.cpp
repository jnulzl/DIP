/*
The MIT License (MIT)

Copyright (c) 2015 Shiqi Yu
shiqi.yu@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <opencv.hpp>
#include "facedetect-dll.h"
#include "time.h"
//#pragma comment(lib,"libfacedetect.lib")

using namespace cv;
/*
int main(int argc, char* argv[])
{
	//记录程序开始时间
	float programBegin = clock();
	static CvScalar colors[] = 
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};

	//加载一幅灰度图像(单通道图像)
	Mat Color = imread("H:\\img\\face\\face(8).jpg"),gray,Color2,Color3;
	//Color.copyTo(Color2);
	//Color.copyTo(Color3);

	//彩图转为灰度图
	cvtColor( Color, gray, CV_BGR2GRAY );
	if(gray.empty())
	{
		fprintf(stderr, "Can not load the image file.\n");
		return -1;
	}

	int * pResults = NULL; 

	///////////////////////////////////////////
	// 一、正面脸检测
	// it's fast, but cannot detect side view faces
	//////////////////////////////////////////
	//!!! 输入图像必须是一幅灰度图像(单通道图像)
	//!!! 不要释放结果pResults !!!
	pResults = facedetect_frontal((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
											   1.2f, 2,  24);
	printf("%d frontal faces detected.\n", (pResults ? *pResults : 0));
	//输出检测结果
	for(int i = 0; i < (pResults ? *pResults : 0); i++)
	{
        short * p = ((short*)(pResults+1))+6*i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];
		int neighbors = p[4];
		printf("face_rect=[%d, %d, %d, %d], neighbors=%d\n", x,y,w,h,neighbors);

		CvPoint center;
		int radius;
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		circle(Color, center, radius, colors[i%8], 3, 8, 0 );
	}
	namedWindow("正面脸检测",0);
	imshow("正面脸检测",Color);
	waitKey();

	///////////////////////////////////////////
	// 二、多副图像检测
	// it can detection side view faces, but slower than the frontal face detection.
	//////////////////////////////////////////
	//!!! 输入图像必须是一幅灰度图像(单通道图像)
	//!!! 不要释放结果pResults !!!
	pResults = facedetect_multiview((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
											   1.2f, 4, 24);
	printf("%d faces detected.\n", (pResults ? *pResults : 0));

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

		printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);

		CvPoint center;
		int radius;	
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		circle(Color2, center, radius, colors[i%8], 3, 8, 0 );
	}
	namedWindow("多副图像检测",0);
	imshow("多副图像检测",Color2);
	waitKey();

	///////////////////////////////////////////
	// 三、增强版的多视角图像检测
	// it can detection side view faces, but slower than the frontal face detection.
	//////////////////////////////////////////
	//!!! 输入图像必须是一幅灰度图像(单通道图像)
	//!!! 不要释放结果pResults !!!
	pResults = facedetect_multiview_reinforce((unsigned char*)(gray.ptr(0)), gray.cols, gray.rows, gray.step,
											   1.2f, 4, 24);
	printf("一共检测到%d张脸\n", (pResults ? *pResults : 0));

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

		//printf("face_rect=[%d, %d, %d, %d], neighbors=%d, angle=%d\n", x,y,w,h,neighbors, angle);

		Point center;
		int radius;
		center.x = cvRound((x + w*0.5));
		center.y = cvRound((y + h*0.5));
		radius = cvRound((w + h)*0.25);
		circle(Color, center, radius, colors[i%8], 3, 8, 0 );
	}
	namedWindow("增强版的多视角图像检测",0);
	imshow("增强版的多视角图像检测",Color);
	//记录程序开始时间
	float programStop = clock();
	printf("运行时间:%fms\n",programStop-programBegin);
	waitKey();

	return 0;
}

*/
