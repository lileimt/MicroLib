#include "qbasewebengineview.h"

#ifdef _DEBUG
#pragma comment(lib,"Qt5WebEngineWidgetsd.lib")
#else
#pragma comment(lib,"Qt5WebEngineWidgets.lib")
#endif

QBaseWebEngineView::QBaseWebEngineView(QWidget *parent)
	: QWebEngineView(parent)
{

}

QBaseWebEngineView::~QBaseWebEngineView()
{

}
