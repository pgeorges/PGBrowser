#include "../MainApplication.h"
#include "BookmarksToolBar.h"

BookmarksToolBar::BookmarksToolBar(QWidget* parent)
: QToolBar(parent)
{
  setMovable(false);
  setFloatable(false);
  setObjectName(QString("BookmarksToolBar"));

  updateBookmarks();
}

BookmarksToolBar::~BookmarksToolBar()
{
}

void BookmarksToolBar::updateBookmarks()
{
  clear();

  //get the bookmarks
  BookmarksContainer* bookmarksContainer = MainApplication::application()->bookmarksContainer();
  QMap<QString, QAction*> bookmarkTagMenus;

  //go through each bookmark and add it to the menu
  foreach (Bookmark* bookmark, bookmarksContainer->bookmarks())
  {
    if (bookmark->tags.contains("toolbar"))
    {
      if (bookmark->tags.length() > 1)
      {
      }

      //add the new window action
      QAction* bookmarkAction = addAction(bookmark->name);
      bookmarkAction->setData(QVariant::fromValue(bookmark));
      connect(bookmarkAction, SIGNAL(triggered(bool)), this, SLOT(bookmarkTriggered(bool)));
    }
  }
}

void BookmarksToolBar::bookmarkTriggered(bool checked)
{
  QAction* bookmarkAction = dynamic_cast<QAction*>(sender());
  Bookmark* bookmark = bookmarkAction->data().value<Bookmark*>();
  emit bookmarkTriggered(bookmark->url);
}


