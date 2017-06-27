// NetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "../Net/Net.h"

#pragma comment(lib,"../Debug/Net.lib")

//string url = "http://sw.bos.baidu.com/sw-search-sp/software/7049cf3e3b04f/npp_7.4.2_Installer.exe";
string url = "http://sw.bos.baidu.com/sw-search-sp/software/3286ec7d3719a/QQ_8.9.3.21159_setup.exe";
string fileName = "npp_7.4.2_Installer.exe";
FILE *fp = NULL;

size_t downloadCallBack(void* pBuffer, size_t nSize, size_t nMemByte)
{
	//FILE *fp = fopen(fileName.c_str(), "ab+");
	if (fp){
		fwrite(pBuffer, nSize, nMemByte, fp);
		//fclose(fp);
		fflush(fp);
	}else{
		printf("error:%d\n", errno);
	}
	return nMemByte;
}

int progressCallBack(double dltotal, double dlnow, double ultotal, double ulnow)
{
	if ((int)dltotal == 0)return 0;
	printf("%d,%d,%d %%\n", (int)dltotal,(int)dlnow,(int)(dlnow/dltotal*100));
	if (dltotal == dlnow){
		if (fp){
			fclose(fp);
			fp = NULL;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	globalInitCurl();
	fp = fopen(fileName.c_str(), "ab+");
	CDownloadThread *thread = getDownloadThread(downloadCallBack, progressCallBack, url, "", fileName, "");
	startThread(thread);
	globalCleanUpCurl();
	system("pause");
	return 0;
}

