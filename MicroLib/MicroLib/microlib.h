#ifndef MICROLIB_H
#define MICROLIB_H

#include <QtWidgets/QMainWindow>
#include "ui_microlib.h"
#include "Dialogs/qtitlewidget.h"
#include "Dialogs/qtoolwidget.h"
#include "Dialogs/qsubtranswidget.h"
#include <QVBoxLayout>

class MicroLib : public QMainWindow
{
	Q_OBJECT

public:
	MicroLib(QWidget *parent = 0);
	~MicroLib();

private:
	Ui::MicroLibClass ui;
	
	QVBoxLayout *m_pLayout;
	QTitleWidget *m_titleWidget;
	QToolWidget *m_toolWidget;
	QSubTransWidget *m_subTransWidget;
};

#endif // MICROLIB_H
