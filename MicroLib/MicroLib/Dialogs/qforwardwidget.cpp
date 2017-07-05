#include "qforwardwidget.h"

QForwardWidget::QForwardWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
	connect(ui.btnNew, &QToolButton::clicked, [=](){
		QTreeWidgetItem *item = ui.treeWidget->currentItem();
		if (item == NULL)return;
		addNode(item, QStringLiteral("�½��ļ���"));
	});

	QTreeWidgetItem *topItem = addRoot(QStringLiteral("�ҵ��ļ�"));
	addNode(topItem, QStringLiteral("�ҵ��ļ�"));

	ui.treeWidget->expandAll();
}

QForwardWidget::~QForwardWidget()
{

}

QTreeWidgetItem *QForwardWidget::addRoot(QString text)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget);
	item->setIcon(0, QIcon(":/filetype/dir"));
	//item->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
	item->setText(0, text);
	ui.treeWidget->addTopLevelItem(item);
	return item;
}

QTreeWidgetItem *QForwardWidget::addNode(QTreeWidgetItem *parent, QString text)
{
	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setIcon(0, QIcon(":/filetype/dir"));
	item->setText(0, text);
	parent->addChild(item);
	return item;
}