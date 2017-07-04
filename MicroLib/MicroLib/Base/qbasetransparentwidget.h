#ifndef QBASETRANSPARENTWIDGET_H
#define QBASETRANSPARENTWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_basetransparentwidget.h"

class QBaseTransparentWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QBaseTransparentWidget(QWidget *parent = 0);
	~QBaseTransparentWidget();

private:
	Ui::QBaseTransparentWidget ui;
};

#endif // QBASETRANSPARENTWIDGET_H
