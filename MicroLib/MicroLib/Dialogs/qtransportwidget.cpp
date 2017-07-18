#include "qtransportwidget.h"

QTransportWidget::QTransportWidget(QString strTitle, bool bShowMin, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(620,220);
	m_pLayout = new QVBoxLayout;
	m_titleWidget = new QBaseTitleWidget(strTitle, bShowMin,this);
	connect(m_titleWidget, &QBaseTitleWidget::sigMinClicked, [=](){
		emit sigMinClicked();
	});
	connect(m_titleWidget, &QBaseTitleWidget::sigCloseClicked, [=](){
		clearList();
		close();
	});
	m_pLayout->addWidget(m_titleWidget);
	m_titleWidget->setGeometry(0, 0, 620, m_titleWidget->height());
	m_listWidget = new QListWidget(this);
	m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_listWidget->setStyleSheet("border:none;");
	m_pHeader = new QTransportItem(NULL, true,this);
	m_pHeader->setFixedSize(620, 40);
	m_pLayout->addWidget(m_pHeader);
	m_pLayout->addWidget(m_listWidget);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayout->setSpacing(0);
	m_pLayout->setMargin(0);
	setLayout(m_pLayout);

	showList();
}

QTransportWidget::~QTransportWidget()
{
	clearList();
	delete m_titleWidget;
	delete m_pHeader;
	delete m_listWidget;
	delete m_pLayout;
}

void QTransportWidget::addItem(QTransportItem *pItem)
{
	QListWidgetItem *aItem = new QListWidgetItem(m_listWidget);
	QSize size = pItem->size();
	aItem->setSizeHint(QSize(pItem->width()-5,pItem->height()));
	m_listWidget->addItem(aItem);
	m_listWidget->setItemWidget(aItem, pItem);
}

void QTransportWidget::showList()
{
	TRANSLIST::iterator it = m_transList.begin();
	for (; it != m_transList.end(); it++){
		QTransportItem *item = new QTransportItem(&(*it), false);
		addItem(item);
	}
}

void QTransportWidget::insertList(FILETRANSPORT &st)
{
	m_transList.append(st);
	QTransportItem *pItem = new QTransportItem(&st, false);
	QListWidgetItem *aItem = new QListWidgetItem(m_listWidget);
	QSize size = pItem->size();
	aItem->setSizeHint(QSize(pItem->width() - 5, pItem->height()));
	m_listWidget->insertItem(0,aItem);
	m_listWidget->setItemWidget(aItem, pItem);
}

void QTransportWidget::clearList()
{
	m_transList.clear();
	int count = m_listWidget->count();
	for (int i = 0; i < count; i++){
		QListWidgetItem *pItem = m_listWidget->takeItem(0);
		delete pItem;
	}
}