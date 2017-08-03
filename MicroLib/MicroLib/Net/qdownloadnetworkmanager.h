#ifndef QDOWNLOADNETWORKMANAGER_H
#define QDOWNLOADNETWORKMANAGER_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#define DOWNLOAD_FILE_SUFFIX "_tmp"

class QDownloadNetworkManager : public QObject
{
	Q_OBJECT

public:
	QDownloadNetworkManager(QObject *parent);
	~QDownloadNetworkManager();

	void downloadFile(QString url, QString fileName);
	void stopWork();
	void stopDownload();
	void reset();
	void removeFile(QString fileName);
	void closeDownload();

public slots:
	void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void onReadyRead();
	void onFinished();
	void onError(QNetworkReply::NetworkError);

signals:
	void sigDownloadProgress(qint64, qint64);
	void sigReplyFinished(int);
	void sigDownloadError();
private:
	QNetworkAccessManager *m_networkManager;
	QNetworkReply *m_reply;
	QUrl m_url;
	QString m_fileName;
	qint64 m_bytesReceived;
	qint64 m_bytesTotal;
	qint64 m_bytesCurrentReceived;
	bool m_isStop;
};

#endif // QDOWNLOADNETWORKMANAGER_H
