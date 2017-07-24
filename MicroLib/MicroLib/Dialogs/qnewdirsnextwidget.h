#ifndef QNEWDIRSNEXTWIDGET_H
#define QNEWDIRSNEXTWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_newdirsnextwidget.h"
#include "Common/quser.h"

class QNewDirsNextWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QNewDirsNextWidget(QWidget *parent = 0, QUser *user = NULL);
	~QNewDirsNextWidget();
signals:
	void sigCloseClicked();
	void sigBackClicked();
	void sigCreateClicked();
private:
	Ui::QNewDirsNextWidget ui;
	QUser *m_user;

	void setTreeWidget();
};

#endif // QNEWDIRSNEXTWIDGET_H
