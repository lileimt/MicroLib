#ifndef QMSGITEM_H
#define QMSGITEM_H

#include "Base/qbasewidget.h"
#include "ui_msgitem.h"
#include "Common/common.h"

class QMsgItem : public QBaseWidget
{
	Q_OBJECT

public:
	QMsgItem(MSGITEM item,QWidget *parent = 0);
	~QMsgItem();

private:
	Ui::QMsgItem ui;
};

#endif // QMSGITEM_H
