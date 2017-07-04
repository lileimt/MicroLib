#ifndef QTRANSPORTWIDGET_H
#define QTRANSPORTWIDGET_H

#include "Base/qbasewidget.h"
#include "Base/qbasetitlewidget.h"
#include "ui_transportwidget.h"
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QListWidget>
#include "Dialogs/qtransportitem.h"

typedef QList<FILETRANSPORT> TRANSLIST;

class QTransportWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QTransportWidget(QString strTitle, bool bShowMin = false, QWidget *parent = 0);
	~QTransportWidget();

private:
	Ui::QTransportWidget ui;
	QBaseTitleWidget *m_titleWidget;
	QVBoxLayout *m_pLayout;
	TRANSLIST m_transList;
	QListWidget *m_listWidget;

	void addItem(QTransportItem *pItem);
	void showList();
};

#endif // QTRANSPORTWIDGET_H
