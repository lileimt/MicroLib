#include "qtransportitem.h"

QTransportItem::QTransportItem(FILETRANSPORT *stFileTransport, bool bFirst, QWidget *parent)
: QBaseWidget(parent),
m_downloadManager(NULL),
m_timeInterval(0),
m_intervalDownload(0),
m_currentDownload(0)
{
	ui.setupUi(this);
	m_stFileTransport = stFileTransport;

	if (!bFirst){
		ui.lblOperation->setVisible(false);
		setStyleSheet("QLabel{color:#000000;font: 12pt Î¢ÈíÑÅºÚ;}"
			"QToolButton{border:none;}");

		if (stFileTransport->state == upload){
			ui.lblPix->setPixmap(QPixmap(":/images/uploadt"));
		}
		else{
			ui.lblPix->setPixmap(QPixmap(":/images/downloadt"));
		}

		ui.lblIcon->setPixmap(QPixmap(stFileTransport->fileIcon));
		ui.lblName->setText(stFileTransport->fileName);

		//if (stFileTransport->status == normal){
		//	ui.lblStatus->setPixmap(QPixmap(":/images/ok"));
		//}else if (stFileTransport->status == pause){
		//	ui.lblStatus->setPixmap(QPixmap(":/images/pause"));
		//}else{
		//	ui.lblStatus->setPixmap(QPixmap(":/images/error"));
		//}

		ui.lblSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.lblSize->setText(stFileTransport->fileSize);
		ui.lblPath->setAlignment(Qt::AlignCenter);
		ui.lblPath->setText(stFileTransport->filePath);
		stFileTransport->status = normal;
		ui.btnStatus->setIcon(QIcon(":/images/pause"));
		ui.btnOperate->setIcon(QIcon(":/images/filedelete"));
	}
	else{
		ui.lblName->move(ui.lblIcon->pos().x(), 0);
		ui.lblPix->setVisible(false);
		ui.lblIcon->setVisible(false);
		ui.btnStatus->setVisible(false);
		ui.btnOperate->setVisible(false);
		ui.lblSize->setAlignment(Qt::AlignCenter);
		ui.lblPath->setAlignment(Qt::AlignCenter);
		setStyleSheet("QTransportItem{background:white;}"
			"QLabel{color:#858585;font: 14pt Î¢ÈíÑÅºÚ;}"
			"QToolButton{border:none;}");
	}
	connect(ui.btnStatus, SIGNAL(clicked()), this, SLOT(slotStatus()));
}

QTransportItem::~QTransportItem()
{

}

void QTransportItem::onStartDownload(QString url, QString fileName)
{
	if (m_downloadManager == NULL){
		m_downloadManager = new QDownloadNetworkManager(this);
		connect(m_downloadManager, SIGNAL(sigDownloadProgress(qint64, qint64)), this, SLOT(onDownloadProgress(qint64,qint64)));
		connect(m_downloadManager, SIGNAL(sigReplyFinished(int)), this,SLOT(onReplyFinished(int)));
	}

	m_downloadManager->downloadFile(url, fileName);
	m_recordTime.start();
	m_timeInterval = 0;
}

void QTransportItem::onStopDownload()
{
	if (m_downloadManager == NULL){
		m_downloadManager->stopDownload();
	}
}

void QTransportItem::onCloseDownload()
{
	m_downloadManager->closeDownload();
}

void QTransportItem::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	m_intervalDownload += bytesReceived - m_currentDownload;
	m_currentDownload = bytesReceived;

	uint timeNow = m_recordTime.elapsed();
	if (timeNow - m_timeInterval > TIME_INTERVAL){
		qint64 isSpeed = m_intervalDownload * 100 / (timeNow - m_timeInterval);
		QString strSpeed = transformUnit(m_intervalDownload, true);
		QString strCurrent = transformUnit(m_currentDownload);

		QString text = strSpeed + "/" + strCurrent;
		ui.lblStatus->setText(text);

		m_intervalDownload = 0;
		m_timeInterval = timeNow;
	}
}

void QTransportItem::onReplyFinished(int statusCode)
{
	if (statusCode > 200 && statusCode < 400){
		qDebug() << "error";
	}else{
		qDebug() << "success";
	}
}

QString QTransportItem::transformUnit(qint64 bytes, bool isSpeed)
{
	QString strUnit = "B";
	if (bytes < 0){
		bytes = 0;
	}else if (bytes < UNIT_KB){

	}
	else if (bytes < UNIT_MB){
		bytes /= UNIT_KB;
		strUnit = "KB";
	}
	else if(bytes < UNIT_GB){
		bytes /= UNIT_MB;
		strUnit = "MB";
	}
	else{
		bytes /= UNIT_GB;
		strUnit = "GB";
	}

	if (isSpeed){
		strUnit += "/s";
	}

	return QString("%1 %2").arg(bytes).arg(strUnit);
}

void QTransportItem::slotStatus()
{
	if (m_stFileTransport->state == download){
		if (m_stFileTransport->status == normal){
			m_stFileTransport->status = pause;
			ui.btnStatus->setIcon(QIcon(":/images/start"));
		}
		else{
			m_stFileTransport->status = normal;
			ui.btnStatus->setIcon(QIcon(":/images/pause"));
		}
		onStartDownload(m_stFileTransport->url, m_stFileTransport->fileName);
	}
}