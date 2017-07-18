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

	void insertList(FILETRANSPORT &st);
signals:
	void sigMinClicked();
private:
	Ui::QTransportWidget ui;
	QBaseTitleWidget *m_titleWidget;
	QVBoxLayout *m_pLayout;
	TRANSLIST m_transList;
	QListWidget *m_listWidget; 
	QTransportItem *m_pHeader;

	void addItem(QTransportItem *pItem);
	void showList();
	void clearList();
};

#endif // QTRANSPORTWIDGET_H
