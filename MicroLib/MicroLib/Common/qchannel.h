#ifndef QCHANNEL_H
#define QCHANNEL_H

#include <QObject>

class QChannel : public QObject
{
	Q_OBJECT

public:
	static QChannel *getInstance();

signals:
	//void sigTest();

public slots:
	//void demoTest();
	//void test();

private:
	QChannel(QObject *parent = 0);
	~QChannel();

	static QChannel *m_pInstance;
};

#endif // QCHANNEL_H
