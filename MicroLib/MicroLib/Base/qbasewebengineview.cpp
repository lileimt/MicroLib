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
	m_webChannel = new QWebChannel(parent);
	m_channel = new QChannel();
	m_webChannel->registerObject(QString("channel"), m_channel);
	m_page->setWebChannel(m_webChannel);
}

QBaseWebEngineView::~QBaseWebEngineView()
{
	RELEASE(m_channel);
	RELEASE(m_webChannel);
	RELEASE(m_page);
}

QChannel *QBaseWebEngineView::getChannel()
{
	return m_channel;
}