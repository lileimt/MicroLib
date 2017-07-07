#ifndef QNEWDIRSWIDGET_H
#define QNEWDIRSWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_newdirswidget.h"

class QNewDirsWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QNewDirsWidget(QWidget *parent = 0);
	~QNewDirsWidget();
signals:
	void sigCloseClicked();
private:
	Ui::QNewDirsWidget ui;
};

#endif // QNEWDIRSWIDGET_H
