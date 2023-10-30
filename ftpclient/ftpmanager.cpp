#include "ftpmanager.h"

#include <QFileInfo>

FtpManager::FtpManager(QObject *parent)
    : QObject{parent}
{
  m_isUploading = OperationStatus::INVALID;
}

void FtpManager::setHostPort(const QString &host, const int port)
{
  m_hostname = host;
  m_port = port;
}

void FtpManager::setUserInfo(const QString &username, const QString &password)
{
  m_username = username;
  m_password = password;
}

void FtpManager::put(const QString &localFileName, const QString &remoteDirName)
{
  if (localFileName.isEmpty()) {
    return;
  }

  QFile file(localFileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug("Failed to open file: %s\n", qPrintable(localFileName));
    return;
  }
  QByteArray data = file.readAll();
  file.close();
  if (data.isEmpty()) {
    qDebug("Ffile(%s) is empty\n", qPrintable(localFileName));
    return;
  }

  QFileInfo fileInfo(localFileName);
  QUrl url;
  url.setScheme("ftp");
  url.setHost(m_hostname);
  url.setPort(m_port);
  url.setUserName(m_username);
  url.setPassword(m_password);
  url.setPath(remoteDirName + "/" + fileInfo.fileName());

//  QNetworkReply *pReply = m_manager.put(QNetworkRequest(url), data);
//  connect(pReply, )
}
