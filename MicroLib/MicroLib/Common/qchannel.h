#ifndef QCHANNEL_H
#define QCHANNEL_H

#include <QObject>

class QChannel : public QObject
{
	Q_OBJECT

public:
	QChannel(QObject *parent = 0);
	~QChannel();

	QString getCurDir();
	void setNewDir();
	void setToken(QString token);
	void setCurType(int type);
	void setCurFiles();  //发送信号获取下载文件信息
	void deleteFiles();
signals:
	void sigToken(QString token);
	void sigCurType(int type);  //设置当前是公共目录还是我的文件
	void sigNewDir();   //js端新建文件夹(绑定js事件)
	void sigCurFiles();    //js端获取当前选中需要下载的文件
	void sigDeleteFiles(); //js端处理删除操作

	//C++信号
	void sigChangeToolBar(int index);  //发信号改变工具栏
	void sigStartDownload(QString curFiles);//获取到当前选中的文件信息后开始下载
	void sigSendFiles(QStringList ids);
public slots :
	void slotCurDir(QString curDir);   //C++端更新当前路径(js调用)
	void slotChangeToolBar(int index);  //C++端更新工具栏(js调用)
	void slotCurFiles(QString curFiles);  //C++端获取需要下载的文件信息(js调用)
	void slotSendFiles(QStringList ids);//C++端获取
private:
	QString m_curDir;
};

#endif // QCHANNEL_H
