#ifndef QPARSEJSON_H
#define QPARSEJSON_H

#include <QObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "Common/quser.h"
#include "Common/common.h"
#include "Dialogs/qsendwidget.h"
#include "Dialogs/qnewdirsnextwidget.h"

using namespace  std;

class QParseJson : public QObject
{
	Q_OBJECT

public:
	QParseJson(QObject *parent = 0);
	~QParseJson();

	//用户名和密码组成json
	QString getUserJsonParams(QString username, QString password);
	//解析用户信息
	void getUserInfo(string data, QUser *user);
	//解析返回的用户信息json
	void parseUserJson(QJsonObject obj, QUser *user);
	//解析返回的token
	void parseTokenJson(QJsonObject obj);
	//解析从js传过来的下载文件json
	void parseDownloadJson(string data, QList<FILETRANSPORT *> &transList);
	//解析发送的文件的id
	QJsonArray parseSendFileId(QString ids);
	//创建发送文件的json对象
	QString getSendFileJson(QSendWidget *widget, QJsonArray ids, QString comment);
	//解析下载文件存放路径的url
	QString parseHostJson(string data,int &baseId);
	//创建公共目录
	QString getCreateDocumentJson(int pid, QString filename, QListWidget *pWidget,ItemList map, QString comment, int notice, QString msg="");
private:
	QString m_token;
};

#endif // QPARSEJSON_H
