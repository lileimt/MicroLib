#include "qtransportitem.h"

QTransportItem::QTransportItem(FILETRANSPORT &stFileTransport, bool bFirst, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	if (!bFirst){
		ui.lblOperation->setVisible(false);
		setStyleSheet("QLabel{color:#000000;}");

		if (stFileTransport.state){
			ui.lblPix->setPixmap(QPixmap(":/images/uploadt"));
		}else{
			ui.lblPix->setPixmap(QPixmap(":/images/downloadt"));
		}

		ui.lblIcon->setPixmap(QPixmap(stFileTransport.fileIcon));
		ui.lblName->setText(stFileTransport.fileName);

		if (stFileTransport.status == 0){
			ui.lblStatus->setPixmap(QPixmap(":/images/ok"));
		}else if (stFileTransport.status == 1){
			ui.lblStatus->setPixmap(QPixmap(":/images/pause"));
		}else{
			ui.lblStatus->setPixmap(QPixmap(":/images/error"));
		}

		ui.lblSize->setText(stFileTransport.fileSize);
		ui.lblPath->setText(stFileTransport.filePath);
		ui.btnStatus->setIcon(QIcon(":/images/pause"));
		ui.btnOperate->setIcon(QIcon(":/images/filedelete"));
	}else{
		ui.lblPix->setVisible(false);
		ui.lblIcon->setVisible(false);
		ui.btnStatus->setVisible(false);
		ui.btnOperate->setVisible(false);
		setStyleSheet("QLabel{color:#858585;}");
	}
}

QTransportItem::~QTransportItem()
{

}
