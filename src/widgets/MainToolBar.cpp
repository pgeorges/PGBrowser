#include "../MainApplication.h"
#include "MainToolBar.h"
#include "TabWidget.h"
#include "WebPanel.h"
#include <QtCore/Qt>
#include <QtGui/QIcon>
#include <QtWebKit/QWebHistory>

MainToolBar::MainToolBar(TabWidget* tabWidget, QWidget* parent)
: QToolBar(parent)
, m_tabWidget(tabWidget)
{
  setMovable(false);
  setFloatable(false);
  setObjectName(QString("MainToolBar"));

  //create the location bar
  m_locationBar = new LocationBar();
  connect(m_locationBar, SIGNAL(returnPressed()),
          this, SLOT(locationBarActivated()));

  //set the size of the buttons and the icon based on the height of the locationbar
  QSize buttonSize(m_locationBar->sizeHint().height(), m_locationBar->sizeHint().height());
  QSize iconSize(m_locationBar->sizeHint().height()-4, m_locationBar->sizeHint().height()-4);

  //create the back button
  m_backButton = new QPushButton(QIcon(QString("icons/back.png")), "");
  m_backButton->setToolTip("Go back one page");
  m_backButton->setFlat(true);
  m_backButton->setFixedSize(buttonSize);
  m_backButton->setIconSize(iconSize);
  connect(m_backButton, SIGNAL(released()),
          this, SLOT(backButtonReleased()));

  //create the forward button
  m_forwardButton = new QPushButton(QIcon(QString("icons/forward.png")), "");
  m_forwardButton->setToolTip("Go forward one page");
  m_forwardButton->setFlat(true);
  m_forwardButton->setFixedSize(buttonSize);
  m_forwardButton->setIconSize(iconSize);
  connect(m_forwardButton, SIGNAL(released()),
          this, SLOT(forwardButtonReleased()));

  //create the reload button
  m_reloadButton = new QPushButton(QIcon(QString("icons/repeat.png")), "");
  m_reloadButton->setToolTip("Reload the page");
  m_reloadButton->setFlat(true);
  m_reloadButton->setFixedSize(buttonSize);
  m_reloadButton->setIconSize(iconSize);
  connect(m_reloadButton, SIGNAL(released()),
          this, SLOT(reloadButtonReleased()));

  //create the stop button
  m_stopButton = new QPushButton(QIcon(QString("icons/stop.png")), "");
  m_stopButton->setToolTip("Stop loading the page");
  m_stopButton->setFlat(true);
  m_stopButton->setFixedSize(buttonSize);
  m_stopButton->setIconSize(iconSize);
  setStopButtonDisabled(true);
  connect(m_stopButton, SIGNAL(released()),
          this, SLOT(stopButtonReleased()));

  //add the progressBar
  m_progressBar = new QProgressBar();
  m_progressBar->setFixedWidth(100);

  //create the plugin button
  m_pluginButton = new QPushButton("");
  m_pluginButton->setCheckable(true);
  setPluginButtonState(webPanel());
  m_pluginButton->setFixedSize(buttonSize);
  m_pluginButton->setIconSize(iconSize);
  connect(m_pluginButton, SIGNAL(released()),
          this, SLOT(pluginButtonToggled()));

  //add the widgets to the toolbar
  addWidget(m_backButton);
  addWidget(m_forwardButton);
  addWidget(m_reloadButton);
  addWidget(m_stopButton);
  addWidget(m_locationBar);
  m_progressBarAction = addWidget(m_progressBar);
  addWidget(m_pluginButton);

  connect(m_tabWidget, SIGNAL(tabChanged(WebPanel*)),
          this, SLOT(onTabChanged(WebPanel*)));
}

MainToolBar::~MainToolBar()
{
  delete m_locationBar;
}

LocationBar* MainToolBar::locationBar()
{
  return m_locationBar;
}

QProgressBar* MainToolBar::progressBar()
{
  return m_progressBar;
}

QAction* MainToolBar::progressBarAction()
{
  return m_progressBarAction;
}

void MainToolBar::setNavigationButtonStates(WebPanel* webPanel)
{
  m_backButton->setDisabled(true);
  m_forwardButton->setDisabled(true);

  if (!webPanel)
    return;

  if (webPanel->history()->canGoBack())
    m_backButton->setDisabled(false);

  if (webPanel->history()->canGoForward())
    m_forwardButton->setDisabled(false);
}

void MainToolBar::setPluginButtonState(WebPanel* webPanel)
{
  if (!webPanel)
  {
    m_pluginButton->setDisabled(true);
    return;
  }

  m_pluginButton->setDisabled(false);
  if (webPanel->page()->settings()->testAttribute(QWebSettings::PluginsEnabled))
  {
    m_pluginButton->setIcon(QIcon("icons/pluginOn.png"));
    m_pluginButton->setToolTip("Turn plug-ins off for the current tab");
    m_pluginButton->setChecked(true);
  }
  else
  {
    m_pluginButton->setIcon(QIcon("icons/pluginOff.png"));
    m_pluginButton->setToolTip("Turn plug-ins on for the current tab");
    m_pluginButton->setChecked(false);
  }
}

WebPanel* MainToolBar::webPanel()
{
  if (m_tabWidget->currentIndex() == -1)
    return NULL;
  else
    return dynamic_cast<WebPanel*>(m_tabWidget->currentWidget());
}

void MainToolBar::backButtonReleased()
{
  if (webPanel())
    webPanel()->back();
}

void MainToolBar::forwardButtonReleased()
{
  if (webPanel())
    webPanel()->forward();
}

void MainToolBar::reloadButtonReleased()
{
  if (webPanel())
    webPanel()->reload();
}

void MainToolBar::stopButtonReleased()
{
  if (webPanel())
    webPanel()->stop();
}

void MainToolBar::locationBarActivated()
{
  QString url = m_locationBar->text();
  if (!webPanel())
  {
    qDebug() << QString("location bar activated (new tab):") << url;
    m_tabWidget->addNewTab(url);
  }
  else
  {
    qDebug() << QString("location bar activated (existing tab):") << url;
    QString url = m_locationBar->text();
    webPanel()->setUrl(url);
  }
}

void MainToolBar::pluginButtonToggled()
{
  bool checked = m_pluginButton->isChecked();
  if (checked)
    webPanel()->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
  else
    webPanel()->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, false);

  setPluginButtonState(webPanel());
  webPanel()->reload();
}

void MainToolBar::onTabChanged(WebPanel* webPanel)
{
  if (webPanel)
  {
    blockSignals(true);
    m_locationBar->blockSignals(true);
    m_locationBar->setText(webPanel->url().toString());
    m_locationBar->blockSignals(false);
    blockSignals(false);
  }
  setNavigationButtonStates(webPanel);
  setPluginButtonState(webPanel);
}

void MainToolBar::setStopButtonDisabled(bool disabled)
{
  m_stopButton->setDisabled(disabled);
}


