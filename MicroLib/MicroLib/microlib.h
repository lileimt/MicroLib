#ifndef MICROLIB_H
#define MICROLIB_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_microlib.h"
#include "Dialogs/qtitlewidget.h"
#include "Dialogs/qtoolwidget.h"
#include "Dialogs/qsubtranswidget.h"
#include "Base/qbasewebengineview.h"
#include "Dialogs/qtransportwidget.h"
#include "Base/qbasetransparentwidget.h"
#include "Dialogs/qforwardwidget.h"
#include "Dialogs/qstaticswidget.h"
#include "Dialogs/qnewdirswidget.h"
#include "Dialogs/qnewdirsnextwidget.h"
#include "Dialogs/qsidewidget.h"
#include "Dialogs/qmsgwidget.h"

class MicroLib : public QMainWindow
{
	Q_OBJECT

public:
	MicroLib(QWidget *parent = 0);
	~MicroLib();

	void showForwardWidget();
	void showStaticsWidget();
	void showNewDirsWidget();
	void showNewDirsNextWidget();
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	Ui::MicroLibClass ui;
	
	QVBoxLayout *m_pLayout;
	QHBoxLayout *m_pHLayout;
	QTitleWidget *m_titleWidget;
	QToolWidget *m_toolWidget;
	QBaseWebEngineView *m_webEngine;
	QSubTransWidget *m_subTransWidget;
	QTransportWidget *m_transWidget;
	QBaseTransparentWidget *m_baseTransWidget;
	QForwardWidget *m_forwardWidget;
	QStaticsWidget *m_staticsWidget;
	QNewDirsWidget *m_newDirsWidget;
	QNewDirsNextWidget *m_newDirsNextWidget;
	QSideWidget *m_sideWidget;
	QMsgWidget *m_msgWidget;

	QPoint m_point;
	bool m_bPressed;
	bool m_bCovered;
	OPERTYPE m_eOperType;
};

#endif // MICROLIB_H
