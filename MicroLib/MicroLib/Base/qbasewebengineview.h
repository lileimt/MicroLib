#ifndef QBASEWEBENGINEVIEW_H
#define QBASEWEBENGINEVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEngineSettings>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QtWebChannel/QWebChannel>
#include "Common/qchannel.h"

class QBaseWebEngineView : public QWebEngineView
{
	Q_OBJECT

public:
	QBaseWebEngineView(QWidget *parent);
	~QBaseWebEngineView();

private:
	QWebEnginePage *m_page;
	QWebChannel *m_channel;
};

#endif // QBASEWEBENGINEVIEW_H
