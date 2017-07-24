#ifndef _COMMON_H
#define  _COMMON_H

#include <QString>

#define WIDTH 966
#define HEIGHT 640

#define RELEASE(x) if(x){delete x;x= NULL;}

enum OPERTYPE{sharefiles,myfiles};   //当前操作的类型
enum TOOLINDEX{shareindex,myfilesindex,subshareindex};    //选择对应的工具栏索引

#define USERURL  "http://api-x.sunfuedu.com/admin/v1/users"

typedef struct{
	QString fileName;
	QString fileIcon;
	QString fileSize;
	QString filePath;
	int status;  //0 正常  1暂停 2错误
	int state;   //0下载 1上传
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
