#ifndef _COMMON_H_
#define  _COMMON_H

#include <QString>

#define WIDTH 966
#define HEIGHT 640

#define RELEASE(x) if(x){delete x;x= NULL;}

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
