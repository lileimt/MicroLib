#include "qbasetreewidget.h"

QBaseTreeWidget::QBaseTreeWidget(QWidget *parent)
	: QTreeWidget(parent)
{
}

QBaseTreeWidget::~QBaseTreeWidget()
{

}

QTreeWidgetItem *QBaseTreeWidget::addTreeRoot(QStringList list)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(list);
	addTopLevelItem(item);
	return item;
}

QTreeWidgetItem *QBaseTreeWidget::addTreeNode(QTreeWidgetItem *parent, QStringList list)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(list);
	parent->addChild(item);
	return item;
}