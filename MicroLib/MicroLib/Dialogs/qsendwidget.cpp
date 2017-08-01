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

void QSendWidget::addItem(QListItem *pItem)
{
	QListWidgetItem *aItem = new QListWidgetItem(ui.listWidget);
	QSize size = pItem->size();
	aItem->setSizeHint(QSize(pItem->width() - 6, pItem->height()));
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, pItem);
}