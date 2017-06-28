#pragma once

#include "Curl.h"
#include <iostream>
using namespace std;

class CThread
{
public:
	CThread(int nPriority = THREAD_PRIORITY_NORMAL);
	virtual ~CThread();

	HANDLE m_hThread;
	void Resume();
	void Terminate();
	BOOL Terminated();
	HANDLE GetThreadHandle();

private:
	static DWORD WINAPI ThreadProc(LPVOID pVoid);
protected:
	BOOL m_bTerminated;

	virtual void Execute() = 0;
};

typedef int (*ProgressCallBack)(double dltotal, double dlnow, double ultotal, double ulnow);
typedef size_t (*DownloadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte,FILE *fp);
typedef size_t(*UploadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte, FILE *fp);

class CDownloadThread : public CThread,public IHttpRequest
{
public:
	CDownloadThread(ProgressCallBack progressCallBack, string url, string token, string fileName, string path);
	virtual ~CDownloadThread();

	virtual size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte);
	virtual size_t uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte);
	virtual int progressCallback(double dltotal, double dlnow, double ultotal, double ulnow);

	void setDownloadCallback(DownloadCallBack downloadCallBack);
	long getFileSize(string fullFileName);
protected:
	string m_url;
	string m_fileName;
	string m_path;
	string m_token;
	FILE *m_fp;
	ProgressCallBack m_progressCallBack;

	void Execute();
private:
	DownloadCallBack m_downloadCallBack;
};

class CUploadThread :public CDownloadThread
{
public:
	CUploadThread(ProgressCallBack progressCallBack, string url, string token, string fileName);
	virtual ~CUploadThread();

	virtual size_t uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte);
	void setUploadCallback(UploadCallBack uploadCallBack);
protected:
	void Execute();
private:
	UploadCallBack m_uploadCallBack;
};