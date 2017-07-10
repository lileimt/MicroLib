#include "qtitlewidget.h"

QTitleWidget::QTitleWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(966, 72);
	ui.lblIcon->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblTitle->setAttribute(Qt::WA_TranslucentBackground);
	ui.lblUser->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnUser->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnFiles->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnShare->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnSet->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnMin->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnClose->setAttribute(Qt::WA_TranslucentBackground);
	ui.btnDang->setAttribute(Qt::WA_TranslucentBackground);

	ui.lblUser->setPixmap(QPixmap(":/images/ming"));
	m_pLabel = new QLabel(this);
	m_pLabel->setPixmap(QPixmap(":/images/circle"));
	m_pLabel->setScaledContents(true);

	connect(ui.btnDang, &QToolButton::clicked, [=](){
		emit sigDangClicked();
	});

	connect(ui.btnMin, &QToolButton::clicked, [=](){
		emit sigMinClicked();
	});

	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});
}

QTitleWidget::~QTitleWidget()
{
	delete m_pLabel;
}

void QTitleWidget::paintEvent(QPaintEvent *event)
{
	QRect rect = ui.btnDang->geometry();
	m_pLabel->setGeometry(rect.left() + 8 ,rect.top() - 8, 24, 24);
	QBaseWidget::paintEvent(event);
}