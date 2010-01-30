#ifndef __BOOKMARKSTOOLBAR__
#define __BOOKMARKSTOOLBAR__

#include <QtCore/QUrl>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

class BookmarksToolBar : public QToolBar
{
  Q_OBJECT
  
public:
  BookmarksToolBar(QWidget* parent);
  virtual ~BookmarksToolBar();

signals:
  void bookmarkTriggered(const QUrl& url);

private:
  void updateBookmarks();

private slots:
  void bookmarkTriggered(bool checked);
};
#endif

