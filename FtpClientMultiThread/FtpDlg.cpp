// FtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
#include "Afxinet.h"
#include "mt.h"
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
// CFtpDlg dialog

CFtpDlg::CFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFtpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFtpDlg)
	m_strFtp = _T("");
	m_strName = _T("");
	m_strPwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFtpDlg)
	DDX_Control(pDX, IDC_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, IDOK, m_btnQuery);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Control(pDX, IDC_STATIC_PWD, m_staPwd);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staName);
	DDX_Control(pDX, IDC_STATIC_FTP, m_staFtp);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFtpDlg, CDialog)
	//{{AFX_MSG_MAP(CFtpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnQuery)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, OnSelchangeListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFtpDlg message handlers

BOOL CFtpDlg::OnInitDialog()
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
	m_strFtp=_T("");    // 初始化服务器域名
	m_strName=_T("");     // 初始化登录用户名
	m_strPwd=_T("");      //  初始化登录口令
	UpdateData(FALSE);    //更新界面

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpDlg::OnPaint() 
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
HCURSOR CFtpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//当用户单击“查询”按钮时，执行此函数，此函数创建一个新线程，执行实际的查询
void  CFtpDlg::OnQuery()
{
	//获得用户在对话框中的当前输入
	UpdateData(TRUE);
	//构造用于线程控制函数参数传递的结构对象
	FTP_INFO* pp = new FTP_INFO;
	pp->pList = &m_listFile;
	pp->strFtpSite = m_strFtp;
	pp->strName = m_strName;
	pp->strPwd = m_strPwd;
	// 清除对话框中列表框的内容
	while (m_listFile.GetCount() != 0) m_listFile.DeleteString(0);
	//创建并启动新线程，执行实际的查询任务
	AfxBeginThread(mtQuery, pp);
}

//查询以后，当用户在列表框中选择了一个文件时，执行此函数。
void CFtpDlg::OnSelchangeListFile() 
{
	// 禁用用来输入的文本框控件
	m_editFtp.EnableWindow(FALSE);          //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);        //登录用户名输入文本框 
	m_editPwd.EnableWindow(FALSE);          //口令输入文本框
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//禁用查询和上传按钮
	m_btnUpload.EnableWindow(FALSE);      //上传按钮
	m_btnQuery.EnableWindow(FALSE);        //查询按钮

	//激活下载按钮
	m_btnDownload.EnableWindow(TRUE);
}

//当用户单击“下载”按钮时，执行此函数
void CFtpDlg::OnDownload()
{
	//获得用户在对话框中的当前输入
	UpdateData(TRUE);
	//构造用于线程控制函数参数传递的结构对象
	FTP_INFO* pp = new FTP_INFO;
	//将用户输入的相关信息赋值到结构对象的成员变量中
	pp->pList = &m_listFile;
	pp->strFtpSite = m_strFtp;
	pp->strName = m_strName;
	pp->strPwd = m_strPwd;
	//创建并启动新的线程，完成实际的下载任务
	AfxBeginThread(mtDownloadFile, pp);

	//禁用对话框中的“下载”按钮
	m_btnDownload.EnableWindow(FALSE);

	//激活对话框中的“查询”和“上传”按钮
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//激活对话框中用来输入的文本框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

//当用户单击“上传”按钮时，执行此事件处理函数
void CFtpDlg::OnUpload()
{
	//获得用户在对话框中的当前输入，如服务器名、用户名和口令
	UpdateData(TRUE);

	//将对话框中用于输入的文本框控件禁用
	m_editFtp.EnableWindow(FALSE);			//服务器域名输入文本框
	m_editName.EnableWindow(FALSE);			//登录客户名输入文本框
	m_editPwd.EnableWindow(FALSE);			//口令输入文本框
	m_staFtp.EnableWindow(FALSE);			//响应的静态文本
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//禁用对话框中的“查询”按钮
	m_btnQuery.EnableWindow(FALSE);
	//构造用于线程控制函数参数传递的结构对象
	FTP_INFO* pp = new FTP_INFO;
	//将用户输入的相关信息赋值到结构对象的成员变量中
	pp->pList = NULL;
	pp->strFtpSite = m_strFtp;
	pp->strName = m_strName;
	pp->strPwd = m_strPwd;
	//创建并启动新的线程，来完成实际的上传工作
	AfxBeginThread(mtUploadFile, pp);

	//激活对话框中的“查询”按钮
	m_btnQuery.EnableWindow(TRUE);

	//激活对话框中用于输入的文本框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

