#include "qparsejson.h"
#include <QVariant>
#include <QDebug>
#include "Common/common.h"
#include "Common/commonhelper.h"

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


void QParseJson::getUserInfo(string data, QUser *user)
{
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(data.data(), &json_error);
	if (json_error.error == QJsonParseError::NoError){
		//qDebug() << data.data();
		if (parse_doucment.isObject()){
			QJsonObject obj = parse_doucment.object();
			parseUserJson(obj, user);
		}
	}
}

void QParseJson::parseUserJson(QJsonObject obj, QUser *user)
{
	if (obj.contains("children")){
		QJsonValue arrays_value = obj.take("children");
		if (arrays_value.isArray()){//判断他是不是json数组  
			QJsonArray arrays = arrays_value.toArray();
			//qDebug() << "size = " << arrays.size();
			for (int i = 0; i < arrays.size(); i++){
				QJsonObject childObj = arrays.at(i).toObject();
				QUser *childUser = new QUser;
				if (childObj.contains("id")){
					QJsonValue value = childObj.take("id");
					if (value.isDouble()){
						//qDebug() << "id" << value.toVariant().toInt();
						childUser->setId(value.toVariant().toInt());
					}
				}
				if (childObj.contains("name")){
					QJsonValue value = childObj.take("name");
					if (value.isString()){
						//qDebug() << "name" << value.toString();
						childUser->setName(value.toString());
					}
				}
				if (childObj.contains("type")){
					QJsonValue value = childObj.take("type");
					if (value.isString()){
						//qDebug() << "type" << value.toString();
						childUser->setType(value.toString());
					}
				}
				if (childObj.contains("children")){
					//qDebug() << "children";
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
			//qDebug() << "access_token" << value.toString();
			m_token = value.toString();
		}
	}
	if (obj.contains("user_id")){
		QJsonValue value = obj.take("user_id");
		if (value.toDouble()){
			//qDebug() << "user_id" << value.toInt();
		}
	}
}

//解析文件下载的JSON数据
void QParseJson::parseDownloadJson(string data,QList<FILETRANSPORT> &transList)
{
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(data.data(), &json_error);
	if (json_error.error == QJsonParseError::NoError){
		if (parse_doucment.isArray()){
			QJsonArray arrValue = parse_doucment.array();
			for (int i = 0; i < arrValue.size(); i++){
				QJsonValue objValue = arrValue.at(i);
				QJsonObject obj = objValue.toObject();

				FILETRANSPORT st;		
				st.state = download;
				st.status = normal;
				if (obj.contains("id")){
					QJsonValue id = obj.take("id");
					qDebug() << id.toInt();
					st.id = id.toInt();
				}
				if (obj.contains("name")){
					QJsonValue name = obj.take("name");
					qDebug() << name.toString();
					st.fileName = name.toString();
					st.fileIcon = CommonHelper::getIconBySuffix(st.fileName);
				}
				if (obj.contains("size")){
					QJsonValue size = obj.take("size");
					st.fileSize = size.toString();
				}
				if (obj.contains("path")){
					QJsonValue path = obj.take("path");
					st.filePath = path.toString();
				}
				transList.append(st);
			}
		}
	}
}

QJsonArray QParseJson::parseSendFileId(QString ids)
{
	QJsonParseError json_error;
	QJsonDocument parse_doucment = QJsonDocument::fromJson(ids.toStdString().data(), &json_error);
	if (json_error.error == QJsonParseError::NoError){
		if (parse_doucment.isArray()){
			QJsonArray arrValue = parse_doucment.array();
			return arrValue;
		}
	}
}

QString QParseJson::getSendFileJson(QSendWidget *widget, QJsonArray ids, QString comment)
{
	QJsonArray json;
	ItemMap map = widget->getItemMap();
	ItemMap::iterator it = map.begin();
	for (; it != map.end(); it++){
		QJsonObject obj;
		int id = it.key();
		QString name = widget->getName(id);
		obj.insert("id", id);
		obj.insert("name", name);
		json.append(obj);
	}

	QJsonObject obj;
	obj.insert("ids", QJsonValue(ids));
	obj.insert("receiveIds", QJsonValue(json));
	obj.insert("comment", comment);

	QJsonDocument document;
	document.setObject(obj);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	QString strJson(byteArray);
	qDebug() << strJson;
	return strJson;
}