#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_titlewidget.h"

class QTitleWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QTitleWidget(QWidget *parent = 0);
	~QTitleWidget();

private:
	Ui::QTitleWidget ui;
};

#endif // QTITLEWIDGET_H
