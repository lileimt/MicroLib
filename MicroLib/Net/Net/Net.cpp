// Net.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Net.h"
#include "Curl.h"
#include "Thread.h"

NET_API void globalInitCurl()
{
	CCurl::globalInitCurl();
}

NET_API void globalCleanUpCurl()
{
	CCurl::cleanUpCurl();
}

NET_API string httpGet(string url, string token)
{
	CCurl curl(url);
	curl.setHeaders(token);
	string strResponse;
	curl.httpGet(strResponse);
	return strResponse;
}

NET_API string httpPost(string url, string &strPost, string token)
{
	CCurl curl(url);
	curl.setHeaders(token);
	string strResponse;
	curl.httpPost(strPost, strResponse);
	return strResponse;
}

NET_API CDownloadThread *getDownloadThread(ProgressCallBack progressCallBack, string url, string token, string fileName, string path)
{
	return new CDownloadThread(progressCallBack, url, token, fileName, path);
}

NET_API void setDownloadCallBack(CDownloadThread *thread, DownloadCallBack downloadCallBack)
{
	thread->setDownloadCallback(downloadCallBack);
}

NET_API void startDownloadThread(CDownloadThread *thread)
{
	thread->Resume();
}

NET_API CUploadThread *getUploadThread(ProgressCallBack progressCallBack, string url, string token, string fileName)
{
	return new CUploadThread(progressCallBack, url, token, fileName);
}

NET_API void setUploadCallBack(CUploadThread *thread, UploadCallBack uploadCallBack)
{
	thread->setUploadCallback(uploadCallBack);
}

NET_API void startUploadThread(CUploadThread *thread)
{
	thread->Resume();
}