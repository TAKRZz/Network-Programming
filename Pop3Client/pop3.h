// pop3.h : main header file for the POP3 application
//

#if !defined(AFX_POP3_H__49C6B986_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_)
#define AFX_POP3_H__49C6B986_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPop3App:
// See pop3.cpp for the implementation of this class
//

class CPop3App : public CWinApp
{
public:
	CPop3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPop3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPop3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POP3_H__49C6B986_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_)
