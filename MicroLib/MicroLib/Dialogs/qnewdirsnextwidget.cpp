#include "qnewdirsnextwidget.h"

QNewDirsNextWidget::QNewDirsNextWidget(QWidget *parent, QUser *user)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	m_user = user;
	setTreeWidget();

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

void QNewDirsNextWidget::setTreeWidget()
{

}