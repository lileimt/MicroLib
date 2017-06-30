#include "qsearchwidget.h"

QSearchWidget::QSearchWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(212, 28);
}

QSearchWidget::~QSearchWidget()
{

}

void QSearchWidget::setPlaceholderText(QString text)
{
	ui.edtSearch->setPlaceholderText(text);
}
