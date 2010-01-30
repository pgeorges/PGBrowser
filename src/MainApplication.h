#ifndef __MAINAPPLICATION__
#define __MAINAPPLICATION__

#include "bookmarks/BookmarksContainer.h"
#include "network/PersistentCookieJar.h"
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtSingleApplication>
#include <QtGui/QIcon>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class MainWindow;
typedef QList<MainWindow*> MainWindowList;
Q_DECLARE_METATYPE(MainWindowList);

class MainApplication : public QtSingleApplication
{
  Q_OBJECT

public:
  MainApplication(int&, char**);
  virtual ~MainApplication();

  static MainApplication* application();
  void registerWindow(MainWindow* window);
  void unregisterWindow(MainWindow* window);
  MainWindowList mainWindows();

  static QDir temporaryDir();
  QString homePage();
  bool openInTab();
  bool pluginDefault();
  BookmarksContainer* bookmarksContainer();
  QNetworkAccessManager* networkAccessManager();
  QNetworkProxy::ProxyType proxyType();
  QString proxyHostName();
  QString proxyPort();

public slots:
  void setHomePage(const QString& homePage);
  void setOpenInTab(int status);
  void setPluginDefault(int status);
  void setProxyType(QNetworkProxy::ProxyType type);
  void setProxyHostName(const QString& hostName);
  void setProxyPort(quint16 port);

private:
  void saveState();
  void restoreState();

private slots:
  void onProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*);
  void onAuthenticationRequired(QNetworkReply*, QAuthenticator*);
  void onFinished(QNetworkReply*);
  void onMessageReceived(const QString& message);

public:
  static const QString ORGANISATION_NAME;
  static const QString APPLICATION_NAME;

private:
  static MainApplication* s_application;
  MainWindowList m_mainWindows;
  QString m_homePage;
  bool m_openInTab;
  bool m_pluginDefault;
  QSettings* m_settings;
  BookmarksContainer* m_bookmarksContainer;
  QNetworkAccessManager* m_networkAccessManager;
  QNetworkProxy* m_networkProxy;
  QNetworkCookieJar* m_networkCookieJar;
  PersistentCookieJar* m_persistentCookieJar;
};
#endif

