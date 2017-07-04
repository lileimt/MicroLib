#ifndef QPARSEJSON_H
#define QPARSEJSON_H

#include <QObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "Common/quser.h"

class QParseJson : public QObject
{
	Q_OBJECT

public:
	QParseJson(QObject *parent);
	~QParseJson();

	QString getUserJsonParams(QString username, QString password);
	void parseUserJson(QJsonObject obj, QUser *user);
	void parseTokenJson(QJsonObject obj);
private:
	QString m_token;
};

#endif // QPARSEJSON_H
