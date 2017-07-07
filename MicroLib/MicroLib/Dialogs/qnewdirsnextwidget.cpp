#include "qnewdirsnextwidget.h"

QNewDirsNextWidget::QNewDirsNextWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
	connect(ui.btnBack, &QToolButton::clicked, [=](){
		emit sigBackClicked();
	});
	connect(ui.btnCreate, &QToolButton::clicked, [=](){
		emit sigCreateClicked();
	});
}

QNewDirsNextWidget::~QNewDirsNextWidget()
{

}
