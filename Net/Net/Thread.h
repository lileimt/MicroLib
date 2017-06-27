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
typedef size_t (*DownloadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte);

class CDownloadThread : public CThread,public IHttpDownload
{
public:
	CDownloadThread(DownloadCallBack downloadCallBack,ProgressCallBack progressCallBack, string url, string token, string fileName, string path);
	~CDownloadThread();

	//DownloadFunc m_downloadFunc;

	virtual size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte);
	virtual int progressCallback(double dltotal, double dlnow, double ultotal, double ulnow);

protected:
	void Execute();

private:
	string m_url;
	string m_fileName;
	string m_path;
	string m_token;
	DownloadCallBack m_downloadCallBack;
	ProgressCallBack m_progressCallBack;
};