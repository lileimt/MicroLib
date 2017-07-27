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
signals:
	void sigToken(QString token);
	void sigCurType(int type);  //设置当前是公共目录还是我的文件
	void sigNewDir();   //js端新建文件夹(绑定js事件)
	void sigChangeToolBar(int index);  //发信号改变工具栏
public slots :
	void slotCurDir(QString curDir);   //C++端更新当前路径(js调用)
	void slotChangeToolBar(int index);  //C++端更新工具栏(js调用)

private:
	QString m_curDir;
};

#endif // QCHANNEL_H
