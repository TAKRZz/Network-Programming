// smtpDlg.cpp : implementation file
//

//#include "rpcdce.h"
#include "stdafx.h"
#include "smtp.h"
#include "smtpDlg.h"
#include "mySock.h"
#include "Base64.h"

#define SMTP_MAXLINE  76

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmtpDlg dialog

CSmtpDlg::CSmtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmtpDlg)
	m_Addr = _T("");
	m_Attach = _T("");
	m_BCC = _T("");
	m_CC = _T("");
	m_Letter = _T("");
	m_Name = _T("");
	m_Pass = _T("");
	m_Port = 0;
	m_Receiver = _T("");
	m_Server = _T("");
	m_Title = _T("");
	m_User = _T("");
	m_Info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmtpDlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Addr);
	DDX_Text(pDX, IDC_EDIT_ATTACH, m_Attach);
	DDX_Text(pDX, IDC_EDIT_BCC, m_BCC);
	DDX_Text(pDX, IDC_EDIT_CC, m_CC);
	DDX_Text(pDX, IDC_EDIT_LETTER, m_Letter);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_PASS, m_Pass);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	DDX_Text(pDX, IDC_EDIT_RECEIVER, m_Receiver);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_Server);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT_USER, m_User);
	DDX_Text(pDX, IDC_RICH_LIST, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSmtpDlg, CDialog)
	//{{AFX_MSG_MAP(CSmtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmtpDlg message handlers

BOOL CSmtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Name = _T("wang");               //发信人
	m_Addr = _T("mu_l@163.com");     //发信地址
	m_Server = _T("smtp.163.com");   //smtp服务器
	m_Port = 25;                     //smtp的保留端口
	m_User = _T("mu_l");             //用户名
	m_Pass = _T("491015");           //口令

	m_Receiver = _T("mu_lm@sina.com"); //收信人地址
	m_Title = _T("");            //主题
	m_CC = _T("");                   //抄送
	m_BCC = _T("");                  //暗送
	m_Letter = _T("");               //信件内容
	m_Attach = _T("");               //附件
	UpdateData(FALSE);               //更新用户界面

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmtpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//当用户点击“发送”按钮时，执行此函数
void CSmtpDlg::OnOK() 
{
	//设定smtp类的变量，使之指向本对话框，以便传递信息
	smtpSocket.SetParent(this); 
	UpdateData(TRUE);           //取来用户在对话框中输入的数据
	smtpSocket.Create();        //创建套接字对象的底层套接字
	smtpSocket.Connect((LPCSTR)m_Server,m_Port); //连接pop3服务器
	//列表框清空
	//while (m_listInfo.GetCount()!=0)
     //          m_listInfo.DeleteString(0);

	//UpdateData(FALSE);          //更新用户界面
}

//当用户点击“浏览”按钮，寻找附件时，执行此函数
void CSmtpDlg::OnBtnView() 
{
	UpdateData(TRUE); 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() == IDOK) 
	{
		CString sNewFile = dlg.GetPathName();
		if (m_Attach.GetLength())
		{
			m_Attach += _T(", ");
			m_Attach += sNewFile;
		}
		else
			m_Attach = sNewFile;
		UpdateData(FALSE);
	}
	LPSTR pszBody = NULL;
	int nBodySize = 0;
	if (!GetBody(pszBody, nBodySize))
	{
		TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
	}
	CString s;
	s = pszBody;
	m_Info += s;
	UpdateData(FALSE);

//	CString s;
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	coder.Encode(m_User);
//	s.Format(_T("%s\r\n"), coder.EncodedMessage());
//	m_listInfo.AddString(m_User);	
//	m_listInfo.AddString(s);
//	AfxMessageBox(s);

//	coder.Encode(m_Pass);
//	s.Format(_T("%s\r\n"), coder.EncodedMessage());
//	m_listInfo.AddString(m_Pass);	
//	m_listInfo.AddString(s);
//	AfxMessageBox(s);
}

//根据不同的情况，向用户显示不同的信息
void CSmtpDlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //已连接到服务器，显示信息
		s = "已经连接到"+m_Server+"服务器\r\n";
		m_Info += s;
		//m_listInfo.AddString(s);
		break;
	case S_RECEIVE: //收到服务器发来的数据,显示该数据
		m_Info += smtpSocket.lastMsg;
		//m_listInfo.AddString(smtpSocket.lastMsg);
		break; 
	case S_CLOSE: //显示关闭连接的信息
		m_Info += smtpSocket.error;
//		m_listInfo.AddString(smtpSocket.error);
		s = "连接已经关闭\r\n";
		m_Info += s;
		//m_listInfo.AddString(s); 
		break;
	}
	UpdateData(FALSE);   //更新用户界面
}

void CSmtpDlg::GetHeader()
{
	UpdateData(TRUE);
	CString sepa;
	CString sReply;
	sReply = _T("");

	//创建 "Date:" 标题行内容
	CTime now(CTime::GetCurrentTime());
	CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S ")));
	sDate +="+0800 (CST)";

	CString sBuf(sReply);
	if (m_Attach.GetLength())
	{
		sReply.Format(_T("MIME-Version: 1.0\r\n"));
		sBuf += sReply;
	}

	//添加 From 和 to 字段
	//From: "=?GB2312?B?XXXXXXXXXX=?=" // 发信人，进行了编码
	//To: Li@163.com 

	coder.Encode(m_Addr);
	sReply.Format(_T("From: %s\r\n"), m_Addr);
//	sReply.Format(_T("From: =?gb2312?B?%s?=\r\n"), coder.EncodedMessage());
	sBuf += sReply;
	
	sReply.Format(_T("To: %s\r\n"),m_Receiver);
	sBuf += sReply;

	//添加 Date字段
	//Date: Wed, 8 Apr 2004 16:16:16 +0800 // 发信的日期时间
	sReply.Format(_T("Date: %s\r\n"),sDate);
	sBuf += sReply;

	//添加 subject字段
	//Subject: =?GB2312?B?XXXXXX=?= // 主题，进行了编码
	coder.Encode(m_Title);
	sReply.Format(_T("Subject: %s\r\n"),m_Title);
//	sReply.Format(_T("Subject: =?gb2312?B?%s?=\r\n"),coder.EncodedMessage());
	sBuf += sReply;

	//如果有，添加 Cc 字段
	if (m_CC.GetLength())
	{
		sReply.Format(_T("Cc: %s\r\n"), m_CC);
		sBuf += sReply;
	}

	//如果有，添加Bcc 字段
	if (m_BCC.GetLength())
	{
		sReply.Format(_T("Bcc: %s\r\n"), m_BCC);
		sBuf += sReply;
	}

	//如果需要，添加 Mime 字段
	//MIME-Version: 1.0               // MIME版本
	//Content-type: multipart/mixed;  // 内容类型是多部分/混合型
	//boundary = "NextPart_000_00A"  // 指定一级边界特征字符串
	
	sepa= _T("Boundary-=_HfNFaIwtPvzJDUQrvChaEKIMklNx");
	if (m_Attach.GetLength())
	{
//		sReply.Format(_T("MIME-Version: 1.0\r\n"));
//		sBuf += sReply;
		sReply.Format("Content-Type:Multipart/mixed;boundary=%s\r\n",sepa);
		sBuf += sReply;
		sBuf += _T("\r\n");
	} else {
		sBuf += _T("\r\n");
		sReply.Format(_T(" %s\r\n"), m_Letter);
		sBuf += sReply;
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
	}
	smtpSocket.Send((LPCSTR)sBuf,sBuf.GetLength());
	m_Info+=sBuf;

	if (m_Attach.GetLength())
	{
		sReply.Format(_T("--%s\r\n"),sepa);
		sBuf = sReply;	
		
		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		coder.Encode(m_Letter);
		sReply.Format(_T("%s\r\n"),coder.EncodedMessage());
		sBuf += sReply;
		
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;

		sBuf += _T("Content-Type: text/plain; charset='gb2312'\r\n");
		sBuf += _T("Content-Transfer-Encoding: base64\r\n");
		sBuf += _T("\r\n");
		
		//add Letter	
		LPSTR pszBody = NULL;
		int nBodySize = 0;
		if (!GetBody(pszBody, nBodySize))
		{
			TRACE(_T("Failed in call to send body parts body, GetLastError returns: %d\n"), GetLastError());
		}
		sReply = pszBody;
		sBuf += sReply;
		sReply.Format(_T("--%s\r\n"), sepa);
		sBuf += sReply;
		
		sReply.Format(_T("%c%c.%c%c"),13,10,13,10);
		sBuf += sReply;
		smtpSocket.Send((LPCSTR)sBuf,sBuf.GetLength());
		m_Info+=sBuf;
	}
	UpdateData(FALSE);
}

BOOL CSmtpDlg::GetBody(LPSTR& pszBody, int& nBodySize)
{
	BOOL bSuccess = FALSE;

	//打开附件文件
	CFile infile;
	if (infile.Open(m_Attach, CFile::modeRead | CFile::shareDenyWrite))
	{
		DWORD dwSize = infile.GetLength();
		if (dwSize)
		{
			//读入数据
			BYTE* pszIn = new BYTE[dwSize];
			try
			{
				infile.Read(pszIn, dwSize);
				bSuccess = TRUE;
			}
			catch(CFileException* pEx)
			{
				bSuccess = FALSE;
				pEx->Delete();
			}

			if (bSuccess)
			{
				coder.Encode(pszIn, dwSize); //编码
				delete [] pszIn;               //删除了输入缓冲区
				infile.Close();                //关闭输入文件

				//形成编码后的发送内容
				LPSTR pszEncoded = coder.EncodedMessage();
				int nEncodedSize = coder.EncodedMessageSize();
				nBodySize = nEncodedSize + (((nEncodedSize/76)+1)*2) + 1;
				pszBody = new char[nBodySize];
				--nBodySize; 

				int nInPos = 0;
				int nOutPos = 0;
				while (nInPos < nEncodedSize)
				{
					int nThisLineSize = min(nEncodedSize - nInPos, SMTP_MAXLINE);
					CopyMemory(&pszBody[nOutPos], &pszEncoded[nInPos], nThisLineSize);
					nOutPos += nThisLineSize;
					CopyMemory(&pszBody[nOutPos], "\r\n", 2);
					nOutPos += 2;
					nInPos += nThisLineSize;
				}
				pszBody[nOutPos] = '\0'; //以空字符串结束
			}
		}  else  {
			bSuccess = TRUE;
			pszBody = NULL;
			nBodySize = 0;
		}
	}  else
		TRACE(_T("No bodypart body text or filename specified!\n"));

	return bSuccess;
}