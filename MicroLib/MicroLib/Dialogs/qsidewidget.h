#ifndef QSIDEWIDGET_H
#define QSIDEWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_sidewidget.h"
#include "Dialogs/qloguserwidget.h"
#include <QHBoxLayout>

class QSideWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QSideWidget(QWidget *parent = 0);
	~QSideWidget();
	
	void addItem(QLogUserWidget *pWidget);
private:
	Ui::QSideWidget ui;

	QHBoxLayout  *pLogLayout;
};

#endif // QSIDEWIDGET_H
