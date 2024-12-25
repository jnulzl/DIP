#if !defined(AFX_DLGHIST_H__FE8E9DCB_5E86_4906_AE95_A4CED37A41F0__INCLUDED_)
#define AFX_DLGHIST_H__FE8E9DCB_5E86_4906_AE95_A4CED37A41F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHist dialog

class CDlgHist : public CDialog
{
// Construction
public:
	double m_fIntensity[256];
	CDlgHist(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHist)
	enum { IDD = IDD_HIST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHist)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHIST_H__FE8E9DCB_5E86_4906_AE95_A4CED37A41F0__INCLUDED_)
