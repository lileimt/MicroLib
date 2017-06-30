#ifndef QSUBTRANSWIDGET_H
#define QSUBTRANSWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_subtranswidget.h"
#include <QMouseEvent>

class QSubTransWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QSubTransWidget(QWidget *parent = 0);
	~QSubTransWidget();

	void setText(QString text);

protected:
	void mousePressEvent(QMouseEvent *event);

signals:
	void clicked();

private:
	Ui::QSubTransWidget ui;
};

#endif // QSUBTRANSWIDGET_H
