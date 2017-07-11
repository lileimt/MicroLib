#include "qchannel.h"

QChannel *QChannel::m_pInstance = NULL;

QChannel::QChannel(QObject *parent)
	: QObject(parent)
{

}

QChannel::~QChannel()
{
	if (m_pInstance){
		delete m_pInstance;
	}
}

QChannel *QChannel::getInstance()
{
	if (m_pInstance == NULL){
		m_pInstance = new QChannel;
	}
	return m_pInstance;
}