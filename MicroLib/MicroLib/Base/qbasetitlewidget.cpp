#include "qbasetitlewidget.h"

QBaseTitleWidget::QBaseTitleWidget(QString strTitle, bool bShowMin, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedHeight(30);
	ui.lblTitle->setText(strTitle);
	ui.btnMin->setVisible(bShowMin);
	connect(ui.btnMin, &QToolButton::clicked, [=](){
		emit sigMinClicked();
	});
	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
}

QBaseTitleWidget::~QBaseTitleWidget()
{

}
