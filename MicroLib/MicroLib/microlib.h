#ifndef MICROLIB_H
#define MICROLIB_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QtWidgets/QMainWindow>
#include "ui_microlib.h"
#include "Dialogs/qtitlewidget.h"
#include "Dialogs/qtoolwidget.h"
#include "Dialogs/qsubtranswidget.h"
#include "Base/qbasewebengineview.h"
#include "Dialogs/qtransportwidget.h"
#include "Base/qbasetransparentwidget.h"
#include "Dialogs/qforwardwidget.h"
#include "Dialogs/qstaticswidget.h"
#include "Dialogs/qnewdirswidget.h"
#include "Dialogs/qnewdirsnextwidget.h"
#include "Dialogs/qsidewidget.h"
#include "Dialogs/qmsgwidget.h"
#include "Dialogs/qsendwidget.h"
#include "Common/qchannel.h"
#include "Common/quser.h"
#include "Common/qparsejson.h"

class MicroLib : public QMainWindow
{
	Q_OBJECT

public:
	MicroLib(QWidget *parent = 0);
	~MicroLib();

	//��ʾת���ļ�����
	void showForwardWidget();
	//��ʾͳ����Ϣ����
	void showStaticsWidget();
	//��ʾ�½�����Ŀ¼����
	void showNewDirsWidget();
	//��ʾ�½�����Ŀ¼��һ������
	void showNewDirsNextWidget();
	//��ʾ�����ļ�����
	void ShowSendFilesWidget(int count);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	Ui::MicroLibClass ui;
	
	QVBoxLayout *m_pLayout;
	QHBoxLayout *m_pHLayout;
	QTitleWidget *m_titleWidget;
	QToolWidget *m_toolWidget;
	QBaseWebEngineView *m_webEngine;
	QSubTransWidget *m_subTransWidget;
	QTransportWidget *m_transWidget;
	QBaseTransparentWidget *m_baseTransWidget;
	QForwardWidget *m_forwardWidget;
	QStaticsWidget *m_staticsWidget;
	QNewDirsWidget *m_newDirsWidget;
	QNewDirsNextWidget *m_newDirsNextWidget;
	QSideWidget *m_sideWidget;
	QMsgWidget *m_msgWidget;
	QSendWidget *m_sendWidget;

	QParseJson m_parseJson;
	QUser *m_user;

	QPoint m_point;
	bool m_bPressed;
	bool m_bCovered;
	OPERTYPE m_eOperType;

	QList<FILETRANSPORT> m_transList;  //�ļ��ϴ������б�

	//���ϴ��ļ��Ի���
	void openUploadFileDialog();
	//�źŹ���
	void sigConnect();
	//��ȡ��jsͨ�ŵ�channel����
	QChannel *getChannel();
	//��ȡ�û�����
	void getUserInfo();
	void downloadFiles(QString curFiles);
};

#endif // MICROLIB_H
