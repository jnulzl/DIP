#if !defined(AFX_DLGTEMPLATESIZE_H__815E0A23_AB1F_4071_BF49_1065FF4C048B__INCLUDED_)
#define AFX_DLGTEMPLATESIZE_H__815E0A23_AB1F_4071_BF49_1065FF4C048B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemplateSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTemplateSize dialog

class CDlgTemplateSize : public CDialog
{
// Construction
public:
	CDlgTemplateSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTemplateSize)
	enum { IDD = IDD_DIALOG10 };
	int	m_template_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemplateSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemplateSize)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPLATESIZE_H__815E0A23_AB1F_4071_BF49_1065FF4C048B__INCLUDED_)
