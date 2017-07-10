#ifndef QTITLEWIDGET_H
#define QTITLEWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "ui_titlewidget.h"

class QTitleWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QTitleWidget(QWidget *parent = 0);
	~QTitleWidget();

protected:
	void paintEvent(QPaintEvent *event);
signals:
	void sigMinClicked();
	void sigCloseClicked();
	void sigDangClicked();
private:
	Ui::QTitleWidget ui;
	QLabel *m_pLabel;
};

#endif // QTITLEWIDGET_H
