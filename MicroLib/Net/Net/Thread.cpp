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

CDownloadThread::CDownloadThread(/*DownloadCallBack downloadCallBack, */ProgressCallBack progressCallBack, string url, string token, string fileName, string path)
	:CThread(),
	IHttpRequest(),
	//m_downloadCallBack(downloadCallBack),
	m_progressCallBack(progressCallBack),
	m_fp(NULL),
	m_url(url),
	m_fileName(fileName),
	m_path(path),
	m_token(token)
{
	//string fullPath = path +"\\"+ fileName;
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
		//curl.setResumeRange(getFileSize(m_fileName));
		//printf("execute\n");
		curl.setHttpDownload(static_cast<IHttpRequest *>(this));
		m_fp = fopen(m_fileName.c_str(), "ab+");
		CURLcode res = curl.downloadFile();
		if (res == CURLE_OK){
			printf("finish\n");
			fclose(m_fp);
			m_fp = NULL;
		}
	//	m_bTerminated = FALSE;
	//}
}

void CDownloadThread::setDownloadCallback(DownloadCallBack downloadCallBack)
{
	m_downloadCallBack = downloadCallBack;
}

size_t CDownloadThread::downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte)
{
	if (!m_downloadCallBack)return 0;
	return m_downloadCallBack(pBuffer, nSize, nMemByte,m_fp);
}

size_t CDownloadThread::uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte)
{
	return 0;
}

int CDownloadThread::progressCallback(double dltotal, double dlnow, double ultotal, double ulnow)
{
	if (!m_progressCallBack) return -1;
	return m_progressCallBack(dltotal,dlnow,ultotal,ulnow);
}

long CDownloadThread::getFileSize(string fullFileName)
{
	FILE *fp = fopen(fullFileName.c_str(), "rb");
	if (fp == NULL)return 0;

	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fclose(fp);

	return length;
}

CUploadThread::CUploadThread(ProgressCallBack progressCallBack, string url, string token, string fileName)
	:CDownloadThread(progressCallBack, url, token, fileName, "")
{

}

CUploadThread::~CUploadThread()
{

}

size_t CUploadThread::uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte)
{
	if (!m_uploadCallBack)return 0;
	return m_uploadCallBack(pBuffer, nSize, nMemByte, m_fp);
}

void CUploadThread::setUploadCallback(UploadCallBack uploadCallBack)
{
	m_uploadCallBack = uploadCallBack;
}

void CUploadThread::Execute()
{
	CCurl curl(m_url);
	//curl.setHeaders(m_token);
	curl.setHttpDownload(static_cast<IHttpRequest *>(this));

	m_fp = fopen(m_fileName.c_str(), "rb");
	CURLcode res = curl.uploadFile(getFileSize(m_fileName));
	if (res == CURLE_OK){
		printf("finish\n");
		fclose(m_fp);
		m_fp = NULL;
	}
}