#ifndef __PREFERENCESDIALOG__
#define __PREFERENCESDIALOG__

#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>

class PreferencesDialog : public QDialog
{
  Q_OBJECT
  
public:
  PreferencesDialog(QWidget* parent);
  virtual ~PreferencesDialog();

private:
  QWidget* createGeneralOptions();
  QWidget* createNetworkOptions();

private slots:
  void showGeneralOptions();
  void showNetworkOptions();
  void setProxyType(int index);
  void setProxyHostName(const QString& hostname);
  void setProxyPort(const QString& port);

private:
  QVBoxLayout* m_optionsLayout;
  QWidget* m_currentOptions;
  QComboBox* m_proxyTypeCombo;
};
#endif
