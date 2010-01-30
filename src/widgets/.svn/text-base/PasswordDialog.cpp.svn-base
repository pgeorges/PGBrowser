#include "PasswordDialog.h"
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

PasswordDialog::PasswordDialog(QWidget* parent)
: QDialog(parent)
{
  QGridLayout* gridLayout = new QGridLayout();

  QLabel* userNameLabel = new QLabel(QString("Username:"), this);
  m_userNameLineEdit = new QLineEdit(this);

  QLabel* passwordLabel = new QLabel(QString("Password:"), this);
  m_passwordLineEdit = new QLineEdit(this);
  m_passwordLineEdit->setEchoMode(QLineEdit::Password);
  
  QHBoxLayout* buttonLayout = new QHBoxLayout();

  QPushButton* okButton = new QPushButton(QString("OK"));
  okButton->setDefault(true);
  QPushButton* cancelButton = new QPushButton(QString("Cancel"));
  
  buttonLayout->addWidget(okButton);
  buttonLayout->addWidget(cancelButton);

  gridLayout->addWidget(userNameLabel, 0, 0);
  gridLayout->addWidget(m_userNameLineEdit, 0, 1);
  gridLayout->addWidget(passwordLabel, 1, 0);
  gridLayout->addWidget(m_passwordLineEdit, 1, 1);
  gridLayout->addLayout(buttonLayout, 2, 0, 1, 0);

  setLayout(gridLayout);
  setWindowTitle(QString("Enter password"));
  setSizeGripEnabled(false);
  adjustSize();

  connect(okButton, SIGNAL(released()), this, SLOT(accept()));
  connect(cancelButton, SIGNAL(released()), this, SLOT(reject()));
}

PasswordDialog::~PasswordDialog()
{
}

QString PasswordDialog::userName()
{
  return m_userNameLineEdit->text();
}

QString PasswordDialog::password()
{
  return m_passwordLineEdit->text();
}

void PasswordDialog::onAccepted()
{
  accept();
}

void PasswordDialog::onRejected()
{
  reject();
}

void PasswordDialog::closeEvent(QCloseEvent* event)
{
}

#include "PasswordDialog.moc"

