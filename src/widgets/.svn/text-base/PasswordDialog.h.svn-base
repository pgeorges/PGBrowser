#ifndef __PASSWORDDIALOG__
#define __PASSWORDDIALOG__

#include "LocationBar.h"
#include <QtGui/QDialog>

class QLineEdit;

class PasswordDialog : public QDialog
{
  Q_OBJECT
  
public:
  PasswordDialog(QWidget* parent);
  virtual ~PasswordDialog();

  QString userName();
  QString password();

private:
  void closeEvent(QCloseEvent* event);

private slots:
  void onAccepted();
  void onRejected();

private:
  QLineEdit* m_userNameLineEdit;
  QLineEdit* m_passwordLineEdit;
};
#endif
