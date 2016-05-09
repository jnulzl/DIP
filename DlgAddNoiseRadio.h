#if !defined(AFX_DLGADDNOISERADIO_H__961E927E_0979_4AC5_8FD8_24FA3C1D2F5C__INCLUDED_)
#define AFX_DLGADDNOISERADIO_H__961E927E_0979_4AC5_8FD8_24FA3C1D2F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddNoiseRadio.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddNoiseRadio dialog

class CDlgAddNoiseRadio : public CDialog
{
// Construction
public:
	CDlgAddNoiseRadio(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddNoiseRadio)
	enum { IDD = IDD_DIALOG9 };
	float	m_noise_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddNoiseRadio)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddNoiseRadio)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDNOISERADIO_H__961E927E_0979_4AC5_8FD8_24FA3C1D2F5C__INCLUDED_)
