#ifndef QFORWARDWIDGET_H
#define QFORWARDWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_forwardwidget.h"

class QForwardWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QForwardWidget(QWidget *parent = 0);
	~QForwardWidget();

private:
	Ui::QForwardWidget ui;
};

#endif // QFORWARDWIDGET_H
