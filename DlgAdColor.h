#if !defined(AFX_DLGADCOLOR_H__8F514D0D_5943_4322_B074_6E5BD1284ABC__INCLUDED_)
#define AFX_DLGADCOLOR_H__8F514D0D_5943_4322_B074_6E5BD1284ABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAdColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAdColor dialog

class CDlgAdColor : public CDialog
{
// Construction
public:
	CDlgAdColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAdColor)
	enum { IDD = IDD_DIALOG11 };
	int		m_R;
	int		m_G;
	int		m_B;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAdColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAdColor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADCOLOR_H__8F514D0D_5943_4322_B074_6E5BD1284ABC__INCLUDED_)
