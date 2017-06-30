#include "microlib.h"

MicroLib::MicroLib(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setFixedSize(966, 640);

	QWidget *widget = new QWidget();
	this->setCentralWidget(widget);

	m_pLayout = new QVBoxLayout(widget);
	m_titleWidget = new QTitleWidget(widget);
	m_toolWidget = new QToolWidget(widget);
	m_subTransWidget = new QSubTransWidget(widget);
	QRect rect = geometry();
	m_subTransWidget->setGeometry(rect.right() - 202, rect.bottom() - 36, 202, 36);

	m_pLayout->addWidget(m_titleWidget);
	m_pLayout->addWidget(m_toolWidget);
	m_pLayout->addStretch();
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
	delete m_subTransWidget;
}
