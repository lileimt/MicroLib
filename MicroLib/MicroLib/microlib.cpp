#include "microlib.h"

MicroLib::MicroLib(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setWindowTitle(QStringLiteral("微库"));
	setFixedSize(966, 640);

	QWidget *widget = new QWidget();
	this->setCentralWidget(widget);

	m_pLayout = new QVBoxLayout(widget);
	m_titleWidget = new QTitleWidget(widget);
	connect(m_titleWidget, &QTitleWidget::sigMinClicked, [=](){
		showMinimized();
	});
	connect(m_titleWidget, &QTitleWidget::sigCloseClicked, [=](){
		qApp->quit();
	});
	m_toolWidget = new QToolWidget(widget);

	m_webEngine = new QBaseWebEngineView(widget);
	m_webEngine->setUrl(QUrl("https://www.hao123.com"));
	//m_subTransWidget = new QSubTransWidget(widget);
	QRect rect = geometry();
	//m_subTransWidget->setGeometry(rect.right() - 202, rect.bottom() - 36, 202, 36);

	m_transWidget = new QTransportWidget(QStringLiteral("1项未完成传输"),true,widget);
	m_transWidget->setGeometry(rect.right() - m_transWidget->width(), rect.bottom() - m_transWidget->height(), m_transWidget->width(), m_transWidget->height());

	m_pLayout->addWidget(m_titleWidget);
	m_pLayout->addWidget(m_toolWidget);
	m_pLayout->addWidget(m_webEngine);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayout->setMargin(0);
	m_pLayout->setSpacing(0);
	widget->setLayout(m_pLayout);
}

MicroLib::~MicroLib()
{
	delete m_pLayout;
	delete m_titleWidget;
	delete m_toolWidget;
	//delete m_subTransWidget;
}
