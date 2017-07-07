#include "qstaticswidget.h"

QStaticsWidget::QStaticsWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(560, 420);
	ui.treeWidget->expandToDepth(0);

	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
}

QStaticsWidget::~QStaticsWidget()
{

}
