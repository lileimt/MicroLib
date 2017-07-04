#ifndef QUSER_H
#define QUSER_H

#include <QObject>
#include <QString>
#include <QList>

class QUser;

typedef QList<QUser *> USERLIST;

class QUser : public QObject
{
	Q_OBJECT

public:
	QUser(QObject *parent = 0);
	~QUser();

	int getId();
	void setId(int id);
	QString getName();
	void setName(QString name);
	QString getType();
	void setType(QString type);
	int getChildCount();

	void append(QUser *user);
private:
	int m_id;
	QString m_name;
	QString m_type;

	USERLIST m_children;
};

#endif // QUSER_H
