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

//typedef QList<FILETRANSPORT *> TRANSLIST;
typedef QList<QListWidgetItem *> ITEMLIST;

class QTransportWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QTransportWidget(QString strTitle, bool bShowMin = false, QWidget *parent = 0);
	~QTransportWidget();

	void insertList(FILETRANSPORT *st);
	void initTransList(QString curFiles);
signals:
	void sigMinClicked();

public slots:
	void slotUpdate(int id);
private:
	Ui::QTransportWidget ui;
	QBaseTitleWidget *m_titleWidget;
	QVBoxLayout *m_pLayout;
	//TRANSLIST m_transList;    //上传下载队列
	//TRANSLIST m_finishList;   //上传下载完成队列
	QListWidget *m_listWidget; 
	QTransportItem *m_pHeader;
	ITEMLIST m_itemList;             //上传下载队列
	ITEMLIST m_itemFinishList;    //上传下载完成队列

	void addItem(QTransportItem *pItem);
	void clearList();
};

#endif // QTRANSPORTWIDGET_H
