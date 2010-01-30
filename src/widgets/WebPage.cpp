#include "WebPage.h"
#include "MainWindow.h"
#include "TabWidget.h"
#include <QtGui/QCursor>
#include <QtGui/QToolTip>
#include <QtWebKit/QWebView>
#include <iostream>

WebPage::WebPage(MainWindow* window,
                 TabWidget* tabWidget,
                 QObject* parent)
: QWebPage(parent)
, m_window(window)
, m_tabWidget(tabWidget)
, m_currentButtons(Qt::NoButton)
{
  connect(this, SIGNAL(linkHovered(const QString&, const QString&, const QString&)),
          this, SLOT(onLinkHovered(const QString&, const QString&, const QString&)));
}

WebPage::~WebPage()
{
}

void WebPage::onLinkHovered(const QString& link, const QString& title, const QString& textContent)
{
//  if (link.isEmpty())
//    QToolTip::hideText();
//  else
  QString tooltip = link;
  if (tooltip.length() > 80)
  {
    tooltip = tooltip.left(40) + QString("...") + tooltip.right(40);
  }
  QToolTip::showText(QCursor::pos(), tooltip);
}

void WebPage::setCurrentButtons(Qt::MouseButtons buttons)
{
  m_currentButtons = buttons;
}

QWebPage* WebPage::createWindow(WebWindowType type)
{
  qDebug() << QString("create window request");
  if (type == QWebPage::WebModalDialog)
  {
    QWebView* webPanel = new QWebView();
    webPanel->show();
    return webPanel->page();
  }

  if (MainApplication::application()->openInTab())
  {
    WebPanel* webPanel = m_tabWidget->addNewTab(true);
    return webPanel->page();
  }
  else
  {
    MainWindow* window = new MainWindow();
    window->show();
    return window->webPanel()->page();
  }
}

bool WebPage::acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type)
{
  if (type == QWebPage::NavigationTypeLinkClicked && m_currentButtons == Qt::MidButton)
  {
    qDebug() << QString("navigation request (new tab): ") << request.url();
    m_tabWidget->addNewTab(request.url());
    return false;
  }

  qDebug() << QString("accept navigation request") << request.url();
  return QWebPage::acceptNavigationRequest(frame, request, type);
}

#include "WebPage.moc"

