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
	//����Ŀ¼����
	QBaseWidget *m_pShareWidget;
	QHBoxLayout *m_pRootShareLayout;
	//�ҵ��ļ�����
	QBaseWidget *m_pMyFilesWidget;
	QHBoxLayout *m_pRootMyFilesLayout;
	//����Ŀ¼��Ŀ¼
	QBaseWidget *m_pSubShareWidget;
	QHBoxLayout *m_pSubRootShareLayout;

	QToolButton *m_newShare;        //�½�����
	QToolButton *m_editShare;        //�༭����
	QToolButton *m_editShare1;

	QToolButton *m_uploadFile;     //�ϴ��ļ�
	QToolButton *m_uploadFile1;
	QToolButton *m_newFile;    //�½��ļ�
	QToolButton *m_shareFile;  //�����ļ�
	QToolButton *m_downloadFile;   //�����ļ�
	QToolButton *m_downloadFile1;
	QToolButton *m_deleteFile;   //ɾ���ļ�
	QToolButton *m_more;   //����
	QToolButton *m_more1;

	QToolButton *m_transSave;   //ת��

	QToolButton *getNewButton(QString name, QString icon);
};

#endif // QTOOLWIDGET_H
