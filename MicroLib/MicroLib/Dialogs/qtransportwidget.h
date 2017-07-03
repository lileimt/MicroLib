#ifndef QTRANSPORTWIDGET_H
#define QTRANSPORTWIDGET_H

#include "Base/qbasewidget.h"
#include "Base/qbasetitlewidget.h"
#include "ui_transportwidget.h"
#include <QList>
#include <QScrollArea>
#include <QVBoxLayout>
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
	QBaseWidget *m_tmpWidget;
	QScrollArea *m_scrollArea;
	QVBoxLayout *m_pLayout;
	//QVBoxLayout *m_pListLayout;
	TRANSLIST m_transList;

	void showList();
};

#endif // QTRANSPORTWIDGET_H
