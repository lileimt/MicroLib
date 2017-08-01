#include "qsendwidget.h"

QSendWidget::QSendWidget(QWidget *parent, QUser *user,int count)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	ui.listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_user = user;

	setTreeWidget(m_user, NULL, true);
	ui.treeWidget->expandAll();

	QString content = QStringLiteral("%1¸öÎÄ¼þ").arg(count);
	ui.lblContent->setText(content);

	connect(ui.btnClose, SIGNAL(clicked()), this, SIGNAL(sigCloseClicked()));
	connect(ui.btnOk, SIGNAL(clicked()), this, SIGNAL(sigOKClicked()));
	connect(ui.btnArrow, &QToolButton::clicked, [=](){
		QTreeWidgetItem *curItem = ui.treeWidget->currentItem();
		QString username = curItem->text(0);
		int id = curItem->text(1).toInt();
		if (m_ids.contains(id)){
			return;
		}
		QListItem *item = new QListItem(username, id, 2);
		addItem(id,item);
	});
}

QSendWidget::~QSendWidget()
{

}

void QSendWidget::setTreeWidget(QUser *pUser, QTreeWidgetItem *parent, bool top)
{
	USERLIST children = pUser->getChildren();
	auto it = children.begin();
	for (; it != children.end(); it++){
		QUser *user = *it;
		QTreeWidgetItem *pItem = NULL;
		QStringList list;
		list << user->getName() << QString::number(user->getId());
		if (top){
			pItem = ui.treeWidget->addTreeRoot(list);
		}
		else{
			pItem = ui.treeWidget->addTreeNode(parent, list);
		}
		if (user->getType() == "depart"){
			setTreeWidget(user, pItem);
		}
	}
}

void QSendWidget::addItem(int id,QListItem *pItem)
{
	QListWidgetItem *aItem = new QListWidgetItem(ui.listWidget);
	QSize size = pItem->size();
	aItem->setSizeHint(QSize(pItem->width() - 6, pItem->height()));
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, pItem);
	m_ids.insert(id, aItem);

	connect(pItem, &QListItem::sigCancelClicked, [=](int id){
		ItemList::iterator it = m_ids.find(id);
		ui.listWidget->removeItemWidget(it.value());
		delete it.value();
		m_ids.remove(id);
	});
}