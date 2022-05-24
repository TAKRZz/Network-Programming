// FtpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ftp.h"
#include "FtpDlg.h"
#include "Afxinet.h"

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

//当用户点击'查询'按钮，执行此函数。
void CFtpDlg::OnQuery() 
{
	CInternetSession* pSession;     //定义会话对象指针变量
	CFtpConnection* pConnection;   //定义连接对象指针变量
	CFtpFileFind* pFileFind;          //定义文件查询对象指针变量
	CString strFileName;
	BOOL bContinue;

	pConnection=NULL;      //初始化
	pFileFind=NULL;

	UpdateData(TRUE);      // 获得用户的当前输入（服务器名，用户名和口令）
	while(m_listFile.GetCount()!=0) m_listFile.DeleteString(0);  // 清除列表框的内容

	pSession=new CInternetSession(          // 创建Internet会话类对象
			AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try 
	{  // 试图建立与指定FTP服务器的连接
		pConnection=
			pSession->GetFtpConnection(m_strFtp,m_strName,m_strPwd);
	}  catch (CInternetException* e)  {   
		e->Delete();                          // 无法建立连接，进行错误处理
		pConnection=NULL;
	}
	
	if (pConnection!=NULL)
	{
		// 创建CFtpFileFind对象，向构造函数传递CFtpConnection对象的指针
		pFileFind=new CFtpFileFind(pConnection);
		
		bContinue = pFileFind->FindFile(_T("*"));  // 查找服务器上当前目录的任意文件
		if (!bContinue)   // 如果一个文件都找不到，结束查找
		{

			pFileFind->Close();
			pFileFind=NULL;
		}

		while (bContinue)  // 找到了第一个文件，继续找其它的文件
		{
			bContinue = pFileFind->FindNextFile();
			strFileName=pFileFind->GetFileName();  // 获得找到的文件的文件名
			// 如果找到的是否目录，将目录名放在括弧中
			if (pFileFind->IsDirectory())  strFileName="["+strFileName+"]";
			// 将找到的文件或目录名显示在列表框中。
			m_listFile.AddString(strFileName);
		}

		if (pFileFind!=NULL)
		{
			pFileFind->Close();   // 结束查询
			pFileFind=NULL;
		}
	}
	delete pFileFind;              // 删除文件查询对象
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;      // 删除FTP连接对象
	}
	delete pSession;             // 删除Internet 会话对象 
	
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

//当用户点击"下载"按钮时，执行此函数
void CFtpDlg::OnDownload() 
{
	//获得当前输入
	UpdateData(TRUE);
	int nSel=m_listFile.GetCurSel();
	CString strSourceName;

	//获得用户在列表框中的选择
	nSel=m_listFile.GetCurSel();
	m_listFile.GetText(nSel,strSourceName);

	if (strSourceName.GetAt(0)!='[' )
	{
		//选择的是文件
		CString strDestName;
		CFileDialog dlg(FALSE,"","*.*");   //定义了一个文件对话框对象变量
		if (dlg.DoModal()==IDOK)        //激活文件对话框
		{
			//获得下载文件在本地机上存储的路径和名称
			strDestName=dlg.GetPathName();

			//调用函数下载文件
			if (Download (strSourceName,strDestName))
				AfxMessageBox("下载成功！",MB_OK|MB_ICONINFORMATION);
			else
				AfxMessageBox("下载失败！",MB_OK|MB_ICONSTOP);
		}  else  {
			AfxMessageBox("请写入文件名！",MB_OK|MB_ICONSTOP);
		}
	}  else  {
		//选择的是目录
		AfxMessageBox("不能下载目录!\n请重选!",MB_OK|MB_ICONSTOP);
	}

	//禁用下载按钮
	m_btnDownload.EnableWindow(FALSE);

	//激活查询和上传按钮
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//激活用来输入的文本和编辑框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

// Download函数由OnDownload函数调用，执行实际的下载任务
BOOL CFtpDlg::Download(CString strSName, CString strDName)
{
	CInternetSession* pSession;      //定义会话对象变量指针
	CFtpConnection* pConnection;    //定义连接对象变量指针

	pConnection=NULL;

	//创建Internet会话对象
	pSession=new CInternetSession( AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection=pSession->GetFtpConnection(m_strFtp,
				m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//下载文件
		if (!pConnection->GetFile(strSName,strDName))
		{
			//下载文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
		delete pSession;

	return TRUE;
}

//当用户点击"上传"按钮时，执行此函数
void CFtpDlg::OnUpload() 
{
	//获得当前输入
	UpdateData(TRUE);

	//禁用用于输入的文本框控件
	m_editFtp.EnableWindow(FALSE);            //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);          //登录客户名输入文本框
	m_editPwd.EnableWindow(FALSE);            //口令输入文本框
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//禁用查询按钮
	m_btnQuery.EnableWindow(FALSE);

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,"","*.*");       //定义文本对话框对象变量
	if (dlg.DoModal()==IDOK)
	{
		//获得待上传的本地机文件路径和文件名
		strSourceName=dlg.GetPathName();
		strDestName=dlg.GetFileName();

		//调用Upload函数上传文件
		if (Upload (strSourceName,strDestName))
			AfxMessageBox("上传成功！",MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox("上传失败！",MB_OK|MB_ICONSTOP);
	}  else  {
		//文件选择有错误
		AfxMessageBox("请选择文件！",MB_OK|MB_ICONSTOP);
	}

	//激活查询按钮
	m_btnQuery.EnableWindow(TRUE);

	//激活用于输入的文本框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);
}

// Upload函数由事件处理函数OnUpload调用，执行实际的上传任务
BOOL CFtpDlg::Upload(CString strSName, CString strDName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection=NULL;

	//创建Internet会话
	pSession=new CInternetSession(	AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection=pSession->GetFtpConnection(	m_strFtp,
		m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//上传文件
		if (!pConnection->PutFile(strSName,strDName))
		{
			//上传文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}

	delete pSession;

	return TRUE;
}
