#if !defined(AFX_DLGLOG_H__B0C56E55_099D_4AB4_B780_EB553E31DA94__INCLUDED_)
#define AFX_DLGLOG_H__B0C56E55_099D_4AB4_B780_EB553E31DA94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLog dialog

class CDlgLog : public CDialog
{
// Construction
public:
	CDlgLog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLog)
	enum { IDD = IDD_DIALOG6 };
	float	m_logCoeff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOG_H__B0C56E55_099D_4AB4_B780_EB553E31DA94__INCLUDED_)
