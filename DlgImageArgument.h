#if !defined(AFX_DLGIMAGEARGUMENT_H__19433D3D_FABE_48A1_9EF8_4257DB01BDB9__INCLUDED_)
#define AFX_DLGIMAGEARGUMENT_H__19433D3D_FABE_48A1_9EF8_4257DB01BDB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImageArgument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgImageArgument dialog

class CDlgImageArgument : public CDialog
{
// Construction
public:
	CDlgImageArgument(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgImageArgument)
	enum { IDD = IDD_DIALOG14 };
	UINT	m_ImageHeight;
	UINT	m_ImageWidth;
	UINT	m_ImageNBIts;
	CString	m_filePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgImageArgument)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgImageArgument)
	afx_msg void OnButtonScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMAGEARGUMENT_H__19433D3D_FABE_48A1_9EF8_4257DB01BDB9__INCLUDED_)
