#ifndef __BOOKMARKSCONTAINER__
#define __BOOKMARKSCONTAINER__

#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtCore/QDebug>
#include <QtCore/QDataStream>

class Bookmark
{
public:
  Bookmark();
  Bookmark(QString& name, QString& url, QStringList& tags);
  Bookmark(const Bookmark& bookmark);
  ~Bookmark();

  const Bookmark& operator=(const Bookmark &bookmark);
  bool operator==(const Bookmark& bookmark) const;
  bool operator!=(const Bookmark& bookmark) const;

public:
  QString name;
  QString url;
  QStringList tags;
};

Q_DECLARE_METATYPE(Bookmark);
Q_DECLARE_METATYPE(Bookmark*);
Q_DECLARE_METATYPE(const Bookmark*);
typedef QList<Bookmark> BookmarksList;
typedef QList<Bookmark*> BookmarksPtrList;
Q_DECLARE_METATYPE(BookmarksList);
Q_DECLARE_METATYPE(BookmarksPtrList);

inline QDebug operator<<(QDebug debug, const Bookmark& bookmark)
{
  debug.nospace() << "Bookmark(" 
  << bookmark.name << "," 
  << bookmark.url << "," 
  << bookmark.tags << ")";
  return debug.space();
}

inline QDataStream& operator<<(QDataStream& out, const Bookmark& bookmark)
{
  out << bookmark.name;
  out << bookmark.url;
  out << bookmark.tags;
  return out;
}

inline QDataStream& operator>>(QDataStream& in, Bookmark& bookmark)
{
  in >> bookmark.name;
  in >> bookmark.url;
  in >> bookmark.tags;
  return in;
}

class BookmarksContainer
{
public:
  BookmarksContainer();
  virtual ~BookmarksContainer();

  BookmarksPtrList& bookmarks();
  void addBookmark(QString& name, QString& url, QStringList& tags);

  void saveState();
  void restoreState();

private:
  BookmarksPtrList m_bookmarks;
};
#endif
