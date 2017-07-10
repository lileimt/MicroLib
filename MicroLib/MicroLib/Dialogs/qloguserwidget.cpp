#include "qloguserwidget.h"

QLogUserWidget::QLogUserWidget(USERLOGITEM logItem, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(250, 105);
	ui.lblUserImage->setPixmap(logItem.userImage);
	if (logItem.state == 0){
		ui.lblIcon->setPixmap(QPixmap(":/images/add"));
		ui.lblPrompt->setText(QStringLiteral("新建了文件(夹)"));
	}else{
		ui.lblIcon->setPixmap(QPixmap(":/images/uploading"));
		ui.lblPrompt->setText(QStringLiteral("上传了文件(夹)"));
	}
	ui.lblUserName->setText(logItem.userName);
	ui.lblFileName->setText(logItem.fileName);
	ui.lblFileIcon->setPixmap(QPixmap(logItem.fileIcon));
	ui.lblTime->setText(logItem.time);
}

QLogUserWidget::~QLogUserWidget()
{

}
