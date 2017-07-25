#include "quser.h"

QUser::QUser(QObject *parent)
	: QObject(parent)
{

}

QUser::~QUser()
{

}

int QUser::getId()
{
	return m_id;
}

void QUser::setId(int id)
{
	m_id = id;
}

QString QUser::getName()
{
	return m_name;
}

void QUser::setName(QString name)
{
	m_name = name;
}

QString QUser::getType()
{
	return m_type;
}

void QUser::setType(QString type)
{
	m_type = type;
}

int QUser::getChildCount()
{
	return m_children.count();
}

USERLIST QUser::getChildren()
{
	return m_children;
}

void QUser::append(QUser *user)
{
	m_children.append(user);
}

QUser *QUser::getUserById(int id)
{
	if (id == m_id){
		return this;
	}
	auto it = m_children.begin();
	for (; it != m_children.end(); it++){
		QUser *user = dynamic_cast<QUser *>(*it);
		if (user->getId() == id){
			return user;
		}
	}
}