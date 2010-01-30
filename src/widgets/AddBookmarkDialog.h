#ifndef __ADDBOOKMARKDIALOG__
#define __ADDBOOKMARKDIALOG__

#include <QtCore/QUrl>
#include <QtGui/QDialog>
#include <QtGui/QLineEdit>

class AddBookmarkDialog : public QDialog
{
  Q_OBJECT
  
public:
  AddBookmarkDialog(const QString& title, const QUrl& url, QWidget* parent);
  virtual ~AddBookmarkDialog();

signals:
  void bookmarkAdded();

private slots:
  void onAdd();
  
private:
  QUrl m_url;
  QLineEdit* m_nameEdit;
  QLineEdit* m_tagsEdit;
};
#endif
