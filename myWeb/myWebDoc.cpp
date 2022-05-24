// myWebDoc.cpp : implementation of the CMyWebDoc class
//

#include "stdafx.h"
#include "myWeb.h"
#include "myWebDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWebDoc

IMPLEMENT_DYNCREATE(CMyWebDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyWebDoc, CDocument)
	//{{AFX_MSG_MAP(CMyWebDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWebDoc construction/destruction

CMyWebDoc::CMyWebDoc()
{
	// TODO: add one-time construction code here

}

CMyWebDoc::~CMyWebDoc()
{
}

BOOL CMyWebDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyWebDoc serialization

void CMyWebDoc::Serialize(CArchive& ar)
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
// CMyWebDoc diagnostics

#ifdef _DEBUG
void CMyWebDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyWebDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWebDoc commands
