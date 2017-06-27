#pragma once

#include "curl/curl.h"
#include <iostream>

using namespace std;

class IHttpDownload{
public:
	IHttpDownload();
	virtual ~IHttpDownload();
	
	virtual size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte) = 0;
	virtual int progressCallback(double dltotal, double dlnow, double ultotal, double ulnow) = 0;
};

class CCurl
{
public:
	CCurl(string &url);
	~CCurl();

	static void globalInitCurl();
	static void cleanUpCurl();

	CURLcode setHeaders(string strToken = "");
	CURLcode setRange(string range = "0-");

	int httpGet(string &strResponse);
	long httpGetFileSize();
	int httpPost(string &strPost, string &strResponse);

	void setHttpDownload(IHttpDownload *pHttpDownload);
	int downloadFile();

	static size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static int progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

private:
	CURL *m_curl;
	string m_strUrl;
	struct curl_slist *m_headers;

	IHttpDownload *m_pHttpDownload;
	//ProgressCallBack m_progressCallBack;
	//DownloadCallBack m_downloadCallBack;
};

