#ifndef _COMMON_H
#define  _COMMON_H

#include <QString>
#include <QList>

#define WIDTH 966
#define HEIGHT 640

#define RELEASE(x) if(x){delete x;x= NULL;}

enum OPERTYPE{sharefiles,myfiles};   //当前操作的类型
enum TOOLINDEX{shareindex,myfilesindex,subshareindex};    //选择对应的工具栏索引

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
	FILESTATUS status;  //0 正常  1暂停 2错误
	FILESTATE state;   //0下载 1上传
}FILETRANSPORT;

typedef struct {
	QString userName;
	QString userImage;
	QString fileName;
	QString fileIcon;
	QString time;
	int state;   //0新建 1上传
}USERLOGITEM;

typedef struct{
	QString userName;
	QString fileName;
	int type;   //0公共目录邀请 1收到文件
}MSGITEM;

#endif // !_COMMON_H_
