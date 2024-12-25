#if !defined(AFX_DLGTHRE_H__303F8D93_228D_4B55_9678_73D4698AA493__INCLUDED_)
#define AFX_DLGTHRE_H__303F8D93_228D_4B55_9678_73D4698AA493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThre dialog

class CDlgThre : public CDialog
{
// Construction
public:
	CDlgThre(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThre)
	enum { IDD = IDD_DIALOG2 };
	int		m_threshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThre)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHRE_H__303F8D93_228D_4B55_9678_73D4698AA493__INCLUDED_)
