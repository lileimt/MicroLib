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
	int getId();
	void setNewDir();
	void setNewCommonDir(int id, QString fileName, int permission);
	void setToken(QString token);
	void setCurType(int type);
	void setCurFiles();  //�����źŻ�ȡ�����ļ���Ϣ
	void deleteFiles();
signals:
	void sigToken(QString token);
	void sigCurType(int type);  //���õ�ǰ�ǹ���Ŀ¼�����ҵ��ļ�
	void sigNewDir();   //js���½��ļ���(��js�¼�)
	void sigNewCommonDir(int id,QString fileName,int permission);
	void sigCurFiles();    //js�˻�ȡ��ǰѡ����Ҫ���ص��ļ�
	void sigDeleteFiles(); //js�˴���ɾ������

	//C++�ź�
	void sigChangeToolBar(int index);  //���źŸı乤����
	void sigStartDownload(QString curFiles);//��ȡ����ǰѡ�е��ļ���Ϣ��ʼ����
	void sigSendFiles(QString ids);
	void sigShowSideBar(bool visible);
	void sigDeleteEnable(bool enable);
public slots :
	void slotCurDir(int id,QString curDir);   //C++�˸��µ�ǰ·��(js����)
	void slotChangeToolBar(int index);  //C++�˸��¹�����(js����)
	void slotCurFiles(QString curFiles);  //C++�˻�ȡ��Ҫ���ص��ļ���Ϣ(js����)
	void slotSendFiles(QString ids);//C++�˻�ȡ
	void slotSideBar(bool bVisible); //C++����ʾ�������Ҳ������js���ã�
	void slotDeleteEnable(bool enable); //C++��ɾ����ť�Ƿ�ɵ����js���ã�
private:
	QString m_curDir;
	int m_id;
};

#endif // QCHANNEL_H
