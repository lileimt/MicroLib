#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QFileInfo>
#include <QDateTime>
#include <QFileDialog>
#include <QApplication>
#include <QCryptographicHash>
#include <QStandardPaths> 

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class CommonHelper{
public:
    static void setStyle(const QString &style){
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        if(!qss.isOpen()){
            #ifdef QT_DEBUG
                qDebug()<<"CommonHelper 18 qss open failed";
            #endif
            qss.close();
            return ;
        }
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }

    static QString getSavePath(){
        QFileDialog dialog;
        dialog.setWindowTitle(QStringLiteral("保存"));
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dialog.setLabelText(QFileDialog::Accept,QString::fromUtf8("保存"));
        if(dialog.exec() == QFileDialog::Accepted){
            #ifdef QT_DEBUG
                //qDebug()<<dialog.selectedUrls().value(0);
                qDebug()<<dialog.selectedFiles().value(0);
            #endif
            return dialog.selectedFiles().value(0);
        }else{
            return "";
        }
    }

    static QString getIconBySuffix(QString fileName,bool bDir = false){
        if(bDir)return QString(":/filetype/dir");
        QFileInfo file(fileName);
        QString suffix = file.suffix().toLower();
        QString type = QString(":/filetype/unknown");
        if(suffix == "apk"){
            type = QString(":/filetype/apk");
        }else if(suffix == "ipa"){
            type = QString(":/filetype/ipa");
        }else if(suffix == "docx" || suffix == "doc"){
            type = QString(":/filetype/doc");
        }else if(suffix == "xlsx" || suffix == "xls"){
            type = QString(":/filetype/xls");
        }else if(suffix == "pptx" || suffix == "ppt"){
            type = QString(":/filetype/ppt");
        }else if(suffix == "html" || suffix == "htm"){
            type = QString(":/filetype/html");
        }else if(suffix == "rar" || suffix == "zip" || suffix == "gz"){
            type = QString(":/filetype/zip");
        }else if(suffix == "jpg" || suffix == "bmp" || suffix == "jpeg" || suffix == "png" || suffix == "gif"){
            type = QString(":/filetype/img");
        }else if(suffix == "mp4" || suffix == "mkv" || suffix == "rmvb" || suffix == "avi" || suffix == "wmv"){
            type = QString(":/filetype/vedio");
        }else if(suffix == "mp3"){
            type = QString(":/filetype/music");
        }else if(suffix == "pdf"){
            type = QString(":/filetype/pdf");
        }else if(suffix == "torrent"){
            type = QString(":/filetype/torrent");
        }else if(suffix == "txt"){
            type = QString(":/filetype/unknown");
        }else if(suffix == "vsd"){
            type = QString(":/filetype/vsd");
        }else{
            type = QString(":/filetype/unknown");
        }
        return type;
    }

	static QString getCurrentTime(){
		QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
		return time.toString("yyyy-MM-dd hh:mm");
	}

	static QString getFileMd5(QString filePath){
		QFile localFile(filePath);
		if (!localFile.open(QFile::ReadOnly)){
			return 0;
		}

		QCryptographicHash ch(QCryptographicHash::Md5);

		quint64 totalBytes = 0;
		quint64 bytesWritten = 0;
		quint64 bytesToWrite = 0;
		quint64 loadSize = 1024 * 4;
		QByteArray buf;

		totalBytes = localFile.size();
		bytesToWrite = totalBytes;

		while (1){
			if (bytesToWrite > 0){
				buf = localFile.read(qMin(bytesToWrite, loadSize));
				ch.addData(buf);
				bytesWritten += buf.length();
				bytesToWrite -= buf.length();
				buf.resize(0);
			}else{
				break;
			}
			if (bytesWritten == totalBytes){
				break;
			}
		}
		localFile.close();
		QByteArray md5 = ch.result();
		return md5.toHex();
	}

	static QString getDownloadDir(){ 
		QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/MicroLib/";
		QDir dir(path);
		if (!dir.exists()){
			dir.mkdir(path);
		}
		return path;
	}
};

#endif // COMMONHELPER_H
