#ifndef QSEARCHWIDGET_H
#define QSEARCHWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_searchwidget.h"

class QSearchWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QSearchWidget(QWidget *parent = 0);
	~QSearchWidget();

	void setPlaceholderText(QString text);
private:
	Ui::QSearchWidget ui;
};

#endif // QSEARCHWIDGET_H
