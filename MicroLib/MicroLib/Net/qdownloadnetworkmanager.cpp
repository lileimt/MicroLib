#include "qdownloadnetworkmanager.h"

QDownloadNetworkManager::QDownloadNetworkManager(QObject *parent)
	: QObject(parent),
	m_networkManager(NULL),
	m_url(QUrl("")),
	m_fileName(""),
	m_bytesReceived(0),
	m_bytesTotal(0),
	m_bytesCurrentReceived(0),
	m_isStop(true)
{
	m_networkManager = new QNetworkAccessManager(this);
}

QDownloadNetworkManager::~QDownloadNetworkManager()
{

}

void QDownloadNetworkManager::downloadFile(QString url, QString fileName)
{
	if (m_isStop){
		m_isStop = false;
		m_url = QUrl(url);

		m_fileName = fileName + DOWNLOAD_FILE_SUFFIX;
		if (m_bytesCurrentReceived <= 0){
			removeFile(m_fileName);
		}

		QNetworkRequest request;
		request.setUrl(m_url);

		//¶ÏµãÐø´«
		QString strRange = QString("bytes=%1-").arg(m_bytesCurrentReceived);
		request.setRawHeader("Range",strRange.toLatin1());

		m_reply = m_networkManager->get(request);
		connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
		connect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
		connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
	}
}

void QDownloadNetworkManager::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (!m_isStop){
		m_bytesReceived = bytesReceived;
		m_bytesTotal = bytesTotal;

		emit sigDownloadProgress(m_bytesReceived + m_bytesCurrentReceived, m_bytesTotal + m_bytesCurrentReceived);
	}
}

void QDownloadNetworkManager::onReadyRead()
{
	if (!m_isStop){
		QFile file(m_fileName);
		if (file.open(QIODevice::WriteOnly | QIODevice::Append)){
			file.write(m_reply->readAll());
		}
		file.close();
	}
}

void QDownloadNetworkManager::onFinished()
{
	m_isStop = true;
	QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	if (m_reply->error() == QNetworkReply::NoError){
		QFileInfo fileInfo(m_fileName);
		if (fileInfo.exists()){
			int index = m_fileName.lastIndexOf(DOWNLOAD_FILE_SUFFIX);
			QString realName = m_fileName.left(index);
			QFile::rename(m_fileName, realName);
		}
	}else{
		QString strError = m_reply->errorString();
	}
	emit sigReplyFinished(statusCode.toInt());
}

void QDownloadNetworkManager::onError(QNetworkReply::NetworkError)
{
	QString strError = m_reply->errorString();

	closeDownload();
	emit sigDownloadError();
}

void QDownloadNetworkManager::stopWork()
{
	m_isStop = true;
	if (m_reply != NULL){
		disconnect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64, qint64)));
		disconnect(m_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
		disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
		m_reply->abort();
		m_reply->deleteLater();
		m_reply = NULL;
	}
}

void QDownloadNetworkManager::stopDownload()
{
	if (!m_isStop){
		m_bytesCurrentReceived += m_bytesReceived;
		stopWork();
	}
}

void QDownloadNetworkManager::reset()
{
	m_bytesCurrentReceived = 0;
	m_bytesReceived = 0;
	m_bytesTotal = 0;
}

void QDownloadNetworkManager::removeFile(QString fileName)
{
	QFileInfo fileInfo(fileName);
	if (fileInfo.exists()){
		QFile::remove(fileName);
	}
}

void QDownloadNetworkManager::closeDownload()
{
	stopWork();
	reset();
	removeFile(m_fileName);
}