#ifndef __TABWIDGET__
#define __TABWIDGET__

#include <QtGui/QTabWidget>
#include <QtGui/QIcon>
#include <QtCore/QString>
#include <QtCore/QUrl>

class MainWindow;

class TabWidget : public QTabWidget
{
  Q_OBJECT

public:
  TabWidget(MainWindow * window, QWidget* parent);
  virtual ~TabWidget();

  void setTabTitle(QWidget* widget, QString& title);
  void setTabIcon(QWidget* widget, const QIcon& icon);
  void setTabToolTip(QWidget* widget, const QString& tooltip);
  bool isSelectedWidget(QWidget* widget);

signals:
  void tabChanged(WebPanel* webPanel);

public slots:
  WebPanel* addNewTab(bool switchToTab=false);
  WebPanel* addNewTab(const QUrl& url, bool switchToTab=false);
  void closeTab(QWidget* widget);
  void closeTab(int index);

private:
  QString elideTitle(QString title);

private slots:
  void tabChanged(int index);
  void createContextMenu(const QPoint& pos);

private:
  MainWindow* m_window;
};
#endif
