#ifndef __WEBPAGE__
#define __WEBPAGE__

#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>
#include <QtNetwork/QNetworkRequest>

class MainWindow;
class TabWidget;

class WebPage : public QWebPage
{
  Q_OBJECT

public:
  WebPage(MainWindow* window,
          TabWidget* tabWidget,
          QObject* parent);
  virtual ~WebPage();

  void setCurrentButtons(Qt::MouseButtons mouseButtons);

private:
  QWebPage* createWindow(WebWindowType type);
  bool acceptNavigationRequest(QWebFrame* frame,
                               const QNetworkRequest& request,
                               NavigationType type);

private slots:
  void onLinkHovered(const QString& link, const QString& title, const QString& textContent);

private:
  MainWindow* m_window;
  TabWidget* m_tabWidget;
  Qt::MouseButtons m_currentButtons;
};
#endif

