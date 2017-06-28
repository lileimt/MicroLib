// NetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "../Net/Net.h"

#pragma comment(lib,"../Debug/Net.lib")

//string url = "http://sw.bos.baidu.com/sw-search-sp/software/7049cf3e3b04f/npp_7.4.2_Installer.exe";
//string url = "http://sw.bos.baidu.com/sw-search-sp/software/3286ec7d3719a/QQ_8.9.3.21159_setup.exe";
string url = "http://www.baidu.com";
//string fileName = "npp_7.4.2_Installer.exe";
string fileName = "ReadMe.txt";

size_t downloadCallBack(void* pBuffer, size_t nSize, size_t nMemByte,FILE *fp)
{
	size_t length = 0;
	if (fp){
		length =fwrite(pBuffer, nSize, nMemByte, fp);
	}
	return length;
}

size_t uploadCallBack(void* pBuffer, size_t nSize, size_t nMemByte, FILE *fp)
{
	size_t retcode = fread(pBuffer, nSize, nMemByte, fp);
	printf("upload %d\n", retcode);
	return retcode;
}

int progressCallBack(double dltotal, double dlnow, double ultotal, double ulnow)
{
	if ((int)dltotal == 0)return 0;
	printf("%d,%d,%d %%\n", (int)dltotal,(int)dlnow,(int)(dlnow/dltotal*100));

	//printf("%d,%d,%d %%\n", (int)ultotal, (int)ulnow, (int)(ulnow / ultotal * 100));
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	globalInitCurl();
	//CDownloadThread *thread = getDownloadThread(progressCallBack, url, "", fileName, "");
	//setDownloadCallBack(thread, downloadCallBack);
	//startDownloadThread(thread);
	CUploadThread *thread = getUploadThread(progressCallBack, url, "", fileName);
	setUploadCallBack(thread, uploadCallBack);
	startUploadThread(thread);
	globalCleanUpCurl();
	system("pause");
	return 0;
}

