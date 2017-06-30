#ifndef QTOOLWIDGET_H
#define QTOOLWIDGET_H

#include "Base/qbasewidget.h"
#include "ui_toolwidget.h"
#include "qsearchwidget.h"
#include <QHBoxLayout>

#define RELEASE(x) if(x){delete x;x= NULL;}

class QToolWidget : public QBaseWidget
{
	Q_OBJECT

public:
	QToolWidget(QWidget *parent = 0);
	~QToolWidget();

	void showRootShareLayout();
	void showSubRootShareLayout();
	void showRootMyFilesLayout();

private:
	Ui::QToolWidget ui;
	QSearchWidget *m_searchWidget;
	QHBoxLayout *m_pLayout;
	//公共目录布局
	QHBoxLayout *m_pRootShareLayout;
	//我的文件布局
	QHBoxLayout *m_pRootMyFilesLayout;
	//公共目录子目录
	QHBoxLayout *m_pSubRootShareLayout;

	QToolButton *m_newShare;        //新建共享
	QToolButton *m_editShare;        //编辑共享

	QToolButton *m_uploadFile;     //上传文件
	QToolButton *m_newFile;    //新建文件
	QToolButton *m_shareFile;  //分享文件
	QToolButton *m_downloadFile;   //下载文件
	QToolButton *m_more;   //更多

	QToolButton *m_transSave;   //转存

	void setRootShareLayout();
	void setSubRootShareLayout();
	void setRootMyFilesLayout();
	QToolButton *getNewButton(QString name, QString icon);
};

#endif // QTOOLWIDGET_H
