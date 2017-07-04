#include "qtransportwidget.h"

QTransportWidget::QTransportWidget(QString strTitle, bool bShowMin, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(620,220);
	m_pLayout = new QVBoxLayout;
	m_titleWidget = new QBaseTitleWidget(strTitle, bShowMin,this);
	m_pLayout->addWidget(m_titleWidget);
	m_titleWidget->setGeometry(0, 0, 620, m_titleWidget->height());
	m_listWidget = new QListWidget(this);
	m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QTransportItem *item = new QTransportItem(NULL, true);
	addItem(item);

	m_pLayout->addWidget(m_listWidget);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayout->setSpacing(0);
	m_pLayout->setMargin(0);
	setLayout(m_pLayout);

	showList();
}

QTransportWidget::~QTransportWidget()
{
	delete m_titleWidget;
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
	FILETRANSPORT st;
	st.fileName = QStringLiteral("我的文件.exe");
	st.fileIcon = QString(":/images/ok");
	st.filePath = QStringLiteral("文件夹");
	st.fileSize = QString("999.21M");
	st.state = 0;
	st.status = 0;

	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	//m_transList.append(st);

	TRANSLIST::iterator it = m_transList.begin();
	for (; it != m_transList.end(); it++){
		QTransportItem *item = new QTransportItem(&(*it), false);
		addItem(item);
	}
}