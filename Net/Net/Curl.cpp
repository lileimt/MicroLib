#include "stdafx.h"
#include "Curl.h"

IHttpRequest::IHttpRequest()
{

}

IHttpRequest::~IHttpRequest()
{

}

CCurl::CCurl(string &url)
	:m_headers(NULL),
	m_pHttpRequest(NULL)
{
	m_strUrl = url;
	m_curl = curl_easy_init();
	if (!m_curl)return;
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 3);
	curl_easy_setopt(m_curl, CURLOPT_URL, m_strUrl.c_str());
}


CCurl::~CCurl()
{
	if (m_headers){
		curl_slist_free_all(m_headers);
		m_headers = NULL;
	}
}

void CCurl::globalInitCurl()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

void CCurl::cleanUpCurl()
{
	curl_global_cleanup();
}

CURLcode CCurl::setHeaders(string strToken)
{
	m_headers = curl_slist_append(m_headers, "Content-Type:application/json");
	if (!strToken.empty()){
		string strAuth = "Authorization:Bearer " + strToken;
		m_headers = curl_slist_append(m_headers, strAuth.c_str());
	}
	m_headers = curl_slist_append(m_headers, "User-Agent:Mozilla/4.0 (compatible; MSIE 5.5; Windows NT");
	return curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headers);
}

CURLcode CCurl::setRange(string range)
{
	return curl_easy_setopt(m_curl, CURLOPT_RANGE, range);
}

CURLcode CCurl::setResumeRange(long length)
{
	return curl_easy_setopt(m_curl, CURLOPT_RESUME_FROM_LARGE, length);
}

void CCurl::setHttpDownload(IHttpRequest *pHttpDownload)
{
	m_pHttpRequest = pHttpDownload;
}

static size_t OnWriteData(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if (NULL == str || NULL == buffer){
		return -1;
	}

	char* pData = (char*)buffer;
	str->append(pData, size * nmemb);
	return nmemb;
}

int CCurl::httpGet(string &strResponse)
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	return m_res;
}

long CCurl::httpGetFileSize()
{
	long downloadFileLenth = 0;
	curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);    //只要求header头
	curl_easy_setopt(m_curl, CURLOPT_NOBODY, 1);    //不需求body
	if (curl_easy_perform(m_curl) == CURLE_OK) {
		curl_easy_getinfo(m_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &downloadFileLenth);
	}else {
		downloadFileLenth = -1;
	}
	return downloadFileLenth;
}

int CCurl::httpPost(string &strPost, string &strResponse)
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_POST, 1);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strPost.c_str());
	curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);

	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	return m_res;
}

int CCurl::httpCustomRequest(string cmd, string strParams, string &strResponse)
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, cmd);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strParams.c_str());
	curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);

	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	return m_res;
}

size_t CCurl::downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
	IHttpRequest *pHttpDownload = static_cast<IHttpRequest *>(pParam);
	return pHttpDownload->downloadCallback(pBuffer, nSize, nMemByte);
}

size_t CCurl::uploadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
	printf("uploadCallback\n");
	IHttpRequest *pHttpDownload = static_cast<IHttpRequest *>(pParam);
	return pHttpDownload->uploadCallback(pBuffer, nSize, nMemByte);
}

int CCurl::progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	IHttpRequest *pHttpDownload = static_cast<IHttpRequest *>(clientp);
	return pHttpDownload->progressCallback(dltotal, dlnow, ultotal, ulnow);
}

CURLcode CCurl::downloadFile()
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 600);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, downloadCallback);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, m_pHttpRequest);
	//设置重定向的最大次数
	curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 5);
	//设置301、302跳转跟随location
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, m_pHttpRequest);

	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	printf("downloadFile\n");
	return m_res;
}

CURLcode CCurl::uploadFile(long filesize)
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_HEADER, 0);
	//curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 600);
	curl_easy_setopt(m_curl, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(m_curl, CURLOPT_PUT, 1L);
	curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, uploadCallback);
	curl_easy_setopt(m_curl, CURLOPT_READDATA, m_pHttpRequest);
	curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, m_pHttpRequest);
	curl_easy_setopt(m_curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)filesize);

	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	printf("uploadFile\n");
	return m_res;
}