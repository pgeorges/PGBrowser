#include "../MainApplication.h"
#include "AddBookmarkDialog.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

AddBookmarkDialog::AddBookmarkDialog(const QString& title, const QUrl& url, QWidget* parent)
: QDialog(parent)
, m_url(url)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  QLabel* nameLabel = new QLabel("Type a name for the bookmark", this);
  m_nameEdit = new QLineEdit(title, this);
  QLabel* tagsLabel = new QLabel("Add some tags for the bookmark", this);
  m_tagsEdit = new QLineEdit(this);

  QHBoxLayout* buttonLayout = new QHBoxLayout();
  
  QPushButton* addButton = new QPushButton(QString("Add"));
  addButton->setDefault(true);
  QPushButton* cancelButton = new QPushButton(QString("Cancel"));
  
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(cancelButton);

  mainLayout->addWidget(nameLabel);
  mainLayout->addWidget(m_nameEdit);
  mainLayout->addWidget(tagsLabel);
  mainLayout->addWidget(m_tagsEdit);
  mainLayout->addLayout(buttonLayout);

  setWindowTitle("Add Bookmark");
  adjustSize();

  connect(addButton, SIGNAL(released()), this, SLOT(onAdd()));
  connect(cancelButton, SIGNAL(released()), this, SLOT(close()));
}

AddBookmarkDialog::~AddBookmarkDialog()
{
}

void AddBookmarkDialog::onAdd()
{
  QString name(m_nameEdit->text());
  QString url(m_url.toString());
  QStringList tags(m_tagsEdit->text().split(" "));
  tags.removeOne("");
  BookmarksContainer* bookmarksContainer = MainApplication::application()->bookmarksContainer();
  bookmarksContainer->addBookmark(name, url, tags);
  emit bookmarkAdded();
  
  close();
}

