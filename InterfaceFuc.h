#include "cv.h"
#include "highgui.h"

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

//函数声明
void cvImShow(IplImage* img,const char* imgName = "Image",int flagWindow = 1,int flagWaitKey = 1);


//显示图像
void cvImShow(IplImage *img,const char* imgName,int flagWindow,int flagWaitKey)
{
	cvNamedWindow(imgName,flagWindow);
	cvShowImage(imgName,img);
	if(1 == flagWaitKey)
		cvWaitKey(0);
	cvDestroyWindow(imgName);
}

//检测人脸并用圆形标出
IplImage* detect_and_draw( IplImage* img,CvMemStorage* storage,CvHaarClassifierCascade* cascade,int* faceNum,float scale = 1.172)
{
 
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)), 8, 1 );
 
    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );
 
    if( cascade )
    {
        /*函数cvHaarDetectObjects检测图像中的目标，由OpenCV提供。*/
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage, scale, 2, 0 ,
                                            cvSize(30, 30) );
		//记录检测到的人脸数量
		*faceNum = (int)(faces ? faces->total : 0);
        for( int i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
        }
    }
    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
	return img;
}
