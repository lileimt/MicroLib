#ifndef QLISTITEM_H
#define QLISTITEM_H

#include "Base/qbasewidget.h"
#include "ui_listitem.h"

class QListItem : public QBaseWidget
{
	Q_OBJECT

public:
	QListItem(QString user,int id,int type,QWidget *parent = 0);
	~QListItem();

signals:
	void sigCancelClicked(int id);
private:
	Ui::QListItem ui;
	int m_id;
};

#endif // QLISTITEM_H
