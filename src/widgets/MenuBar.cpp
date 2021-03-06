#include "../MainApplication.h"
#include "MenuBar.h"
#include "MainWindow.h"
#include "../bookmarks/BookmarksContainer.h"
#include "AddBookmarkDialog.h"
#include "BookmarksManagerDialog.h"
#include "PreferencesDialog.h"

MenuBar::MenuBar(MainWindow* window)
: QMenuBar()
, m_window(window)
{
  //setup the menus
  setupFileMenu();
  setupEditMenu();
  setupViewMenu();
  setupHistoryMenu();
  setupBookmarksMenu();
  setupHelpMenu();
}

MenuBar::~MenuBar()
{
  delete m_bookmarksMenu;
}

MainWindow* MenuBar::currentWindow()
{
  return m_window;
}

void MenuBar::setupFileMenu()
{
  QMenu* fileMenu = addMenu(tr("&File"));

  //add the new window action
  QAction* newWindowAction = fileMenu->addAction(tr("New Window"));
  newWindowAction->setShortcut(QKeySequence::New);
  connect(newWindowAction, SIGNAL(triggered(bool)), this, SLOT(newWindowTriggered(bool)));

  //add the new tab action
  QAction* newTabAction = fileMenu->addAction(tr("New Tab"));
  newTabAction->setShortcut(QKeySequence::AddTab);
  connect(newTabAction, SIGNAL(triggered(bool)), this, SLOT(newTabTriggered(bool)));

  //add the open location action
  QAction* openLocationAction = fileMenu->addAction(tr("Open Location"));
  openLocationAction->setShortcut(QKeySequence("Ctrl+L"));
  connect(openLocationAction, SIGNAL(triggered(bool)), this, SLOT(openLocationTriggered(bool)));

  fileMenu->addSeparator();

  //add the previous tab action
  QAction* previousTabAction = fileMenu->addAction(tr("Previous Tab"));
  previousTabAction->setShortcut(QKeySequence::PreviousChild);
  connect(previousTabAction, SIGNAL(triggered(bool)), this, SLOT(previousTabTriggered(bool)));

  //add the next tab action
  QAction* nextTabAction = fileMenu->addAction(tr("Next Tab"));
  nextTabAction->setShortcut(QKeySequence::NextChild);
  connect(nextTabAction, SIGNAL(triggered(bool)), this, SLOT(nextTabTriggered(bool)));

  fileMenu->addSeparator();

  //add the close tab action
  QAction* closeTabAction = fileMenu->addAction(tr("Close Tab"));
  closeTabAction->setShortcut(QKeySequence::Close);
  connect(closeTabAction, SIGNAL(triggered(bool)), this, SLOT(closeTabTriggered(bool)));
}

void MenuBar::setupEditMenu()
{
  QMenu* editMenu = addMenu(tr("&Edit"));

  //add the select all action
  QAction* selectAllAction = editMenu->addAction(tr("Select All"));
  selectAllAction->setShortcut(QKeySequence::SelectAll);
  connect(selectAllAction, SIGNAL(triggered(bool)), this, SLOT(selectAllTriggered(bool)));

  editMenu->addSeparator();

  //add the cut action
  QAction* cutAction = editMenu->addAction(tr("Cut"));
  cutAction->setShortcut(QKeySequence::Cut);
  connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cutTriggered(bool)));

  //add the copy action
  QAction* copyAction = editMenu->addAction(tr("Copy"));
  copyAction->setShortcut(QKeySequence::Copy);
  connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(copyTriggered(bool)));

  //add the paste action
  QAction* pasteAction = editMenu->addAction(tr("Paste"));
  pasteAction->setShortcut(QKeySequence::Paste);
  connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(pasteTriggered(bool)));

  editMenu->addSeparator();

  //add the find text action
  QAction* findAction = editMenu->addAction(tr("Find"));
  findAction->setShortcut(QKeySequence::Find);
  connect(findAction, SIGNAL(triggered(bool)), this, SLOT(findTriggered(bool)));

  //add the find text action
  QAction* findNextAction = editMenu->addAction(tr("Find Next"));
  findNextAction->setShortcut(QKeySequence::FindNext);
  connect(findNextAction, SIGNAL(triggered(bool)), this, SLOT(findNextTriggered(bool)));

  editMenu->addSeparator();

  //add the preferences action
  QAction* preferencesAction = editMenu->addAction(tr("Preferences"));
  connect(preferencesAction, SIGNAL(triggered(bool)), this, SLOT(preferencesTriggered(bool)));
  preferencesAction->setMenuRole(QAction::PreferencesRole);
}

void MenuBar::setupViewMenu()
{
  QMenu* viewMenu = addMenu(tr("&View"));

  //add the stop action
  QAction* stopAction = viewMenu->addAction(tr("Stop"));
  stopAction->setShortcut(Qt::Key_Escape);
  connect(stopAction, SIGNAL(triggered(bool)), this, SLOT(stopTriggered(bool)));

  //add the reload action
  QAction* reloadAction = viewMenu->addAction(tr("Reload"));
  reloadAction->setShortcut(QKeySequence::Refresh);
  connect(reloadAction, SIGNAL(triggered(bool)), this, SLOT(reloadTriggered(bool)));

  viewMenu->addSeparator();

  //add the zoom in action
  QAction* zoomInAction = viewMenu->addAction(tr("Zoom In"));
  zoomInAction->setShortcut(QKeySequence::ZoomIn);
  connect(zoomInAction, SIGNAL(triggered(bool)), this, SLOT(zoomInTriggered(bool)));

  //add the zoom out action
  QAction* zoomOutAction = viewMenu->addAction(tr("Zoom Out"));
  zoomOutAction->setShortcut(QKeySequence::ZoomOut);
  connect(zoomOutAction, SIGNAL(triggered(bool)), this, SLOT(zoomOutTriggered(bool)));
}

void MenuBar::setupHistoryMenu()
{
  QMenu* historyMenu = addMenu(tr("&History"));

  //add the back action
  QAction* backAction = historyMenu->addAction(tr("Back"));
  backAction->setShortcut(QKeySequence::Back);
  connect(backAction, SIGNAL(triggered(bool)), this, SLOT(backTriggered(bool)));

  //add the forward action
  QAction* forwardAction = historyMenu->addAction(tr("Forward"));
  forwardAction->setShortcut(QKeySequence::Forward);
  connect(forwardAction, SIGNAL(triggered(bool)), this, SLOT(forwardTriggered(bool)));

  //add the home action
  QAction* homeAction = historyMenu->addAction(tr("Home"));
  homeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_H));
  connect(homeAction, SIGNAL(triggered(bool)), this, SLOT(homeTriggered(bool)));
}

void MenuBar::setupBookmarksMenu()
{
  m_bookmarksMenu = addMenu(tr("&Bookmarks"));
  updateBookmarks();
}

void MenuBar::setupHelpMenu()
{
  QMenu* helpMenu = addMenu(tr("&Help"));

  //add the about action
  QAction* aboutAction = helpMenu->addAction(tr("About"));
  aboutAction->setMenuRole(QAction::AboutRole);
}

void MenuBar::updateBookmarks()
{
  m_bookmarksMenu->clear();

  //add the 'Bookmark this page' action
  QAction* addBookmarkAction = m_bookmarksMenu->addAction("Bookmark this page");
  connect(addBookmarkAction, SIGNAL(triggered(bool)), this, SLOT(addBookmarkTriggered(bool)));

  //add the 'Manage Bookmarks' action
  QAction* manageBookmarksAction = m_bookmarksMenu->addAction("Manage Bookmarks");
  connect(manageBookmarksAction, SIGNAL(triggered(bool)), this, SLOT(manageBookmarksActionTriggered(bool)));

  m_bookmarksMenu->addSeparator();

  //get the bookmarks
  BookmarksContainer* bookmarksContainer = MainApplication::application()->bookmarksContainer();
  QMap<QString, QMenu*> bookmarkTagMenus;

  //go through each bookmark and add it to the menu
  foreach (Bookmark* bookmark, bookmarksContainer->bookmarks())
  {
    if (bookmark->tags.isEmpty())
    {
      QAction* bookmarkAction = m_bookmarksMenu->addAction(bookmark->name);
      bookmarkAction->setData(QVariant::fromValue(bookmark));
      connect(bookmarkAction, SIGNAL(triggered(bool)), this, SLOT(bookmarkTriggered(bool)));      
    }
    else
    {
      QStringListIterator tagsIterator(bookmark->tags);
      while (tagsIterator.hasNext())
      {
        QString tag = tagsIterator.next();
        if (!bookmarkTagMenus.contains(tag))
        {
          QMenu* tagMenu = m_bookmarksMenu->addMenu(tag);
          bookmarkTagMenus.insert(tag, tagMenu);
        }
      
        QAction* bookmarkAction = bookmarkTagMenus[tag]->addAction(bookmark->name);
        bookmarkAction->setData(QVariant::fromValue(bookmark));
        connect(bookmarkAction, SIGNAL(triggered(bool)), this, SLOT(bookmarkTriggered(bool)));
      }
    }
  }
}

void MenuBar::newWindowTriggered(bool checked)
{
  MainWindow* window = new MainWindow();
  window->show();
}

void MenuBar::newTabTriggered(bool checked)
{

  currentWindow()->tabWidget()->addNewTab(true);
  currentWindow()->mainToolBar()->locationBar()->setFocus(Qt::OtherFocusReason);
}

void MenuBar::openLocationTriggered(bool checked)
{
  currentWindow()->mainToolBar()->locationBar()->setFocus(Qt::OtherFocusReason);
  currentWindow()->mainToolBar()->locationBar()->selectAll();
}

void MenuBar::previousTabTriggered(bool checked)
{
  int index = currentWindow()->tabWidget()->currentIndex() - 1;
  currentWindow()->tabWidget()->setCurrentIndex(index);
}

void MenuBar::nextTabTriggered(bool checked)
{
  int index = currentWindow()->tabWidget()->currentIndex() + 1;
  currentWindow()->tabWidget()->setCurrentIndex(index);
}

void MenuBar::closeTabTriggered(bool checked)
{
  currentWindow()->tabWidget()->closeTab(currentWindow()->tabWidget()->currentIndex());
}

void MenuBar::selectAllTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->page()->triggerAction(QWebPage::SelectAll);
}

void MenuBar::cutTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->page()->triggerAction(QWebPage::Cut);
}

void MenuBar::copyTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->page()->triggerAction(QWebPage::Copy);
}

void MenuBar::pasteTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->page()->triggerAction(QWebPage::Paste);
}

void MenuBar::findTriggered(bool checked)
{
  currentWindow()->showFindToolBar();
}

void MenuBar::findNextTriggered(bool checked)
{
  currentWindow()->findNext();
}

void MenuBar::zoomInTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->setZoomFactor(currentWindow()->webPanel()->zoomFactor() + qreal(0.1));
}

void MenuBar::zoomOutTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->setZoomFactor(currentWindow()->webPanel()->zoomFactor() - qreal(0.1));
}

void MenuBar::stopTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->stop();
}

void MenuBar::reloadTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->reload();
}

void MenuBar::backTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->back();
}

void MenuBar::forwardTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->forward();
}

void MenuBar::homeTriggered(bool checked)
{
  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->setUrl(MainApplication::application()->homePage());
  else
    currentWindow()->tabWidget()->addNewTab(MainApplication::application()->homePage());
}

void MenuBar::preferencesTriggered(bool checked)
{
  PreferencesDialog preferencesDialog(this);
  preferencesDialog.exec();
}

void MenuBar::addBookmarkTriggered(bool checked)
{
  if (currentWindow()->webPanel())
  {
    AddBookmarkDialog bookmarkDialog(currentWindow()->webPanel()->title(), 
                                     currentWindow()->webPanel()->url(),
                                     this);
    bookmarkDialog.exec();
    updateBookmarks();
  }
}

void MenuBar::manageBookmarksActionTriggered(bool checked)
{
  BookmarksManagerDialog bookmarksManagerDialog(this);
  bookmarksManagerDialog.exec();
}

void MenuBar::bookmarkTriggered(bool checked)
{
  QAction* bookmarkAction = dynamic_cast<QAction*>(sender());
  Bookmark* bookmark = bookmarkAction->data().value<Bookmark*>();

  if (currentWindow()->webPanel())
    currentWindow()->webPanel()->setUrl(bookmark->url);
  else
    currentWindow()->tabWidget()->addNewTab(bookmark->url);
}


