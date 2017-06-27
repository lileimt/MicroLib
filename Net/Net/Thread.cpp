#include "stdafx.h"
#include "Thread.h"

CThread::CThread(int nPriority)
{
	m_bTerminated = FALSE;

	DWORD dwThreadID;
	m_hThread = CreateThread(NULL, 0, ThreadProc,this,CREATE_SUSPENDED,&dwThreadID);
	SetThreadPriority(m_hThread, nPriority);
}


CThread::~CThread()
{
	CloseHandle(m_hThread);
	m_hThread = NULL;
}

DWORD CThread::ThreadProc(LPVOID pVoid)
{
	((CThread *)(pVoid))->Execute();
	return 0;
}

void CThread::Resume()
{
	ResumeThread(m_hThread);
}

void CThread::Terminate()
{
	m_bTerminated = TRUE;
}

BOOL CThread::Terminated()
{
	return m_bTerminated;
}

HANDLE CThread::GetThreadHandle()
{
	return m_hThread;
}

CDownloadThread::CDownloadThread(DownloadCallBack downloadCallBack, ProgressCallBack progressCallBack, string url, string token, string fileName, string path)
	:CThread(),
	IHttpDownload(),
	m_downloadCallBack(downloadCallBack),
	m_progressCallBack(progressCallBack),
	m_url(url),
	m_fileName(fileName),
	m_path(path),
	m_token(token)
{

}

CDownloadThread::~CDownloadThread()
{

}

void CDownloadThread::Execute()
{
	//while (!m_bTerminated)
	//{
		CCurl curl(m_url);
		curl.setHeaders(m_token);
		//curl.setRange();
		curl.setHttpDownload(static_cast<IHttpDownload *>(this));
		curl.downloadFile();
	//	m_bTerminated = FALSE;
	//}
}

size_t CDownloadThread::downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte)
{
	if (!m_downloadCallBack)return 0;
	return m_downloadCallBack(pBuffer, nSize, nMemByte);
}

int CDownloadThread::progressCallback(double dltotal, double dlnow, double ultotal, double ulnow)
{
	if (!m_progressCallBack) return -1;
	return m_progressCallBack(dltotal,dlnow,ultotal,ulnow);
}