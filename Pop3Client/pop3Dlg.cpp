// pop3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "pop3.h"
#include "pop3Dlg.h"
#include "mySock.h"      //手工添加的包含语句

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
// CPop3Dlg dialog

CPop3Dlg::CPop3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPop3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPop3Dlg)
	m_strPass = _T("");
	m_strServer = _T("");
	m_strUser = _T("");
	m_bolDel = FALSE;
	m_Info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPop3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPop3Dlg)
	DDX_Control(pDX, IDC_RICH_INFO, m_ctrInfo);
	DDX_Control(pDX, IDC_COMB_LIST, m_ctrList);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
	DDX_Text(pDX, IDC_EDIT_SERVER, m_strServer);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Check(pDX, IDC_CHECK_DEL, m_bolDel);
	DDX_Text(pDX, IDC_RICH_INFO, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPop3Dlg, CDialog)
	//{{AFX_MSG_MAP(CPop3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONN, OnBtnConn)
	ON_BN_CLICKED(IDC_BTN_DISC, OnBtnDisc)
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPop3Dlg message handlers

BOOL CPop3Dlg::OnInitDialog()
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
	//用户在这里添加控件成员变量的初始化代码
	m_strServer = _T("pop.sina.com.cn");   //POP3服务器地址
	m_strUser = _T("mu_lm");               //邮箱的用户名
	m_strPass = _T("491015");              //口令
	m_bolDel = FALSE;                      //下载邮件后不删除
	m_Info = _T("");                       //多文本框清空
	m_ctrList.Clear();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPop3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPop3Dlg::OnPaint() 
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
HCURSOR CPop3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//以下是事件处理函数和其他成员函数的代码
//当用户点击"连接"按钮时，执行此函数
void CPop3Dlg::OnBtnConn() 
{
	//设定pop3类的对话框指针变量，使之指向本对话框，以便传递信息
	pop3Socket.SetParent(this); 
	UpdateData(TRUE);           //取来用户在对话框中输入的数据
	pop3Socket.Create();        //创建套接字对象的底层套接字
	pop3Socket.Connect((LPCSTR)m_strServer,110); //连接pop3服务器
	m_Info = "";                //多文本列表框清空
	UpdateData(FALSE);          //更新用户界面

}
//当用户点击"断开"按钮时，执行此函数
void CPop3Dlg::OnBtnDisc() 
{
	pop3Socket.Close();
}
//当用户点击"查看邮件"按钮时，执行此函数
void CPop3Dlg::OnBtnView() 
{
	int i;
	i = m_ctrList.GetCurSel();  //获得用户在组合框中的选择
	//获得并显示指定信件的基本属性及信件内容
	m_Info += pop3Socket.GetMsgStuff(i);
	m_Info += pop3Socket.GetMsgBody(i);
//	CString s;
//	for(int i=0;i<pop3Socket.retrMsg;i++)
//	{
//		s.Format("%c%c第 %d 封信 %c%c",13,10,i,13,10);
//		m_Info +=s;
//		m_Info += pop3Socket.msgs[i].text;
//	}
	UpdateData(FALSE);
}
//在不同的情况下，向用户显示不同的信息
void CPop3Dlg::Disp(LONG flag)
{
	CString s;
	switch(flag)
	{
	case S_CONNECT: //已连接到服务器，显示信息
		s = "已连接到"+m_strServer+"...\r\n";
		m_Info+=s;
		//禁用连接按钮
		GetDlgItem(IDC_BTN_CONN)->EnableWindow(FALSE);
		//启用断开按钮
		GetDlgItem(IDC_BTN_DISC)->EnableWindow(TRUE); 
		//禁用查看邮件按钮
		GetDlgItem(IDC_BTN_VIEW)->EnableWindow(FALSE);
		break;
	case S_RECEIVE: //收到服务器发来的响应，显示它的内容
		m_Info+=pop3Socket.lastMsg;
		break; 
	case S_CLOSE: //显示关闭连接的信息
		m_Info+=pop3Socket.error;
		s = "连接已经关闭\r\n";
		m_Info+=s;
		//启用连接按钮
		GetDlgItem(IDC_BTN_CONN)->EnableWindow(TRUE);
		//禁用断开按钮
		GetDlgItem(IDC_BTN_DISC)->EnableWindow(FALSE);
		break;
	case S_GETNUM: //已经知道了邮箱中信件的总数
		s.Format("邮箱中共有 %d 封信\r\n",pop3Socket.numMsg);
		m_Info+=s;
		break;
	case S_GETSIZE: //显示信件的大小
		s.Format("信箱中信件大小为：%d字节\r\n",pop3Socket.sizeMsg);
		m_Info+=s;
		break;
	case S_ENDRETR: //所有信件已下载完毕，显示信息
		s.Format("共下载了 %d 封信件\r\n",pop3Socket.msgs.size());
		m_Info+=s;
		//如果有信件下载，启用查看邮件按钮
		if((pop3Socket.msgs.size())>0)
			GetDlgItem(IDC_BTN_VIEW)->EnableWindow(TRUE);
		break;
	}
	UpdateData(FALSE);   //更新用户界面
}

void CPop3Dlg::OnBtnSave() 
{
	int i;
	CString s;
	i = m_ctrList.GetCurSel();
	//获得指定信件的基本属性及信件内容
	s = pop3Socket.GetMsgStuff(i);
	s += pop3Socket.GetMsgBody(i);
	
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
	{
		CFile file(dlg.GetPathName(),
			CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
		file.Write((LPCSTR)s,s.GetLength());
		file.Close();
	}
}
