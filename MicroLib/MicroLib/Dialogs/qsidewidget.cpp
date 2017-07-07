#include "qsidewidget.h"

QSideWidget::QSideWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(250, 520);
}

QSideWidget::~QSideWidget()
{

}
