#ifndef QSTATICSWIDGET_H
#define QSTATICSWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_staticswidget.h"

class QStaticsWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QStaticsWidget(QWidget *parent = 0);
	~QStaticsWidget();

signals:
	void sigCloseClicked();
private:
	Ui::QStaticsWidget ui;
};

#endif // QSTATICSWIDGET_H
