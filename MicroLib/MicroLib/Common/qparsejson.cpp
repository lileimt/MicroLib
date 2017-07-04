#include "qparsejson.h"
#include <QDebug>

QParseJson::QParseJson(QObject *parent)
	: QObject(parent)
{

}

QParseJson::~QParseJson()
{

}

QString QParseJson::getUserJsonParams(QString username, QString password)
{
	QJsonObject json;
	json.insert("username", username);
	json.insert("password", password);

	QJsonDocument document;
	document.setObject(json);
	QByteArray byte_array = document.toJson(QJsonDocument::Compact);
	return QString(byte_array);
}

//QJsonParseError json_error;
//QJsonDocument parse_doucment = QJsonDocument::fromJson(str.data(), &json_error);
//if (json_error.error == QJsonParseError::NoError)
//{
//	qDebug() << str.data();
//	if (parse_doucment.isObject()){
//		QJsonObject obj = parse_doucment.object();
//		parseUserJson(obj, m_user);
//	}
//}
void QParseJson::parseUserJson(QJsonObject obj, QUser *user)
{
	if (obj.contains("children")){
		QJsonValue arrays_value = obj.take("children");
		if (arrays_value.isArray()){//判断他是不是json数组  
			QJsonArray arrays = arrays_value.toArray();
			qDebug() << "size = " << arrays.size();
			for (int i = 0; i < arrays.size(); i++){
				QJsonObject childObj = arrays.at(i).toObject();
				QUser *childUser = new QUser;
				if (childObj.contains("id")){
					QJsonValue value = childObj.take("id");
					if (value.isDouble()){
						qDebug() << "id" << value.toVariant().toInt();
						childUser->setId(value.toVariant().toInt());
					}
				}
				if (childObj.contains("name")){
					QJsonValue value = childObj.take("name");
					if (value.isString()){
						qDebug() << "name" << value.toString();
						childUser->setName(value.toString());
					}
				}
				if (childObj.contains("type")){
					QJsonValue value = childObj.take("type");
					if (value.isString()){
						qDebug() << "type" << value.toString();
						childUser->setType(value.toString());
					}
				}
				if (childObj.contains("children")){
					qDebug() << "children";
					parseUserJson(childObj, childUser);
				}
				user->append(childUser);
			}
		}
	}
}

void QParseJson::parseTokenJson(QJsonObject obj)
{
	if (obj.contains("access_token")){
		QJsonValue value = obj.take("access_token");
		if (value.isString()){
			qDebug() << "access_token" << value.toString();
			m_token = value.toString();
		}
	}
	if (obj.contains("user_id")){
		QJsonValue value = obj.take("user_id");
		if (value.toDouble()){
			qDebug() << "user_id" << value.toInt();
		}
	}
}