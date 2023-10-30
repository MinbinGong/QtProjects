#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QObject>
#include <QUrl>
#include <QFile>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class FtpManager : public QObject
{
  Q_OBJECT
 public:
  explicit FtpManager(QObject *parent = nullptr);

  void setHostPort(const QString &host, const int port);
  void setUserInfo(const QString &username, const QString &password);
  void put(const QString &localFileName, const QString &localDirName);
  void get(const QString &remoteFileName, const QString &localDirName);

  void uploadFiles(const QStringList localFileNames, const QString &remoteDirName);
  void downloadFiles(const QStringList remoteFileNames, const QString &localDirName);

 signals:
  void sigError(QNetworkReply::NetworkError);
  void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
  void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
  void oneFileUploaded(QString);
  void allFilesUploaded();
  void oneFileDownloaded(QString);
  void allFilesDownloaded();

 private slots:
  void downloadFinished();
  void updateUploadProcess(qint64 bytesSent, qint64 bytesTotal);
  void updateDownloadProcess(qint64 bytesReceived, qint64 bytesTotal);
  void updateError(QNetworkReply::NetworkError);

 private:
  QFile m_file;
  QNetworkAccessManager m_manager;

 private:
  QString m_username;
  QString m_password;
  QString m_hostname;
  int     m_port;

 private:
  enum class OperationStatus {
    UPLOAD,
    DOWNLOAD,
    INVALID
  };
  OperationStatus m_isUploading;
  QStringList m_downloadFileList;
  QString m_downloadSavepath;
  QString m_downloadingFileName;

  QStringList m_uploadFileList;
  QString m_uploadSavePath;
  QString m_uploadingFileName;

};

#endif // FTPMANAGER_H
