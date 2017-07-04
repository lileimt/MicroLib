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

void QUser::append(QUser *user)
{
	m_children.append(user);
}