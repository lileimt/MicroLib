#include "qsidewidget.h"
#include <QDebug>
#include <QHBoxLayout>

QSideWidget::QSideWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(250, 520);
	ui.listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	QHBoxLayout  *pLayout = new QHBoxLayout(this);
	pLayout->addWidget(ui.listWidget);
	pLayout->setContentsMargins(0, 0, 0, 0);
	pLayout->setSpacing(0);
	ui.tabLog->setLayout(pLayout);

	USERLOGITEM logItem;
	logItem.userName = QStringLiteral("李明远");
	logItem.userImage = QString(":/images/ming");
	logItem.fileName = QStringLiteral("我的文档.docx");
	logItem.fileIcon = QString(":/filetype/dir");
	logItem.state = 0;
	
	for (int i = 0; i < 10; i++){
		logItem.fileName = QStringLiteral("我的文档%1.docx").arg(i);
		logItem.time = QString("12:1%1").arg(i);
		QLogUserWidget *pWidget = new QLogUserWidget(logItem);
		addItem(pWidget);
	}

	connect(ui.btnEdt, &QToolButton::clicked, [=](){
		qDebug() << "btnEdt clicked";
	});
}

QSideWidget::~QSideWidget()
{

}

void QSideWidget::addItem(QLogUserWidget *pWidget)
{
	QListWidgetItem *pItem = new QListWidgetItem(ui.listWidget);
	QSize size = pWidget->size();
	pItem->setSizeHint(QSize(pWidget->width() - 5, pWidget->height()));
	ui.listWidget->addItem(pItem);
	ui.listWidget->setItemWidget(pItem, pWidget);
}