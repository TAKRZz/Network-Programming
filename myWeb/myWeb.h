// myWeb.h : main header file for the MYWEB application
//

#if !defined(AFX_MYWEB_H__67113E84_08E4_11DA_BB87_84BCC08BA219__INCLUDED_)
#define AFX_MYWEB_H__67113E84_08E4_11DA_BB87_84BCC08BA219__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyWebApp:
// See myWeb.cpp for the implementation of this class
//

class CMyWebApp : public CWinApp
{
public:
	CMyWebApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWebApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyWebApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWEB_H__67113E84_08E4_11DA_BB87_84BCC08BA219__INCLUDED_)
