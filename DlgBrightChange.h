#if !defined(AFX_DLGBRIGHTCHANGE_H__0104C7BE_3BE5_4C30_A872_9D1BF1713A27__INCLUDED_)
#define AFX_DLGBRIGHTCHANGE_H__0104C7BE_3BE5_4C30_A872_9D1BF1713A27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBrightChange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBrightChange dialog

class CDlgBrightChange : public CDialog
{
// Construction
public:
	CDlgBrightChange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBrightChange)
	enum { IDD = IDD_DIALOG12 };
	CScrollBar	m_HorScrollBar;
	int		m_bright;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBrightChange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBrightChange)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBRIGHTCHANGE_H__0104C7BE_3BE5_4C30_A872_9D1BF1713A27__INCLUDED_)
