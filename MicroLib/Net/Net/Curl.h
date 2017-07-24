#pragma once

#include "curl/curl.h"
#include <iostream>

using namespace std;

class IHttpRequest{
public:
	IHttpRequest();
	virtual ~IHttpRequest();
	
	virtual size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte) = 0;
	virtual size_t uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte) = 0;
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
	CURLcode setResumeRange(long length);

	int httpGet(string &strResponse);
	long httpGetFileSize();
	int httpPost(string &strPost, string &strResponse);
	//PUT DELETE
	int httpCustomRequest(string cmd,string strParams,string &strResponse);

	void setHttpDownload(IHttpRequest *pHttpDownload);
	CURLcode downloadFile();
	CURLcode uploadFile(long filesize);

	static size_t downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static size_t uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static int progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

private:
	CURL *m_curl;
	string m_strUrl;
	struct curl_slist *m_headers;

	IHttpRequest *m_pHttpRequest;
};

