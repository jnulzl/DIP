#if !defined(AFX_DLGPOWER_H__ADC13409_1810_4B3C_9EF4_06A05D0F0F50__INCLUDED_)
#define AFX_DLGPOWER_H__ADC13409_1810_4B3C_9EF4_06A05D0F0F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPower dialog

class CDlgPower : public CDialog
{
// Construction
public:
	CDlgPower(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPower)
	enum { IDD = IDD_DIALOG7 };
	float	m_C;
	float	m_Gamma;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPower)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOWER_H__ADC13409_1810_4B3C_9EF4_06A05D0F0F50__INCLUDED_)
