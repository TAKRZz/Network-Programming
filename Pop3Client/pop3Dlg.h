// pop3Dlg.h : header file
//

#if !defined(AFX_POP3DLG_H__49C6B988_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_)
#define AFX_POP3DLG_H__49C6B988_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_

#include "mySock.h"	// 添加套接字类的包含文件

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPop3Dlg dialog

class CPop3Dlg : public CDialog
{
// Construction
public:
	void Disp(LONG flag);  //在不同的会话阶段显示不同的信息
	mySock pop3Socket;     //套接字类对象实例
	CPop3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPop3Dlg)
	enum { IDD = IDD_POP3_DIALOG };
	CRichEditCtrl	m_ctrInfo;
	CComboBox	m_ctrList;
	CString	m_strPass;
	CString	m_strServer;
	CString	m_strUser;
	BOOL	m_bolDel;
	CString	m_Info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPop3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPop3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConn();
	afx_msg void OnBtnDisc();
	afx_msg void OnBtnView();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POP3DLG_H__49C6B988_0C23_11DA_BB87_AF2B44E1925E__INCLUDED_)
