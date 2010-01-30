#ifndef __BOOKMARKSMANAGERDIALOG__
#define __BOOKMARKSMANAGERDIALOG__

#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QTreeWidget>

class BookmarksManagerDialog : public QDialog
{
  Q_OBJECT
  
public:
  BookmarksManagerDialog(QWidget* parent);
  virtual ~BookmarksManagerDialog();

private:
  void updateBookmarksTree();
  void updateBookmarkEditPane();

private slots:
  void manageBookmarksTreeItemTriggered(QTreeWidgetItem* item, int column);
  void setBookmarkName();
  void setBookmarkUrl();
  void setBookmarkTags();
  void onDeleteBookmark();

private:
  QTreeWidget* m_bookmarksTree;
  QGroupBox* m_bookmarkEditGroupBox;
  QLineEdit* m_nameEdit;
  QLineEdit* m_urlEdit;
  QLineEdit* m_tagsEdit;
  Bookmark* m_currentBookmark;
};
#endif

