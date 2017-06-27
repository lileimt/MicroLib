#include "stdafx.h"
#include "Curl.h"

IHttpDownload::IHttpDownload()
{

}

IHttpDownload::~IHttpDownload()
{

}

CCurl::CCurl(string &url)
	:m_headers(NULL),
	m_pHttpDownload(NULL)
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

void CCurl::setHttpDownload(IHttpDownload *pHttpDownload)
{
	m_pHttpDownload = pHttpDownload;
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

size_t CCurl::downloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
	IHttpDownload *pHttpDownload = static_cast<IHttpDownload *>(pParam);
	return pHttpDownload->downloadCallback(pBuffer, nSize, nMemByte);
}

int CCurl::progressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	IHttpDownload *pHttpDownload = static_cast<IHttpDownload *>(clientp);
	return pHttpDownload->progressCallback(dltotal, dlnow, ultotal, ulnow);
}

int CCurl::downloadFile()
{
	CURLcode m_res;
	curl_easy_setopt(m_curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 600);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, downloadCallback);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, m_pHttpDownload);
	//curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 5);
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSFUNCTION, progressCallback);
	curl_easy_setopt(m_curl, CURLOPT_PROGRESSDATA, m_pHttpDownload);

	m_res = curl_easy_perform(m_curl);
	curl_easy_cleanup(m_curl);
	return m_res;
}