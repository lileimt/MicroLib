#include "qtitlewidget.h"

QTitleWidget::QTitleWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(966, 72);
	ui.lblIcon->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblTitle->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblUser->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnUser->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnFiles->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnShare->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnSet->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnMin->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnClose->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnDang->setAttribute(Qt::WA_TranslucentBackground);

	ui.lblUser->setPixmap(QPixmap(":/images/ming"));
}

QTitleWidget::~QTitleWidget()
{

}
