#ifndef QTRANSPORTITEM_H
#define QTRANSPORTITEM_H

#include "Base/qbasewidget.h"
#include "ui_transportitem.h"
#include "Common/common.h"

class QTransportItem : public QBaseWidget
{
	Q_OBJECT

public:
	QTransportItem(FILETRANSPORT &stFileTransport,bool bFirst = false,QWidget *parent = 0);
	~QTransportItem();

private:
	Ui::QTransportItem ui;
};

#endif // QTRANSPORTITEM_H
