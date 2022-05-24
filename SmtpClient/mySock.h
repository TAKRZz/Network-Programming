#if !defined(AFX_MYSOCK_H__87167880_0CBD_11DA_BB87_A61D2D224B00__INCLUDED_)
#define AFX_MYSOCK_H__87167880_0CBD_11DA_BB87_A61D2D224B00__INCLUDED_

#include  "Base64.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mySock.h : header file
//

#include <vector>
#include <strstream>
#include <string>

using namespace std;

class  CSmtpDlg;

/////////////////////////////////////////////////////////////////////////////
// mySock command target
//表示显示信息的标志
#define S_CLOSE 1
#define S_CONNECT 2
#define S_RECEIVE 3
#define S_GETNUMMSGS 4 
#define S_GETSIZEMSGS 5 
#define S_ENDRETR 6 

//表示smtp会话状态的枚举类型
typedef enum {FIRST=0,EHLO,AUTH,USER,PASS,MAIL,RCPT,DATA,QUIT} STATE;

class mySock : public CAsyncSocket
{
// Attributes
public:
	CString lastMsg;
	CString error;
	
// Operations
public:
	void Close();            //退出服务器
	void SetParent(CSmtpDlg *  pDlg);
	mySock();
	virtual ~mySock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(mySock)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(mySock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	void AnalyzeMsg();   //分析从服务器发来的数据，做出响应的响应
	CSmtpDlg* m_pDlg;    //指向主对话框的指针
	STATE state;         //smtp会话的状态
	CBase64 coder;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCK_H__87167880_0CBD_11DA_BB87_A61D2D224B00__INCLUDED_)
