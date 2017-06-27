#ifndef _NET_H_
#define _NET_H_

#ifdef NET_EXPORTS
#define  NET_API __declspec(dllexport)
#else
#define  NET_API __declspec(dllimport)
#endif

#include <iostream>
using namespace std;

typedef int(*ProgressCallBack)(double dltotal, double dlnow, double ultotal, double ulnow);
typedef size_t(*DownloadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte);

class CDownloadThread;

NET_API void globalInitCurl();
NET_API void globalCleanUpCurl();

NET_API string httpGet(string url,string token = "");
NET_API string httpPost(string url, string &strPost,string token = "");
NET_API CDownloadThread *getDownloadThread(DownloadCallBack downloadCallBack, ProgressCallBack progressCallBack, string url, string token, string fileName, string path);
NET_API void startThread(CDownloadThread *thread);

#endif