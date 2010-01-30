#ifndef __WEBPANEL__
#define __WEBPANEL__

#include "WebPage.h"
#include "LocationBar.h"
#include "../MainApplication.h"
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtCore/QUrl>
#include <QtWebKit/QWebView>
#include <QtNetwork/QNetworkRequest>

class MainWindow;
class TabWidget;

class WebPanel : public QWebView
{
  Q_OBJECT

public:
  WebPanel(MainWindow* window,
           TabWidget* tabWidget,
           const QUrl& url = QUrl(MainApplication::application()->homePage()));
  virtual ~WebPanel();

  void setUrl(const QUrl& url);
  void setUrl(QString& url);
  int currentProgress();

private:
  void setTabStatus();
  void mouseReleaseEvent(QMouseEvent* event);

private slots:
  void loadStarted();
  void loadProgress(int progress);
  void loadFinished(bool ok);
  void onTitleChange(const QString& title);
  void onIconChange();
  void onUrlChange(const QUrl& url);
  void onDownloadRequested(const QNetworkRequest& request);

private:
  WebPage* m_webPage;
  MainWindow* m_window;
  TabWidget* m_tabWidget;
  int m_currentProgress;
};
#endif

