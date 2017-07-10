#ifndef QLOGUSERWIDGET_H
#define QLOGUSERWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_loguserwidget.h"
#include "Common/common.h"

class QLogUserWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QLogUserWidget(USERLOGITEM logItem, QWidget *parent = 0);
	~QLogUserWidget();

private:
	Ui::QLogUserWidget ui;
};

#endif // QLOGUSERWIDGET_H
