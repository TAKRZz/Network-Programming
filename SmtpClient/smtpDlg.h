// smtpDlg.h : header file
//

#if !defined(AFX_SMTPDLG_H__5435A046_0CB7_11DA_BB87_A61D2D224B00__INCLUDED_)
#define AFX_SMTPDLG_H__5435A046_0CB7_11DA_BB87_A61D2D224B00__INCLUDED_

#include "mySock.h"
#include  "Base64.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSmtpDlg dialog

class CSmtpDlg : public CDialog
{
// Construction
public:
	void Disp(LONG flag);
	void GetHeader();

	mySock smtpSocket;    //套接字类对象
	CSmtpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSmtpDlg)
	enum { IDD = IDD_SMTP_DIALOG };
	CString	m_Addr;
	CString	m_Attach;
	CString	m_BCC;
	CString	m_CC;
	CString	m_Letter;
	CString	m_Name;
	CString	m_Pass;
	UINT	m_Port;
	CString	m_Receiver;
	CString	m_Server;
	CString	m_Title;
	CString	m_User;
	CString	m_Info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmtpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSmtpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnView();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBase64 coder;
	BOOL GetBody(LPSTR& pszBody, int& nBodySize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMTPDLG_H__5435A046_0CB7_11DA_BB87_A61D2D224B00__INCLUDED_)
