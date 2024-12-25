#if !defined(AFX_DLGTRAN_H__53F7BEBC_7A6E_45E9_AE46_D331F3D80646__INCLUDED_)
#define AFX_DLGTRAN_H__53F7BEBC_7A6E_45E9_AE46_D331F3D80646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTran.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTran dialog

class CDlgTran : public CDialog
{
// Construction
public:
	CDlgTran(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTran)
	enum { IDD = IDD_DIALOG1 };
	int		m_horOff;
	int		m_verOff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTran)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTran)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAN_H__53F7BEBC_7A6E_45E9_AE46_D331F3D80646__INCLUDED_)
