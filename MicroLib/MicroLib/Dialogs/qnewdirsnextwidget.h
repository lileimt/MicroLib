#ifndef QNEWDIRSNEXTWIDGET_H
#define QNEWDIRSNEXTWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_newdirsnextwidget.h"
#include "Common/quser.h"
#include "Dialogs/qlistitem.h"

typedef QMap<int, QListWidgetItem *> ItemList;

class QNewDirsNextWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QNewDirsNextWidget(QWidget *parent = 0, QUser *user = NULL);
	~QNewDirsNextWidget();

	//获取当前选中的用户
	ItemList getSubmitter();
	QListWidget *getListWidget();
	QString getFileName();
	QString getComment();
	int getNotice();
	QString getMsg();
	void setInfo(QString fileName, QString comment);
signals:
	void sigCloseClicked();
	void sigBackClicked();
	void sigCreateClicked();
private:
	Ui::QNewDirsNextWidget ui;
	QUser *m_user;
	//QList<int> m_idList;
	ItemList m_map;
	QString m_fileName;
	QString m_comment;

	void setTreeWidget(QUser *user, QTreeWidgetItem *parent, bool top = false);
	void addItem(int id,QListItem *pItem);
};

#endif // QNEWDIRSNEXTWIDGET_H
