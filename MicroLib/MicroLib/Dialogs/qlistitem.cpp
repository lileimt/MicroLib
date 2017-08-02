#include "qlistitem.h"

QListItem::QListItem(QString user, int id, int type, QWidget *parent)
	: QBaseWidget(parent)
{
	ui.setupUi(this);
	m_id = id;
	ui.lblUser->setText(user);
	if (type == 0){
		ui.lblOther->setText(QStringLiteral("仅查看"));
	}else if(type == 1){
		ui.lblOther->setText(QStringLiteral("查看和上传"));
	}else{
		ui.lblOther->hide();
	}

	connect(ui.btnCancel, &QToolButton::clicked, [=](){
		emit sigCancelClicked(m_id);
	});
}

QListItem::~QListItem()
{

}

QString QListItem::getName()
{
	return ui.lblUser->text();
}
