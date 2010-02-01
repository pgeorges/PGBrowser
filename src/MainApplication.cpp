#include "MainApplication.h"
#include "widgets/MainWindow.h"
#include "widgets/MenuBar.h"
#include "widgets/PasswordDialog.h"
#include <QtWebKit/QWebSettings>
#include <QtGui/QDesktopServices>

const QString MainApplication::ORGANISATION_NAME = "Peter Georges";
const QString MainApplication::APPLICATION_NAME = "PGBrowser";
MainApplication* MainApplication::s_application = 0;

MainApplication::MainApplication(int & argc, char ** argv)
: QtSingleApplication(argc, argv)
, m_homePage(QString("http://www.google.com"))
, m_openInTab(1)
, m_pluginDefault(1)
{
  //create the bookmark container
  m_bookmarksContainer = new BookmarksContainer();

  //create the proxy
  m_networkProxy = new QNetworkProxy(QNetworkProxy::NoProxy, QString(""), 0);

  //create the cookie jar
  m_persistentCookieJar = new PersistentCookieJar(this);

  //create the network access manager object
  m_networkAccessManager = new QNetworkAccessManager(this);
  m_networkAccessManager->setProxy(*m_networkProxy);
  m_networkAccessManager->setCookieJar(m_persistentCookieJar);

  connect(m_networkAccessManager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
          this, SLOT(onAuthenticationRequired(QNetworkReply*, QAuthenticator*)));
  connect(m_networkAccessManager, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),
          this, SLOT(onProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)));
  connect(m_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(onFinished(QNetworkReply*)));

  connect(this, SIGNAL(messageReceived(const QString&)), 
          this, SLOT(onMessageReceived(const QString&)));

  restoreState();

  //set the default web settings
  m_settings = new QSettings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, pluginDefault());
  QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);

  setWindowIcon(QIcon("icons/logo.png"));
}

MainApplication::~MainApplication()
{
  saveState();
  delete m_bookmarksContainer;
  delete m_networkProxy;
  delete m_persistentCookieJar;
  delete m_networkAccessManager;
}

void MainApplication::saveState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  settings.setValue("Application/homePage", homePage());
  settings.setValue("Application/openInTab", openInTab());
  settings.setValue("Application/pluginDefault", pluginDefault());
  settings.setValue("Application/proxyType", proxyType());
  settings.setValue("Application/proxyHostname", proxyHostName());
  settings.setValue("Application/proxyPort", m_networkProxy->port());
}

void MainApplication::restoreState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  if (settings.value("Application/homePage").isValid())
    setHomePage(settings.value("Application/homePage").toString());
  if (settings.value("Application/openInTab").isValid())
    setOpenInTab(settings.value("Application/openInTab").toBool());
  if (settings.value("Application/pluginDefault").isValid())
    setPluginDefault(settings.value("Application/pluginDefault").toBool());
  if (settings.value("Application/proxyHostname").isValid())
    m_networkProxy->setHostName(settings.value("Application/proxyHostname").toString());
  if (settings.value("Application/proxyPort").isValid())
    m_networkProxy->setPort(settings.value("Application/proxyPort").toInt());
  if (settings.value("Application/proxyType").isValid())
    setProxyType((QNetworkProxy::ProxyType)settings.value("Application/proxyType").toInt());
}

MainApplication* MainApplication::application()
{
  if (!s_application)
  {
    int* argc = new int(0);
    s_application = new MainApplication(*argc, NULL);
  }

  return s_application;
}

void MainApplication::registerWindow(MainWindow* window)
{
  m_mainWindows.append(window);
}

void MainApplication::unregisterWindow(MainWindow* window)
{
  m_mainWindows.removeOne(window);
}

MainWindowList MainApplication::mainWindows()
{
  return m_mainWindows;
}

QDir MainApplication::temporaryDir()
{
  QDir temporaryPath(QString(QDir::tempPath() + "/" + MainApplication::APPLICATION_NAME));
  if (!temporaryPath.exists())
  {
    temporaryPath.mkpath(temporaryPath.path());
  }
  return temporaryPath;
}

BookmarksContainer* MainApplication::bookmarksContainer()
{
  return m_bookmarksContainer;
}

QNetworkAccessManager* MainApplication::networkAccessManager()
{
  return m_networkAccessManager; 
}

void MainApplication::setHomePage(const QString& homePage)
{
  m_homePage = homePage;
}

QString MainApplication::homePage()
{
  return m_homePage;
}

void MainApplication::setOpenInTab(int status)
{
  m_openInTab = status;
}

void MainApplication::setPluginDefault(int status)
{
  m_pluginDefault = status;
}

bool MainApplication::openInTab()
{
  return m_openInTab;
}

bool MainApplication::pluginDefault()
{
  return m_pluginDefault;
}

void MainApplication::setProxyType(QNetworkProxy::ProxyType type)
{
  QNetworkProxy* networkProxy = new QNetworkProxy(type);
  networkProxy->setHostName(m_networkProxy->hostName());
  networkProxy->setPort(m_networkProxy->port());
  m_networkAccessManager->setProxy(*networkProxy);
  delete m_networkProxy;
  m_networkProxy = networkProxy;
}

QNetworkProxy::ProxyType MainApplication::proxyType()
{
  return m_networkProxy->type();
}

void MainApplication::setProxyHostName(const QString& hostName)
{
  m_networkProxy->setHostName(hostName);
}

QString MainApplication::proxyHostName()
{
  return m_networkProxy->hostName();
}

void MainApplication::setProxyPort(quint16 port)
{
  m_networkProxy->setPort(port);
}

QString MainApplication::proxyPort()
{
  char buffer[50];
  snprintf(buffer, 50, "%d", m_networkProxy->port());
  return buffer;
}

void MainApplication::onProxyAuthenticationRequired(const QNetworkProxy& networkProxy, QAuthenticator* authenticator)
{
  PasswordDialog passwordDialog(activationWindow());
  passwordDialog.exec();

  if (passwordDialog.result() == QDialog::Accepted)
    authenticator->setUser(passwordDialog.userName());
    authenticator->setPassword(passwordDialog.password());
}

void MainApplication::onAuthenticationRequired(QNetworkReply* networkReply, QAuthenticator* authenticator)
{
  PasswordDialog passwordDialog(activationWindow());
  passwordDialog.exec();

  if (passwordDialog.result() == QDialog::Accepted)
  {
    authenticator->setUser(passwordDialog.userName());
    authenticator->setPassword(passwordDialog.password());
  }
}
 
void MainApplication::onFinished(QNetworkReply* networkReply)
{
}

void MainApplication::onMessageReceived(const QString& message)
{
  if (message.isEmpty())
    return;

  MainWindow* window = dynamic_cast<MainWindow*>(activationWindow());
  window->tabWidget()->addNewTab(QUrl(message), true);
}
