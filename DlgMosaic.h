#if !defined(AFX_DLGMOSAIC_H__E0089C1F_0000_4F3D_845E_369C0E6EB601__INCLUDED_)
#define AFX_DLGMOSAIC_H__E0089C1F_0000_4F3D_845E_369C0E6EB601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMosaic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMosaic dialog

class CDlgMosaic : public CDialog
{
// Construction
public:
	CDlgMosaic(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMosaic)
	enum { IDD = IDD_DIALOG13 };
	int		m_widht;
	int		m_height;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMosaic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMosaic)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOSAIC_H__E0089C1F_0000_4F3D_845E_369C0E6EB601__INCLUDED_)
