#include "qmasklabel.h"
#include <QPainter>

QMaskLabel::QMaskLabel(QWidget *parent)
	: QLabel(parent)
{

}

QMaskLabel::~QMaskLabel()
{

}

void QMaskLabel::paintEvent(QPaintEvent *paint)
{
	if (pixmap()){
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		QPainterPath path;
		int round = qMin(width(), height());
		path.addEllipse(2, 2, round-4, round-4);
		painter.setClipPath(path);
		painter.drawPixmap(0, 0, round, round, *pixmap());
	}else{
		QLabel::paintEvent(paint);
	}
}