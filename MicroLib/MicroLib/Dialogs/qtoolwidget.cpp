#include "qtoolwidget.h"
#include "Common/common.h"

QToolWidget::QToolWidget(QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(966, 46);

	m_pLayout = new QHBoxLayout;
	m_searchWidget = new QSearchWidget;

	m_newShare = getNewButton(QStringLiteral("�½�����"), ":/images/newfile");
	m_editShare = getNewButton(QStringLiteral("�༭����"), ":/images/edit");
	m_transSave = getNewButton(QStringLiteral("ת��"), ":/images/save");

	m_uploadFile = getNewButton(QStringLiteral("�ϴ�"), ":/images/upload");
	m_newFile = getNewButton(QStringLiteral("�½�"), ":/images/newfile");
	m_shareFile = getNewButton(QStringLiteral("����"), ":/images/share");
	m_downloadFile = getNewButton(QStringLiteral("����"), ":/images/download");
	m_more = getNewButton(QStringLiteral("����..."), ":/images/more");

	setRootShareLayout();
	setRootMyFilesLayout();
	setSubRootShareLayout();

	m_pLayout->addStretch();
	m_pLayout->addStretch();
	m_pLayout->addWidget(m_searchWidget, 0, Qt::AlignRight);
	m_pLayout->setContentsMargins(20, 0, 20, 0);
	m_pLayout->setMargin(0);
	m_pLayout->setSpacing(0);
	setLayout(m_pLayout);

	//����Ĭ����ʾ��
	showRootShareLayout();
	//showRootMyFilesLayout();
	showSubRootShareLayout();
}

QToolWidget::~QToolWidget()
{
	RELEASE(m_pSubRootShareLayout);
	RELEASE(m_pRootShareLayout);
	RELEASE(m_pRootMyFilesLayout);
	RELEASE(m_pLayout);

	RELEASE(m_searchWidget);
	RELEASE(m_newShare);
	RELEASE(m_editShare);
	RELEASE(m_transSave);

	RELEASE(m_uploadFile);
	RELEASE(m_newFile);
	RELEASE(m_shareFile);
	RELEASE(m_downloadFile);
	RELEASE(m_more);
}

QToolButton *QToolWidget::getNewButton(QString name, QString icon)
{
	QToolButton *btn = new QToolButton;
	btn->setAutoRaise(true);
	btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	btn->setIcon(QIcon(icon));
	btn->setIconSize(QSize(20, 20));
	btn->setText(name);
	btn->setStyleSheet("border:none;color:#3ba79a;font-family:΢���ź�;font-size:12px;");
	return btn;
}

void QToolWidget::setRootShareLayout()
{
	m_pRootShareLayout = new QHBoxLayout;

	m_pRootShareLayout->addWidget(m_newShare);
	m_pRootShareLayout->addWidget(m_editShare);

	m_searchWidget->setPlaceholderText(QStringLiteral("��������Ŀ¼"));
	m_pRootShareLayout->setSpacing(22);
	m_pRootShareLayout->setContentsMargins(0, 0, 0, 0);
}

void QToolWidget::setSubRootShareLayout()
{
	m_pSubRootShareLayout = new QHBoxLayout;

	m_pSubRootShareLayout->addWidget(m_uploadFile);
	m_pSubRootShareLayout->addWidget(m_downloadFile);
	m_pSubRootShareLayout->addWidget(m_transSave);
	m_pSubRootShareLayout->addWidget(m_editShare);
	m_pSubRootShareLayout->addWidget(m_more);

	m_searchWidget->setPlaceholderText(QStringLiteral("��������Ŀ¼"));
	m_pSubRootShareLayout->setSpacing(22);
	m_pSubRootShareLayout->setContentsMargins(0, 0, 0, 0);
}

void QToolWidget::setRootMyFilesLayout()
{
	m_pRootMyFilesLayout = new QHBoxLayout;

	m_pRootMyFilesLayout->addWidget(m_uploadFile);
	m_pRootMyFilesLayout->addWidget(m_newFile);
	m_pRootMyFilesLayout->addWidget(m_shareFile);
	m_pRootMyFilesLayout->addWidget(m_downloadFile);
	m_pRootMyFilesLayout->addWidget(m_more);

	m_searchWidget->setPlaceholderText(QStringLiteral("�����ҵ��ļ�"));
	m_pRootMyFilesLayout->setSpacing(22);
	m_pRootMyFilesLayout->setContentsMargins(0, 0, 0, 0);
}

void QToolWidget::showRootShareLayout()
{
	QLayoutItem *pLayout = m_pLayout->itemAt(0);
	if (pLayout){
		m_pLayout->removeItem(pLayout);
	}
	m_pLayout->insertLayout(0, m_pRootShareLayout);
	m_pLayout->setContentsMargins(20, 0, 20, 0);
}

void QToolWidget::showSubRootShareLayout()
{
	QLayoutItem *pLayout = m_pLayout->itemAt(0);
	if (pLayout){
		m_pLayout->removeItem(pLayout);
	}
	m_pLayout->insertLayout(0, m_pSubRootShareLayout);
	m_pLayout->setContentsMargins(20, 0, 20, 0);
}

void QToolWidget::showRootMyFilesLayout()
{
	QLayoutItem *pLayout = m_pLayout->itemAt(0);
	if (pLayout){
		m_pLayout->removeItem(pLayout);
	}
	m_pLayout->insertLayout(0, m_pRootMyFilesLayout);
	m_pLayout->setContentsMargins(20, 0, 20, 0);
}
