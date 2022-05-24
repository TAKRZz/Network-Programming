// myWebView.cpp : implementation of the CMyWebView class
//

#include "stdafx.h"
#include "myWeb.h"
#include "MainFrm.h"
#include "myWebDoc.h"
#include "myWebView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWebView

IMPLEMENT_DYNCREATE(CMyWebView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyWebView, CHtmlView)
	//{{AFX_MSG_MAP(CMyWebView)
	ON_COMMAND(ID_FOWARD, OnFoward)
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_UPDATE, OnUpdate)
	ON_COMMAND(ID_HOMEPAGE, OnHomepage)
	ON_COMMAND(ID_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWebView construction/destruction

CMyWebView::CMyWebView()
{
	// TODO: add construction code here

}

CMyWebView::~CMyWebView()
{
}

BOOL CMyWebView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyWebView drawing

void CMyWebView::OnDraw(CDC* pDC)
{
	CMyWebDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMyWebView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMyWebView printing


/////////////////////////////////////////////////////////////////////////////
// CMyWebView diagnostics

#ifdef _DEBUG
void CMyWebView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyWebView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMyWebDoc* CMyWebView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWebDoc)));
	return (CMyWebDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWebView message handlers

//前进到下一个网页
void CMyWebView::OnFoward() 
{
	GoForward();
}
//退到前一个网页
void CMyWebView::OnBack() 
{
	GoBack();	
}
//停止网页的下载
void CMyWebView::OnStop() 
{
	Stop();
}
//刷新当前的网页
void CMyWebView::OnUpdate() 
{
	Refresh();
}
//回到主页
void CMyWebView::OnHomepage() 
{
	GoHome();
}
//进行搜索
void CMyWebView::OnSearch() 
{
	GoSearch();
}

void CMyWebView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CMainFrame*)GetParentFrame())->SetPage(lpszURL);
	CHtmlView::OnDocumentComplete(lpszURL);
}
