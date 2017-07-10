#include "qmsgitem.h"

QMsgItem::QMsgItem(MSGITEM item, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	if (item.type == 0){
		ui.lblImage->setPixmap(QPixmap(":/images/list"));
		ui.lblContent1->setText(QStringLiteral("收到公共目录访问邀请"));
	}else{
		ui.lblImage->setPixmap(QPixmap(":/images/recvfile"));
		ui.lblContent1->setText(QStringLiteral("收到文件"));
		ui.lblDelete->hide();
	}
	QString text = QString("%1:%2").arg(item.userName, item.fileName);
	ui.lblContent2->setText(text);
}

QMsgItem::~QMsgItem()
{

}
