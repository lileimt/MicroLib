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
	//����Ŀ¼����
	QHBoxLayout *m_pRootShareLayout;
	//�ҵ��ļ�����
	QHBoxLayout *m_pRootMyFilesLayout;
	//����Ŀ¼��Ŀ¼
	QHBoxLayout *m_pSubRootShareLayout;

	QToolButton *m_newShare;        //�½�����
	QToolButton *m_editShare;        //�༭����

	QToolButton *m_uploadFile;     //�ϴ��ļ�
	QToolButton *m_newFile;    //�½��ļ�
	QToolButton *m_shareFile;  //�����ļ�
	QToolButton *m_downloadFile;   //�����ļ�
	QToolButton *m_more;   //����

	QToolButton *m_transSave;   //ת��

	void setRootShareLayout();
	void setSubRootShareLayout();
	void setRootMyFilesLayout();
	QToolButton *getNewButton(QString name, QString icon);
};

#endif // QTOOLWIDGET_H
