// myWebView.h : interface of the CMyWebView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYWEBVIEW_H__67113E8C_08E4_11DA_BB87_84BCC08BA219__INCLUDED_)
#define AFX_MYWEBVIEW_H__67113E8C_08E4_11DA_BB87_84BCC08BA219__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "myWebDoc.h"

class CMyWebView : public CHtmlView
{
protected: // create from serialization only
	CMyWebView();
	DECLARE_DYNCREATE(CMyWebView)

// Attributes
public:
	CMyWebDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWebView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyWebView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyWebView)
	afx_msg void OnFoward();
	afx_msg void OnBack();
	afx_msg void OnStop();
	afx_msg void OnUpdate();
	afx_msg void OnHomepage();
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in myWebView.cpp
inline CMyWebDoc* CMyWebView::GetDocument()
   { return (CMyWebDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWEBVIEW_H__67113E8C_08E4_11DA_BB87_84BCC08BA219__INCLUDED_)
