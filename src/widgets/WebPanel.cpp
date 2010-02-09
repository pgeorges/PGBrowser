#include "../MainApplication.h"
#include "WebPanel.h"
#include "MainWindow.h"
#include "TabWidget.h"
#include <QtCore/Qt>
#include <QtCore/QString>
#include <QtGui/QKeySequence>
#include <QtGui/QColor>
#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QNetworkRequest>
#include <iostream>

WebPanel::WebPanel(MainWindow* window, TabWidget* tabWidget, const QUrl& url)
: QWebView()
, m_window(window)
, m_tabWidget(tabWidget)
, m_currentProgress(0)
{
  m_webPage = new WebPage(m_window, m_tabWidget, this);
  setPage(m_webPage);

  //set the default background color to white
  QPalette palette = page()->palette();
  palette.setColor(QPalette::Base, QColor(255,255,255));
  page()->setPalette(palette);

  //set the networkAccessManager
  MainApplication* application = MainApplication::application();
  page()->setNetworkAccessManager(application->networkAccessManager());

  connect(this, SIGNAL(iconChanged()), this, SLOT(onIconChange()));
  connect(this, SIGNAL(loadStarted()), this, SLOT(loadStarted()));
  connect(this, SIGNAL(loadProgress(int)), this, SLOT(loadProgress(int)));
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadFinished(bool)));
  connect(this, SIGNAL(titleChanged(const QString&)), this, SLOT(onTitleChange(const QString&)));
  connect(this, SIGNAL(urlChanged(const QUrl&)), this, SLOT(onUrlChange(const QUrl&)));
  connect(page(), SIGNAL(downloadRequested(const QNetworkRequest&)), this, SLOT(onDownloadRequested(const QNetworkRequest&)));

  setUrl(url);
}

WebPanel::~WebPanel()
{
}

void WebPanel::setUrl(const QUrl& url)
{
  load (url);
}

void WebPanel::setUrl(QString& url)
{
  setUrl(QUrl(url));
}

int WebPanel::currentProgress()
{
  return m_currentProgress;
}

void WebPanel::loadStarted()
{
  if (m_tabWidget->isSelectedWidget(this))
  {
    m_window->mainToolBar()->setStopButtonDisabled(false);
    m_window->mainToolBar()->progressBarAction()->setVisible(true);
  }
}

void WebPanel::loadProgress(int progress)
{
  m_currentProgress = progress;
  if (m_tabWidget->isSelectedWidget(this))
  {
    m_window->mainToolBar()->setStopButtonDisabled(false);
    m_window->mainToolBar()->setNavigationButtonStates(this);
    m_window->mainToolBar()->progressBarAction()->setVisible(true);
    m_window->mainToolBar()->progressBar()->setValue(progress);
  }
}

void WebPanel::loadFinished(bool ok)
{
  m_currentProgress = 0;

  if (!ok)
    return;

  m_tabWidget->setTabToolTip(this, title() + QString("\n") + url().toString());
  m_tabWidget->setTabIcon(this, icon());

  if (m_tabWidget->isSelectedWidget(this))
  {
    m_window->mainToolBar()->setNavigationButtonStates(this);
    m_window->mainToolBar()->setStopButtonDisabled(true);
    m_window->mainToolBar()->progressBarAction()->setVisible(false);
  }
}

void WebPanel::onTitleChange(const QString& title)
{
  QString panelTitle = title;
  if (panelTitle.isEmpty())
      panelTitle = "Untitled";
  m_tabWidget->setTabTitle(this, panelTitle);
}

void WebPanel::onIconChange()
{
  m_tabWidget->setTabIcon(this, icon());
}

void WebPanel::onUrlChange(const QUrl& url)
{
  if (m_tabWidget->isSelectedWidget(this))
    if (!m_window->mainToolBar()->locationBar()->hasFocus() or
        m_window->mainToolBar()->locationBar()->text().isEmpty())
      m_window->setLocationBarText(url.toString());
}

void WebPanel::onDownloadRequested(const QNetworkRequest& request)
{
  std::cout << "download" << std::endl;
}

void WebPanel::mouseReleaseEvent(QMouseEvent* event)
{
  m_webPage->setCurrentButtons(event->button());
  QWebView::mouseReleaseEvent(event);
}

void WebPanel::setTabStatus()
{
  QString titleStr = title();
  QString toolTipStr = titleStr + QString("\n") + url().toString();
  m_tabWidget->setTabTitle(this, titleStr);
  m_tabWidget->setTabToolTip(this, toolTipStr);
}


