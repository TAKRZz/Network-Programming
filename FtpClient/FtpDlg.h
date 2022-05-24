// FtpDlg.h : header file
//

#if !defined(AFX_FTPDLG_H__C75FCF26_098B_11DA_BC43_000795DF7F99__INCLUDED_)
#define AFX_FTPDLG_H__C75FCF26_098B_11DA_BC43_000795DF7F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg dialog

class CFtpDlg : public CDialog
{
// Construction
public:
	BOOL Upload(CString strSName,CString strDName);
	BOOL Download(CString strSName,CString strDName);
	CFtpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFtpDlg)
	enum { IDD = IDD_FTP_DIALOG };
	CButton	m_btnUpload;
	CButton	m_btnDownload;
	CButton	m_btnQuery;
	CListBox	m_listFile;
	CEdit	m_editPwd;
	CEdit	m_editName;
	CEdit	m_editFtp;
	CStatic	m_staPwd;
	CStatic	m_staName;
	CStatic	m_staFtp;
	CString	m_strFtp;
	CString	m_strName;
	CString	m_strPwd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFtpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFtpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnQuery();
	afx_msg void OnDownload();
	afx_msg void OnUpload();
	afx_msg void OnSelchangeListFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPDLG_H__C75FCF26_098B_11DA_BC43_000795DF7F99__INCLUDED_)
