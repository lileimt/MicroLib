#include "qmsgwidget.h"
#include "Common/common.h"

QMsgWidget::QMsgWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);

	MSGITEM item;
	item.userName = QStringLiteral("����Զ");
	item.fileName = QStringLiteral("�ҵ��ĵ�.docx");
	item.type = 0;

	for (int i = 0; i < 5; i++){
		item.type = i % 2;
		QMsgItem *pWidget = new QMsgItem(item);
		addItem(ui.listWidget1, pWidget);
	}
	for (int i = 0; i < 5; i++){
		item.type = i%2;
		QMsgItem *pWidget = new QMsgItem(item);
		addItem(ui.listWidget2, pWidget);
	}
}

QMsgWidget::~QMsgWidget()
{

}


void QMsgWidget::addItem(QListWidget *pListWidget,QMsgItem *pWidget)
{
	QListWidgetItem *pItem = new QListWidgetItem(pListWidget);
	QSize size = pWidget->size();
	pItem->setSizeHint(QSize(pWidget->width() - 5, pWidget->height()));
	pListWidget->addItem(pItem);
	pListWidget->setItemWidget(pItem, pWidget);
}