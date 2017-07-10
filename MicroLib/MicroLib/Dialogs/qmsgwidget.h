#ifndef QMSGWIDGET_H
#define QMSGWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_msgwidget.h"
#include "Dialogs/qmsgitem.h"

class QMsgWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QMsgWidget(QWidget *parent = 0);
	~QMsgWidget();

	void addItem(QListWidget *pListWidget, QMsgItem *pWidget);
private:
	Ui::QMsgWidget ui;
};

#endif // QMSGWIDGET_H
