#include "qsubtranswidget.h"

QSubTransWidget::QSubTransWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(202, 36);
}

QSubTransWidget::~QSubTransWidget()
{

}

void QSubTransWidget::setText(QString text)
{
	ui.lblText->setText(text);
}

void QSubTransWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton){
		hide();
		emit clicked();
	}else{
		QWidget::mousePressEvent(event);
	}
}