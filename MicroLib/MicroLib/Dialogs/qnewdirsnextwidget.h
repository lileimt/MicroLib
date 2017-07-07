#ifndef QNEWDIRSNEXTWIDGET_H
#define QNEWDIRSNEXTWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_newdirsnextwidget.h"

class QNewDirsNextWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QNewDirsNextWidget(QWidget *parent = 0);
	~QNewDirsNextWidget();
signals:
	void sigCloseClicked();
	void sigBackClicked();
	void sigCreateClicked();
private:
	Ui::QNewDirsNextWidget ui;
};

#endif // QNEWDIRSNEXTWIDGET_H
