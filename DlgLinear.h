#if !defined(AFX_DLGLINEAR_H__4E66EC25_EB04_4280_948C_9FA6EF2932B7__INCLUDED_)
#define AFX_DLGLINEAR_H__4E66EC25_EB04_4280_948C_9FA6EF2932B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinear.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLinear dialog

class CDlgLinear : public CDialog
{
// Construction
public:
	CDlgLinear(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinear)
	enum { IDD = IDD_DIALOG3 };
	float	m_a;
	int		m_b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinear)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinear)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINEAR_H__4E66EC25_EB04_4280_948C_9FA6EF2932B7__INCLUDED_)
