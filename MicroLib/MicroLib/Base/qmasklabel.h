#ifndef QMASKLABEL_H
#define QMASKLABEL_H

#include <QLabel>
#include <QPaintEvent>

class QMaskLabel : public QLabel
{
	Q_OBJECT

public:
	QMaskLabel(QWidget *parent = 0);
	~QMaskLabel();
protected:
	void paintEvent(QPaintEvent *painter);
private:
	
};

#endif // QMASKLABEL_H
