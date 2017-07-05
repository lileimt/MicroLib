#ifndef QFORWARDWIDGET_H
#define QFORWARDWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_forwardwidget.h"

class QForwardWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QForwardWidget(QWidget *parent = 0);
	~QForwardWidget();

signals:
	void sigCloseClicked();
private:
	Ui::QForwardWidget ui;

	QTreeWidgetItem *addRoot(QString text);
	QTreeWidgetItem *addNode(QTreeWidgetItem *parent, QString text);
};

#endif // QFORWARDWIDGET_H
