#ifndef QBASEWEBENGINEVIEW_H
#define QBASEWEBENGINEVIEW_H

#include <QtWebEngineWidgets/QWebEngineView>

class QBaseWebEngineView : public QWebEngineView
{
	Q_OBJECT

public:
	QBaseWebEngineView(QWidget *parent);
	~QBaseWebEngineView();

private:
	
};

#endif // QBASEWEBENGINEVIEW_H
