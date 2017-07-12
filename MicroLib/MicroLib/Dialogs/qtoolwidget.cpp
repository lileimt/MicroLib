#include "qtoolwidget.h"

QToolWidget::QToolWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(966, 46);

	m_pLayout = new QHBoxLayout;
	m_stackLayout = new QStackedLayout;

	m_pShareWidget = new QBaseWidget;
	m_pRootShareLayout = new QHBoxLayout;
	m_newShare = getNewButton(QStringLiteral("新建共享"), ":/images/newfile");
	m_editShare = getNewButton(QStringLiteral("编辑共享"), ":/images/edit");
	m_pRootShareLayout->addWidget(m_newShare);
	m_pRootShareLayout->addWidget(m_editShare);
	m_pRootShareLayout->addStretch();
	m_pRootShareLayout->setSpacing(22);
	m_pRootShareLayout->setContentsMargins(0, 0, 0, 0);
	m_pShareWidget->setLayout(m_pRootShareLayout);
	m_stackLayout->addWidget(m_pShareWidget);

	m_pMyFilesWidget = new QBaseWidget;
	m_pRootMyFilesLayout = new QHBoxLayout;
	m_uploadFile = getNewButton(QStringLiteral("上传"), ":/images/upload");
	m_downloadFile = getNewButton(QStringLiteral("下载"), ":/images/download");
	m_shareFile = getNewButton(QStringLiteral("分享"), ":/images/share");
	m_deleteFile = getNewButton(QStringLiteral("删除"), ":/images/delete");
	m_newFile = getNewButton(QStringLiteral("新建文件夹"), ":/images/newfile");
	m_more = getNewButton(QStringLiteral("更多..."), ":/images/more");
	m_pRootMyFilesLayout->addWidget(m_uploadFile);
	m_pRootMyFilesLayout->addWidget(m_downloadFile);
	m_pRootMyFilesLayout->addWidget(m_shareFile);
	m_pRootMyFilesLayout->addWidget(m_deleteFile);
	m_pRootMyFilesLayout->addWidget(m_newFile);
	m_pRootMyFilesLayout->addWidget(m_more);
	m_pRootMyFilesLayout->addStretch();
	m_pRootMyFilesLayout->setSpacing(22);
	m_pRootMyFilesLayout->setContentsMargins(0, 0, 0, 0);
	m_pMyFilesWidget->setLayout(m_pRootMyFilesLayout);
	m_stackLayout->addWidget(m_pMyFilesWidget);

	m_pSubShareWidget = new QBaseWidget;
	m_pSubRootShareLayout = new QHBoxLayout;
	m_uploadFile1 = getNewButton(QStringLiteral("上传"), ":/images/upload");
	m_downloadFile1 = getNewButton(QStringLiteral("下载"), ":/images/download");
	m_transSave = getNewButton(QStringLiteral("转存"), ":/images/save");
	m_editShare1 = getNewButton(QStringLiteral("编辑共享"), ":/images/edit");
	m_more1 = getNewButton(QStringLiteral("更多..."), ":/images/more");
	m_pSubRootShareLayout->addWidget(m_uploadFile1);
	m_pSubRootShareLayout->addWidget(m_downloadFile1);
	m_pSubRootShareLayout->addWidget(m_transSave);
	m_pSubRootShareLayout->addWidget(m_editShare1);
	m_pSubRootShareLayout->addWidget(m_more1);
	m_pSubRootShareLayout->addStretch();
	m_pSubRootShareLayout->setSpacing(22);
	m_pSubRootShareLayout->setContentsMargins(0, 0, 0, 0);
	m_pSubShareWidget->setLayout(m_pSubRootShareLayout);
	m_stackLayout->addWidget(m_pSubShareWidget);

	m_pLayout->addLayout(m_stackLayout);
	m_pLayout->addStretch();
	m_searchWidget = new QSearchWidget;
	m_pLayout->addWidget(m_searchWidget);
	m_pLayout->setContentsMargins(20, 0, 20, 0);
	m_pLayout->setSpacing(0);
	setLayout(m_pLayout);

	showIndex(shareindex);
}

QToolWidget::~QToolWidget()
{
	RELEASE(m_newShare);
	RELEASE(m_editShare);
	RELEASE(m_editShare1);
	RELEASE(m_transSave);

	RELEASE(m_uploadFile);
	RELEASE(m_uploadFile1);
	RELEASE(m_newFile);
	RELEASE(m_shareFile);
	RELEASE(m_downloadFile);
	RELEASE(m_downloadFile1);
	RELEASE(m_more);
	RELEASE(m_more1);

	RELEASE(m_pSubRootShareLayout);
	RELEASE(m_pRootShareLayout);
	RELEASE(m_pRootMyFilesLayout);
	RELEASE(m_stackLayout);

	RELEASE(m_searchWidget);
	RELEASE(m_pShareWidget);
	RELEASE(m_pMyFilesWidget);
	RELEASE(m_pSubShareWidget);

	RELEASE(m_pLayout);
}

QToolButton *QToolWidget::getNewButton(QString name, QString icon)
{
	QToolButton *btn = new QToolButton;
	btn->setAutoRaise(true);
	btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	btn->setIcon(QIcon(icon));
	btn->setIconSize(QSize(20, 20));
	btn->setText(name);
	btn->setStyleSheet("border:none;color:#3ba79a;font-family:微软雅黑;font-size:12px;");
	return btn;
}

void QToolWidget::showIndex(TOOLINDEX index)
{
	m_stackLayout->setCurrentIndex((int)index);
	if (index == myfilesindex){
		m_searchWidget->setPlaceholderText(QStringLiteral("搜索公共目录"));
	}else{
		m_searchWidget->setPlaceholderText(QStringLiteral("搜索我的文件"));
	}
}