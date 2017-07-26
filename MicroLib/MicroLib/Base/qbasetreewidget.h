#ifndef QBASETREEWIDGET_H
#define QBASETREEWIDGET_H

#include <QTreeWidget>

class QBaseTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	QBaseTreeWidget(QWidget *parent = 0);
	~QBaseTreeWidget();

	QTreeWidgetItem *addTreeRoot(QStringList list);
	QTreeWidgetItem *addTreeNode(QTreeWidgetItem *item, QStringList list);

private:
	
};

#endif // QBASETREEWIDGET_H