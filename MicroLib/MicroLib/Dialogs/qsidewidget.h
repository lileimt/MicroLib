#ifndef QSIDEWIDGET_H
#define QSIDEWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_sidewidget.h"
#include "Dialogs/qloguserwidget.h"

class QSideWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QSideWidget(QWidget *parent = 0);
	~QSideWidget();
	
	void addItem(QLogUserWidget *pWidget);
private:
	Ui::QSideWidget ui;
};

#endif // QSIDEWIDGET_H
