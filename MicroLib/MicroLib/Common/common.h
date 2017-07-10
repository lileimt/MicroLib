#ifndef _COMMON_H
#define  _COMMON_H

#include <QString>

#define WIDTH 966
#define HEIGHT 640

#define RELEASE(x) if(x){delete x;x= NULL;}

typedef struct{
	QString fileName;
	QString fileIcon;
	QString fileSize;
	QString filePath;
	int status;  //0 ����  1��ͣ 2����
	int state;   //0���� 1�ϴ�
}FILETRANSPORT;

typedef struct {
	QString userName;
	QString userImage;
	QString fileName;
	QString fileIcon;
	QString time;
	int state;   //0�½� 1�ϴ�
}USERLOGITEM;

typedef struct{
	QString userName;
	QString fileName;
	int type;   //0����Ŀ¼���� 1�յ��ļ�
}MSGITEM;

#endif // !_COMMON_H_
