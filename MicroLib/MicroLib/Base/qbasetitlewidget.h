#ifndef QBASETITLEWIDGET_H
#define QBASETITLEWIDGET_H

#include "qbasewidget.h"
#include "ui_basetitlewidget.h"

class QBaseTitleWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QBaseTitleWidget(QString strTitle,bool bShowMin = false,QWidget *parent = 0);
	~QBaseTitleWidget();

signals:
	void sigMinClicked();
	void sigCloseClicked();
private:
	Ui::QBaseTitleWidget ui;
};

#endif // QBASETITLEWIDGET_H
