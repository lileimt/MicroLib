#ifndef _COMMON_H_
#define  _COMMON_H

#include <QString>

typedef struct FileTransport
{
	QString fileName;
	QString fileIcon;
	QString fileSize;
	QString filePath;
	int status;  //0 ����  1��ͣ 2����
	int state;   //0���� 1�ϴ�
}FILETRANSPORT;

#endif // !_COMMON_H_
