BOOL mtDownload(CString  strFtpSite,
	CString  strName,
	CString  strPwd,
	CString  strSourceName,
	CString  strDestName);
BOOL  mtUpload(CString strFtpSite, CString strName,
	CString strPwd, CString strSourceName, CString strDestName);
//1．用于查询的线程函数
UINT mtQuery(LPVOID  pParam)
{
	if (pParam == NULL)  AfxEndThread(NULL);
	//这一段代码是用来获取函数调用的参数的，用法非常典型，函数调用的入口参数
	//pParam是一个LPVOID类型的指针，必须将它转化为FTP_INFO结构类型的指针
	//变量，才能从中取出相应的数据成员
	FTP_INFO* PP;
	CListBox*  pList;
	CString  strFtpSite;
	CString  strName;
	CString  strPwd;
	PP = (FTP_INFO*)pParam;
	pList = PP->pList;
	strFtpSite = PP->strFtpSite;
	strName = PP->strName;
	strPwd = PP->strPwd;

	CInternetSession* pSession;			//定义会话对象指针变量
	CFtpConnection* pConnection;			//定义连接对象指针变量
	CFtpFileFind* pFileFind; 			//定义文件查询对象指针变量
	CString strFileName;
	BOOL bContinue;

	pConnection = NULL;					//初始化
	pFileFind = NULL;

	pSession = new CInternetSession(		// 创建Internet会话类对象
		AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	try
	{  // 试图建立与指定FTP服务器的连接
		pConnection =
			pSession->GetFtpConnection(strFtpSite, strName, strPwd);
	}
	catch (CInternetException* e) {
		e->Delete(); 						// 无法建立连接，进行错误处理
		pConnection = NULL;
	}

	if (pConnection != NULL)
	{// 创建CFtpFileFind对象，向构造函数传递CFtpConnection对象的指针
		pFileFind = new CFtpFileFind(pConnection);
		bContinue = pFileFind->FindFile(_T("*"));	// 查找服务器上当前目录的任意文件
		if (!bContinue)						// 如果一个文件都找不到，结束查找
		{
			pFileFind->Close();
			pFileFind = NULL;
		}

		while (bContinue)					// 找到了第一个文件，继续找其他的文件
		{
			bContinue = pFileFind->FindNextFile();		// 查找下一个文件
			strFileName = pFileFind->GetFileName();	// 获得找到的文件的文件名
													// 如果找到的对象是个目录，就将目录名放在括弧中
			if (pFileFind->IsDirectory())  strFileName = "[" + strFileName + "]";
			// 将找到的文件或目录名显示在列表框中
			pList->AddString(strFileName);
			
		}

		if (pFileFind != NULL)
		{
			pFileFind->Close();						// 结束查询
			pFileFind = NULL;
		}
	}
	delete pFileFind;								// 删除文件查询对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;							// 删除FTP连接对象
	}
	delete pSession; 								// 删除Internet 会话对象 
	return 0;									// 必须要有返回值
}
//2．用于下载的线程函数
UINT mtDownloadFile(LPVOID  pParam)
{
	if (pParam == NULL)  AfxEndThread(NULL);
	//用来获取函数调用的参数的代码 
	FTP_INFO* PP;
	CListBox*  pList;
	CString  strFtpSite;
	CString  strName;
	CString  strPwd;
	PP = (FTP_INFO*)pParam;
	pList = PP->pList;
	strFtpSite = PP->strFtpSite;
	strName = PP->strName;
	strPwd = PP->strPwd;

	int  nSel = pList->GetCurSel();
	CString  strSourceName;
	pList->GetText(nSel, strSourceName);
	if (strSourceName.GetAt(0) != '[' )
	   {
		   //选择的是文件
		   CString strDestName;
	   CFileDialog dlg(FALSE,"","*.*");	//定义了一个文件对话框对象变量
	   if (dlg.DoModal() == IDOK)     		//激活文件对话框
	   {
		   //获得下载文件在本地机上存储的路径和名称
		   strDestName = dlg.GetPathName();

		   //调用函数下载文件
		   if (mtDownload(strFtpSite, strName, strPwd,
			   strSourceName,strDestName))
			   AfxMessageBox("下载成功！",MB_OK | MB_ICONINFORMATION);
		   else {
			   AfxMessageBox("下载失败！",MB_OK | MB_ICONSTOP);
			   return FALSE;
		   }
	   }
	   else {
		   AfxMessageBox("请写入文件名！",MB_OK | MB_ICONSTOP);
		   return FALSE;
	   }
	   }
	else {
		   //选择的是目录
		   AfxMessageBox("不能下载目录!\n请重选!", MB_OK | MB_ICONSTOP);
		   return FALSE;
	   }
	   return 0;
}

//下载文件调用的函数
BOOL mtDownload(CString  strFtpSite,
	CString  strName,
	CString  strPwd,
	CString  strSourceName,
	CString  strDestName)
{
	CInternetSession* pSession;		//定义会话对象变量指针
	CFtpConnection* pConnection;		//定义连接对象变量指针

	pConnection = NULL;

	//创建Internet会话对象
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection = pSession->GetFtpConnection(strFtpSite,
			strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//下载文件
		if (!pConnection->GetFile(strSourceName, strDestName))
		{
			//下载文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	return TRUE;
}
//3．用于上传的线程函数
UINT  mtUploadFile(LPVOID  pParam)
{
	if (pParam == NULL)  AfxEndThread(NULL);
	//用来获取函数调用的参数的代码 
	FTP_INFO* PP;
	CListBox*  pList;
	CString  strFtpSite;
	CString  strName;
	CString  strPwd;
	PP = (FTP_INFO*)pParam;
	pList = PP->pList;
	strFtpSite = PP->strFtpSite;
	strName = PP->strName;
	strPwd = PP->strPwd;

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE, "", "*.*");       //定义文本对话框对象变量
	if (dlg.DoModal() == IDOK)
	{
		//获得待上传的本地机文件路径和文件名
		strSourceName = dlg.GetPathName();
		strDestName = dlg.GetFileName();

		//调用Upload函数上传文件
		if (mtUpload(strFtpSite, strName, strPwd,
			strSourceName, strDestName))
			AfxMessageBox("上传成功！", MB_OK | MB_ICONINFORMATION);
		else
			AfxMessageBox("上传失败！", MB_OK | MB_ICONSTOP);
	}
	else {
		//文件选择有错误
		AfxMessageBox("请选择文件！", MB_OK | MB_ICONSTOP);
	}
	return 0;
}

//上传文件调用的函数
BOOL  mtUpload(CString strFtpSite, CString strName,
	CString strPwd, CString strSourceName, CString strDestName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection = NULL;

	//创建Internet会话
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection = pSession->GetFtpConnection(strFtpSite,
			strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//上传文件
		if (!pConnection->PutFile(_T(strSourceName), _T(strDestName)))
		{
			//上传文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;
	return TRUE;
}