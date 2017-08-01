#ifndef QSENDWIDGET_H
#define QSENDWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_sendwidget.h"
#include "Common/quser.h"
#include "Dialogs/qlistitem.h"

class QSendWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QSendWidget(QWidget *parent = 0, QUser *user = NULL, int count = 1);
	~QSendWidget();

signals:
	void sigCloseClicked();
	void sigOKClicked();
private:
	Ui::QSendWidget ui;
	QUser *m_user;

	void setTreeWidget(QUser *user, QTreeWidgetItem *parent, bool top = false);
	void addItem(QListItem *pItem);
};

#endif // QSENDWIDGET_H
