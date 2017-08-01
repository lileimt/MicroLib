#include "qtransportitem.h"

QTransportItem::QTransportItem(FILETRANSPORT *stFileTransport, bool bFirst, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	if (!bFirst){
		ui.lblOperation->setVisible(false);
		setStyleSheet("QLabel{color:#000000;font: 12pt Î¢ÈíÑÅºÚ;}"
							 "QToolButton{border:none;}");

		if (stFileTransport->state == upload){
			ui.lblPix->setPixmap(QPixmap(":/images/uploadt"));
		}else{
			ui.lblPix->setPixmap(QPixmap(":/images/downloadt"));
		}

		ui.lblIcon->setPixmap(QPixmap(stFileTransport->fileIcon));
		ui.lblName->setText(stFileTransport->fileName);

		if (stFileTransport->status == normal){
			ui.lblStatus->setPixmap(QPixmap(":/images/ok"));
		}else if (stFileTransport->status == pause){
			ui.lblStatus->setPixmap(QPixmap(":/images/pause"));
		}else{
			ui.lblStatus->setPixmap(QPixmap(":/images/error"));
		}

		ui.lblSize->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		ui.lblSize->setText(stFileTransport->fileSize);
		ui.lblPath->setAlignment(Qt::AlignCenter);
		ui.lblPath->setText(stFileTransport->filePath);
		ui.btnStatus->setIcon(QIcon(":/images/pause"));
		ui.btnOperate->setIcon(QIcon(":/images/filedelete"));
	}else{
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
}

QTransportItem::~QTransportItem()
{

}
