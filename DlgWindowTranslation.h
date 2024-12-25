#if !defined(AFX_DLGWINDOWTRANSLATION_H__8D1E5E94_0D13_483E_A3C3_6D29E3EA0E03__INCLUDED_)
#define AFX_DLGWINDOWTRANSLATION_H__8D1E5E94_0D13_483E_A3C3_6D29E3EA0E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWindowTranslation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWindowTranslation dialog

class CDlgWindowTranslation : public CDialog
{
// Construction
public:
	CDlgWindowTranslation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWindowTranslation)
	enum { IDD = IDD_DIALOG5 };
	UINT	m_High;
	UINT	m_Low;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWindowTranslation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWindowTranslation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWINDOWTRANSLATION_H__8D1E5E94_0D13_483E_A3C3_6D29E3EA0E03__INCLUDED_)
