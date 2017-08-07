#include "qchannel.h"
#include <QMessageBox>
#include <QDebug>

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

void QChannel::slotCurDir(int id, QString curDir)
{
	m_id = id;
	m_curDir = curDir;
}

void QChannel::setNewDir()
{
	emit sigNewDir();
}

void QChannel::setNewCommonDir(int id, QString fileName, int permission)
{
	emit sigNewCommonDir(id, fileName, permission);
}

void QChannel::setToken(QString token)
{
	emit sigToken(token);
}
//公共目录还是我的文件
void QChannel::setCurType(int type)
{
	emit sigCurType(type);
}
void QChannel::setCurFiles()
{
	emit sigCurFiles();
}
void QChannel::deleteFiles()
{
	emit sigDeleteFiles();
}

void QChannel::slotChangeToolBar(int index)
{
	emit sigChangeToolBar(index);
}

//js调用开始下载
void QChannel::slotCurFiles(QString curFiles){
	qDebug() << curFiles;
	emit sigStartDownload(curFiles);
}

void QChannel::slotSendFiles(QString ids)
{
	qDebug() << ids;
	emit sigSendFiles(ids);
}

void QChannel::slotSideBar(bool bVisible)
{
	emit sigShowSideBar(bVisible);
}

void QChannel::slotDeleteEnable(bool enable)
{
	emit sigDeleteEnable(enable);
}

int QChannel::getId()
{
	return m_id;
}