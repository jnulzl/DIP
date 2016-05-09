#include "StdAfx.h"
#include "MyDib.h"
#include <math.h>
#include "fitsio.h"
/*
功能：
	获取图像显示宽度
输出：
	图像显示宽度
*/

LONG MyDib::GetShowWidth()
{	//指向原图像数据的指针	
	return showWidth;
}

/*
功能：
	获取图像显示宽度
输出：
	图像显示宽度
*/

LONG MyDib::GetShowHeight()
{	//指向原图像数据的指针	
	return showHeight;
}


void MyDib::SetShowWidth(LONG showWidth)
{	//指向原图像数据的指针	
	this->showWidth = showWidth;
}

/*
功能：
	获取图像显示宽度
输出：
	图像显示宽度
*/

void MyDib::SetShowHeight(LONG showHeight)
{	//指向原图像数据的指针
	this->showHeight = showHeight;
}


/*
功能：
	保存原始图像数据
*/
void MyDib::SaveOriginImage()
{
	LPBYTE p_Data = GetData();//获取当前图像数据指针
	originImageData = new BYTE[GetHeight()*GetLineByte()];
	//判断原始图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	originImageIsRgb = flag;
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)//如果原图像是彩色的
			{
				for(int k=0;k<3;k++)
					originImageData[i*GetLineByte()+3*j + k] = p_Data[i*GetLineByte()+3*j + k];
			}
			else//否则，如果原图像是灰色的
				originImageData[i*GetLineByte()+j] = p_Data[i*GetLineByte()+j];
		}
	/*FILE *fp;
	fp=fopen("H:\\data.txt","w");//打开文件以便写入数据
	 //将a数组中的整数写入fp指向的c:\a.txt文件
	for (i = 0; i < 2; i++) 
		for(int j = 0;j<GetWidth();j++)
			fprintf(fp,"%6d\n",originImageData[i*GetLineByte()+j]);
	fclose(fp); //写入完毕，关闭文件*/
}

/*
功能：
	显示原图
*/
void MyDib::ShowOriginImage()
{
	//**************重新设置显示宽度、高度为原始图像的宽度、高度**************
	SetShowWidth(GetWidth());
	SetShowHeight(GetHeight());
	//**************重新设置显示宽度、高度为原始图像的宽度、高度**************

	//判断当前图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	//如果原图和当前图都是彩色的或者都是灰色的
	if(originImageIsRgb&&!flag)//如果原图是彩色的而当前图是灰色的
	{
		if(GradeToRgb())//如果灰色转彩色成功
		{
			LPBYTE p_Data = GetData();//获取当前图像数据指针
			memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
		}
		else//否则，如果转换失败
		{
			AfxMessageBox("操作失败！");
			return;
		}
	}
	else if(!originImageIsRgb&&flag)//否则，如果原图是灰色的而当前图是彩色的
	{
		if(RgbToGrade())//如果彩色转灰色成功
		{
			//AfxMessageBox("彩色转灰色成功");//用来测试的语句
			LPBYTE p_Data = GetData();//获取当前图像数据指针
			memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
		}
		else//否则，如果转换失败
		{
			AfxMessageBox("操作失败！");
			return;
		}
	}
	else
	{
		LPBYTE p_Data = GetData();//获取当前图像数据指针
		memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
	}
	//************************保存原图后，上一步也恢复为原图数据*********************
		SavePreImage();//该句可选
	//************************保存原图后，上一步也恢复为原图数据*********************
}

/*
功能：
	保存上一步图像数据
*/
void MyDib::SavePreImage()
{
	LPBYTE p_Data = GetData();//获取当前图像数据指针
	preImageData = new BYTE[GetHeight()*GetLineByte()];
	//判断当前图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	preImageIsRgb = flag;
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)//如果原图像是彩色的
			{
				for(int k=0;k<3;k++)
					preImageData[i*GetLineByte()+3*j + k] = p_Data[i*GetLineByte()+3*j + k];
			}
			else//否则，如果原图像是灰色的
				preImageData[i*GetLineByte()+j] = p_Data[i*GetLineByte()+j];
		}
	//保存上一步图像的显示宽度和高度
	preShowWidth = GetShowWidth();
	preShowHeight = GetShowHeight();
}

/*
功能：
	显示上一步的图像
*/
void MyDib::ShowPreImage()
{
	//**************设置图像显示宽度、高度为上一步图像的宽度、高度**************
	SetShowWidth(preShowWidth);
	SetShowHeight(preShowHeight);
	//**************设置图像显示宽度、高度为上一步图像的宽度、高度**************
	//判断当前图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	//如果上一步的图像和当前图都是彩色的或者都是灰色的
	if(preImageIsRgb&&!flag)//如果上一步的图像是彩色的而当前图是灰色的
	{
		if(GradeToRgb())//如果灰色转彩色成功
		{
			LPBYTE p_Data = GetData();//获取当前图像数据指针
			memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
		}
		else//否则，如果转换失败
		{
			AfxMessageBox("操作失败！");
			return;
		}
	}
	else if(!preImageIsRgb&&flag)//否则，如果原图是灰色的而当前图是彩色的
	{
		if(RgbToGrade())//如果彩色转灰色成功
		{
			//AfxMessageBox("彩色转灰色成功");//用来测试的语句
			LPBYTE p_Data = GetData();//获取当前图像数据指针
			memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
		}
		else//否则，如果转换失败
		{
			AfxMessageBox("操作失败！");
			return;
		}
	}
	else
	{
		LPBYTE p_Data = GetData();//获取当前图像数据指针
		memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
	}

}

/*
功能:
	全屏显示
*/
/*void MyDib::ShowFullScreen()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	isFullScreen = true;
}*/

/*
功能：
	图像阈值化处理
输入：
	threshold：阈值
*/
/*
CDib MyDib::ImageThreshold(CDib m_Dib,int threshold)
{	//指向原图像数据的指针	
	LPBYTE pData = m_Dib.GetData();
	for(int i=0;i<m_Dib.GetHeight();i++)
		for(int j=0;j<m_Dib.GetWidth();j++)
		{
			if(pData[i*m_Dib.GetWidth()+j]>threshold)
				pData[i*m_Dib.GetWidth()+j]=255;
			else
				pData[i*m_Dib.GetWidth()+j]=0;
		}
	return m_Dib;
}
*/


/*
功能：
	图像阈值化处理
输入：
	threshold：阈值
*/
void MyDib::ImageThreshold(int threshold)
{	
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原图像数据的指针	
	LPBYTE pData = GetData();
	//判断当前图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(!flag)
			{
				if(pData[i*GetLineByte()+j]>threshold)
					pData[i*GetLineByte()+j]=255;
				else
					pData[i*GetLineByte()+j]=0;
			}
			else
			{
				//处理R
				if(pData[i*GetLineByte()+3*j]>threshold)
					pData[i*GetLineByte()+3*j]=255;
				else
					pData[i*GetLineByte()+3*j]=0;
				//处理G
				if(pData[i*GetLineByte()+3*j + 1]>threshold)
					pData[i*GetLineByte()+3*j + 1]=255;
				else
					pData[i*GetLineByte()+3*j + 1]=0;
				//处理B
				if(pData[i*GetLineByte()+3*j + 2]>threshold)
					pData[i*GetLineByte()+3*j + 2]=255;
				else
					pData[i*GetLineByte()+3*j + 2]=0;
			}
		}
}
/*
功能：
	灰度图像反转
输入：
	无输入
*/

void MyDib::ImageContrary()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原图像数据的指针
	LPBYTE pData = GetData();
	BYTE R,G,B;
	UINT LineBytes = GetLineByte();
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == this->GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)
			{
				R = pData[i*LineBytes+3*j];
				pData[i* LineBytes+3*j] = 255-R;

				G = pData[i*LineBytes+3*j + 1];
				pData[i*LineBytes+3*j + 1] = 255-G;

				B = pData[i*LineBytes+3*j + 2];
				pData[i*LineBytes+3*j + 2] = 255-B;
			}
			else
			{
				BYTE gray = pData[i*LineBytes+j];
				pData[i*LineBytes+j] = 255-gray;
			}
		}
}

/*
功能：
	图像线性化
输入：
	a：斜率
	b:截距
*/

void MyDib::ImageLinear(float a,int b)
{	
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原图像数据的指针
	LPBYTE pData = GetData();
	BYTE R,G,B;
	UINT LineBytes = GetLineByte();
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)
			{
				R = pData[i*LineBytes+3*j];
				pData[i* LineBytes+3*j] = (int)(a*R+b);

				G = pData[i*LineBytes+3*j + 1];
				pData[i*LineBytes+3*j + 1] = (int)(a*G+b);

				B = pData[i*LineBytes+3*j + 2];
				pData[i*LineBytes+3*j + 2] = (int)(a*B+b);
			}
			else
			{
				BYTE gray = pData[i*LineBytes+j];
				pData[i*LineBytes+j] = (int)(a*gray+b);
			}
		}
}

/*
功能：
	彩色图像反转
输入：
	无输入
*/


/*
功能：
	图像与模板进行卷积
输入：
	m_pdata:指向原像素的指针
	*Template:卷积模板
	tempH:模板高度
	tempW:模板宽度
	fCoef:模板系数
*/

void MyDib::Connv2(LPBYTE m_pdata,float *Template,int tempH,int tempW,double fCoef)
{
	int i,j,k,t;//循环变量
	//建立临时像素存储区
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//(一维动态数组)
	//将原像素数据赋给临时像素存储区
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	//模板中心坐标
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//开始逐个像素计算卷积
	for(j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			if(!flag)//如果图像是灰色
			{
				double fResult = 0;//单个像素计算卷积结果
				for(k=0;k<tempH;k++)
					for(t=0;t<tempW;t++)
						fResult = fResult+m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*Template[k*tempW+t];
							
					
					fResult*=fCoef;
					fResult = (float)fabs(fResult);
					if(fResult>255)
						temp[j*GetLineByte()+i]=255;
					else
						temp[j*GetLineByte()+i]=(int)(fResult+0.5);//四舍五入
			}
			else//否则，如果图像是彩色
			{
				double fResultR = 0;//单个像素计算卷积结果
				double fResultG = 0;
				double fResultB = 0;
				for(k=0;k<tempH;k++)
					for(t=0;t<tempW;t++)
					{
						fResultR = fResultR+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t)]*Template[k*tempW+t];
						fResultG = fResultG+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 1]*Template[k*tempW+t];
						fResultB = fResultB+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 2]*Template[k*tempW+t];
					}
				fResultR*=fCoef;
				fResultG*=fCoef;
				fResultB*=fCoef;
				fResultR = (float)fabs(fResultR);
				fResultG = (float)fabs(fResultG);
				fResultB = (float)fabs(fResultB);
				//对R处理
				if(fResultR>255)
					temp[j*GetLineByte()+3*i]=255;
				else
					temp[j*GetLineByte()+3*i]=(int)(fResultR+0.5);//四舍五入
				//对G处理
				if(fResultG>255)
					temp[j*GetLineByte()+3*i + 1]=255;
				else
					temp[j*GetLineByte()+3*i + 1]=(int)(fResultG+0.5);//四舍五入
				//对B处理
				if(fResultB>255)
					temp[j*GetLineByte()+3*i + 2]=255;
				else
					temp[j*GetLineByte()+3*i + 2]=(int)(fResultB+0.5);//四舍五入
			}
		}
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//删除一维动态数组
}
/*
功能：
	求中值
输入：
	a[]:数组
	n：数组长度
	type：返回值类型，1为最小值，2为中值，3为最大值
*/
int MyDib::GetMedian(int* a,int n,int type)
{
	int temp;
	for(int i=0;i<n;i++)
	{	int temp0 = a[i];
		for(int j=i+1;j<n;j++)
		{
			if(temp0>a[j])
			{
				temp = a[j];
				a[j] = a[i];
				a[i] = temp;
				temp0 = a[i];
			}
		}
	}
	if(1 == type)
		return a[0];
	else if(2 == type)
		return a[n/2];
	else
		return a[n-1];
}
/*
功能：
	Sobel边缘检测
输入：
	无输入
*/

void MyDib::SobelEdge()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = this->GetData();
	//开辟两个新的缓冲区并赋予其原图像的值
	BYTE* temP1 = new BYTE[GetLineByte()*GetHeight()];
	BYTE* temP2 = new BYTE[GetLineByte()*GetHeight()];
	memcpy(temP1,pData,GetLineByte()*GetHeight());
	memcpy(temP2,pData,GetLineByte()*GetHeight());
	//模板1
	float temp1[9];
	temp1[0]=-1;temp1[1]=-2;temp1[2]=-1;
	temp1[3]=0;temp1[4]=0;temp1[5]=0;
	temp1[6]=1;temp1[7]=2;temp1[8]=1;
	//模板2
	float temp2[9];
	temp2[0]=-1;temp2[1]=0;temp2[2]=1;
	temp2[3]=-2;temp2[4]=0;temp2[5]=2;
	temp2[6]=-1;temp2[7]=0;temp2[8]=1;

	Connv2(temP1,temp1,3,3,1);
	Connv2(temP2,temp2,3,3,1);
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//将处理后的数据赋给原数据
	memcpy(pData,temP1,GetLineByte()*GetHeight());
	delete temP1;//删除一维动态数组temP1
	delete temP2;//删除一维动态数组temP2
}

/*
功能：
	Robert边缘检测
输入：
	无输入
*/

void MyDib::RobertEdge()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = this->GetData();
	BYTE* temp = new BYTE[GetHeight()*GetLineByte()];//临时图像缓冲区(动态数组)
	memset(temp,255,GetHeight()*GetLineByte());//设定临时图像各像素初值都为255
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	int pixel[4];//Robert;
	for(int i=0;i<GetHeight()-1;i++)
		for(int j=0;j<GetWidth()-1;j++)
		{
			if(!flag)
			{
				pixel[0] = pData[i*GetLineByte()+j];
				pixel[1] = pData[i*GetLineByte()+j+1];
				pixel[2] = pData[(i+1)*GetLineByte()+j];
				pixel[3] = pData[(i+1)*GetLineByte()+j+1];

				temp[i*GetLineByte()+j] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
			}
			else
			{
				//处理R
				pixel[0] = pData[i*GetLineByte()+3*j];
				pixel[1] = pData[i*GetLineByte()+3*(j+1)];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1)];

				temp[i*GetLineByte()+3*j] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
				//处理G
				pixel[0] = pData[i*GetLineByte()+3*j +1];
				pixel[1] = pData[i*GetLineByte()+3*(j+1) +1];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j +1];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1) +1];

				temp[i*GetLineByte()+3*j + 1] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
				//处理B
				pixel[0] = pData[i*GetLineByte()+3*j +2];
				pixel[1] = pData[i*GetLineByte()+3*(j+1) +2];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j +2];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1) +2];

				temp[i*GetLineByte()+3*j + 2] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
			}
		}
	//将处理后的像素数据(temp)复制给原像素数据
	memcpy(pData,temp,GetHeight()*GetLineByte());
	delete temp;//删除一维动态数组
}

/*
功能：
	PreWitt边缘检测
输入：
	无输入
*/

void MyDib::PreWittEdge()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	//模板1
	float temp1[9];
	temp1[0]=-1;temp1[1]=-1;temp1[2]=-1;
	temp1[3]=0;temp1[4]=0;temp1[5]=0;
	temp1[6]=1;temp1[7]=1;temp1[8]=1;
	//模板2
	float temp2[9];
	temp2[0]=1;temp2[1]=0;temp2[2]=-1;
	temp2[3]=1;temp2[4]=0;temp2[5]=-1;
	temp2[6]=1;temp2[7]=0;temp2[8]=-1;
	Connv2(pData,temp1,3,3,1);
	Connv2(pData,temp2,3,3,1);
}

/*
功能：
	高斯拉普拉斯边缘检测
输入：
	无输入
*/

void MyDib::Guasslaplacian()
{	
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	//模板
	float temp[25];
	temp[0]=-2;temp[1]=-4;temp[2]=-4;temp[3]=-4;temp[4]=-2;
	temp[5]=-4;temp[6]=0;temp[7]=8;temp[8]=0;temp[9]=-4;
	temp[10]=-4;temp[11]=8;temp[12]=24;temp[13]=8;temp[14]=-4;
	temp[15]=-4;temp[16]=0;temp[17]=8;temp[18]=0;temp[19]=-4;
	temp[20]=-2;temp[21]=-4;temp[22]=-4;temp[23]=-4;temp[24]=-2;
	Connv2(pData,temp,5,5,0.25);
}

/*
功能：
	Krisch边缘检测
*/
void MyDib::KrischEdge()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	BYTE* temP1 = new BYTE[GetHeight()*GetLineByte()];
	memcpy(temP1,pData,GetHeight()*GetLineByte());
	BYTE* temP2 = new BYTE[GetHeight()*GetLineByte()];
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	int i,j;
	//模板1
	float temp1[9];
	temp1[0]=5;temp1[1]=5;temp1[2]=5;
	temp1[3]=-3;temp1[4]=0;temp1[5]=-3;
	temp1[6]=-3;temp1[7]=-3;temp1[8]=-3;
	Connv2(temP1,temp1,3,3,0.5);
	//模板2
	temp1[0]=-3;temp1[1]=5;temp1[2]=5;
	temp1[3]=-3;temp1[4]=0;temp1[5]=5;
	temp1[6]=-3;temp1[7]=-3;temp1[8]=-3;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板3
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=-3;temp1[1]=-3;temp1[2]=5;
	temp1[3]=-3;temp1[4]=0;temp1[5]=5;
	temp1[6]=-3;temp1[7]=-3;temp1[8]=5;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板4
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=-3;temp1[1]=-3;temp1[2]=-3;
	temp1[3]=-3;temp1[4]=0;temp1[5]=5;
	temp1[6]=-3;temp1[7]=5;temp1[8]=5;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板5
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=-3;temp1[1]=-3;temp1[2]=-3;
	temp1[3]=-3;temp1[4]=0;temp1[5]=-3;
	temp1[6]=5;temp1[7]=5;temp1[8]=5;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板6
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=-3;temp1[1]=-3;temp1[2]=-3;
	temp1[3]=5;temp1[4]=0;temp1[5]=-3;
	temp1[6]=5;temp1[7]=5;temp1[8]=-3;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板7
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=5;temp1[1]=-3;temp1[2]=-3;
	temp1[3]=5;temp1[4]=0;temp1[5]=-3;
	temp1[6]=5;temp1[7]=-3;temp1[8]=-3;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	//模板8
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	temp1[0]=5;temp1[1]=5;temp1[2]=-3;
	temp1[3]=5;temp1[4]=0;temp1[5]=-3;
	temp1[6]=-3;temp1[7]=-3;temp1[8]=-3;
	Connv2(temP2,temp1,3,3,0.5);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			if(temP2[i*GetLineByte() + j] > temP1[i*GetLineByte() + j])
				temP1[i*GetLineByte() + j] = temP2[i*GetLineByte() + j];
		}
	
	//把temP1中的数据赋给原图像数据
	memcpy(pData,temP1,GetHeight()*GetLineByte());
	delete temP1;
	delete temP2;
}

/*
功能：
	图像平移
输入：
	horOff：水平偏移量
	verOff：垂直偏移量
*/

void MyDib::ImageTranslation(int horOff,int verOff)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
		
	if((horOff>-GetWidth()&&horOff<GetWidth())&&(verOff>-GetHeight()&&verOff<GetHeight()))
	{
		
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
				if((i-verOff>=0)&&(i-verOff<GetHeight())&&(j+horOff>=0)&&(j+horOff<GetWidth()))
				{
					int t = i-verOff;
					int k = j+horOff;
					if(flag)
					{
							R = pData[i*LineBytes+3*j];
							temp[t* LineBytes+3*k] = R;

							G = pData[i*LineBytes+3*j + 1];
							temp[t*LineBytes+3*k + 1] = G;

							B = pData[i*LineBytes+3*j + 2];
							temp[t*LineBytes+3*k + 2] = B;
					}
					else
					{
						Gray = pData[i*GetLineByte()+j];
						temp[t*GetLineByte()+k] = Gray;
					}
					
				}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
	}
	else
	{
		AfxMessageBox("平移量违法，请重新输入！");
		return;
	}
}

/*
功能：
	图像旋转
输入：
	alpha：旋转角度
*/

void MyDib::ImageRotate(float alpha)
{

}
/*
功能：
	水平图像镜像
*/
void MyDib::ImageMirror()
{
 	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************   
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
				int k = (GetWidth()-1-j);
					if(flag)
					{
							R = pData[i*LineBytes+3*j];
							temp[i*LineBytes+3*k] = R;

							G = pData[i*LineBytes+3*j + 1];
							temp[i*LineBytes+3*k + 1] = G;

							B = pData[i*LineBytes+3*j + 2];
							temp[i*LineBytes+3*k + 2] = B;
					}
					else
					{
						Gray = pData[i*LineBytes+j];
						temp[i*LineBytes+k] = Gray;
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

/*
功能：
	垂直图像镜像
	若flagSavePreData=1表示保存上一步的图像数据
*/
void MyDib::ImageMirror1(int flagSavePreData)
{
 	//************************保存上一步数据*********************
	if(1 == flagSavePreData)
		SavePreImage();
	//************************保存上一步数据*********************   
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(!IsGrade())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
				int k = (GetHeight()-1-i);
					if(flag)
					{
							R = pData[i*LineBytes+3*j];
							temp[k*LineBytes+3*j] = R;

							G = pData[i*LineBytes+3*j + 1];
							temp[k*LineBytes+3*j + 1] = G;

							B = pData[i*LineBytes+3*j + 2];
							temp[k*LineBytes+3*j + 2] = B;
					}
					else
					{
						Gray = pData[i*LineBytes+j];
						temp[k*LineBytes+j] = Gray;
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

/*
功能：
	图像缩放

*/
void MyDib::ImageZoom(float ZoomX,float ZoomY)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	LONG Width = (LONG)(GetShowWidth()*ZoomX);
	LONG Height = (LONG)(GetShowHeight()*ZoomX);

//****************************可有可无的代码**************************
	if((GetHeight()<GetWidth())&&Height<5)//如果原始图像的高小于宽的话，当高小于5时
	{
		Height = 5;
		Width = (LONG)(5*GetWidth()/GetHeight());
	}
	else if((GetWidth()<GetHeight())&&Width<5)//否则，如果原始图像的宽小于高的话，当宽小于5时
	{
		Width = 5;
		Height = (LONG)(5*GetHeight()/GetWidth());
	}
	else if(Height<5&&Width<5)//否则(如果原始图像的宽等于高的话)当高和宽小于5时
	{
		Height = 5;
		Width  = 5;
	}
//****************************可有可无的代码**************************

	SetShowWidth(Width);
	SetShowHeight(Height);
}
/*
功能：
	图像转置
*/
void MyDib::ImageTranspose()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	if(GetHeight() !=  GetWidth())
	{
		AfxMessageBox("暂时不能处理宽高不等的图像！");
			return ;
	}
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(!IsGrade())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
					if(flag)
					{
							R = pData[i*LineBytes+3*j];
							temp[j*LineBytes+3*i] = R;

							G = pData[i*LineBytes+3*j + 1];
							temp[j*LineBytes+3*i + 1] = G;

							B = pData[i*LineBytes+3*j + 2];
							temp[j*LineBytes+3*i + 2] = B;
					}
					else
					{
						Gray = pData[i*GetLineByte()+j];
						temp[j*LineBytes+i] = Gray;
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

void MyDib::ImageWindowTranslation(int low,int high)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
					if(flag)
					{	
							R = pData[i*LineBytes+3*j];
							if(R < low)
								temp[i*LineBytes+3*j] = 0;
							else if(R > high)
								temp[i*LineBytes+3*j] = 255;
							else
								temp[i*LineBytes+3*j]=R;

							G = pData[i*LineBytes+3*j + 1];
							if(G < low)
								temp[i*LineBytes+3*j + 1] = 0;
							else if(G > high)
								temp[i*LineBytes+3*j + 1] = 255;
							else
								temp[i*LineBytes+3*j]=G;

							B = pData[i*LineBytes+3*j + 2];
							if(B < low)
								temp[i*LineBytes+3*j + 2] = 0;
							else if(B > high)
								temp[i*LineBytes+3*j + 2] = 255;
							else
								temp[i*LineBytes+3*j]=B;
					}
					else
					{
						Gray = pData[i*LineBytes+j];
						if(Gray < low)
							temp[i*LineBytes+j] = 0;
						else if(Gray > high)
							temp[i*LineBytes+j] = 255;
						else
							temp[i*LineBytes+j]=Gray;
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

/*
功能：
	图像对数变换
*/
void MyDib::ImageLog(float coeff)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	LPBYTE temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
					if(flag)
					{	
							R = pData[i*LineBytes+3*j];
							temp[i*LineBytes+3*j]=(int)(coeff*log(1+R));

							G = pData[i*LineBytes+3*j + 1];
							temp[i*LineBytes+3*j + 1]=(int)(coeff*log(1+G));

							B = pData[i*LineBytes+3*j + 2];
							temp[i*LineBytes+3*j + 1]=(int)(coeff*log(1+B));
					}
					else
					{
						Gray = pData[i*LineBytes+j];
						temp[i*LineBytes+j]=(int)(coeff*log(1+Gray));
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

/*
功能：
	图像幂次变换
*/
void MyDib::ImagePower(float coeff,float gamma)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区(一维动态数组)
	memset(temp,255,GetHeight()*LineBytes);//设定临时图像各像素初值都为255
	//BYTE Gray;
	
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
					if(flag)
					{	
							R = pData[i*LineBytes+3*j];
							temp[i*LineBytes+3*j]=(int)(coeff*pow(R,gamma));

							G = pData[i*LineBytes+3*j + 1];
							temp[i*LineBytes+3*j+1]=(int)(coeff*pow(G,gamma));

							B = pData[i*LineBytes+3*j + 2];
							temp[i*LineBytes+3*j + 2]=(int)(coeff*pow(B,gamma));
					}
					else
					{
						Gray = pData[i*LineBytes+j];
						temp[i*LineBytes+j]=(int)(coeff*pow(Gray,gamma));
					}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}
/*
功能：
	邻域平均
*/
void MyDib::ImageAreaAverage(int n)
{	
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//检查出入模板参数是否为奇数
	if(n<3||1 != n%2)
	{
		AfxMessageBox("参数错误！邻域平均模板的尺寸必须为大于3的奇数！");
		return ;
	}
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	//模板
	//float temp[10000];//普通数组
	float* temp = new float[n*n];//一维动态数组
	for(int i=0;i<n*n;i++)
		temp[i]=1;
	Connv2(pData,temp,n,n,1.0/(n*n));
	delete temp;//删除一维动态数组
}
/*
功能：
	加权平均
*/
void MyDib::ImageWeightAverage()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	
	//模板
	float temp[9];
	temp[0]=1;temp[1]=2;temp[2]=1;
	temp[3]=2;temp[4]=4;temp[5]=2;
	temp[6]=1;temp[7]=2;temp[8]=1;
	
	Connv2(pData,temp,3,3,1/16.0);
}
/*
功能：
	中值滤波
输入：
	tempH：模板高度
	tempW：模板宽度
	type:对中值滤波来说，type=2
*/
void MyDib::ImageMedianFilter(int tempH,int tempW,int type)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//检查出入模板参数是否为奇数
	if(tempH<3||1 != tempH%2||tempW<3||1 != tempW%2)
	{
		AfxMessageBox("参数错误！模板的高与宽必须为大于3奇数！");
		return ;
	}
	//建立滤波模板,控制参与统计排序的像素所构成的几何形状
	//int myTemplate[100][100];//普通二维数组
//*******************动态二维数组(定义方式1)**********************
	/*int*  *myTemplate = new int*[tempH];//动态二维数组每行
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
		*/
//*******************动态二维数组(定义方式1)**********************
	////////////////////////////////////////////////////////////////////////
//*******************动态二维数组(定义方式2)**********************
	LPINT*  myTemplate = new LPINT[tempH];//动态二维数组每行
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
		//说明：其实这里只是定义：typedef int far     *LPINT;
//*******************动态二维数组(定义方式2)**********************
	for(int k=0;k<tempH;k++)
		for(int t=0;t<tempW;t++)	
			myTemplate[k][t] = 1;//模板内所有像素都参与统计排序
	//存储滤波模板内的像素值
	//int Template[10000];//普通数组
	int* Template = new int[tempH*tempW];//一维动态数组
	//int** Template = new int[tempH][tempW];二维动态数组不能这样定义

	//设置临时图像缓冲区
	LPBYTE m_pdata = GetData();
	//建立临时像素存储区
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//一维动态数组
	//将原像素数据赋给临时像素存储区
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//模板中心坐标
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//开始逐个像素计算卷积
	for(int j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(int i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			for(int k=0;k<tempH;k++)
			{	
				for(int t=0;t<tempW;t++)	
					//把窗口为tempHxtempW内的像素读到临时存储模板中去
					Template[k*tempW+t] = m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*myTemplate[k][t];
			}	
			//调用求中值函数，取每个模板内像素大小的中值，并赋值到临时存储区temp内
			temp[j*GetLineByte()+i]=GetMedian(Template,tempH*tempW,type);
		}
	//将处理完后的像素数据temp复制给原像素数据m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//删除一维动态数组
	delete Template;//删除一维动态数组
	//删除动态二维数组
	for(int index=0;index<tempH;index++)
		delete[] myTemplate[index];
	delete[] myTemplate;
}

/*
功能：
	十字形中值滤波,与一般的中值滤波相比只是滤波模板不同而已
输入：
	tempH：模板高度
	tempW：模板宽度
*/
void MyDib::ImagePlusMedianFilter(int tempH,int tempW)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//检查出入模板参数是否为奇数
	if(tempH<3||1 != tempH%2||tempW<3||1 != tempW%2)
	{
		AfxMessageBox("参数错误！模板的高与宽必须为大于3奇数！");
		return ;
	}
	//建立滤波模板,控制参与统计排序的像素所构成的几何形状
	//int myTemplate[100][100];//普通数组
	//*************二维动态数组******************
	int** myTemplate = new int*[tempH];
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
	//*************二维动态数组******************
	int k,t;
	//1、先将滤波模板全部赋值为0
	for(k=0;k<tempH;k++)
		for(t=0;t<tempW;t++)	
			myTemplate[k][t] = 0;
	//2、再把模板的水平中心赋值为1
	k = tempH/2;
	for(t=0;t<tempW;t++)	
			myTemplate[k][t] = 1;
	//3、最后把模板的竖直中心赋值为1
	t = tempW/2;
	for(k=0;k<tempH;k++)	
			myTemplate[k][t] = 1;
	//存储滤波模板内的像素值
	 int* Template = new int[tempH+tempW-1];//一维动态数组
	//int Template[10000];//普通数组

	//设置临时图像缓冲区
	LPBYTE m_pdata = GetData();
	//建立临时像素存储区
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//一维动态数组
	//将原像素数据赋给临时像素存储区
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//模板中心坐标
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//开始逐个像素计算卷积
	for(int j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(int i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			int TemplateIndex = 0;
			for(int k=0;k<tempH;k++)
			{	
				for(int t=0;t<tempW;t++)	
				{	//把窗口为tempHxtempW中水平和垂直中心线内的像素保存起来
					int tempPoint = m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*myTemplate[k][t];
					if(0 != tempPoint)
						Template[TemplateIndex++] = tempPoint;
				}
			}	
			//调用求中值函数，取每个模板内像素大小的中值，并赋值到临时存储区temp内
			temp[j*GetLineByte()+i]=GetMedian(Template,tempH+tempW-1,2);//这里的2表示取中值
		}
	//将处理完后的像素数据temp复制给原像素数据m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//删除一维动态数组
	delete Template;//删除一维动态数组
	//删除动态二维数组
	for(int index=0;index<tempH;index++)
		delete[] myTemplate[index];
	delete[] myTemplate;//一维动态数组
}

/*
功能：
	添加随机噪声
*/
void MyDib::AddRandNoise(float radio)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区
	memcpy(temp,pData,GetHeight()*LineBytes);//设原像素数据复制到临时图像缓冲区
	int noisePoint;//随机数
	//彩色图像处理的必须变量
	//BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{	
				noisePoint = rand()%256;
				if(noisePoint>(255-127.5*radio))
				{
					if(flag)
					{	
							temp[i*LineBytes+3*j] += noisePoint;
							temp[i*LineBytes+3*j + 1] += noisePoint;
							temp[i*LineBytes+3*j + 2] += noisePoint;	
					}
					else
					{
						temp[i*LineBytes+j] += noisePoint;
					}
				}
				else if(noisePoint<127.5*radio)
				{
					if(flag)
					{	
							temp[i*LineBytes+3*j] -= noisePoint;
							temp[i*LineBytes+3*j + 1] -= noisePoint;
							temp[i*LineBytes+3*j + 2] -= noisePoint;	
					}
					else
					{
						temp[i*LineBytes+j] -= noisePoint;
					}
				}
			}
		//将处理后的像素数据(temp)复制给原像素数据
	memcpy(pData,temp,GetHeight()*LineBytes);
	delete temp;//删除一维动态数组
}

/*
功能：
	添加椒盐噪声
*/
void MyDib::AddSaltPepperNoise(float radio)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//临时图像缓冲区
	memcpy(temp,pData,GetHeight()*LineBytes);//设原像素数据复制到临时图像缓冲区
	//彩色图像处理的必须变量
	//BYTE R,G,B,Gray;
	//判断图像是彩色的还是灰色的
	bool flag;
	if(24 == GetBitCount())
		flag = true;//图像是彩色的
	else
		flag = false;//图像是灰色的
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{
				if((rand()%256)>(255-127.5*radio))
				{	
					if(flag)
					{	
							temp[i*LineBytes+3*j]=255;
							temp[i*LineBytes+3*j + 1]=255;
							temp[i*LineBytes+3*j + 2]=255;	
					}
					else
					{
						temp[i*LineBytes+j]=255;
					}
				}
				else if((rand()%256)<(127.5*radio))
				{
					if(flag)
					{	
							temp[i*LineBytes+3*j]=0;
							temp[i*LineBytes+3*j + 1]=0;
							temp[i*LineBytes+3*j + 2]=0;	
					}
					else
					{
						temp[i*LineBytes+j]=0;
					}
				}
			}
		//将处理后的像素数据(temp)复制给原像素数据
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//删除一维动态数组
}

/*
功能：
	提取图像轮廓
*/
void MyDib::ImageProfileDetect()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//建立滤波模板,控制参与统计排序的像素所构成的几何形状

	//设置临时图像缓冲区
	LPBYTE m_pdata = GetData();
	//建立临时像素存储区
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//建立动态数组的标准方式
	//将原像素数据赋给临时像素存储区
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//模板中心坐标
	//开始逐个像素进行处理
	for(int j = 1;j<GetHeight()-1;j++)
		for(int i = 1;i<GetWidth()-1;i++)
		{	int flag = 1;
			BYTE tempPoint = m_pdata[j*GetLineByte()+i];//为当前的中心像素
			for(int k=0;k<3;k++)
			{	
				for(int t=0;t<3;t++)	
				{
					//把窗口为tempHxtempW内的像素读到临时存储模板中去
					if((m_pdata[(j-1 + k)*GetLineByte()+(i-1+t)]-tempPoint) < 10)//如果
						flag*=1;
					else
						flag*=0;
				}
			}
			if(1 == flag)//如果中心像素(i,j)的与其8邻域的像素差<10的话，给(i,j)赋值为255
				temp[j*GetLineByte()+i]=255;
		}
	//将处理完后的像素数据temp复制给原像素数据m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//删除一维动态数组	
}

/*
功能：
	彩色图像着色处理
*/
void MyDib::RgbAddColor(int m_R,int m_G,int m_B)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	//彩色图像处理的必须变量
	BYTE R,G,B,Gray;
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
			{	
					B = pData[i*LineBytes+3*j];
					G = pData[i*LineBytes+3*j + 1];
					R = pData[i*LineBytes+3*j + 2];
					Gray = (BYTE)(0.3*R+0.59*G+0.11*B);
					pData[i*LineBytes+3*j] = m_B*Gray/255;
					pData[i*LineBytes+3*j + 1] = m_G*Gray/255;
					pData[i*LineBytes+3*j + 2] = m_R*Gray/255;				
			}
}
/*
功能：	
	亮度改变
*/
void MyDib::ChangeBright(int m_radio)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<(int)GetLineByte();j++)
			{	
				BYTE temp;
				temp = int(*pData*m_radio/100);//调整当前点的亮度
				if(temp<0)//如果调整后的值小于0
					*pData = 0;
				if(temp>255)//如果调整后的值大于255
					*pData = 255;

				*pData = temp;
				pData++;//指针向下移动
			}
}

/*
功能：
	马赛克效应
*/
void MyDib::Mosaic(int tempW,int tempH)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原像素数据
	LPBYTE m_pdata = GetData();
	int i,j,k,t;//循环变量
	//模板中心坐标
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//开始逐个像素计算卷积
	for(j = tempMY;j<GetHeight()-tempH+tempMY+1;j+=tempH)
		for(i = tempMX;i<GetWidth()-tempW+tempMX+1;i+=tempW)
		{
			float fResultR = 0;
			float fResultG = 0;
			float fResultB = 0;
			//计算模板下像素的平均值
			for(k=0;k<tempH;k++)
				for(t=0;t<tempW;t++)
				{
					fResultR = fResultR+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t)];	
					fResultG = fResultG+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 1];	
					fResultB = fResultB+m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 2];	
				}
			fResultR/=(tempH*tempW);
			fResultG/=(tempH*tempW);
			fResultB/=(tempH*tempW);
			//把计算得到的平均值赋给模板下的每个像素
			for(k=0;k<tempH;k++)
				for(t=0;t<tempW;t++)
				{
					m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t)] = (BYTE)fResultR;
					m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 1] = (BYTE)fResultG;
					m_pdata[(j-tempMY + k)*GetLineByte()+3*(i-tempMX+t) + 2] = (BYTE)fResultB;
				}
		}
}

/*
功能：
	提取彩色图像分量
*/
void MyDib::GetRGBComponent(int tempRGB)
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************

	//获取原图像数据指针
	LPBYTE pData = GetData();
	//灰度图像临时缓存区
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + tempRGB];//计算机中是按BGR顺去存储的

	if(!RgbToGrade())//如果彩图转灰度图像失败，则直接返回
	{
		AfxMessageBox("提取R分量失败！");
		return;
	}
	//再次获取原图像数据指针
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//删除临时缓存区
}
/*
功能：
	彩图R分量提取
*/

/*
void MyDib::RColor()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************

	//获取原图像数据指针
	LPBYTE pData = GetData();
	//灰度图像临时缓存区
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + 2];//计算机中是BGR

	if(!RgbToGrade())//如果彩图转灰度图像失败，则直接返回
	{
		AfxMessageBox("提取R分量失败！");
		return;
	}
	//再次获取原图像数据指针
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//删除临时缓存区
}
*/
/*
功能：
	彩图R分量提取
*/

/*
void MyDib::GColor()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//获取原图像数据
	LPBYTE pData = GetData();
	//灰度图像临时缓存区
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + 1];
	if(!RgbToGrade())//如果彩图转灰度图像失败，则直接返回
	{
		AfxMessageBox("提取G分量失败！");
		return;
	}
	//再次获取原图像数据指针
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//删除临时缓存区
}
*/
/*
功能：
	彩图R分量提取
*/
/*
void MyDib::BColor()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************

	//获取原图像数据
	LPBYTE pData = GetData();
	//灰度图像临时缓存区
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j];
	if(!RgbToGrade())//如果彩图转灰度图像失败，则直接返回
	{
		AfxMessageBox("提取B分量失败！");
		return;
	}
	//再次获取原图像数据指针
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//删除临时缓存区
}
*/
/*
功能：
	向下扫描
*/
void MyDib::ToDownScan(CDC *pDC,CPoint origin,CSize size)
{
	// 位图无效，无法绘制，返回错误
    if(!IsValid())
    {
        return;
    }

    // 旧的调色板句柄
	HPALETTE hOldPalette = NULL;

	// 如果位图指针为空，则返回FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// 如果位图有调色板，则选进设备环境中
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// 设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);


	// 将位图在pDC所指向的设备上进行显示
	for(int i=0;i<GetHeight();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x,origin.y+i, size.cx, 1,
			0, GetHeight()-i, GetWidth(), 1, GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// 恢复旧的调色板
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
功能：
	向上扫描
*/
void MyDib::ToUpScan(CDC *pDC,CPoint origin,CSize size)
{
	// 位图无效，无法绘制，返回错误
    if(!IsValid())
    {
        return;
    }

    // 旧的调色板句柄
	HPALETTE hOldPalette = NULL;

	// 如果位图指针为空，则返回FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// 如果位图有调色板，则选进设备环境中
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// 设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);


	// 将位图在pDC所指向的设备上进行显示
	for(int i=0;i<GetHeight();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x,origin.y+GetHeight()-i, size.cx, 1,
			0, i, GetWidth(), 1, GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// 恢复旧的调色板
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
功能：
	向右扫描
*/
void MyDib::ToRightScan(CDC *pDC,CPoint origin,CSize size)
{
	// 位图无效，无法绘制，返回错误
    if(!IsValid())
    {
        return;
    }

    // 旧的调色板句柄
	HPALETTE hOldPalette = NULL;

	// 如果位图指针为空，则返回FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// 如果位图有调色板，则选进设备环境中
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// 设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);


	// 将位图在pDC所指向的设备上进行显示
	for(int i=0;i<GetWidth();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x+i,origin.y, 1, size.cy,
			i, 0, 1,GetHeight(), GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// 恢复旧的调色板
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
功能：
	向左扫描
*/
void MyDib::ToLeftScan(CDC *pDC,CPoint origin,CSize size)
{
	// 位图无效，无法绘制，返回错误
    if(!IsValid())
    {
        return;
    }

    // 旧的调色板句柄
	HPALETTE hOldPalette = NULL;

	// 如果位图指针为空，则返回FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// 如果位图有调色板，则选进设备环境中
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// 设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);


	// 将位图在pDC所指向的设备上进行显示
	for(int i=0;i<GetWidth();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x+GetWidth()-i,origin.y, 1, size.cy,
			GetWidth()-i, 0, 1,GetHeight(), GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// 恢复旧的调色板
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
功能：
	实现图像直方图均衡化
*/
void MyDib::HistogramEqualization()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************

	//*******************************调式程序*********************************
		/*	FILE *fp;
		fp=fopen("H:\\data2.txt","w");//打开文件以便写入数据
		 //将a数组中的整数写入fp指向的c:\a.txt文件
		for (i = 0; i < 256; i++) 	
			fprintf(fp,"%.2f\n",tempImageHistogram[i]);
		fclose(fp); //写入完毕，关闭文件
		*/
	//********************************调式程序********************************
	//指向原图像数据的指针
	LPBYTE pData = GetData();
	if(IsGrade())//如果图像是灰色的话	
		Equalization(pData,1,0);	
	else//否则，如果图像是彩色的话
	{
		//*******************************处理R分量************************
		Equalization(pData,3,0);	
		//*******************************处理G分量************************
		Equalization(pData,3,1);	
		//*******************************处理B分量************************
		Equalization(pData,3,2);			
	}
}

/*
功能：
	求图像的直方图
*/
void MyDib::Histogram(LPBYTE p_data,double* ImageHistogram)
{
	int i,j;
	//为直方图赋初值
	for(i=0;i<256;i++)
			ImageHistogram[i]=0;
	//求灰度图像中每个灰度级的数量
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
				int gray = (int)p_data[i*GetWidth()+j];
				ImageHistogram[gray]++;
		}
	//求灰度图像中每个灰度级出现的概率(频率)
	for(i=0;i<256;i++)
		ImageHistogram[i] /= (GetHeight()*GetWidth()*1.0);
}
/*
功能：
	图像直方图均衡化
*/
void MyDib::Equalization(LPBYTE originData,int coef,int num)
{
	//图像灰度直方图
	//double ImageHistogram[256];
	//中间临时变量
	double tempImageHistogram[256];
	//临时图像数据存储区
	LPBYTE tempData = new BYTE[GetHeight()*GetWidth()];
	int i,j;

	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			tempData[i*GetWidth()+j] = (BYTE)originData[i*GetLineByte()+coef*j+num];
	//求灰色图像直方图
	Histogram(tempData,ImageHistogram);
	//定义直方图累积求和并初始化
	double tempHistogram[256];
	tempHistogram[0] = ImageHistogram[0];
	for(i=0;i<256;i++)
	{	
		//1、求累计密度函数
		if(0 != i)
			tempHistogram[i] = tempHistogram[i-1] + ImageHistogram[i];
		//2、求均衡化后的像素
		tempImageHistogram[i] = (255.0*tempHistogram[i]+0.5);
	}
		//3、将均衡化后的像素赋给原图像数据
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
				int gray = (int)tempData[i*GetWidth()+j];
				originData[i*GetLineByte()+coef*j + num] = (BYTE)tempImageHistogram[gray];
		}
	delete tempData;//删除临时数据
}	

/*
功能：
	//RGB空间转化为HSI空间
*/
void MyDib::RgbToHSI()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************

	//获取原图像数据指针
	LPBYTE pData = GetData();
	//灰度图像临时缓存区
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = (BYTE)((pData[i*GetLineByte()+3*j]
						+pData[i*GetLineByte()+3*j+1]+pData[i*GetLineByte()+3*j+2])/3);

	if(!RgbToGrade())//如果彩图转灰度图像失败，则直接返回
	{
		AfxMessageBox("转换失败！");
		return;
	}
	//再次获取原图像数据指针
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//删除临时缓存区
}

/*
功能：
	输出当前图像数据
*/
bool MyDib::OutPutImageData(CString txtFilePath)
{
	if(!IsValid())
		return false;
	//获取原图像数据指针
	LPBYTE pData = GetData();
	FILE *fp;
	int i,j;
		
	if(IsGrade())//如果当前图像是灰度图像
	{
		fp=fopen(txtFilePath,"w");//打开文件以便写入数据
		fprintf(fp,"高=%-3d，宽=%-3d\n",GetWidth(),GetHeight());
		for (i = 0; i <GetHeight();i++) 
		{
			for (j = 0; j <GetWidth();j++) 
				fprintf(fp,"%-4d",pData[i*GetLineByte()+j]);
			fprintf(fp,"\n");
		}
		fclose(fp); //写入完毕，关闭文件
		return true;
	}
	else//否则，如果当前图像是彩色图像
	{
		fp=fopen(txtFilePath,"w");//打开文件以便写入数据
		fprintf(fp,"高=%-3d，宽=%-3d\n",GetWidth(),GetHeight());
		for (i = 0; i < GetHeight(); i++) 
		{
			for (j = 0; j < GetWidth(); j++) 
				fprintf(fp,"(%-3d,%-3d,%-3d)",pData[i*GetLineByte()+3*j+2],pData[i*GetLineByte()+3*j+1],pData[i*GetLineByte()+3*j]);
			fprintf(fp,"\n");
		}
		fclose(fp); //写入完毕，关闭文件
		return true;
	}
	return false;
}

/*
功能：
	对图像进行快速傅里叶变换
*/
void MyDib::ImageFourier()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	
	//一
	//FirstQuickFourier();//快速傅里叶变换（未将变换后的原点移到中心）
	//二
	QuickFourier();//快速傅里叶变换（将变换后的原点移到中心）
	//三
	/*LPBYTE pData = GetData();
	int i,j;
	double* temp = new double[GetLineByte()*GetHeight()];
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			temp[i*GetLineByte()+j] = (double)pData[i*GetLineByte()+j];
	fourier(temp,GetWidth(),GetHeight(),-1);
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			pData[i*GetLineByte()+j] = (BYTE)temp[i*GetLineByte()+j];
	delete temp;
	*/


	/*//获取原图像数据指针
	LPBYTE pData = GetData();
	int i,j;
	//灰度图像临时缓存区
	CplexNum* pTd = new CplexNum[sizeof(CplexNum)*GetHeight()*GetWidth()];
	CplexNum* pFd = new CplexNum[sizeof(CplexNum)*GetHeight()*GetWidth()];
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			pTd[i*sizeof(CplexNum)*GetWidth()+j].re = (double)pData[i*GetLineByte()+j];
			pTd[i*sizeof(CplexNum)*GetWidth()+j].im = 0;
		}

	Fourier(pTd,GetWidth(), GetHeight(),pFd);

	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
			double temp1 = pTd[i*sizeof(CplexNum)*GetWidth()+j].re;
			double temp2 = pTd[i*sizeof(CplexNum)*GetWidth()+j].im;
			pData[i*GetLineByte()+j] = (BYTE)(sqrt(temp1*temp1+temp2+temp2));
		}
		delete pTd;
		delete pFd;*/
}
/*
功能：
	对图像进行水平腐蚀
*/
/*
void MyDib::HorCorrosion()
{

}
*/

/*
功能：
	画图像直方图
*/

double* MyDib::GetImageHist(int coef,int num)
{
	//获取当前图像数据(默认当前图像为灰度图像)
	LPBYTE pData = GetData();
	//临时图像数据存储区
	LPBYTE tempData = new BYTE[GetHeight()*GetWidth()];
	int i,j;
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			tempData[i*GetWidth()+j] = (BYTE)pData[i*GetLineByte()+coef*j+num];
	//求灰色图像直方图
	Histogram(tempData,ImageHistogram);
	return ImageHistogram;
}

/*
功能：
	拉普拉斯边缘检测
*/
void MyDib::Laplacian()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//设置临时图像缓冲区
	LPBYTE pData = GetData();
	//模板1
	/*float temp1[9];
	temp1[0]=0;temp1[1]=-1;temp1[2]=0;
	temp1[3]=-1;temp1[4]=4;temp1[5]=-1;
	temp1[6]=0;temp1[7]=-1;temp1[8]=0;
	Connv2(pData,temp1,3,3,1);*/
	//模板2
	float temp2[9];
	temp2[0]=-1;temp2[1]=-1;temp2[2]=-1;
	temp2[3]=-1;temp2[4]=8;temp2[5]=-1;
	temp2[6]=-1;temp2[7]=-1;temp2[8]=-1;
	Connv2(pData,temp2,3,3,1);
	
}

/*
功能：
	最大方差阈值分割
*/
void MyDib::OtusThreshold()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	// 循环变量
	int i, j;

    // 原图数据区指针
    LPBYTE p_data = GetData();
    
    // 图像每行像素所占的字节数
    int nLineByte = GetLineByte();

    // 图像的宽度
    int nWidth = GetWidth();

    // 图像的高度
    int nHeight = GetHeight();

	// 灰度直方图数组，并初始化
	int nGrayHistogram[256];
	memset(nGrayHistogram, 0, sizeof(nGrayHistogram));
     
	// 统计各个灰度级对应的像素个数，并存放到灰度直方图数组中
    int nPixel;
	for (j = 0; j < nHeight; j ++)
	    for (i = 0; i < nWidth; i ++)
	    {
		    // 获取当前像素点的灰度值
            nPixel = p_data[nLineByte * j + i];	

		    // 对灰度值统计计数
		    nGrayHistogram[nPixel] ++;		
	    }

    // c0组和c1组的均值
    float u0, u1;

    // c0组和c1组的概率
    float w0, w1;

    // c0组的像素总数
    int nCount0;

    // 阈值和最佳阈值（对应方差最大时的阈值）
    int nT, nBestT;

    // 方差和最大方差
    float fVaria, fMaxVaria = 0;

    // 统计直方图中像素点的总数，并存放到nSum中
    int nSum=0;
    for(i = 0; i < 256; i ++)
        nSum += nGrayHistogram[i];


    // 令阈值nT从0遍历到255
    for(nT = 0; nT < 256; nT ++)
    {
        // 当阈值为nT时，计算c0组的均值和概率
        u0 = 0;
        nCount0 = 0;
        for(i = 0; i <= nT; i++)
        {
            u0 += i * nGrayHistogram[i];
            nCount0 += nGrayHistogram[i];
        }
        u0 /= nCount0;
        w0 = (float) nCount0 / nSum;

        // 当阈值为nT时，计算c1组的均值和概率
        u1 = 0;
        for(i = nT+1; i < 256; i ++)
             u1 += i * nGrayHistogram[i];
        u1 /= (nSum - nCount0);
        w1 = 1 - w0;

        // 计算两组间的方差
        fVaria = w0 * w1 * (u0 - u1) * (u0 - u1);

        // 记录最大方差和最佳阈值
        if(fVaria > fMaxVaria)
        {
            fMaxVaria = fVaria;
            nBestT = nT;
        }
    }

    // 利用最佳阈值对原图像作分割处理
    for(j = 0; j < nHeight; j ++)
        for(i = 0; i < nWidth; i ++)
        {
            if(p_data[j * nLineByte + i] < nBestT)
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }
}

/*
功能：
	自适应阈值分割
*/
void MyDib::AdaptiveThreshold()
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	// 循环变量
    int i,j;
    
    // 原图像数据区指针
    LPBYTE p_data = GetData();
    

    // 图像每行像素所占的字节数
    int nLineByte = GetLineByte();

    // 图像的宽度
    int nWidth = GetWidth();

    // 图像的高度
    int nHeight = GetHeight();

    // 局部阈值
    int nThreshold[2][2];

    // 子图像的灰度平均值
    int nAvgValue;

    // 对左上图像逐点扫描,计算该子图像的灰度平均值
    nAvgValue = 0;
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = 0; i < nWidth / 2; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // 设置阈值为子图像的平均值
    nThreshold[0][0] = nAvgValue;

    // 对左上图像逐点扫描并进行阈值分割
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = 0; i < nWidth / 2; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // 对右上图像逐点扫描,计算该子图像的灰度平均值
    nAvgValue = 0;
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // 设置阈值为子图像的平均值
    nThreshold[0][1] = nAvgValue;

    // 对右上图像逐点扫描并进行阈值分割
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // 对左下图像逐点扫描,计算该子图像的灰度平均值
    nAvgValue = 0;
    for(j = 0; j < nHeight / 2; j ++)
        for(i = 0; i < nWidth / 2; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // 设置阈值为子图像的平均值
    nThreshold[1][0] = nAvgValue;

    // 对左下图像逐点扫描并进行阈值分割
    for(j = 0; j < nHeight / 2; j ++)
        for(i = 0; i < nWidth / 2; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // 对右下图像逐点扫描,计算该子图像的灰度平均值
    nAvgValue = 0;
    for(j = 0; j < nHeight / 2; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // 设置阈值为子图像的平均值
    nThreshold[1][1] = nAvgValue;

    // 对右下下图像逐点扫描并进行阈值分割
    for(j = 0; j < nHeight / 2; j ++)
        for(i = nWidth / 2; i < nWidth;i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }
}

/*
功能：
	加载Fits文件
*/
BOOL MyDib::LoadFitsFile(LPCTSTR lpszPath)
{	
	// 清理空间
    Empty(FALSE); 

	fitsfile *fptr; //指向文件的指针
	char *filename  = (LPSTR)lpszPath;     /* 已经存在的fits文件 */
    int status = 0,nfound;
	long naxes[2];//存储图像的长和宽
	int naxis;//存储图像维数
	int bitpix;//存储图像像素位数
	//int maxdim;//存储图像长和宽中的最大者
	long fpixel[2];//左下角坐标
	long lpixel[2];//右上角坐标
	long  inc[2];//
	int nulval;
	int anynul;
	int i,j;

	//1、读取图像数据，只读(READONLY)
    if ( fits_open_data(&fptr, filename, READONLY, &status) )
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}


	//2、获取图像的像素位数
	if(fits_get_img_type(fptr, &bitpix, &status))
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}
	//3、获取图像的维数
	if(fits_get_img_dim(fptr, &naxis, &status))
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}

	//4、获取图像的长和宽
	if ( fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}

	//5、读取像素数据
	fpixel[0]=1;
	fpixel[1]=1;
	lpixel[0]=naxes[0];
	lpixel[1]=naxes[1];
	inc[0] = 1;
	inc[1] = 1;

	int *array = new int[naxes[0]*naxes[1]];
	if ( fits_read_subset(fptr, TUINT, fpixel,lpixel,inc, &nulval, array,&anynul, &status) )
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}

	//求最大和最小像素值
	int maxPixel = array[0];
	int minPixel = array[0];
	for(i = 0;i<naxes[1];i++)
		for(j = 0;j<naxes[0];j++)
		{
			int temp = array[i*naxes[0] + j];
			if(maxPixel <= temp)
				maxPixel = temp;
			if(minPixel >= temp)
				minPixel = temp;
		}

	//图像灰度变换
	for(i = 0;i<naxes[1];i++)
		for(j = 0;j<naxes[0];j++)
		{
			int temp = array[i*naxes[0] + j];
			if(temp <= minPixel)
				array[i*naxes[0] + j] = 0;
			if((temp < maxPixel)&&(temp > minPixel))
				array[i*naxes[0] + j] = (int)(255.0*(temp-minPixel)/(maxPixel-minPixel));
			if(temp>=maxPixel)
				array[i*naxes[0] + j] = 255;
		}
	
/*	FILE *fp;
	fp=fopen("H:\\data.txt","w");//打开文件以便写入数据
	 //将a数组中的整数写入fp指向的c:\a.txt文件
	for (i = 0; i < naxes[1]; i++) 
		for(int j = 0;j<naxes[0];j++)
			fprintf(fp,"%6d",array[i*naxes[0]+j]);
		fprintf(fp,"\n");	
	fclose(fp); //写入完毕，关闭文件
	*/
	CreateDIB("newImage",array,lpixel[0],lpixel[1],8,1);

	return TRUE;
}

/*
功能：
	二值图像腐蚀操作(如果模板的中心值与其它值不一样，则将当前中心值取反)
*/
void MyDib::ImageErosion(int Structure[3][3])
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原图像数据的指针
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();//获取行字节数
	//开辟临时缓冲区
	BYTE* temp = new BYTE[GetHeight()*LineBytes];
	//将原像素数据复制到临时缓冲区
	memcpy(temp,pData,GetHeight()*LineBytes);
	
	int backGround;
	int i,j;
	//检查是否为二值图像
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if((temp[i*GetLineByte()+j] != 0)&&(temp[i*GetLineByte()+j] != 255))
				{
					AfxMessageBox("当前图像不是二值图像");
					return;
				}
			}

	//寻找背景点
		/* //(默认颜色多的为背景点)
		int Count255 = 0,Count0 = 0,
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if(temp[i*GetLineByte()+j] ==0)
					Count0++;
				else
					Count255++;
			}
		if(Count0>=Count255)
			backGround = 0;
		else
			backGround = 255;*/
	//(默认第一个点为背景点)
	backGround = temp[0];
	
	//开始进行腐蚀
	int prePoint,nextPoint;
	for(i=1;i<GetHeight()-1;i++)
		for(j=1;j<GetWidth()-1;j++)
		{
			int flag = 0;
			prePoint = temp[i*GetLineByte()+j];//这里的Structure[1][1]是模板的中心值
			for(int k = 0;k<3;k++)
				for(int t = 0;t<3;t++)
				{
					if(k==1&&t==1)//跳过模板(Structure)的中心点
						continue;

					nextPoint = temp[(i-1 + k)*GetLineByte()+(j-1+t)]*Structure[k][t];
					if(0 != Structure[k][t])
						if(prePoint == nextPoint)
							continue;
						else
						{
							flag = 1;
							break;
						}
					else
						continue;

					prePoint = nextPoint;
				}
			if(1 == flag)
				for(int k = 0;k<3;k++)
					for(int t = 0;t<3;t++)
						if(0 != Structure[k][t])
							pData[(i-1 + k)*GetLineByte()+(j-1+t)] = backGround;
		}
	delete temp;
}

/*
功能：
	图像膨胀操作
*/
void MyDib::ImageDilation(int Structure[3][3])
{
	//************************保存上一步数据*********************
		SavePreImage();
	//************************保存上一步数据*********************
	//指向原图像数据的指针
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();//获取行字节数
	//开辟临时缓冲区
	BYTE* temp = new BYTE[GetHeight()*LineBytes];
	//将原像素数据复制到临时缓冲区
	memcpy(temp,pData,GetHeight()*LineBytes);

	int backGround;
	int i,j;
	//检查是否为二值图像
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if((temp[i*GetLineByte()+j] != 0)&&(temp[i*GetLineByte()+j] != 255))
				{
					AfxMessageBox("当前图像不是二值图像");
					return;
				}
			}

	//寻找背景点
		/* //(默认颜色多的为背景点)
		int Count255 = 0,Count0 = 0,
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if(temp[i*GetLineByte()+j] ==0)
					Count0++;
				else
					Count255++;
			}
		if(Count0>=Count255)
			backGround = 0;
		else
			backGround = 255;*/

	//(默认第一个点为背景点)
	backGround = temp[0];

	//开始进行腐蚀
	int prePoint,nextPoint;
	for(i=1;i<GetHeight()-1;i++)
		for(j=1;j<GetWidth()-1;j++)
		{
			int flag = 0;
			prePoint = temp[i*GetLineByte()+j];//这里的Structure[1][1]是模板的中心值
			for(int k = 0;k<3;k++)
				for(int t = 0;t<3;t++)
				{
					if(k==1&&t==1)//跳过模板(Structure)的中心点
						continue;

					nextPoint = temp[(i-1 + k)*GetLineByte()+(j-1+t)]*Structure[k][t];
					if(0 != Structure[k][t])
						if(prePoint == nextPoint)
							continue;
						else
						{
							flag = 1;
							break;
						}
					else
						continue;

					prePoint = nextPoint;
				}
			if(1 == flag)
				for(int k = 0;k<3;k++)
					for(int t = 0;t<3;t++)
						if(0 != Structure[k][t])
							pData[(i-1 + k)*GetLineByte()+(j-1+t)] = 255 - backGround;
		}
	delete temp;
}