#include "../MainApplication.h"
#include "BookmarksManagerDialog.h"
#include "MainWindow.h"
#include <QtCore/QList>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QSplitter>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QTreeWidgetItem>
#include <QtNetwork/QNetworkProxy>
#include <iostream>

BookmarksManagerDialog::BookmarksManagerDialog(QWidget* parent) : QDialog(parent)
{
  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->setMargin(0);

  QSplitter* mainSplitter = new QSplitter();
  mainLayout->addWidget(mainSplitter);

  m_bookmarksTree = new QTreeWidget(mainSplitter);
  m_bookmarksTree->setHeaderLabel("Bookmarks");
  updateBookmarksTree();
  connect(m_bookmarksTree, SIGNAL(itemClicked(QTreeWidgetItem*, int)), 
          this, SLOT(manageBookmarksTreeItemTriggered(QTreeWidgetItem*, int)));

  QWidget* bookmarkEditPane = new QWidget(mainSplitter);

  m_bookmarkEditGroupBox = new QGroupBox(tr("Edit Bookmark"), bookmarkEditPane);
  QGridLayout* bookmarkEditGroupBoxLayout = new QGridLayout(m_bookmarkEditGroupBox);

  QLabel* nameLabel = new QLabel("Name: ");
  m_nameEdit = new QLineEdit();
  connect(m_nameEdit, SIGNAL(editingFinished()), this, SLOT(setBookmarkName()));

  QLabel* urlLabel = new QLabel("Url: ");
  m_urlEdit = new QLineEdit();
  connect(m_urlEdit, SIGNAL(editingFinished()), this, SLOT(setBookmarkUrl()));

  QLabel* tagsLabel = new QLabel("Tags: ");
  m_tagsEdit = new QLineEdit();
  connect(m_tagsEdit, SIGNAL(editingFinished()), this, SLOT(setBookmarkTags()));

  QPushButton* deleteBookmarkButton = new QPushButton("Delete Bookmark");
  connect(deleteBookmarkButton, SIGNAL(released()),
          this, SLOT(onDeleteBookmark()));

  bookmarkEditGroupBoxLayout->addWidget(nameLabel, 0, 0);
  bookmarkEditGroupBoxLayout->addWidget(m_nameEdit, 0, 1);
  bookmarkEditGroupBoxLayout->addWidget(urlLabel, 1, 0);
  bookmarkEditGroupBoxLayout->addWidget(m_urlEdit, 1, 1);
  bookmarkEditGroupBoxLayout->addWidget(tagsLabel, 2, 0);
  bookmarkEditGroupBoxLayout->addWidget(m_tagsEdit, 2, 1);
  bookmarkEditGroupBoxLayout->addWidget(deleteBookmarkButton, 3, 0, 1, 0);

  m_bookmarkEditGroupBox->setVisible(false);

  QList<int> sizes;
  sizes << 350 << 250;
  mainSplitter->setSizes(sizes);
  setLayout(mainLayout);
  setWindowTitle("Manage Bookmarks");
  setFixedSize(600, 400);
}

BookmarksManagerDialog::~BookmarksManagerDialog()
{
}

void BookmarksManagerDialog::updateBookmarksTree()
{
  m_bookmarksTree->clear();

  //get the bookmarks
  BookmarksContainer* bookmarksContainer = MainApplication::application()->bookmarksContainer();
  QMap<QString, QTreeWidgetItem*> bookmarkTagTreeItems;

  //go through each bookmark and add it to the menu
  foreach (Bookmark* bookmark, bookmarksContainer->bookmarks())
  {
    if (bookmark->tags.isEmpty())
    {
      //add the bookmark to the tree under the top level
      QTreeWidgetItem* bookmarkTreeItem = new QTreeWidgetItem(m_bookmarksTree);
      bookmarkTreeItem->setText(0, bookmark->name);
      bookmarkTreeItem->setData(0, Qt::UserRole, QVariant::fromValue(bookmark));
    }
    else
    {
      //first create a tree item for each tag and add the bookmark to them
      QStringListIterator tagsIterator(bookmark->tags);
      while (tagsIterator.hasNext())
      {
        QString tag = tagsIterator.next();

        if (!bookmarkTagTreeItems.contains(tag))
        {
          //add the tag tree item
          QTreeWidgetItem* tagTreeItem = new QTreeWidgetItem(m_bookmarksTree);
          tagTreeItem->setExpanded(true);
          tagTreeItem->setText(0, tag);
          bookmarkTagTreeItems.insert(tag, tagTreeItem);
        }

        //add the bookmark to the tree under the tagTreeItem
        QTreeWidgetItem* bookmarkTreeItem = new QTreeWidgetItem(bookmarkTagTreeItems[tag]);
        bookmarkTreeItem->setText(0, bookmark->name);
        bookmarkTreeItem->setData(0, Qt::UserRole, QVariant::fromValue(bookmark));
      }
    }
  }
  m_bookmarksTree->sortItems(0, Qt::AscendingOrder);
}

void BookmarksManagerDialog::updateBookmarkEditPane()
{
  if (!m_currentBookmark)
  {
    m_bookmarkEditGroupBox->setVisible(false);
    return;
  }

  m_nameEdit->clear();
  m_nameEdit->insert(m_currentBookmark->name);
  m_urlEdit->clear();
  m_urlEdit->insert(m_currentBookmark->url);
  m_tagsEdit->clear();
  m_tagsEdit->insert(m_currentBookmark->tags.join(" "));
  m_bookmarkEditGroupBox->setVisible(true);
}

void BookmarksManagerDialog::manageBookmarksTreeItemTriggered(QTreeWidgetItem* item, int column)
{
  m_currentBookmark = item->data(0, Qt::UserRole).value<Bookmark*>();
  updateBookmarkEditPane();
}

void BookmarksManagerDialog::setBookmarkName()
{
  QString name = m_nameEdit->text();
  m_currentBookmark->name = name;

  updateBookmarksTree();
  foreach (MainWindow* mainWindow, MainApplication::application()->mainWindows())
    mainWindow->menuBar()->updateBookmarks();
}

void BookmarksManagerDialog::setBookmarkUrl()
{
  QString url = m_urlEdit->text();
  m_currentBookmark->url = url;

  updateBookmarksTree();
  foreach (MainWindow* mainWindow, MainApplication::application()->mainWindows())
    mainWindow->menuBar()->updateBookmarks();
}

void BookmarksManagerDialog::setBookmarkTags()
{
  QStringList tags = m_tagsEdit->text().split(" ");
  tags.removeOne("");
  m_currentBookmark->tags = tags;

  foreach (MainWindow* mainWindow, MainApplication::application()->mainWindows())
    mainWindow->menuBar()->updateBookmarks();
  updateBookmarksTree();
}

void BookmarksManagerDialog::onDeleteBookmark()
{
  /*
  MainApplication::application()->bookmarksContainer()->bookmarks().removeOne(m_currentBookmark);
  updateBookmarksTree();
  foreach (MainWindow* mainWindow, MainApplication::application()->mainWindows())
    mainWindow->menuBar()->updateBookmarks();
  */
}

#include "BookmarksManagerDialog.moc"

