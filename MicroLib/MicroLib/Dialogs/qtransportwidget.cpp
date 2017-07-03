#include "qtransportwidget.h"

QTransportWidget::QTransportWidget(QString strTitle, bool bShowMin, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(620,250);
	m_pLayout = new QVBoxLayout;
	m_titleWidget = new QBaseTitleWidget(strTitle, bShowMin,this);
	//m_pLayout->addWidget(m_titleWidget);
	m_titleWidget->setGeometry(0, 0, 620, m_titleWidget->height());
	m_scrollArea = new QScrollArea(this);
	m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//m_scrollArea->setStyleSheet("background:white");
	m_scrollArea->setGeometry(0, m_titleWidget->height(), 620, 250 - m_titleWidget->height());
	m_scrollArea->setWidgetResizable(true);
	m_tmpWidget = new QBaseWidget(this);
	m_tmpWidget->setGeometry(0, 0, m_scrollArea->width(), m_scrollArea->height());
	m_tmpWidget->setStyleSheet("background:white");
	m_scrollArea->setWidget(m_tmpWidget);
	
	//m_pListLayout = new QVBoxLayout(m_scrollArea);
	//m_pListLayout->setContentsMargins(0, 0, 0, 0);
	//m_pListLayout->setSpacing(0);
	//m_pListLayout->setMargin(0);
	//m_scrollArea->setLayout(m_pListLayout);

	//m_pLayout->addWidget(m_scrollArea);
	//m_pLayout->setContentsMargins(0, 0, 0, 0);
	//m_pLayout->setSpacing(0);
	//m_pLayout->setMargin(0);
	//setLayout(m_pLayout);

	showList();
}

QTransportWidget::~QTransportWidget()
{
	delete m_titleWidget;
	//delete m_pListLayout;
	//delete m_scrollArea;
	//delete m_pLayout;
}


void QTransportWidget::showList()
{
	FILETRANSPORT st;
	st.fileName = QStringLiteral("我的文件.exe");
	st.fileIcon = QString(":/images/ok");
	st.filePath = QStringLiteral("文件夹");
	st.fileSize = QString("1.21M");
	st.state = 0;
	st.status = 0;

	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);
	m_transList.append(st);

	//TRANSLIST::iterator it = m_transList.begin();
	//QTransportItem *item = new QTransportItem(*it, true);
	//m_pListLayout->addWidget(item);
	//for (; it != m_transList.end(); it++){
	//	item = new QTransportItem(*it, false);
	//	m_pListLayout->addWidget(item);
	//}
	//m_pListLayout->addStretch();
}