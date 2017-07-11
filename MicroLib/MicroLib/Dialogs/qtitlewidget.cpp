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

	ui.btnShare->setStyleSheet("background:rgba(255, 255, 255, 50);");


	connect(ui.btnDang, &QToolButton::clicked, [=](){
		emit sigDangClicked();
	});

	connect(ui.btnMin, &QToolButton::clicked, [=](){
		emit sigMinClicked();
	});

	connect(ui.btnClose, &QToolButton::clicked, [=](){
		emit sigCloseClicked();
	});

	connect(ui.btnShare, &QToolButton::clicked, [=](){
		emit sigShareClicked(sharefiles);
		ui.btnShare->setStyleSheet("background:rgba(255, 255, 255, 50);");
		ui.btnFiles->setStyleSheet("QToolButton#btnFiles{background:none;}"
												 "QToolButton#btnFiles:hover{background-color: rgba(255, 255, 255, 50);}");
	});

	connect(ui.btnFiles, &QToolButton::clicked, [=](){
		emit sigMyFilesClicked(myfiles);
		ui.btnFiles->setStyleSheet("background:rgba(255, 255, 255, 50);");
		ui.btnShare->setStyleSheet("QToolButton#btnShare{background:none;}"
			"QToolButton#btnShare:hover{background-color: rgba(255, 255, 255, 50);}");
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