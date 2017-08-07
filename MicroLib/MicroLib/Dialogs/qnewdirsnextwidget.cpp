#include "qnewdirsnextwidget.h"
#include <QDebug>

QNewDirsNextWidget::QNewDirsNextWidget(QWidget *parent, QUser *user)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	ui.listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.radioButton->setChecked(true);
	m_user = user;
	setTreeWidget(m_user,NULL,true);
	ui.treeWidget->expandAll();

	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
	connect(ui.btnBack, &QToolButton::clicked, [=](){
		emit sigBackClicked();
	});
	connect(ui.btnCreate, &QToolButton::clicked, [=](){
		emit sigCreateClicked();
	});

	connect(ui.treeWidget, &QBaseTreeWidget::clicked, [=](const QModelIndex &index){
		//qDebug() << ui.treeWidget->currentItem()->text(0);
		//qDebug() << ui.treeWidget->currentItem()->text(1);
		//QTreeWidgetItem *curItem = ui.treeWidget->currentItem();
		//curItem->setFlags(curItem->flags() & ~(Qt::ItemIsSelectable));
	});

	connect(ui.btnArrow, &QToolButton::clicked, [=](){
		QTreeWidgetItem *curItem = ui.treeWidget->currentItem();
		int type = 0;
		if (ui.radioButton_2->isChecked()){
			type = 1;
		}
		QString username = curItem->text(0);
		int id = curItem->text(1).toInt();
		if (m_map.contains(id)){
			return;
		}
		QListItem *item = new QListItem(username, id, type);
		addItem(id,item);
	});
}

QNewDirsNextWidget::~QNewDirsNextWidget()
{

}

void QNewDirsNextWidget::setTreeWidget(QUser *pUser,QTreeWidgetItem *parent,bool top)
{
	USERLIST children = pUser->getChildren();
	auto it = children.begin();
	for (; it != children.end(); it++){
		QUser *user = *it;
		QTreeWidgetItem *pItem = NULL;
		QStringList list;
		list << user->getName()<<QString::number(user->getId());
		if (top){
			pItem = ui.treeWidget->addTreeRoot(list);
		}else{
			pItem = ui.treeWidget->addTreeNode(parent, list);
		}
		if (user->getType() == "depart"){
			setTreeWidget(user, pItem);
		}
	}
}

void QNewDirsNextWidget::addItem(int id,QListItem *pItem)
{
	QListWidgetItem *aItem = new QListWidgetItem(ui.listWidget);
	QSize size = pItem->size();
	aItem->setSizeHint(QSize(pItem->width()-6, pItem->height()));
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem,pItem);
	m_map.insert(id, aItem);

	connect(pItem, &QListItem::sigCancelClicked, [=](int id){
		ItemList::iterator it = m_map.find(id);
		ui.listWidget->removeItemWidget(it.value());
		delete it.value();
		m_map.remove(id);
	});
}

ItemList QNewDirsNextWidget::getSubmitter()
{
	return m_map;
}

QListWidget *QNewDirsNextWidget::getListWidget()
{
	return ui.listWidget;
}

QString QNewDirsNextWidget::getFileName()
{
	return m_fileName;
}

QString QNewDirsNextWidget::getComment()
{
	return m_comment;
}

int QNewDirsNextWidget::getNotice()
{
	if (ui.chkBox->isChecked()){
		return 1;
	}else{
		return 0;
	}
}

QString QNewDirsNextWidget::getMsg()
{
	if (getNotice() == 1){
		return ui.txtEdt->toPlainText();
	}
	return "";
}

void QNewDirsNextWidget::setInfo(QString fileName, QString comment)
{
	m_fileName = fileName;
	m_comment = comment;
}