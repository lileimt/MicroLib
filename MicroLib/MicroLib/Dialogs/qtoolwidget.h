#ifndef QTOOLWIDGET_H
#define QTOOLWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_toolwidget.h"
#include "qsearchwidget.h"
#include <QHBoxLayout>
#include <QStackedLayout>
#include "Common/common.h"

class QToolWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QToolWidget(QWidget *parent = 0);
	~QToolWidget();

	void showIndex(TOOLINDEX index);
signals:
	void sigUploadClicked();
	void sigNewShareClicked();
	void sigNewDirClicked();
	void sigEditShareClicked();
	void sigDownloadClicked();
private:
	Ui::QToolWidget ui;
	QSearchWidget *m_searchWidget;
	QHBoxLayout *m_pLayout;
	QStackedLayout *m_stackLayout;
	//公共目录布局
	QBaseWidget *m_pShareWidget;
	QHBoxLayout *m_pRootShareLayout;
	//我的文件布局
	QBaseWidget *m_pMyFilesWidget;
	QHBoxLayout *m_pRootMyFilesLayout;
	//公共目录子目录
	QBaseWidget *m_pSubShareWidget;
	QHBoxLayout *m_pSubRootShareLayout;

	QToolButton *m_newShare;        //新建共享
	QToolButton *m_editShare;        //编辑共享
	QToolButton *m_editShare1;

	QToolButton *m_uploadFile;     //上传文件
	QToolButton *m_uploadFile1;
	QToolButton *m_newFile;    //新建文件
	QToolButton *m_shareFile;  //分享文件
	QToolButton *m_downloadFile;   //下载文件
	QToolButton *m_downloadFile1;
	QToolButton *m_deleteFile;   //删除文件
	QToolButton *m_more;   //更多
	QToolButton *m_more1;

	QToolButton *m_transSave;   //转存

	QToolButton *getNewButton(QString name, QString icon);
};

#endif // QTOOLWIDGET_H
