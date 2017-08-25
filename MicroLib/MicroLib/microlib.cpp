#include "microlib.h"
#include <QFileDialog>
#include <QFileInfo>
#include "Common/commonhelper.h"
#include "../Net/Net/Net.h"

#pragma  comment(lib,"../Debug/Net.lib")

MicroLib::MicroLib(QWidget *parent)
	: QMainWindow(parent),
	m_subTransWidget(NULL),
	m_transWidget(NULL),
	m_baseTransWidget(NULL),
	m_forwardWidget(NULL),
	m_staticsWidget(NULL),
	m_newDirsWidget(NULL),
	m_newDirsNextWidget(NULL),
	m_msgWidget(NULL),
	m_sendWidget(NULL),
	m_bPressed(false),
	m_bCovered(false),
	m_eOperType(sharefiles)
{
	ui.setupUi(this);

	globalInitCurl();
	m_user = new QUser;
	getUserInfo();

	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);
	setWindowTitle(QStringLiteral("微库"));
	setFixedSize(WIDTH, HEIGHT);

	QWidget *widget = new QWidget();
	this->setCentralWidget(widget);

	m_baseTransWidget = new QBaseTransparentWidget(this);
	m_baseTransWidget->resize(WIDTH, HEIGHT);
	m_baseTransWidget->hide();

	m_pLayout = new QVBoxLayout(widget);
	m_titleWidget = new QTitleWidget(widget);
	m_toolWidget = new QToolWidget(widget);

	m_pHLayout = new QHBoxLayout(widget);
	m_webEngine = new QBaseWebEngineView(widget);

	m_sideWidget = new QSideWidget(widget);
	m_sideWidget->hide();
	m_pHLayout->addWidget(m_webEngine);
	m_pHLayout->addWidget(m_sideWidget);

	m_subTransWidget = new QSubTransWidget(widget);
	m_subTransWidget->hide();
	m_transWidget = new QTransportWidget(QStringLiteral("传输列表"),true,widget);
	//m_transWidget->setGeometry(rect.right() - m_transWidget->width(), rect.bottom() - m_transWidget->height(), m_transWidget->width(), m_transWidget->height());
	m_transWidget->hide();

	m_pLayout->addWidget(m_titleWidget);
	m_pLayout->addWidget(m_toolWidget);
	m_pLayout->addLayout(m_pHLayout);
	m_pHLayout->setContentsMargins(0, 0, 0, 0);
	m_pHLayout->setMargin(0);
	m_pHLayout->setSpacing(0);
	m_pLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayout->setMargin(0);
	m_pLayout->setSpacing(0);
	widget->setLayout(m_pLayout);

	//connect处理
	sigConnect();
	//showForwardWidget();
	//showStaticsWidget();
	//showNewDirsWidget();
	//showNewDirsNextWidget();
}

QChannel *MicroLib::getChannel()
{
	return m_webEngine->getChannel();
}

void MicroLib::sigConnect()
{
	//标题栏
	connect(m_titleWidget, &QTitleWidget::sigMinClicked, [=](){
		showMinimized();
	});
	connect(m_titleWidget, &QTitleWidget::sigCloseClicked, [=](){
		qApp->quit();
	});
	connect(m_titleWidget, &QTitleWidget::sigShareClicked, [=](OPERTYPE type){
		if (type != m_eOperType){
			m_eOperType = type;
			getChannel()->setCurType(type);
			m_toolWidget->showIndex(shareindex);
		}
	});
	connect(m_titleWidget, &QTitleWidget::sigMyFilesClicked, [=](OPERTYPE type){
		if (type != m_eOperType){
			m_eOperType = type;
			getChannel()->setCurType(type);
			m_toolWidget->showIndex(myfilesindex);
		}
	});
	connect(m_titleWidget, &QTitleWidget::sigDangClicked, [=](){
		if (m_msgWidget == NULL){
			m_msgWidget = new QMsgWidget(this);
			m_msgWidget->setGeometry(WIDTH - m_msgWidget->width(), m_titleWidget->height(), m_msgWidget->width(), m_msgWidget->height());
		}
		if (m_msgWidget->isVisible()){
			m_msgWidget->hide();
		}else{
			m_msgWidget->show();
		}
	});
	//工具栏
	connect(m_toolWidget, &QToolWidget::sigUploadClicked, [=](){
		openUploadFileDialog();
	});
	//下载文件
	connect(m_toolWidget, &QToolWidget::sigDownloadClicked, [=](){
		//downloadFiles();
		getChannel()->setCurFiles();
	});
	connect(m_toolWidget, &QToolWidget::sigNewShareClicked, [=](){
		//创建子窗口
		RELEASE(m_newDirsWidget);
		RELEASE(m_newDirsNextWidget);
		m_newDirsWidget = new QNewDirsWidget(m_baseTransWidget);
		m_newDirsWidget->move((WIDTH - m_newDirsWidget->width()) / 2, (HEIGHT - m_newDirsWidget->height()) / 2);
		m_newDirsWidget->hide();
		m_newDirsNextWidget = new QNewDirsNextWidget(m_baseTransWidget, m_user);
		m_newDirsNextWidget->move((WIDTH - m_newDirsNextWidget->width()) / 2, (HEIGHT - m_newDirsNextWidget->height()) / 2);
		m_newDirsNextWidget->hide();

		showNewDirsWidget();
	});
	connect(m_toolWidget, &QToolWidget::sigNewDirClicked, [=](){
		getChannel()->setNewDir();
	});
	connect(m_toolWidget, &QToolWidget::sigEditShareClicked, [=](){
		
	});
	connect(m_toolWidget, &QToolWidget::sigDeleteClicked, [=](){
		getChannel()->deleteFiles();
	});
	//下载子窗口
	connect(m_subTransWidget, &QSubTransWidget::clicked, [=](){
		m_subTransWidget->hide();
		m_transWidget->show();
	});
	//下载窗口
	connect(m_transWidget, &QTransportWidget::sigMinClicked, [=](){
		m_transWidget->hide();
		QRect rect = m_webEngine->geometry();
		m_subTransWidget->setGeometry(rect.right() - 202, rect.bottom() - 36, 202, 36);
		m_subTransWidget->show();
	});
	//js端控制窗口
	connect(getChannel(), &QChannel::sigChangeToolBar, [=](int index){
		m_toolWidget->showIndex((TOOLINDEX)index);
	});
	connect(getChannel(), &QChannel::sigStartDownload, [=](QString curFiles){
		downloadFiles(curFiles);
	});
	connect(getChannel(), &QChannel::sigSendFiles, [=](QString ids){		
		QJsonValue val(ids);
		QJsonArray arr = val.toArray();
		ShowSendFilesWidget(ids);
	});
	connect(getChannel(), &QChannel::sigShowSideBar, [=](bool bVisble){
		if (bVisble){
			if (!m_sideWidget->isVisible()){
				m_sideWidget->show();
			}
		}else{
			m_sideWidget->hide();
		}
	});
	connect(getChannel(), &QChannel::sigDeleteEnable, [=](bool enable){
		m_toolWidget->setButtonEnable(m_toolWidget->getIndex(),enable);
	});
}

MicroLib::~MicroLib()
{
	RELEASE(m_pLayout);
	RELEASE(m_titleWidget);
	RELEASE(m_toolWidget);
	RELEASE(m_subTransWidget);
	RELEASE(m_forwardWidget);
	RELEASE(m_baseTransWidget);
	RELEASE(m_msgWidget);
	globalCleanUpCurl();
}

void MicroLib::showForwardWidget()
{
	m_bCovered = true;
	RELEASE(m_forwardWidget);
	m_forwardWidget = new QForwardWidget(m_baseTransWidget);
	m_forwardWidget->move((WIDTH - m_forwardWidget->width()) / 2, (HEIGHT - m_forwardWidget->height()) / 2);
	m_forwardWidget->show();
	m_baseTransWidget->show();

	connect(m_forwardWidget, &QForwardWidget::sigCloseClicked, [=](){
		m_baseTransWidget->close();
		m_bCovered = false;
	});
}

void MicroLib::showStaticsWidget()
{
	m_bCovered = true;
	RELEASE(m_staticsWidget);
	m_staticsWidget = new QStaticsWidget(m_baseTransWidget);
	m_staticsWidget->move((WIDTH - m_staticsWidget->width()) / 2, (HEIGHT - m_staticsWidget->height()) / 2);
	m_staticsWidget->show();
	m_baseTransWidget->show();

	connect(m_staticsWidget, &QStaticsWidget::sigCloseClicked, [=](){
		m_staticsWidget->close();
		m_baseTransWidget->close();
		m_bCovered = false;
	});
}

void MicroLib::showNewDirsWidget()
{
	m_bCovered = true;
	m_newDirsWidget->show();
	m_baseTransWidget->show();

	connect(m_newDirsWidget, &QNewDirsWidget::sigCloseClicked, [=](){
		m_newDirsWidget->close();
		m_baseTransWidget->close();
		m_bCovered = false;
	});
	connect(m_newDirsWidget, &QNewDirsWidget::sigNextClicked, [=](){
		if (!m_newDirsWidget->getFileName().isEmpty()){
			m_newDirsWidget->close();
			showNewDirsNextWidget();
		}
	});
}

void MicroLib::showNewDirsNextWidget()
{
	m_bCovered = true;
	m_newDirsNextWidget->setInfo(m_newDirsWidget->getFileName(), m_newDirsWidget->getComment());
	m_newDirsNextWidget->show();
	connect(m_newDirsNextWidget, &QNewDirsNextWidget::sigCloseClicked, [=](){
		m_newDirsNextWidget->close();
		m_baseTransWidget->close();
		m_bCovered = false;
	});

	connect(m_newDirsNextWidget, &QNewDirsNextWidget::sigBackClicked, [=](){
		m_newDirsNextWidget->close();
		showNewDirsWidget();
	});
	connect(m_newDirsNextWidget, &QNewDirsNextWidget::sigCreateClicked, [=](){
		QParseJson json;
		int id = getChannel()->getId();
		QString filename = m_newDirsNextWidget->getFileName();
		QString comment = m_newDirsNextWidget->getComment();
		int notice = m_newDirsNextWidget->getNotice();
		QString msg = m_newDirsNextWidget->getMsg();
		string strPost = json.getCreateDocumentJson(id, filename, m_newDirsNextWidget->getListWidget(), m_newDirsNextWidget->getSubmitter(), comment, notice, msg).toStdString();
		string  strRes = httpPost(NEWSHAREURL, strPost, TOKEN);
		QJsonParseError json_error;
		QJsonDocument parse_doucment = QJsonDocument::fromJson(strRes.data(), &json_error);
		if (json_error.error == QJsonParseError::NoError){
			if (parse_doucment.isObject()){
				QJsonObject obj = parse_doucment.object();
				if (obj.contains("id")){
					QJsonValue value = obj.take("id");
					int id = value.toString().toInt();
					getChannel()->setNewCommonDir(id, filename, 1);
					m_newDirsNextWidget->close();
					m_baseTransWidget->close();
					m_bCovered = false;
				}else{
					qDebug() << "error1";
				}
			}else{
				qDebug() << "error2";
			}
		}
	});
}

//显示发送窗口
void MicroLib::ShowSendFilesWidget(QString ids)
{
	QParseJson json;
	QJsonArray arrIds = json.parseSendFileId(ids);

	m_bCovered = true;
	RELEASE(m_sendWidget);
	m_sendWidget = new QSendWidget(m_baseTransWidget, m_user, arrIds.count());
	m_sendWidget->move((WIDTH - m_sendWidget->width()) / 2, (HEIGHT - m_sendWidget->height()) / 2);
	m_sendWidget->show();
	m_baseTransWidget->show();

	connect(m_sendWidget, &QSendWidget::sigCloseClicked, [=](){
		m_sendWidget->close();
		m_baseTransWidget->close();
		m_bCovered = false;
	});

	connect(m_sendWidget, &QSendWidget::sigOKClicked, [=](){
		sendFile(arrIds, m_sendWidget->getComment());

		m_sendWidget->close();
		m_baseTransWidget->close();
		m_bCovered = false;
	});
}

void MicroLib::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton){
		QPoint pos = event->pos();
		if (m_titleWidget->rect().contains(pos) && !m_bCovered){
			m_bPressed = true;
			m_point = pos;
		}
	}
}

void MicroLib::mouseReleaseEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	m_bPressed = false;
}

void MicroLib::mouseMoveEvent(QMouseEvent *event)
{
	if (m_bPressed){
		QPoint pt = event->globalPos();
		move(pt - m_point);
	}
}

void MicroLib::openUploadFileDialog()
{
	QFileDialog dialog(this);
	dialog.setWindowTitle(QStringLiteral("请选择上传的文件"));
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setViewMode(QFileDialog::Detail);
	dialog.setLabelText(QFileDialog::Accept, QStringLiteral("上传"));
	if (dialog.exec() == QDialog::Accepted){
		QStringList fileNames = dialog.selectedFiles();
		for (int i = 0; i < fileNames.length(); i++){
			QFileInfo fileInfo(fileNames[i]);
			FILETRANSPORT *st = new FILETRANSPORT;
			st->fileName = fileInfo.fileName();
			st->fileIcon = CommonHelper::getIconBySuffix(st->fileName);
			st->filePath = fileInfo.filePath();
			st->fileSize = QString::number(fileInfo.size());
			st->state = upload;//上传
			st->status = normal;//正常
			m_transWidget->insertList(st);
		}
		if (!m_transWidget->isVisible()){//窗口不可见
			QRect rect = m_webEngine->geometry();
			m_transWidget->setGeometry(rect.right() - m_transWidget->width(), rect.bottom() - m_transWidget->height(), m_transWidget->width(), m_transWidget->height());
			m_transWidget->show();
		}
	}
}

void MicroLib::getUserInfo()
{
	string userInfo = httpGet(USERURL, TOKEN);
	m_parseJson.getUserInfo(userInfo,m_user);
}

void MicroLib::downloadFiles(QString curFiles)
{
	m_transWidget->initTransList(curFiles);
	if (!m_transWidget->isVisible()){//窗口不可见，则显示窗口
		QRect rect = m_webEngine->geometry();
		m_transWidget->setGeometry(rect.right() - m_transWidget->width(), rect.bottom() - m_transWidget->height(), m_transWidget->width(), m_transWidget->height());
		m_transWidget->show();
	}
}

void MicroLib::sendFile(QJsonArray ids, QString comment)
{
	QParseJson json;
	string strPost = json.getSendFileJson(m_sendWidget,ids,comment).toStdString();
	string  strRes = httpPost(SendFileURL, strPost, TOKEN);
}
