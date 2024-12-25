#if !defined(AFX_DLGMEDIANFILTER_H__743DE475_A699_4D08_A3EC_F14A6DB67F86__INCLUDED_)
#define AFX_DLGMEDIANFILTER_H__743DE475_A699_4D08_A3EC_F14A6DB67F86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMedianFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMedianFilter dialog

class CDlgMedianFilter : public CDialog
{
// Construction
public:
	CDlgMedianFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMedianFilter)
	enum { IDD = IDD_DIALOG8 };
	int		m_temp_height;
	int		m_temp_width;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMedianFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMedianFilter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEDIANFILTER_H__743DE475_A699_4D08_A3EC_F14A6DB67F86__INCLUDED_)
