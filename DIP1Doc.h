// DIP1Doc.h : interface of the CDIP1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIP1DOC_H__CE16E03D_11E5_46DA_9CA5_24CE4B0F1EC0__INCLUDED_)
#define AFX_DIP1DOC_H__CE16E03D_11E5_46DA_9CA5_24CE4B0F1EC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDIP1Doc : public CDocument
{
protected: // create from serialization only
	CDIP1Doc();
	DECLARE_DYNCREATE(CDIP1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIP1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIP1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP1DOC_H__CE16E03D_11E5_46DA_9CA5_24CE4B0F1EC0__INCLUDED_)
