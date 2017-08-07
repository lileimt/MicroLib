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

	//�û������������json
	QString getUserJsonParams(QString username, QString password);
	//�����û���Ϣ
	void getUserInfo(string data, QUser *user);
	//�������ص��û���Ϣjson
	void parseUserJson(QJsonObject obj, QUser *user);
	//�������ص�token
	void parseTokenJson(QJsonObject obj);
	//������js�������������ļ�json
	void parseDownloadJson(string data, QList<FILETRANSPORT *> &transList);
	//�������͵��ļ���id
	QJsonArray parseSendFileId(QString ids);
	//���������ļ���json����
	QString getSendFileJson(QSendWidget *widget, QJsonArray ids, QString comment);
	//���������ļ����·����url
	QString parseHostJson(string data,int &baseId);
	//��������Ŀ¼
	QString getCreateDocumentJson(int pid, QString filename, QListWidget *pWidget,ItemList map, QString comment, int notice, QString msg="");
private:
	QString m_token;
};

#endif // QPARSEJSON_H
