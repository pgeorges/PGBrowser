#include "../MainApplication.h"
#include "PreferencesDialog.h"
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtNetwork/QNetworkProxy>

PreferencesDialog::PreferencesDialog(QWidget* parent) : QDialog(parent)
{
  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->setMargin(0);

  QHBoxLayout* iconsLayout = new QHBoxLayout();
  iconsLayout->setMargin(0);

  QPushButton* generalButton = new QPushButton(QIcon(QString("icons/general.png")), "", this);
  generalButton->setFlat(true);
  generalButton->setFixedSize(QSize(52,52));
  generalButton->setIconSize(QSize(52,52));
  generalButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(generalButton, SIGNAL(released()), this, SLOT(showGeneralOptions()));
  iconsLayout->addWidget(generalButton);

  QPushButton* networkButton = new QPushButton(QIcon(QString("icons/network.png")), "", this);
  networkButton->setFlat(true);
  networkButton->setFixedSize(QSize(52,52));
  networkButton->setIconSize(QSize(52,52));
  networkButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(networkButton, SIGNAL(released()), this, SLOT(showNetworkOptions()));
  iconsLayout->addWidget(networkButton);
  
  QWidget* iconsSpacer = new QWidget(this);
  iconsSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  iconsLayout->addWidget(iconsSpacer);

  mainLayout->addLayout(iconsLayout);
  
  m_optionsLayout = new QVBoxLayout();
  m_optionsLayout->setMargin(0);

  m_currentOptions = createGeneralOptions();

  m_optionsLayout->addWidget(m_currentOptions);

  mainLayout->addLayout(m_optionsLayout);

  setLayout(mainLayout);
  setWindowTitle("Preferences");
  setFixedSize(450, 400);
}

PreferencesDialog::~PreferencesDialog()
{
}

QWidget* PreferencesDialog::createGeneralOptions()
{
  MainApplication* application = MainApplication::application();

  QWidget* generalOptions = new QWidget();
  QGridLayout* generalLayout = new QGridLayout();

  // Home Page Options
  //create the homePageOptions groupbox
  QGroupBox* homePageGroupBox = new QGroupBox(tr("Home Page Options"), generalOptions);
  QGridLayout* homePageGroupLayout = new QGridLayout(homePageGroupBox);
  
  //add the homepage field
  QLabel* homePageLabel = new QLabel("Home Page:");
  QLineEdit* homePageEdit = new QLineEdit();
  homePageEdit->setText(application->homePage());
  homePageEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  connect(homePageEdit, SIGNAL(textChanged(const QString&)), application, SLOT(setHomePage(const QString&)));
  homePageGroupLayout->addWidget(homePageLabel, 0, 0);
  homePageGroupLayout->addWidget(homePageEdit, 0, 1);

  //add the homePageOptions group box
  generalLayout->addWidget(homePageGroupBox);
  //--

  // Misc Options
  //create the pluginOptions groupbox
  QGroupBox* miscGroupBox = new QGroupBox(tr("Misc Options"), generalOptions);
  QGridLayout* miscGroupLayout = new QGridLayout(miscGroupBox);

  //add the plugin default checkbox
  QCheckBox* pluginCheckBox = new QCheckBox("Default Plug-in State");
  pluginCheckBox->setToolTip("Disable this to have plug-ins not loaded by default.");
  if (application->pluginDefault())
    pluginCheckBox->setCheckState(Qt::Checked);
  else
    pluginCheckBox->setCheckState(Qt::Unchecked);
  connect(pluginCheckBox, SIGNAL(stateChanged(int)), application, SLOT(setPluginDefault(int)));
  miscGroupLayout->addWidget(pluginCheckBox, 0, 0);

  //add the open in new tab checkbox
  QCheckBox* openInNewTabCheckBox = new QCheckBox("Open New Windows in Tab");
  openInNewTabCheckBox->setToolTip("Enable this to open new windows in a tab.");
  if (application->openInTab())
    openInNewTabCheckBox->setCheckState(Qt::Checked);
  else
    openInNewTabCheckBox->setCheckState(Qt::Unchecked);
  connect(openInNewTabCheckBox, SIGNAL(stateChanged(int)), application, SLOT(setOpenInTab(int)));
  miscGroupLayout->addWidget(openInNewTabCheckBox, 1, 0);

  //add the pluginOptions group box
  generalLayout->addWidget(miscGroupBox);
  //--

  //add a spacer
  QWidget* generalOptionsSpacer = new QWidget();
  generalOptionsSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  generalLayout->addWidget(generalOptionsSpacer);

  generalOptions->setLayout(generalLayout);

  return generalOptions;
}

QWidget* PreferencesDialog::createNetworkOptions()
{
  MainApplication* application = MainApplication::application();

  QWidget* networkOptions = new QWidget();
  QVBoxLayout* networkLayout = new QVBoxLayout(networkOptions);

  // Proxy Options
  //create the proxy groupbox
  QGroupBox* proxyGroupBox = new QGroupBox(tr("Proxy Options"), networkOptions);
  QGridLayout* proxyGroupLayout = new QGridLayout(proxyGroupBox);

  //add the proxy type combo box
  QLabel* proxyTypeLabel = new QLabel("Proxy Type:");
  m_proxyTypeCombo = new QComboBox();
  m_proxyTypeCombo->addItem("No Proxy", QNetworkProxy::NoProxy);
  m_proxyTypeCombo->addItem("Default Proxy", QNetworkProxy::DefaultProxy);
  m_proxyTypeCombo->addItem("Http Proxy", QNetworkProxy::HttpProxy);
  m_proxyTypeCombo->addItem("Http Caching Proxy", QNetworkProxy::HttpCachingProxy);
  m_proxyTypeCombo->addItem("Socks5 Proxy", QNetworkProxy::Socks5Proxy);
  m_proxyTypeCombo->setCurrentIndex(m_proxyTypeCombo->findData(application->proxyType()));
  connect(m_proxyTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setProxyType(int)));
  proxyGroupLayout->addWidget(proxyTypeLabel, 0, 0);
  proxyGroupLayout->addWidget(m_proxyTypeCombo, 0, 1);

  //add the proxy host name field
  QLabel* proxyHostNameLabel = new QLabel("Host:");
  QLineEdit* proxyHostNameEdit = new QLineEdit();
  proxyHostNameEdit->setText(application->proxyHostName());
  connect(proxyHostNameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setProxyHostName(const QString&)));
  proxyGroupLayout->addWidget(proxyHostNameLabel, 1, 0);
  proxyGroupLayout->addWidget(proxyHostNameEdit, 1, 1);

  //add the proxy port field
  QLabel* proxyPortLabel = new QLabel("Port:");
  QLineEdit* proxyPortEdit = new QLineEdit();
  proxyPortEdit->setText(application->proxyPort());
  connect(proxyPortEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setProxyPort(const QString&)));
  proxyGroupLayout->addWidget(proxyPortLabel, 2, 0);
  proxyGroupLayout->addWidget(proxyPortEdit, 2, 1);

  //add the proxy group box
  networkLayout->addWidget(proxyGroupBox);
  //--

  //add a spacer
  QWidget* networkOptionsSpacer = new QWidget();
  networkOptionsSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  networkLayout->addWidget(networkOptionsSpacer);

  return networkOptions;
}

void PreferencesDialog::showGeneralOptions()
{
  m_optionsLayout->removeWidget(m_currentOptions);
  m_currentOptions->setVisible(false);
  delete m_currentOptions;
  m_currentOptions = createGeneralOptions();
  m_optionsLayout->addWidget(m_currentOptions);
}

void PreferencesDialog::showNetworkOptions()
{
  m_optionsLayout->removeWidget(m_currentOptions);
  m_currentOptions->setVisible(false);
  delete m_currentOptions;
  m_currentOptions = createNetworkOptions();
  m_optionsLayout->addWidget(m_currentOptions);
}

void PreferencesDialog::setProxyType(int index)
{
  MainApplication* application = MainApplication::application();
  application->setProxyType((QNetworkProxy::ProxyType)m_proxyTypeCombo->itemData(index).toInt());
}

void PreferencesDialog::setProxyHostName(const QString& hostname)
{
  MainApplication* application = MainApplication::application();
  application->setProxyHostName(hostname);
}

void PreferencesDialog::setProxyPort(const QString& port)
{
  MainApplication* application = MainApplication::application();
  application->setProxyPort(port.toShort());
}

