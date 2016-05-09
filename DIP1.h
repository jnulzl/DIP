// DIP1.h : main header file for the DIP1 application
//

#if !defined(AFX_DIP1_H__998DE997_F539_4C3B_833E_B776C95515D7__INCLUDED_)
#define AFX_DIP1_H__998DE997_F539_4C3B_833E_B776C95515D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIP1App:
// See DIP1.cpp for the implementation of this class
//

class CDIP1App : public CWinApp
{
public:
	CDIP1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDIP1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP1_H__998DE997_F539_4C3B_833E_B776C95515D7__INCLUDED_)
