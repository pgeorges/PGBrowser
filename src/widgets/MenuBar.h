#ifndef __MENUBAR__
#define __MENUBAR__

#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>

class MainWindow;

class MenuBar : public QMenuBar
{
  Q_OBJECT

public:
  MenuBar(MainWindow* window);
  virtual ~MenuBar();

  void updateBookmarks();

private:
  MainWindow* currentWindow();
  void setupFileMenu();
  void setupEditMenu();
  void setupViewMenu();
  void setupHistoryMenu();
  void setupBookmarksMenu();
  void setupHelpMenu();

private slots:
  void newWindowTriggered(bool checked);
  void newTabTriggered(bool checked);
  void openLocationTriggered(bool checked);
  void previousTabTriggered(bool checked);
  void nextTabTriggered(bool checked);
  void closeTabTriggered(bool checked);
  void selectAllTriggered(bool checked);
  void cutTriggered(bool checked);
  void copyTriggered(bool checked);
  void pasteTriggered(bool checked);
  void findTriggered(bool checked);
  void findNextTriggered(bool checked);
  void preferencesTriggered(bool checked);
  void zoomInTriggered(bool checked);
  void zoomOutTriggered(bool checked);
  void stopTriggered(bool checked);
  void reloadTriggered(bool checked);
  void backTriggered(bool checked);
  void forwardTriggered(bool checked);
  void homeTriggered(bool checked);
  void addBookmarkTriggered(bool checked);
  void manageBookmarksActionTriggered(bool checked);
  void bookmarkTriggered(bool checked);

private:
  MainWindow* m_window;
  QMenu* m_bookmarksMenu;
};
#endif

