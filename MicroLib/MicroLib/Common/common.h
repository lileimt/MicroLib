#ifndef _COMMON_H_
#define  _COMMON_H

#include <QString>

typedef struct FileTransport
{
	QString fileName;
	QString fileIcon;
	QString fileSize;
	QString filePath;
	int status;  //0 正常  1暂停 2错误
	int state;   //0下载 1上传
}FILETRANSPORT;

#endif // !_COMMON_H_
