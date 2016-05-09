// DIP1Doc.cpp : implementation of the CDIP1Doc class
//

#include "stdafx.h"
#include "DIP1.h"

#include "DIP1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIP1Doc

IMPLEMENT_DYNCREATE(CDIP1Doc, CDocument)

BEGIN_MESSAGE_MAP(CDIP1Doc, CDocument)
	//{{AFX_MSG_MAP(CDIP1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIP1Doc construction/destruction

CDIP1Doc::CDIP1Doc()
{
	// TODO: add one-time construction code here
}

CDIP1Doc::~CDIP1Doc()
{
}

BOOL CDIP1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDIP1Doc serialization

void CDIP1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIP1Doc diagnostics

#ifdef _DEBUG
void CDIP1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIP1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIP1Doc commands


