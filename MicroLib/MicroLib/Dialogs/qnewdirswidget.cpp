#include "qnewdirswidget.h"

QNewDirsWidget::QNewDirsWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(420, 260);
	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
	connect(ui.btnNext, &QToolButton::clicked, [=](){
		emit sigNextClicked();
	});
}

QNewDirsWidget::~QNewDirsWidget()
{

}

QString QNewDirsWidget::getFileName()
{
	return ui.edtNewDir->text();
}

QString QNewDirsWidget::getComment()
{
	return ui.edtText->toPlainText();
}