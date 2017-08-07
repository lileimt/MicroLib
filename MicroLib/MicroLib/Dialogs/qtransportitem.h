#ifndef QTRANSPORTITEM_H
#define QTRANSPORTITEM_H

#include <QTime>
#include "Base/qbasewidget.h"
#include "ui_transportitem.h"
#include "Common/common.h"
#include "Net/qdownloadnetworkmanager.h"

#define UNIT_KB 1024
#define UNIT_MB 1024*1024
#define UNIT_GB 1024*1024*1024

#define TIME_INTERVAL 800

class QTransportItem : public QBaseWidget
{
	Q_OBJECT

public:
	QTransportItem(FILETRANSPORT *stFileTransport,bool bFirst = false,QWidget *parent = 0);
	~QTransportItem();

	QString transformUnit(qint64 bytes, bool isSpeed = false);
	QString getStorageHost(QString md5);
	int getId();
public slots:
	void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void onReplyFinished(int statusCode);

	void slotStatus();
signals:
	void sigStatusClicked();
	void sigCloseClicked();
	void sigDownloadFinished(int id);
private:
	Ui::QTransportItem ui;
	QDownloadNetworkManager *m_downloadManager;
	QTime m_recordTime;
	qint64 m_timeInterval;
	qint64 m_intervalDownload;
	qint64 m_currentDownload;
	FILETRANSPORT *m_stFileTransport;

	void startDownload(QString url, QString fileName);
	void stopDownload();
	void closeDownload();
};

#endif // QTRANSPORTITEM_H
