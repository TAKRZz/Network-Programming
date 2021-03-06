// mySock.cpp : implementation file
//

#include "stdafx.h"
#include "smtp.h"
#include "mySock.h"
#include  "smtpDlg.h"    //自己添加的包含语句
#include  "Base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BUFF 20000
/////////////////////////////////////////////////////////////////////////////
// mySock

mySock::mySock()
{
	m_pDlg = NULL;
	state=FIRST;
	error="连接不上服务器\r\n";
}

mySock::~mySock()
{
	m_pDlg = NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(mySock, CAsyncSocket)
	//{{AFX_MSG_MAP(mySock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// mySock member functions

//当套接字收到FD_CONNECT消息时，执行此函数，表明连接已建立
void mySock::OnConnect(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CONNECT);
}

//当套接字收到服务器发来的数据时，执行此函数
void mySock::OnReceive(int nErrorCode) 
{
	if(nErrorCode==0) 
	{
		char buff[MAX_BUFF];             //接收缓冲区
		int rec=Receive(buff,MAX_BUFF);  //接收服务器发来的数据
		buff[rec]=NULL;                  //结尾置为NULL。
		lastMsg=buff;
		AnalyzeMsg();             //分析收到的数据，作不同的处理
	}  else  {
		error="接收期间发生了错误!\r\n";
		m_pDlg->Disp(S_CLOSE);   //显示信息
	}
}

//当关闭连接时，执行此函数
void mySock::OnClose(int nErrorCode) 
{
	if(nErrorCode==0)  m_pDlg->Disp(S_CLOSE);
}
//使套接字类的对话框指针变量指向主对话框
void mySock::SetParent(CSmtpDlg *pDlg)
{
	m_pDlg = pDlg;
}

//退出服务器
void mySock::Close()
{
	CString str;
	str.Format("quit%c%c",13,10);
	Send((LPCSTR)str,str.GetLength());
	m_pDlg->Disp(S_CLOSE);
	state=FIRST;
	CAsyncSocket::Close();
	error="与服务器的连接已经断开\r\n";
}

//分析服务器发来的数据，做出相应的处理
void mySock::AnalyzeMsg()
{
	CString s;
	strstream str;
	string check;
	str<<(LPCSTR)lastMsg;
	str>>check;

	//根据smtp会话所处的状态做出不同的处理	
	switch(state)
	{
	case FIRST: //如果已经连接成功，类初始化的时候state为FIRST
		m_pDlg->Disp(S_RECEIVE); //发送消息到窗体
		if(!(check=="220")) {}
		s.Format("EHLO %s%c%c",m_pDlg->m_Name,13,10);
		Send((LPCSTR)s,s.GetLength()); //发送EHLO命令
		state=EHLO;
		break;

	case EHLO:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("AUTH LOGIN%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //发送AUTH LOGIN命令
		state=AUTH;
		break;

	case AUTH:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="334")) {}
		coder.Encode(m_pDlg->m_User);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
//	AfxMessageBox(s);

//		s.Format("bXVfbA==%c%c",13,10);  ///mu_l
//		s.Format("bXVfbGxs%c%c",13,10);  //mu_lll
		Send((LPCSTR)s,s.GetLength()); //发送用户名
		state=USER; 
		break;

	case USER:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="334")) {}
		
		coder.Encode(m_pDlg->m_Pass);
		s.Format(_T("%s%c%c"), coder.EncodedMessage(),13,10);
//	AfxMessageBox(s);
//		s.Format("NDkxMDE1%c%c",13,10); //491015
		Send((LPCSTR)s,s.GetLength()); //发送口令
		state=PASS;
		break;

	case PASS:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="235")) {}
		s.Format("MAIL FROM:<%s>%c%c",m_pDlg->m_Addr,13,10); 
//		s.Format("MAIL FROM:<mu_lm@sina.com>%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //发送MAIL FROM命令
		state=MAIL;
		break;
	case MAIL:
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
//		s.Format("RCPT TO: <mu_lm@sina.com>%c%c",13,10); 
		s.Format("RCPT TO: <%s>%c%c",m_pDlg->m_Receiver,13,10); 
		Send((LPCSTR)s,s.GetLength()); //发送RECP命令
		state=RCPT;
		break;
	case RCPT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("DATA%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //发送DATA命令
		state=DATA;
		break;
	case DATA: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="354")) {}
//		s.Format("From: %s%c%c",m_pDlg->m_Addr,13,10); 
//		Send((LPCSTR)s,s.GetLength()); //发送信件内容
	
//	s.Format("To: %s%c%c",m_pDlg->m_Receiver,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Date: Tue,04 Dec 2005 16:18:08 +800%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("Subject: %s%c%c",m_pDlg->m_Title,13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%c%c",13,10); 
//	Send((LPCSTR)s,s.GetLength());
	
//	s.Format("%s%c%c",m_pDlg->m_Letter,13,10); 
//	Send((LPCSTR)s,s.GetLength());

//		s.Format("%c%c.%c%c",13,10,13,10); 
//		Send((LPCSTR)s,s.GetLength());

		m_pDlg->GetHeader();
		state=QUIT;
		break;
	case QUIT: 
		m_pDlg->Disp(S_RECEIVE);
		if(!(check=="250")) {}
		s.Format("QUIT%c%c",13,10); 
		Send((LPCSTR)s,s.GetLength()); //发送QUIT命令
		state=DATA;
		break;
	default:
		m_pDlg->Disp(S_RECEIVE);
		break;
	}
}

