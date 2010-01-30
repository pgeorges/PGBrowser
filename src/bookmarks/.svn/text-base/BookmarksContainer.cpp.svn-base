#include "BookmarksContainer.h"
#include "../MainApplication.h"
#include <iostream>

Bookmark::Bookmark()
{
}

Bookmark::Bookmark(QString& name, QString& url, QStringList& tags)
: name(name)
, url(url)
, tags(tags)
{
}

Bookmark::Bookmark(const Bookmark& bookmark)
{
  name = bookmark.name;
  url = bookmark.url;
  tags = bookmark.tags;
}

Bookmark::~Bookmark()
{
}

const Bookmark& Bookmark::operator=(const Bookmark &bookmark)
{
  // avoid copy to self
  if (this != &bookmark)
  {
    name = bookmark.name;
    url = bookmark.url;
    tags = bookmark.tags;
  }
  return *this;
}

bool Bookmark::operator==(const Bookmark& bookmark) const
{
  if (name == bookmark.name && url == bookmark.url && tags == bookmark.tags)
    return true;
  return false;
}

bool Bookmark::operator!=(const Bookmark& bookmark) const
{
  return !((*this) == bookmark);
}

BookmarksContainer::BookmarksContainer()
{
  restoreState();
}

BookmarksContainer::~BookmarksContainer()
{
  saveState();
}

BookmarksPtrList& BookmarksContainer::bookmarks()
{
  return m_bookmarks;
}

void BookmarksContainer::addBookmark(QString& name, QString& url, QStringList& tags)
{
  Bookmark* bookmark = new Bookmark(name, url, tags);
  m_bookmarks.append(bookmark);
}

void BookmarksContainer::saveState()
{
  qRegisterMetaType<BookmarksList>("BookmarksList");
  qRegisterMetaTypeStreamOperators<BookmarksList>("BookmarksList");

  BookmarksList bookmarks;
  foreach (Bookmark* bookmark, m_bookmarks)
    bookmarks.append(*bookmark);

  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  settings.setValue("Application/Bookmarks", QVariant::fromValue(bookmarks));
}

void BookmarksContainer::restoreState()
{
  qRegisterMetaType<BookmarksList>("BookmarksList");
  qRegisterMetaTypeStreamOperators<BookmarksList>("BookmarksList");

  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  //m_bookmarks = qVariantValue<BookmarksList>(settings.value("Application/Bookmarks"));
  BookmarksList bookmarks = settings.value("Application/Bookmarks").value<BookmarksList>();

  foreach (Bookmark bookmark, bookmarks)
  {
    Bookmark* bookmarkPtr = new Bookmark(bookmark.name, bookmark.url, bookmark.tags);
    m_bookmarks.append(bookmarkPtr);
  }
}

