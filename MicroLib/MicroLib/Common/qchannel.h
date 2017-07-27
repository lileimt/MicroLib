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
	void sigCurType(int type);  //���õ�ǰ�ǹ���Ŀ¼�����ҵ��ļ�
	void sigNewDir();   //js���½��ļ���(��js�¼�)
	void sigChangeToolBar(int index);  //���źŸı乤����
public slots :
	void slotCurDir(QString curDir);   //C++�˸��µ�ǰ·��(js����)
	void slotChangeToolBar(int index);  //C++�˸��¹�����(js����)

private:
	QString m_curDir;
};

#endif // QCHANNEL_H
