#include "StdAfx.h"
#include "MyDib.h"
#include <math.h>
#include "fitsio.h"
/*
���ܣ�
	��ȡͼ����ʾ���
�����
	ͼ����ʾ���
*/

LONG MyDib::GetShowWidth()
{	//ָ��ԭͼ�����ݵ�ָ��	
	return showWidth;
}

/*
���ܣ�
	��ȡͼ����ʾ���
�����
	ͼ����ʾ���
*/

LONG MyDib::GetShowHeight()
{	//ָ��ԭͼ�����ݵ�ָ��	
	return showHeight;
}


void MyDib::SetShowWidth(LONG showWidth)
{	//ָ��ԭͼ�����ݵ�ָ��	
	this->showWidth = showWidth;
}

/*
���ܣ�
	��ȡͼ����ʾ���
�����
	ͼ����ʾ���
*/

void MyDib::SetShowHeight(LONG showHeight)
{	//ָ��ԭͼ�����ݵ�ָ��
	this->showHeight = showHeight;
}


/*
���ܣ�
	����ԭʼͼ������
*/
void MyDib::SaveOriginImage()
{
	LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
	originImageData = new BYTE[GetHeight()*GetLineByte()];
	//�ж�ԭʼͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	originImageIsRgb = flag;
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)//���ԭͼ���ǲ�ɫ��
			{
				for(int k=0;k<3;k++)
					originImageData[i*GetLineByte()+3*j + k] = p_Data[i*GetLineByte()+3*j + k];
			}
			else//�������ԭͼ���ǻ�ɫ��
				originImageData[i*GetLineByte()+j] = p_Data[i*GetLineByte()+j];
		}
	/*FILE *fp;
	fp=fopen("H:\\data.txt","w");//���ļ��Ա�д������
	 //��a�����е�����д��fpָ���c:\a.txt�ļ�
	for (i = 0; i < 2; i++) 
		for(int j = 0;j<GetWidth();j++)
			fprintf(fp,"%6d\n",originImageData[i*GetLineByte()+j]);
	fclose(fp); //д����ϣ��ر��ļ�*/
}

/*
���ܣ�
	��ʾԭͼ
*/
void MyDib::ShowOriginImage()
{
	//**************����������ʾ��ȡ��߶�Ϊԭʼͼ��Ŀ�ȡ��߶�**************
	SetShowWidth(GetWidth());
	SetShowHeight(GetHeight());
	//**************����������ʾ��ȡ��߶�Ϊԭʼͼ��Ŀ�ȡ��߶�**************

	//�жϵ�ǰͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	//���ԭͼ�͵�ǰͼ���ǲ�ɫ�Ļ��߶��ǻ�ɫ��
	if(originImageIsRgb&&!flag)//���ԭͼ�ǲ�ɫ�Ķ���ǰͼ�ǻ�ɫ��
	{
		if(GradeToRgb())//�����ɫת��ɫ�ɹ�
		{
			LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
			memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
		}
		else//�������ת��ʧ��
		{
			AfxMessageBox("����ʧ�ܣ�");
			return;
		}
	}
	else if(!originImageIsRgb&&flag)//�������ԭͼ�ǻ�ɫ�Ķ���ǰͼ�ǲ�ɫ��
	{
		if(RgbToGrade())//�����ɫת��ɫ�ɹ�
		{
			//AfxMessageBox("��ɫת��ɫ�ɹ�");//�������Ե����
			LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
			memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
		}
		else//�������ת��ʧ��
		{
			AfxMessageBox("����ʧ�ܣ�");
			return;
		}
	}
	else
	{
		LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
		memcpy(p_Data,originImageData,GetHeight()*GetLineByte());
	}
	//************************����ԭͼ����һ��Ҳ�ָ�Ϊԭͼ����*********************
		SavePreImage();//�þ��ѡ
	//************************����ԭͼ����һ��Ҳ�ָ�Ϊԭͼ����*********************
}

/*
���ܣ�
	������һ��ͼ������
*/
void MyDib::SavePreImage()
{
	LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
	preImageData = new BYTE[GetHeight()*GetLineByte()];
	//�жϵ�ǰͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	preImageIsRgb = flag;
	for(int i=0;i<GetHeight();i++)
		for(int j=0;j<GetWidth();j++)
		{
			if(flag)//���ԭͼ���ǲ�ɫ��
			{
				for(int k=0;k<3;k++)
					preImageData[i*GetLineByte()+3*j + k] = p_Data[i*GetLineByte()+3*j + k];
			}
			else//�������ԭͼ���ǻ�ɫ��
				preImageData[i*GetLineByte()+j] = p_Data[i*GetLineByte()+j];
		}
	//������һ��ͼ�����ʾ��Ⱥ͸߶�
	preShowWidth = GetShowWidth();
	preShowHeight = GetShowHeight();
}

/*
���ܣ�
	��ʾ��һ����ͼ��
*/
void MyDib::ShowPreImage()
{
	//**************����ͼ����ʾ��ȡ��߶�Ϊ��һ��ͼ��Ŀ�ȡ��߶�**************
	SetShowWidth(preShowWidth);
	SetShowHeight(preShowHeight);
	//**************����ͼ����ʾ��ȡ��߶�Ϊ��һ��ͼ��Ŀ�ȡ��߶�**************
	//�жϵ�ǰͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	//�����һ����ͼ��͵�ǰͼ���ǲ�ɫ�Ļ��߶��ǻ�ɫ��
	if(preImageIsRgb&&!flag)//�����һ����ͼ���ǲ�ɫ�Ķ���ǰͼ�ǻ�ɫ��
	{
		if(GradeToRgb())//�����ɫת��ɫ�ɹ�
		{
			LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
			memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
		}
		else//�������ת��ʧ��
		{
			AfxMessageBox("����ʧ�ܣ�");
			return;
		}
	}
	else if(!preImageIsRgb&&flag)//�������ԭͼ�ǻ�ɫ�Ķ���ǰͼ�ǲ�ɫ��
	{
		if(RgbToGrade())//�����ɫת��ɫ�ɹ�
		{
			//AfxMessageBox("��ɫת��ɫ�ɹ�");//�������Ե����
			LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
			memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
		}
		else//�������ת��ʧ��
		{
			AfxMessageBox("����ʧ�ܣ�");
			return;
		}
	}
	else
	{
		LPBYTE p_Data = GetData();//��ȡ��ǰͼ������ָ��
		memcpy(p_Data,preImageData,GetHeight()*GetLineByte());
	}

}

/*
����:
	ȫ����ʾ
*/
/*void MyDib::ShowFullScreen()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	isFullScreen = true;
}*/

/*
���ܣ�
	ͼ����ֵ������
���룺
	threshold����ֵ
*/
/*
CDib MyDib::ImageThreshold(CDib m_Dib,int threshold)
{	//ָ��ԭͼ�����ݵ�ָ��	
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
���ܣ�
	ͼ����ֵ������
���룺
	threshold����ֵ
*/
void MyDib::ImageThreshold(int threshold)
{	
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭͼ�����ݵ�ָ��	
	LPBYTE pData = GetData();
	//�жϵ�ǰͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
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
				//����R
				if(pData[i*GetLineByte()+3*j]>threshold)
					pData[i*GetLineByte()+3*j]=255;
				else
					pData[i*GetLineByte()+3*j]=0;
				//����G
				if(pData[i*GetLineByte()+3*j + 1]>threshold)
					pData[i*GetLineByte()+3*j + 1]=255;
				else
					pData[i*GetLineByte()+3*j + 1]=0;
				//����B
				if(pData[i*GetLineByte()+3*j + 2]>threshold)
					pData[i*GetLineByte()+3*j + 2]=255;
				else
					pData[i*GetLineByte()+3*j + 2]=0;
			}
		}
}
/*
���ܣ�
	�Ҷ�ͼ��ת
���룺
	������
*/

void MyDib::ImageContrary()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭͼ�����ݵ�ָ��
	LPBYTE pData = GetData();
	BYTE R,G,B;
	UINT LineBytes = GetLineByte();
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == this->GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
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
���ܣ�
	ͼ�����Ի�
���룺
	a��б��
	b:�ؾ�
*/

void MyDib::ImageLinear(float a,int b)
{	
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭͼ�����ݵ�ָ��
	LPBYTE pData = GetData();
	BYTE R,G,B;
	UINT LineBytes = GetLineByte();
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
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
���ܣ�
	��ɫͼ��ת
���룺
	������
*/


/*
���ܣ�
	ͼ����ģ����о��
���룺
	m_pdata:ָ��ԭ���ص�ָ��
	*Template:���ģ��
	tempH:ģ��߶�
	tempW:ģ����
	fCoef:ģ��ϵ��
*/

void MyDib::Connv2(LPBYTE m_pdata,float *Template,int tempH,int tempW,double fCoef)
{
	int i,j,k,t;//ѭ������
	//������ʱ���ش洢��
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//(һά��̬����)
	//��ԭ�������ݸ�����ʱ���ش洢��
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	//ģ����������
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//��ʼ������ؼ�����
	for(j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			if(!flag)//���ͼ���ǻ�ɫ
			{
				double fResult = 0;//�������ؼ��������
				for(k=0;k<tempH;k++)
					for(t=0;t<tempW;t++)
						fResult = fResult+m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*Template[k*tempW+t];
							
					
					fResult*=fCoef;
					fResult = (float)fabs(fResult);
					if(fResult>255)
						temp[j*GetLineByte()+i]=255;
					else
						temp[j*GetLineByte()+i]=(int)(fResult+0.5);//��������
			}
			else//�������ͼ���ǲ�ɫ
			{
				double fResultR = 0;//�������ؼ��������
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
				//��R����
				if(fResultR>255)
					temp[j*GetLineByte()+3*i]=255;
				else
					temp[j*GetLineByte()+3*i]=(int)(fResultR+0.5);//��������
				//��G����
				if(fResultG>255)
					temp[j*GetLineByte()+3*i + 1]=255;
				else
					temp[j*GetLineByte()+3*i + 1]=(int)(fResultG+0.5);//��������
				//��B����
				if(fResultB>255)
					temp[j*GetLineByte()+3*i + 2]=255;
				else
					temp[j*GetLineByte()+3*i + 2]=(int)(fResultB+0.5);//��������
			}
		}
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//ɾ��һά��̬����
}
/*
���ܣ�
	����ֵ
���룺
	a[]:����
	n�����鳤��
	type������ֵ���ͣ�1Ϊ��Сֵ��2Ϊ��ֵ��3Ϊ���ֵ
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
���ܣ�
	Sobel��Ե���
���룺
	������
*/

void MyDib::SobelEdge()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = this->GetData();
	//���������µĻ�������������ԭͼ���ֵ
	BYTE* temP1 = new BYTE[GetLineByte()*GetHeight()];
	BYTE* temP2 = new BYTE[GetLineByte()*GetHeight()];
	memcpy(temP1,pData,GetLineByte()*GetHeight());
	memcpy(temP2,pData,GetLineByte()*GetHeight());
	//ģ��1
	float temp1[9];
	temp1[0]=-1;temp1[1]=-2;temp1[2]=-1;
	temp1[3]=0;temp1[4]=0;temp1[5]=0;
	temp1[6]=1;temp1[7]=2;temp1[8]=1;
	//ģ��2
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
	//�����������ݸ���ԭ����
	memcpy(pData,temP1,GetLineByte()*GetHeight());
	delete temP1;//ɾ��һά��̬����temP1
	delete temP2;//ɾ��һά��̬����temP2
}

/*
���ܣ�
	Robert��Ե���
���룺
	������
*/

void MyDib::RobertEdge()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = this->GetData();
	BYTE* temp = new BYTE[GetHeight()*GetLineByte()];//��ʱͼ�񻺳���(��̬����)
	memset(temp,255,GetHeight()*GetLineByte());//�趨��ʱͼ������س�ֵ��Ϊ255
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
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
				//����R
				pixel[0] = pData[i*GetLineByte()+3*j];
				pixel[1] = pData[i*GetLineByte()+3*(j+1)];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1)];

				temp[i*GetLineByte()+3*j] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
				//����G
				pixel[0] = pData[i*GetLineByte()+3*j +1];
				pixel[1] = pData[i*GetLineByte()+3*(j+1) +1];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j +1];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1) +1];

				temp[i*GetLineByte()+3*j + 1] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
				//����B
				pixel[0] = pData[i*GetLineByte()+3*j +2];
				pixel[1] = pData[i*GetLineByte()+3*(j+1) +2];
				pixel[2] = pData[(i+1)*GetLineByte()+3*j +2];
				pixel[3] = pData[(i+1)*GetLineByte()+3*(j+1) +2];

				temp[i*GetLineByte()+3*j + 2] = (int)sqrt((pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
											(pixel[1]-pixel[2])*(pixel[1]-pixel[2]));
			}
		}
	//����������������(temp)���Ƹ�ԭ��������
	memcpy(pData,temp,GetHeight()*GetLineByte());
	delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	PreWitt��Ե���
���룺
	������
*/

void MyDib::PreWittEdge()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	//ģ��1
	float temp1[9];
	temp1[0]=-1;temp1[1]=-1;temp1[2]=-1;
	temp1[3]=0;temp1[4]=0;temp1[5]=0;
	temp1[6]=1;temp1[7]=1;temp1[8]=1;
	//ģ��2
	float temp2[9];
	temp2[0]=1;temp2[1]=0;temp2[2]=-1;
	temp2[3]=1;temp2[4]=0;temp2[5]=-1;
	temp2[6]=1;temp2[7]=0;temp2[8]=-1;
	Connv2(pData,temp1,3,3,1);
	Connv2(pData,temp2,3,3,1);
}

/*
���ܣ�
	��˹������˹��Ե���
���룺
	������
*/

void MyDib::Guasslaplacian()
{	
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	//ģ��
	float temp[25];
	temp[0]=-2;temp[1]=-4;temp[2]=-4;temp[3]=-4;temp[4]=-2;
	temp[5]=-4;temp[6]=0;temp[7]=8;temp[8]=0;temp[9]=-4;
	temp[10]=-4;temp[11]=8;temp[12]=24;temp[13]=8;temp[14]=-4;
	temp[15]=-4;temp[16]=0;temp[17]=8;temp[18]=0;temp[19]=-4;
	temp[20]=-2;temp[21]=-4;temp[22]=-4;temp[23]=-4;temp[24]=-2;
	Connv2(pData,temp,5,5,0.25);
}

/*
���ܣ�
	Krisch��Ե���
*/
void MyDib::KrischEdge()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	BYTE* temP1 = new BYTE[GetHeight()*GetLineByte()];
	memcpy(temP1,pData,GetHeight()*GetLineByte());
	BYTE* temP2 = new BYTE[GetHeight()*GetLineByte()];
	memcpy(temP2,pData,GetHeight()*GetLineByte());
	int i,j;
	//ģ��1
	float temp1[9];
	temp1[0]=5;temp1[1]=5;temp1[2]=5;
	temp1[3]=-3;temp1[4]=0;temp1[5]=-3;
	temp1[6]=-3;temp1[7]=-3;temp1[8]=-3;
	Connv2(temP1,temp1,3,3,0.5);
	//ģ��2
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
	//ģ��3
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
	//ģ��4
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
	//ģ��5
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
	//ģ��6
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
	//ģ��7
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
	//ģ��8
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
	
	//��temP1�е����ݸ���ԭͼ������
	memcpy(pData,temP1,GetHeight()*GetLineByte());
	delete temP1;
	delete temP2;
}

/*
���ܣ�
	ͼ��ƽ��
���룺
	horOff��ˮƽƫ����
	verOff����ֱƫ����
*/

void MyDib::ImageTranslation(int horOff,int verOff)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
		
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
	}
	else
	{
		AfxMessageBox("ƽ����Υ�������������룡");
		return;
	}
}

/*
���ܣ�
	ͼ����ת
���룺
	alpha����ת�Ƕ�
*/

void MyDib::ImageRotate(float alpha)
{

}
/*
���ܣ�
	ˮƽͼ����
*/
void MyDib::ImageMirror()
{
 	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************   
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	��ֱͼ����
	��flagSavePreData=1��ʾ������һ����ͼ������
*/
void MyDib::ImageMirror1(int flagSavePreData)
{
 	//************************������һ������*********************
	if(1 == flagSavePreData)
		SavePreImage();
	//************************������һ������*********************   
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(!IsGrade())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	ͼ������

*/
void MyDib::ImageZoom(float ZoomX,float ZoomY)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	LONG Width = (LONG)(GetShowWidth()*ZoomX);
	LONG Height = (LONG)(GetShowHeight()*ZoomX);

//****************************���п��޵Ĵ���**************************
	if((GetHeight()<GetWidth())&&Height<5)//���ԭʼͼ��ĸ�С�ڿ�Ļ�������С��5ʱ
	{
		Height = 5;
		Width = (LONG)(5*GetWidth()/GetHeight());
	}
	else if((GetWidth()<GetHeight())&&Width<5)//�������ԭʼͼ��Ŀ�С�ڸߵĻ�������С��5ʱ
	{
		Width = 5;
		Height = (LONG)(5*GetHeight()/GetWidth());
	}
	else if(Height<5&&Width<5)//����(���ԭʼͼ��Ŀ���ڸߵĻ�)���ߺͿ�С��5ʱ
	{
		Height = 5;
		Width  = 5;
	}
//****************************���п��޵Ĵ���**************************

	SetShowWidth(Width);
	SetShowHeight(Height);
}
/*
���ܣ�
	ͼ��ת��
*/
void MyDib::ImageTranspose()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	if(GetHeight() !=  GetWidth())
	{
		AfxMessageBox("��ʱ���ܴ����߲��ȵ�ͼ��");
			return ;
	}
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(!IsGrade())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

void MyDib::ImageWindowTranslation(int low,int high)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	ͼ������任
*/
void MyDib::ImageLog(float coeff)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	LPBYTE temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	ͼ���ݴα任
*/
void MyDib::ImagePower(float coeff,float gamma)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���(һά��̬����)
	memset(temp,255,GetHeight()*LineBytes);//�趨��ʱͼ������س�ֵ��Ϊ255
	//BYTE Gray;
	
	//��ɫͼ����ı������
	BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}
/*
���ܣ�
	����ƽ��
*/
void MyDib::ImageAreaAverage(int n)
{	
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ģ������Ƿ�Ϊ����
	if(n<3||1 != n%2)
	{
		AfxMessageBox("������������ƽ��ģ��ĳߴ����Ϊ����3��������");
		return ;
	}
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	//ģ��
	//float temp[10000];//��ͨ����
	float* temp = new float[n*n];//һά��̬����
	for(int i=0;i<n*n;i++)
		temp[i]=1;
	Connv2(pData,temp,n,n,1.0/(n*n));
	delete temp;//ɾ��һά��̬����
}
/*
���ܣ�
	��Ȩƽ��
*/
void MyDib::ImageWeightAverage()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	
	//ģ��
	float temp[9];
	temp[0]=1;temp[1]=2;temp[2]=1;
	temp[3]=2;temp[4]=4;temp[5]=2;
	temp[6]=1;temp[7]=2;temp[8]=1;
	
	Connv2(pData,temp,3,3,1/16.0);
}
/*
���ܣ�
	��ֵ�˲�
���룺
	tempH��ģ��߶�
	tempW��ģ����
	type:����ֵ�˲���˵��type=2
*/
void MyDib::ImageMedianFilter(int tempH,int tempW,int type)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ģ������Ƿ�Ϊ����
	if(tempH<3||1 != tempH%2||tempW<3||1 != tempW%2)
	{
		AfxMessageBox("��������ģ��ĸ�������Ϊ����3������");
		return ;
	}
	//�����˲�ģ��,���Ʋ���ͳ����������������ɵļ�����״
	//int myTemplate[100][100];//��ͨ��ά����
//*******************��̬��ά����(���巽ʽ1)**********************
	/*int*  *myTemplate = new int*[tempH];//��̬��ά����ÿ��
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
		*/
//*******************��̬��ά����(���巽ʽ1)**********************
	////////////////////////////////////////////////////////////////////////
//*******************��̬��ά����(���巽ʽ2)**********************
	LPINT*  myTemplate = new LPINT[tempH];//��̬��ά����ÿ��
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
		//˵������ʵ����ֻ�Ƕ��壺typedef int far     *LPINT;
//*******************��̬��ά����(���巽ʽ2)**********************
	for(int k=0;k<tempH;k++)
		for(int t=0;t<tempW;t++)	
			myTemplate[k][t] = 1;//ģ�����������ض�����ͳ������
	//�洢�˲�ģ���ڵ�����ֵ
	//int Template[10000];//��ͨ����
	int* Template = new int[tempH*tempW];//һά��̬����
	//int** Template = new int[tempH][tempW];��ά��̬���鲻����������

	//������ʱͼ�񻺳���
	LPBYTE m_pdata = GetData();
	//������ʱ���ش洢��
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//һά��̬����
	//��ԭ�������ݸ�����ʱ���ش洢��
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//ģ����������
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//��ʼ������ؼ�����
	for(int j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(int i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			for(int k=0;k<tempH;k++)
			{	
				for(int t=0;t<tempW;t++)	
					//�Ѵ���ΪtempHxtempW�ڵ����ض�����ʱ�洢ģ����ȥ
					Template[k*tempW+t] = m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*myTemplate[k][t];
			}	
			//��������ֵ������ȡÿ��ģ�������ش�С����ֵ������ֵ����ʱ�洢��temp��
			temp[j*GetLineByte()+i]=GetMedian(Template,tempH*tempW,type);
		}
	//������������������temp���Ƹ�ԭ��������m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//ɾ��һά��̬����
	delete Template;//ɾ��һά��̬����
	//ɾ����̬��ά����
	for(int index=0;index<tempH;index++)
		delete[] myTemplate[index];
	delete[] myTemplate;
}

/*
���ܣ�
	ʮ������ֵ�˲�,��һ�����ֵ�˲����ֻ���˲�ģ�岻ͬ����
���룺
	tempH��ģ��߶�
	tempW��ģ����
*/
void MyDib::ImagePlusMedianFilter(int tempH,int tempW)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ģ������Ƿ�Ϊ����
	if(tempH<3||1 != tempH%2||tempW<3||1 != tempW%2)
	{
		AfxMessageBox("��������ģ��ĸ�������Ϊ����3������");
		return ;
	}
	//�����˲�ģ��,���Ʋ���ͳ����������������ɵļ�����״
	//int myTemplate[100][100];//��ͨ����
	//*************��ά��̬����******************
	int** myTemplate = new int*[tempH];
	for(int i=0;i<tempH;i++)
		myTemplate[i] = new int[tempW];
	//*************��ά��̬����******************
	int k,t;
	//1���Ƚ��˲�ģ��ȫ����ֵΪ0
	for(k=0;k<tempH;k++)
		for(t=0;t<tempW;t++)	
			myTemplate[k][t] = 0;
	//2���ٰ�ģ���ˮƽ���ĸ�ֵΪ1
	k = tempH/2;
	for(t=0;t<tempW;t++)	
			myTemplate[k][t] = 1;
	//3������ģ�����ֱ���ĸ�ֵΪ1
	t = tempW/2;
	for(k=0;k<tempH;k++)	
			myTemplate[k][t] = 1;
	//�洢�˲�ģ���ڵ�����ֵ
	 int* Template = new int[tempH+tempW-1];//һά��̬����
	//int Template[10000];//��ͨ����

	//������ʱͼ�񻺳���
	LPBYTE m_pdata = GetData();
	//������ʱ���ش洢��
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//һά��̬����
	//��ԭ�������ݸ�����ʱ���ش洢��
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//ģ����������
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//��ʼ������ؼ�����
	for(int j = tempMY;j<GetHeight()-tempH+tempMY+1;j++)
		for(int i = tempMX;i<GetWidth()-tempW+tempMX+1;i++)
		{
			int TemplateIndex = 0;
			for(int k=0;k<tempH;k++)
			{	
				for(int t=0;t<tempW;t++)	
				{	//�Ѵ���ΪtempHxtempW��ˮƽ�ʹ�ֱ�������ڵ����ر�������
					int tempPoint = m_pdata[(j-tempMY + k)*GetLineByte()+(i-tempMX+t)]*myTemplate[k][t];
					if(0 != tempPoint)
						Template[TemplateIndex++] = tempPoint;
				}
			}	
			//��������ֵ������ȡÿ��ģ�������ش�С����ֵ������ֵ����ʱ�洢��temp��
			temp[j*GetLineByte()+i]=GetMedian(Template,tempH+tempW-1,2);//�����2��ʾȡ��ֵ
		}
	//������������������temp���Ƹ�ԭ��������m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//ɾ��һά��̬����
	delete Template;//ɾ��һά��̬����
	//ɾ����̬��ά����
	for(int index=0;index<tempH;index++)
		delete[] myTemplate[index];
	delete[] myTemplate;//һά��̬����
}

/*
���ܣ�
	����������
*/
void MyDib::AddRandNoise(float radio)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���
	memcpy(temp,pData,GetHeight()*LineBytes);//��ԭ�������ݸ��Ƶ���ʱͼ�񻺳���
	int noisePoint;//�����
	//��ɫͼ����ı������
	//BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
	memcpy(pData,temp,GetHeight()*LineBytes);
	delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	��ӽ�������
*/
void MyDib::AddSaltPepperNoise(float radio)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	BYTE* temp = new BYTE[GetHeight()*LineBytes];//��ʱͼ�񻺳���
	memcpy(temp,pData,GetHeight()*LineBytes);//��ԭ�������ݸ��Ƶ���ʱͼ�񻺳���
	//��ɫͼ����ı������
	//BYTE R,G,B,Gray;
	//�ж�ͼ���ǲ�ɫ�Ļ��ǻ�ɫ��
	bool flag;
	if(24 == GetBitCount())
		flag = true;//ͼ���ǲ�ɫ��
	else
		flag = false;//ͼ���ǻ�ɫ��
	
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
		//����������������(temp)���Ƹ�ԭ��������
		memcpy(pData,temp,GetHeight()*LineBytes);
		delete temp;//ɾ��һά��̬����
}

/*
���ܣ�
	��ȡͼ������
*/
void MyDib::ImageProfileDetect()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//�����˲�ģ��,���Ʋ���ͳ����������������ɵļ�����״

	//������ʱͼ�񻺳���
	LPBYTE m_pdata = GetData();
	//������ʱ���ش洢��
	BYTE* temp = new BYTE[GetLineByte()*GetHeight()];//������̬����ı�׼��ʽ
	//��ԭ�������ݸ�����ʱ���ش洢��
	memcpy(temp,m_pdata,GetLineByte()*GetHeight());
	//ģ����������
	//��ʼ������ؽ��д���
	for(int j = 1;j<GetHeight()-1;j++)
		for(int i = 1;i<GetWidth()-1;i++)
		{	int flag = 1;
			BYTE tempPoint = m_pdata[j*GetLineByte()+i];//Ϊ��ǰ����������
			for(int k=0;k<3;k++)
			{	
				for(int t=0;t<3;t++)	
				{
					//�Ѵ���ΪtempHxtempW�ڵ����ض�����ʱ�洢ģ����ȥ
					if((m_pdata[(j-1 + k)*GetLineByte()+(i-1+t)]-tempPoint) < 10)//���
						flag*=1;
					else
						flag*=0;
				}
			}
			if(1 == flag)//�����������(i,j)������8��������ز�<10�Ļ�����(i,j)��ֵΪ255
				temp[j*GetLineByte()+i]=255;
		}
	//������������������temp���Ƹ�ԭ��������m_pdata
	memcpy(m_pdata,temp,GetLineByte()*GetHeight());
	delete temp;//ɾ��һά��̬����	
}

/*
���ܣ�
	��ɫͼ����ɫ����
*/
void MyDib::RgbAddColor(int m_R,int m_G,int m_B)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	//��ɫͼ����ı������
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
���ܣ�	
	���ȸı�
*/
void MyDib::ChangeBright(int m_radio)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();
	
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<(int)GetLineByte();j++)
			{	
				BYTE temp;
				temp = int(*pData*m_radio/100);//������ǰ�������
				if(temp<0)//����������ֵС��0
					*pData = 0;
				if(temp>255)//����������ֵ����255
					*pData = 255;

				*pData = temp;
				pData++;//ָ�������ƶ�
			}
}

/*
���ܣ�
	������ЧӦ
*/
void MyDib::Mosaic(int tempW,int tempH)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭ��������
	LPBYTE m_pdata = GetData();
	int i,j,k,t;//ѭ������
	//ģ����������
	int tempMX = (tempW-1)/2;
	int tempMY = (tempH-1)/2;
	//��ʼ������ؼ�����
	for(j = tempMY;j<GetHeight()-tempH+tempMY+1;j+=tempH)
		for(i = tempMX;i<GetWidth()-tempW+tempMX+1;i+=tempW)
		{
			float fResultR = 0;
			float fResultG = 0;
			float fResultB = 0;
			//����ģ�������ص�ƽ��ֵ
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
			//�Ѽ���õ���ƽ��ֵ����ģ���µ�ÿ������
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
���ܣ�
	��ȡ��ɫͼ�����
*/
void MyDib::GetRGBComponent(int tempRGB)
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************

	//��ȡԭͼ������ָ��
	LPBYTE pData = GetData();
	//�Ҷ�ͼ����ʱ������
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + tempRGB];//��������ǰ�BGR˳ȥ�洢��

	if(!RgbToGrade())//�����ͼת�Ҷ�ͼ��ʧ�ܣ���ֱ�ӷ���
	{
		AfxMessageBox("��ȡR����ʧ�ܣ�");
		return;
	}
	//�ٴλ�ȡԭͼ������ָ��
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//ɾ����ʱ������
}
/*
���ܣ�
	��ͼR������ȡ
*/

/*
void MyDib::RColor()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************

	//��ȡԭͼ������ָ��
	LPBYTE pData = GetData();
	//�Ҷ�ͼ����ʱ������
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + 2];//���������BGR

	if(!RgbToGrade())//�����ͼת�Ҷ�ͼ��ʧ�ܣ���ֱ�ӷ���
	{
		AfxMessageBox("��ȡR����ʧ�ܣ�");
		return;
	}
	//�ٴλ�ȡԭͼ������ָ��
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//ɾ����ʱ������
}
*/
/*
���ܣ�
	��ͼR������ȡ
*/

/*
void MyDib::GColor()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//��ȡԭͼ������
	LPBYTE pData = GetData();
	//�Ҷ�ͼ����ʱ������
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j + 1];
	if(!RgbToGrade())//�����ͼת�Ҷ�ͼ��ʧ�ܣ���ֱ�ӷ���
	{
		AfxMessageBox("��ȡG����ʧ�ܣ�");
		return;
	}
	//�ٴλ�ȡԭͼ������ָ��
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//ɾ����ʱ������
}
*/
/*
���ܣ�
	��ͼR������ȡ
*/
/*
void MyDib::BColor()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************

	//��ȡԭͼ������
	LPBYTE pData = GetData();
	//�Ҷ�ͼ����ʱ������
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = pData[i*GetLineByte()+3*j];
	if(!RgbToGrade())//�����ͼת�Ҷ�ͼ��ʧ�ܣ���ֱ�ӷ���
	{
		AfxMessageBox("��ȡB����ʧ�ܣ�");
		return;
	}
	//�ٴλ�ȡԭͼ������ָ��
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//ɾ����ʱ������
}
*/
/*
���ܣ�
	����ɨ��
*/
void MyDib::ToDownScan(CDC *pDC,CPoint origin,CSize size)
{
	// λͼ��Ч���޷����ƣ����ش���
    if(!IsValid())
    {
        return;
    }

    // �ɵĵ�ɫ����
	HPALETTE hOldPalette = NULL;

	// ���λͼָ��Ϊ�գ��򷵻�FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// ���λͼ�е�ɫ�壬��ѡ���豸������
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// ����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);


	// ��λͼ��pDC��ָ����豸�Ͻ�����ʾ
	for(int i=0;i<GetHeight();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x,origin.y+i, size.cx, 1,
			0, GetHeight()-i, GetWidth(), 1, GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// �ָ��ɵĵ�ɫ��
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
���ܣ�
	����ɨ��
*/
void MyDib::ToUpScan(CDC *pDC,CPoint origin,CSize size)
{
	// λͼ��Ч���޷����ƣ����ش���
    if(!IsValid())
    {
        return;
    }

    // �ɵĵ�ɫ����
	HPALETTE hOldPalette = NULL;

	// ���λͼָ��Ϊ�գ��򷵻�FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// ���λͼ�е�ɫ�壬��ѡ���豸������
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// ����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);


	// ��λͼ��pDC��ָ����豸�Ͻ�����ʾ
	for(int i=0;i<GetHeight();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x,origin.y+GetHeight()-i, size.cx, 1,
			0, i, GetWidth(), 1, GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// �ָ��ɵĵ�ɫ��
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
���ܣ�
	����ɨ��
*/
void MyDib::ToRightScan(CDC *pDC,CPoint origin,CSize size)
{
	// λͼ��Ч���޷����ƣ����ش���
    if(!IsValid())
    {
        return;
    }

    // �ɵĵ�ɫ����
	HPALETTE hOldPalette = NULL;

	// ���λͼָ��Ϊ�գ��򷵻�FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// ���λͼ�е�ɫ�壬��ѡ���豸������
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// ����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);


	// ��λͼ��pDC��ָ����豸�Ͻ�����ʾ
	for(int i=0;i<GetWidth();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x+i,origin.y, 1, size.cy,
			i, 0, 1,GetHeight(), GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// �ָ��ɵĵ�ɫ��
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
���ܣ�
	����ɨ��
*/
void MyDib::ToLeftScan(CDC *pDC,CPoint origin,CSize size)
{
	// λͼ��Ч���޷����ƣ����ش���
    if(!IsValid())
    {
        return;
    }

    // �ɵĵ�ɫ����
	HPALETTE hOldPalette = NULL;

	// ���λͼָ��Ϊ�գ��򷵻�FALSE
	if(GetBmpPointer() == NULL) 
    {
        return;
    }

	// ���λͼ�е�ɫ�壬��ѡ���豸������
	if(GetBmpPalette() != NULL) 
    {
		hOldPalette = SelectPalette(pDC->GetSafeHdc(), GetBmpPalette(), TRUE);
	}

	// ����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);


	// ��λͼ��pDC��ָ����豸�Ͻ�����ʾ
	for(int i=0;i<GetWidth();i++)
	{
		StretchDIBits(pDC->GetSafeHdc(), origin.x+GetWidth()-i,origin.y, 1, size.cy,
			GetWidth()-i, 0, 1,GetHeight(), GetData(), GetBmpInfo(), DIB_RGB_COLORS, SRCCOPY);
		Sleep(2);
	}
	
	// �ָ��ɵĵ�ɫ��
	if(hOldPalette != NULL)
    {
        SelectPalette(pDC->GetSafeHdc(), hOldPalette, TRUE);
    }
}

/*
���ܣ�
	ʵ��ͼ��ֱ��ͼ���⻯
*/
void MyDib::HistogramEqualization()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************

	//*******************************��ʽ����*********************************
		/*	FILE *fp;
		fp=fopen("H:\\data2.txt","w");//���ļ��Ա�д������
		 //��a�����е�����д��fpָ���c:\a.txt�ļ�
		for (i = 0; i < 256; i++) 	
			fprintf(fp,"%.2f\n",tempImageHistogram[i]);
		fclose(fp); //д����ϣ��ر��ļ�
		*/
	//********************************��ʽ����********************************
	//ָ��ԭͼ�����ݵ�ָ��
	LPBYTE pData = GetData();
	if(IsGrade())//���ͼ���ǻ�ɫ�Ļ�	
		Equalization(pData,1,0);	
	else//�������ͼ���ǲ�ɫ�Ļ�
	{
		//*******************************����R����************************
		Equalization(pData,3,0);	
		//*******************************����G����************************
		Equalization(pData,3,1);	
		//*******************************����B����************************
		Equalization(pData,3,2);			
	}
}

/*
���ܣ�
	��ͼ���ֱ��ͼ
*/
void MyDib::Histogram(LPBYTE p_data,double* ImageHistogram)
{
	int i,j;
	//Ϊֱ��ͼ����ֵ
	for(i=0;i<256;i++)
			ImageHistogram[i]=0;
	//��Ҷ�ͼ����ÿ���Ҷȼ�������
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
				int gray = (int)p_data[i*GetWidth()+j];
				ImageHistogram[gray]++;
		}
	//��Ҷ�ͼ����ÿ���Ҷȼ����ֵĸ���(Ƶ��)
	for(i=0;i<256;i++)
		ImageHistogram[i] /= (GetHeight()*GetWidth()*1.0);
}
/*
���ܣ�
	ͼ��ֱ��ͼ���⻯
*/
void MyDib::Equalization(LPBYTE originData,int coef,int num)
{
	//ͼ��Ҷ�ֱ��ͼ
	//double ImageHistogram[256];
	//�м���ʱ����
	double tempImageHistogram[256];
	//��ʱͼ�����ݴ洢��
	LPBYTE tempData = new BYTE[GetHeight()*GetWidth()];
	int i,j;

	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			tempData[i*GetWidth()+j] = (BYTE)originData[i*GetLineByte()+coef*j+num];
	//���ɫͼ��ֱ��ͼ
	Histogram(tempData,ImageHistogram);
	//����ֱ��ͼ�ۻ���Ͳ���ʼ��
	double tempHistogram[256];
	tempHistogram[0] = ImageHistogram[0];
	for(i=0;i<256;i++)
	{	
		//1�����ۼ��ܶȺ���
		if(0 != i)
			tempHistogram[i] = tempHistogram[i-1] + ImageHistogram[i];
		//2������⻯�������
		tempImageHistogram[i] = (255.0*tempHistogram[i]+0.5);
	}
		//3�������⻯������ظ���ԭͼ������
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
		{
				int gray = (int)tempData[i*GetWidth()+j];
				originData[i*GetLineByte()+coef*j + num] = (BYTE)tempImageHistogram[gray];
		}
	delete tempData;//ɾ����ʱ����
}	

/*
���ܣ�
	//RGB�ռ�ת��ΪHSI�ռ�
*/
void MyDib::RgbToHSI()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************

	//��ȡԭͼ������ָ��
	LPBYTE pData = GetData();
	//�Ҷ�ͼ����ʱ������
	BYTE* temp = new BYTE[GetWidth()*GetHeight()];
		for(int i=0;i<GetHeight();i++)
			for(int j=0;j<GetWidth();j++)
				temp[i*GetWidth()+j] = (BYTE)((pData[i*GetLineByte()+3*j]
						+pData[i*GetLineByte()+3*j+1]+pData[i*GetLineByte()+3*j+2])/3);

	if(!RgbToGrade())//�����ͼת�Ҷ�ͼ��ʧ�ܣ���ֱ�ӷ���
	{
		AfxMessageBox("ת��ʧ�ܣ�");
		return;
	}
	//�ٴλ�ȡԭͼ������ָ��
	pData = GetData();
	memcpy(pData,temp,GetWidth()*GetHeight());
	delete temp;//ɾ����ʱ������
}

/*
���ܣ�
	�����ǰͼ������
*/
bool MyDib::OutPutImageData(CString txtFilePath)
{
	if(!IsValid())
		return false;
	//��ȡԭͼ������ָ��
	LPBYTE pData = GetData();
	FILE *fp;
	int i,j;
		
	if(IsGrade())//�����ǰͼ���ǻҶ�ͼ��
	{
		fp=fopen(txtFilePath,"w");//���ļ��Ա�д������
		fprintf(fp,"��=%-3d����=%-3d\n",GetWidth(),GetHeight());
		for (i = 0; i <GetHeight();i++) 
		{
			for (j = 0; j <GetWidth();j++) 
				fprintf(fp,"%-4d",pData[i*GetLineByte()+j]);
			fprintf(fp,"\n");
		}
		fclose(fp); //д����ϣ��ر��ļ�
		return true;
	}
	else//���������ǰͼ���ǲ�ɫͼ��
	{
		fp=fopen(txtFilePath,"w");//���ļ��Ա�д������
		fprintf(fp,"��=%-3d����=%-3d\n",GetWidth(),GetHeight());
		for (i = 0; i < GetHeight(); i++) 
		{
			for (j = 0; j < GetWidth(); j++) 
				fprintf(fp,"(%-3d,%-3d,%-3d)",pData[i*GetLineByte()+3*j+2],pData[i*GetLineByte()+3*j+1],pData[i*GetLineByte()+3*j]);
			fprintf(fp,"\n");
		}
		fclose(fp); //д����ϣ��ر��ļ�
		return true;
	}
	return false;
}

/*
���ܣ�
	��ͼ����п��ٸ���Ҷ�任
*/
void MyDib::ImageFourier()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	
	//һ
	//FirstQuickFourier();//���ٸ���Ҷ�任��δ���任���ԭ���Ƶ����ģ�
	//��
	QuickFourier();//���ٸ���Ҷ�任�����任���ԭ���Ƶ����ģ�
	//��
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


	/*//��ȡԭͼ������ָ��
	LPBYTE pData = GetData();
	int i,j;
	//�Ҷ�ͼ����ʱ������
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
���ܣ�
	��ͼ�����ˮƽ��ʴ
*/
/*
void MyDib::HorCorrosion()
{

}
*/

/*
���ܣ�
	��ͼ��ֱ��ͼ
*/

double* MyDib::GetImageHist(int coef,int num)
{
	//��ȡ��ǰͼ������(Ĭ�ϵ�ǰͼ��Ϊ�Ҷ�ͼ��)
	LPBYTE pData = GetData();
	//��ʱͼ�����ݴ洢��
	LPBYTE tempData = new BYTE[GetHeight()*GetWidth()];
	int i,j;
	for(i=0;i<GetHeight();i++)
		for(j=0;j<GetWidth();j++)
			tempData[i*GetWidth()+j] = (BYTE)pData[i*GetLineByte()+coef*j+num];
	//���ɫͼ��ֱ��ͼ
	Histogram(tempData,ImageHistogram);
	return ImageHistogram;
}

/*
���ܣ�
	������˹��Ե���
*/
void MyDib::Laplacian()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//������ʱͼ�񻺳���
	LPBYTE pData = GetData();
	//ģ��1
	/*float temp1[9];
	temp1[0]=0;temp1[1]=-1;temp1[2]=0;
	temp1[3]=-1;temp1[4]=4;temp1[5]=-1;
	temp1[6]=0;temp1[7]=-1;temp1[8]=0;
	Connv2(pData,temp1,3,3,1);*/
	//ģ��2
	float temp2[9];
	temp2[0]=-1;temp2[1]=-1;temp2[2]=-1;
	temp2[3]=-1;temp2[4]=8;temp2[5]=-1;
	temp2[6]=-1;temp2[7]=-1;temp2[8]=-1;
	Connv2(pData,temp2,3,3,1);
	
}

/*
���ܣ�
	��󷽲���ֵ�ָ�
*/
void MyDib::OtusThreshold()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	// ѭ������
	int i, j;

    // ԭͼ������ָ��
    LPBYTE p_data = GetData();
    
    // ͼ��ÿ��������ռ���ֽ���
    int nLineByte = GetLineByte();

    // ͼ��Ŀ��
    int nWidth = GetWidth();

    // ͼ��ĸ߶�
    int nHeight = GetHeight();

	// �Ҷ�ֱ��ͼ���飬����ʼ��
	int nGrayHistogram[256];
	memset(nGrayHistogram, 0, sizeof(nGrayHistogram));
     
	// ͳ�Ƹ����Ҷȼ���Ӧ�����ظ���������ŵ��Ҷ�ֱ��ͼ������
    int nPixel;
	for (j = 0; j < nHeight; j ++)
	    for (i = 0; i < nWidth; i ++)
	    {
		    // ��ȡ��ǰ���ص�ĻҶ�ֵ
            nPixel = p_data[nLineByte * j + i];	

		    // �ԻҶ�ֵͳ�Ƽ���
		    nGrayHistogram[nPixel] ++;		
	    }

    // c0���c1��ľ�ֵ
    float u0, u1;

    // c0���c1��ĸ���
    float w0, w1;

    // c0�����������
    int nCount0;

    // ��ֵ�������ֵ����Ӧ�������ʱ����ֵ��
    int nT, nBestT;

    // �������󷽲�
    float fVaria, fMaxVaria = 0;

    // ͳ��ֱ��ͼ�����ص������������ŵ�nSum��
    int nSum=0;
    for(i = 0; i < 256; i ++)
        nSum += nGrayHistogram[i];


    // ����ֵnT��0������255
    for(nT = 0; nT < 256; nT ++)
    {
        // ����ֵΪnTʱ������c0��ľ�ֵ�͸���
        u0 = 0;
        nCount0 = 0;
        for(i = 0; i <= nT; i++)
        {
            u0 += i * nGrayHistogram[i];
            nCount0 += nGrayHistogram[i];
        }
        u0 /= nCount0;
        w0 = (float) nCount0 / nSum;

        // ����ֵΪnTʱ������c1��ľ�ֵ�͸���
        u1 = 0;
        for(i = nT+1; i < 256; i ++)
             u1 += i * nGrayHistogram[i];
        u1 /= (nSum - nCount0);
        w1 = 1 - w0;

        // ���������ķ���
        fVaria = w0 * w1 * (u0 - u1) * (u0 - u1);

        // ��¼��󷽲�������ֵ
        if(fVaria > fMaxVaria)
        {
            fMaxVaria = fVaria;
            nBestT = nT;
        }
    }

    // ���������ֵ��ԭͼ�����ָ��
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
���ܣ�
	����Ӧ��ֵ�ָ�
*/
void MyDib::AdaptiveThreshold()
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	// ѭ������
    int i,j;
    
    // ԭͼ��������ָ��
    LPBYTE p_data = GetData();
    

    // ͼ��ÿ��������ռ���ֽ���
    int nLineByte = GetLineByte();

    // ͼ��Ŀ��
    int nWidth = GetWidth();

    // ͼ��ĸ߶�
    int nHeight = GetHeight();

    // �ֲ���ֵ
    int nThreshold[2][2];

    // ��ͼ��ĻҶ�ƽ��ֵ
    int nAvgValue;

    // ������ͼ�����ɨ��,�������ͼ��ĻҶ�ƽ��ֵ
    nAvgValue = 0;
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = 0; i < nWidth / 2; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // ������ֵΪ��ͼ���ƽ��ֵ
    nThreshold[0][0] = nAvgValue;

    // ������ͼ�����ɨ�貢������ֵ�ָ�
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = 0; i < nWidth / 2; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // ������ͼ�����ɨ��,�������ͼ��ĻҶ�ƽ��ֵ
    nAvgValue = 0;
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // ������ֵΪ��ͼ���ƽ��ֵ
    nThreshold[0][1] = nAvgValue;

    // ������ͼ�����ɨ�貢������ֵ�ָ�
    for(j = nHeight / 2; j < nHeight; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // ������ͼ�����ɨ��,�������ͼ��ĻҶ�ƽ��ֵ
    nAvgValue = 0;
    for(j = 0; j < nHeight / 2; j ++)
        for(i = 0; i < nWidth / 2; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // ������ֵΪ��ͼ���ƽ��ֵ
    nThreshold[1][0] = nAvgValue;

    // ������ͼ�����ɨ�貢������ֵ�ָ�
    for(j = 0; j < nHeight / 2; j ++)
        for(i = 0; i < nWidth / 2; i ++)
        {
            if(p_data[j * nLineByte + i] < nThreshold[0][0])
                p_data[j * nLineByte + i] = 0;
            else
                p_data[j * nLineByte + i] = 255;
        }

    // ������ͼ�����ɨ��,�������ͼ��ĻҶ�ƽ��ֵ
    nAvgValue = 0;
    for(j = 0; j < nHeight / 2; j ++)
        for(i = nWidth / 2; i < nWidth; i ++)
            nAvgValue += p_data[j * nLineByte + i];
    nAvgValue /= ((nHeight / 2) * (nLineByte / 2));

    // ������ֵΪ��ͼ���ƽ��ֵ
    nThreshold[1][1] = nAvgValue;

    // ��������ͼ�����ɨ�貢������ֵ�ָ�
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
���ܣ�
	����Fits�ļ�
*/
BOOL MyDib::LoadFitsFile(LPCTSTR lpszPath)
{	
	// ����ռ�
    Empty(FALSE); 

	fitsfile *fptr; //ָ���ļ���ָ��
	char *filename  = (LPSTR)lpszPath;     /* �Ѿ����ڵ�fits�ļ� */
    int status = 0,nfound;
	long naxes[2];//�洢ͼ��ĳ��Ϳ�
	int naxis;//�洢ͼ��ά��
	int bitpix;//�洢ͼ������λ��
	//int maxdim;//�洢ͼ�񳤺Ϳ��е������
	long fpixel[2];//���½�����
	long lpixel[2];//���Ͻ�����
	long  inc[2];//
	int nulval;
	int anynul;
	int i,j;

	//1����ȡͼ�����ݣ�ֻ��(READONLY)
    if ( fits_open_data(&fptr, filename, READONLY, &status) )
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}


	//2����ȡͼ�������λ��
	if(fits_get_img_type(fptr, &bitpix, &status))
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}
	//3����ȡͼ���ά��
	if(fits_get_img_dim(fptr, &naxis, &status))
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}

	//4����ȡͼ��ĳ��Ϳ�
	if ( fits_read_keys_lng(fptr, "NAXIS", 1, 2, naxes, &nfound, &status) )
	{
		if (status)
		{
			fits_report_error(stderr, status); /* print error report */

		   exit( status );    /* terminate the program, returning error status */
		}
		return FALSE;
	}

	//5����ȡ��������
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

	//��������С����ֵ
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

	//ͼ��Ҷȱ任
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
	fp=fopen("H:\\data.txt","w");//���ļ��Ա�д������
	 //��a�����е�����д��fpָ���c:\a.txt�ļ�
	for (i = 0; i < naxes[1]; i++) 
		for(int j = 0;j<naxes[0];j++)
			fprintf(fp,"%6d",array[i*naxes[0]+j]);
		fprintf(fp,"\n");	
	fclose(fp); //д����ϣ��ر��ļ�
	*/
	CreateDIB("newImage",array,lpixel[0],lpixel[1],8,1);

	return TRUE;
}

/*
���ܣ�
	��ֵͼ��ʴ����(���ģ�������ֵ������ֵ��һ�����򽫵�ǰ����ֵȡ��)
*/
void MyDib::ImageErosion(int Structure[3][3])
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭͼ�����ݵ�ָ��
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();//��ȡ���ֽ���
	//������ʱ������
	BYTE* temp = new BYTE[GetHeight()*LineBytes];
	//��ԭ�������ݸ��Ƶ���ʱ������
	memcpy(temp,pData,GetHeight()*LineBytes);
	
	int backGround;
	int i,j;
	//����Ƿ�Ϊ��ֵͼ��
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if((temp[i*GetLineByte()+j] != 0)&&(temp[i*GetLineByte()+j] != 255))
				{
					AfxMessageBox("��ǰͼ���Ƕ�ֵͼ��");
					return;
				}
			}

	//Ѱ�ұ�����
		/* //(Ĭ����ɫ���Ϊ������)
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
	//(Ĭ�ϵ�һ����Ϊ������)
	backGround = temp[0];
	
	//��ʼ���и�ʴ
	int prePoint,nextPoint;
	for(i=1;i<GetHeight()-1;i++)
		for(j=1;j<GetWidth()-1;j++)
		{
			int flag = 0;
			prePoint = temp[i*GetLineByte()+j];//�����Structure[1][1]��ģ�������ֵ
			for(int k = 0;k<3;k++)
				for(int t = 0;t<3;t++)
				{
					if(k==1&&t==1)//����ģ��(Structure)�����ĵ�
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
���ܣ�
	ͼ�����Ͳ���
*/
void MyDib::ImageDilation(int Structure[3][3])
{
	//************************������һ������*********************
		SavePreImage();
	//************************������һ������*********************
	//ָ��ԭͼ�����ݵ�ָ��
	LPBYTE pData = GetData();
	UINT LineBytes = GetLineByte();//��ȡ���ֽ���
	//������ʱ������
	BYTE* temp = new BYTE[GetHeight()*LineBytes];
	//��ԭ�������ݸ��Ƶ���ʱ������
	memcpy(temp,pData,GetHeight()*LineBytes);

	int backGround;
	int i,j;
	//����Ƿ�Ϊ��ֵͼ��
		for(i=0;i<GetHeight();i++)
			for(j=0;j<GetWidth();j++)
			{	
				if((temp[i*GetLineByte()+j] != 0)&&(temp[i*GetLineByte()+j] != 255))
				{
					AfxMessageBox("��ǰͼ���Ƕ�ֵͼ��");
					return;
				}
			}

	//Ѱ�ұ�����
		/* //(Ĭ����ɫ���Ϊ������)
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

	//(Ĭ�ϵ�һ����Ϊ������)
	backGround = temp[0];

	//��ʼ���и�ʴ
	int prePoint,nextPoint;
	for(i=1;i<GetHeight()-1;i++)
		for(j=1;j<GetWidth()-1;j++)
		{
			int flag = 0;
			prePoint = temp[i*GetLineByte()+j];//�����Structure[1][1]��ģ�������ֵ
			for(int k = 0;k<3;k++)
				for(int t = 0;t<3;t++)
				{
					if(k==1&&t==1)//����ģ��(Structure)�����ĵ�
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