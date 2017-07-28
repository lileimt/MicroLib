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
	void setCurFiles();  //�����źŻ�ȡ�����ļ���Ϣ
signals:
	void sigToken(QString token);
	void sigCurType(int type);  //���õ�ǰ�ǹ���Ŀ¼�����ҵ��ļ�
	void sigNewDir();   //js���½��ļ���(��js�¼�)
	void sigChangeToolBar(int index);  //���źŸı乤����
	void sigCurFiles();    //js�˻�ȡ��ǰѡ����Ҫ���ص��ļ�

	void sigStartDownload(QString curFiles);//��ȡ����ǰѡ�е��ļ���Ϣ��ʼ����
public slots :
	void slotCurDir(QString curDir);   //C++�˸��µ�ǰ·��(js����)
	void slotChangeToolBar(int index);  //C++�˸��¹�����(js����)
	void slotCurFiles(QString curFiles);  //C++�˻�ȡ��Ҫ���ص��ļ���Ϣ(js����)
private:
	QString m_curDir;
};

#endif // QCHANNEL_H
