#include "qbasewebengineview.h"
#include <QDir>
#include "Common/common.h"

#ifdef _DEBUG
#pragma comment(lib,"Qt5WebEngineWidgetsd.lib")
#else
#pragma comment(lib,"Qt5WebEngineWidgets.lib")
#endif

QBaseWebEngineView::QBaseWebEngineView(QWidget *parent)
	: QWebEngineView(parent)
{
	setContextMenuPolicy(Qt::NoContextMenu);
	settings()->setDefaultTextEncoding("utf-8");
	QDir dir;
	QString path = dir.currentPath() + "/web/index.html";
	m_page = new QWebEnginePage(parent);
	m_page->settings()->setDefaultTextEncoding("utf-8");
	setPage(m_page);
	setUrl(QUrl::fromLocalFile(path));
	m_channel = new QWebChannel(parent);
	m_channel->registerObject(QString("channel"), QChannel::getInstance());
	m_page->setWebChannel(m_channel);
}

QBaseWebEngineView::~QBaseWebEngineView()
{
	RELEASE(m_channel);
	RELEASE(m_page);
}
