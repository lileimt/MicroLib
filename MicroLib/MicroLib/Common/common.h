#ifndef _COMMON_H
#define  _COMMON_H

#include <QString>
#include <QList>

#define WIDTH 966
#define HEIGHT 640

#define RELEASE(x) if(x){delete x;x= NULL;}

enum OPERTYPE{sharefiles,myfiles};   //��ǰ����������
enum TOOLINDEX{shareindex,myfilesindex,subshareindex};    //ѡ���Ӧ�Ĺ���������

enum FILESTATUS{normal,pause,error};
enum FILESTATE{download,upload};

#define USERURL  "http://api-x.sunfuedu.com/admin/v1/users"
#define SendFileURL "http://api-x.sunfuedu.com/microlib/v1/files/ids/content"

typedef struct{
	int id;
	QString url;
	QString md5;
	QString fileName;
	QString fileIcon;
	QString curSize;
	QString fileSize;
	QString filePath;
	FILESTATUS status;  //0 ����  1��ͣ 2����
	FILESTATE state;   //0���� 1�ϴ�
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
