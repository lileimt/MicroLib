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
typedef size_t(*DownloadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte,FILE *fp);
typedef size_t(*UploadCallBack)(void* pBuffer, size_t nSize, size_t nMemByte, FILE *fp);

class CDownloadThread;
class CUploadThread;

NET_API void globalInitCurl();
NET_API void globalCleanUpCurl();

NET_API string httpGet(string url,string token = "");
NET_API string httpPost(string url, string &strPost,string token = "");
NET_API CDownloadThread *getDownloadThread(ProgressCallBack progressCallBack, string url, string token, string fileName, string path);
NET_API void setDownloadCallBack(CDownloadThread *thread,DownloadCallBack downloadCallBack);
NET_API void startDownloadThread(CDownloadThread *thread);
NET_API CUploadThread *getUploadThread(ProgressCallBack progressCallBack, string url, string token, string fileName);
NET_API void setUploadCallBack(CUploadThread *thread, UploadCallBack uploadCallBack);
NET_API void startUploadThread(CUploadThread *thread);
#endif