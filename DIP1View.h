// DIP1View.h : interface of the CDIP1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIP1VIEW_H__656B25F3_45E1_4D2B_87D0_B799532E88E6__INCLUDED_)
#define AFX_DIP1VIEW_H__656B25F3_45E1_4D2B_87D0_B799532E88E6__INCLUDED_

#include "cv.h"
#include "highgui.h"


#include "Dib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
	
#include "CvDIP.h"

class CDIP1View : public CScrollView
{
protected: // create from serialization only
	CDIP1View();
	DECLARE_DYNCREATE(CDIP1View)

// Attributes
public:
	CDIP1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	IplImage* m_curImg;
	IplImage* m_cvImg;
	//////////////////////////////////////////////////////////////////////////
	CCvDIP m_dib;
	int alert(int temp);
	//////////////////////////////////////////////////////////////////////////
	virtual ~CDIP1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIP1View)
	afx_msg void OnOpenImage();
	afx_msg void OnSaveImage();
	afx_msg void OnImageTranslation();
	afx_msg void OnImageThreshold();
	afx_msg void OnRgb2Gray();
	afx_msg void OnImageContrary();
	afx_msg void OnGaussLapEdge();
	afx_msg void OnPreWittEdge();
	afx_msg void OnRobertEdge();
	afx_msg void OnSobelEdge();
	afx_msg void OnImageLinear();
	afx_msg void OnImageMirrorhor();
	afx_msg void OnImageMirrorver();
	afx_msg void OnImageZoom();
	afx_msg void OnImageBig();
	afx_msg void OnImageSmall();
	afx_msg void OnImageTranspose();
	afx_msg void OnWindowTranslation();
	afx_msg void OnImageLog();
	afx_msg void OnPower();
	afx_msg void OnAreaAverage();
	afx_msg void OnWeightAverage();
	afx_msg void OnMedianFilter();
	afx_msg void OnMaxFilter();
	afx_msg void OnMinFilter();
	afx_msg void OnPlusMedianFilter();
	afx_msg void OnImageSaltpepper();
	afx_msg void OnProfileDetect();
	afx_msg void OnShowOriginImage();
	afx_msg void OnGray2Rgb();
	afx_msg void OnShowPreimage();
	afx_msg void OnKrischEdge();
	afx_msg void OnRgbAddColor();
	afx_msg void OnBrightChange();
	afx_msg void OnMosaic();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnImageRandNoise();
	afx_msg void OnRColor();
	afx_msg void OnBColor();
	afx_msg void OnGColor();
	afx_msg void OnToDownScan();
	afx_msg void OnToUpscan();
	afx_msg void OnTorightScan();
	afx_msg void OnToleftScan();
	afx_msg void OnImageHistogramEqualization();
	afx_msg void OnSaveData();
	afx_msg void OnImageFourier();
	afx_msg void OnRgb2Hsi();
	afx_msg void OnGrayHist();
	afx_msg void OnBHist();
	afx_msg void OnRHist();
	afx_msg void OnGHist();
	afx_msg void OnLaplacianEdge();
	afx_msg void OnOtsu();
	afx_msg void OnApaptiveThreshold();
	afx_msg void OnShuiPingErosion();
	afx_msg void OnChuiZhiErosion();
	afx_msg void OnShuiPingDilation();
	afx_msg void OnChuiZhiDilation();
	afx_msg void OnDongXiErosion();
	afx_msg void OnXiDongErosion();
	afx_msg void OnDongXiDilation();
	afx_msg void OnXiDongDilation();
	afx_msg void OnImageErosion();
	afx_msg void OnImageDilation();
	afx_msg void OnTestOpenCV();
	afx_msg void OnCvFaceDetection();
	afx_msg void OnCvErode();
	afx_msg void OnCvDilate();
	afx_msg void OnCvCornerDetectipn();
	afx_msg void OnCvSobelEdge();
	afx_msg void OnCvCannyEdge();
	afx_msg void OnCvSplit();
	afx_msg void OnCvLaplacian();
	afx_msg void OnCvPcFaceDetection();
	afx_msg void OnFaceDetectionYushiqi();
	afx_msg void OnDemo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DIP1View.cpp
inline CDIP1Doc* CDIP1View::GetDocument()
   { return (CDIP1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP1VIEW_H__656B25F3_45E1_4D2B_87D0_B799532E88E6__INCLUDED_)
