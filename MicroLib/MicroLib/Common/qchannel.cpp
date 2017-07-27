#include "qchannel.h"
#include <QMessageBox>


QChannel::QChannel(QObject *parent)
	: QObject(parent)
{

}

QChannel::~QChannel()
{

}

QString QChannel::getCurDir()
{
	return m_curDir;
}

void QChannel::slotCurDir(QString curDir)
{
	m_curDir = curDir;
}

void QChannel::setNewDir()
{
	emit sigNewDir();
}
void QChannel::setToken(QString token)
{
	emit sigToken(token);
}
//����Ŀ¼�����ҵ��ļ�
void QChannel::setCurType(int type)
{
	emit sigCurType(type);
}

void QChannel::slotChangeToolBar(int index)
{
	emit sigChangeToolBar(index);
}