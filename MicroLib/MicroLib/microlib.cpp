#include "microlib.h"

MicroLib::MicroLib(QWidget *parent)
	: QMainWindow(parent),
	m_subTransWidget(NULL),
	m_transWidget(NULL),
	m_baseTransWidget(NULL),
	m_forwardWidget(NULL),
	m_bPressed(false),
	m_bCovered(false)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);
	setWindowTitle(QStringLiteral("微库"));
	setFixedSize(WIDTH, HEIGHT);

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

	showForwardWidget();
}

MicroLib::~MicroLib()
{
	RELEASE(m_pLayout);
	RELEASE(m_titleWidget);
	RELEASE(m_toolWidget);
	RELEASE(m_subTransWidget);
	RELEASE(m_forwardWidget);
	RELEASE(m_baseTransWidget);
}

void MicroLib::showForwardWidget()
{
	RELEASE(m_baseTransWidget);
	m_bCovered = true;
	m_baseTransWidget = new QBaseTransparentWidget(this);
	m_baseTransWidget->resize(WIDTH, HEIGHT);
	m_forwardWidget = new QForwardWidget(m_baseTransWidget);
	m_forwardWidget->move((WIDTH - m_forwardWidget->width()) / 2, (HEIGHT - m_forwardWidget->height()) / 2);
	m_baseTransWidget->show();

	connect(m_forwardWidget, &QForwardWidget::sigCloseClicked, [=](){
		m_baseTransWidget->close();
		m_bCovered = false;
	});
}

void MicroLib::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton){
		QPoint pos = event->pos();
		if (m_titleWidget->rect().contains(pos) && !m_bCovered){
			m_bPressed = true;
			m_point = pos;
		}
	}
}

void MicroLib::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	m_bPressed = false;
}

void MicroLib::mouseMoveEvent(QMouseEvent *event)
{
	if (m_bPressed){
		QPoint pt = event->globalPos();
		move(pt - m_point);
	}
}