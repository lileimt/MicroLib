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

using namespace  std;

class QParseJson : public QObject
{
	Q_OBJECT

public:
	QParseJson(QObject *parent = 0);
	~QParseJson();

	QString getUserJsonParams(QString username, QString password);
	void getUserInfo(string data, QUser *user);
	void parseUserJson(QJsonObject obj, QUser *user);
	void parseTokenJson(QJsonObject obj);
	void parseDownloadJson(string data, QList<FILETRANSPORT> &transList);
	QJsonArray parseSendFileId(QString ids);
	QString getSendFileJson(QSendWidget *widget, QJsonArray ids, QString comment);
private:
	QString m_token;
};

#endif // QPARSEJSON_H
