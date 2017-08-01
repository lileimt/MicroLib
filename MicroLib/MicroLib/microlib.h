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

	//显示转存文件窗口
	void showForwardWidget();
	//显示统计信息窗口
	void showStaticsWidget();
	//显示新建公共目录窗口
	void showNewDirsWidget();
	//显示新建公共目录下一步窗口
	void showNewDirsNextWidget();
	//显示发送文件窗口
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

	QList<FILETRANSPORT> m_transList;  //文件上传下载列表

	//打开上传文件对话框
	void openUploadFileDialog();
	//信号关联
	void sigConnect();
	//获取和js通信的channel对象
	QChannel *getChannel();
	//获取用户数据
	void getUserInfo();
	void downloadFiles(QString curFiles);
};

#endif // MICROLIB_H
