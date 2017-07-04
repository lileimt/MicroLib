#include "qbasetransparentwidget.h"

QBaseTransparentWidget::QBaseTransparentWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground, true);
}

QBaseTransparentWidget::~QBaseTransparentWidget()
{

}
