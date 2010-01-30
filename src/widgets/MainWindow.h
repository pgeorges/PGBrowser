#ifndef __MAINWINDOW__
#define __MAINWINDOW__

#include "MenuBar.h"
#include "MainToolBar.h"
#include "BookmarksToolBar.h"
#include "TabWidget.h"
#include "WebPanel.h"
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtGui/QToolBar>
#include <QtGui/QFocusEvent>
#include <QtGui/QCloseEvent>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const QUrl& url = QUrl(""));
  virtual ~MainWindow();

  MenuBar* menuBar();
  MainToolBar* mainToolBar();
  BookmarksToolBar* bookmarksToolBar();
  TabWidget* tabWidget();
  WebPanel* webPanel();
  void updateBookmarks();
  void setLocationBarText(const QString& text);

public slots:
  void showFindToolBar();
  void closeFindToolBar();
  void findNext();

private:
  void setupFindToolBar();
  void saveWindowState();
  void restoreWindowState();
  void contextMenuEvent(QContextMenuEvent* event);
  void closeEvent(QCloseEvent* event);

private slots:
  void setFindText(const QString& findString);
  void onBookmarkTriggered(const QUrl& url);
  void onTabChanged(WebPanel* webPanel);

private:
  MenuBar* m_menuBar;
  TabWidget* m_tabWidget;
  MainToolBar* m_toolBar;
  BookmarksToolBar* m_bookmarksToolBar;
  QToolBar* m_findToolBar;
  QLineEdit* m_findLineEdit;
};
#endif
