#include "MainWindow.h"
#include "../MainApplication.h"
#include <QtCore/QString>
#include <QtGui/QStatusBar>
#include <QtWebKit/QWebSettings>
#include <iostream>

MainWindow::MainWindow(const QUrl& url)
: QMainWindow()
{
  MainApplication::application()->setActivationWindow(this);
  MainApplication::application()->registerWindow(this);

  QWebSettings::setIconDatabasePath(MainApplication::temporaryDir().path());

  //ensure the toolbars are unified on mac
  setUnifiedTitleAndToolBarOnMac(true);

  //create the tab widget
  m_tabWidget = new TabWidget(this, this);

  //create the main toolbar
  m_toolBar = new MainToolBar(m_tabWidget, this);

  //create the bookmarks toolbar
  m_bookmarksToolBar = new BookmarksToolBar(this);
  connect(m_bookmarksToolBar, SIGNAL(bookmarkTriggered(const QUrl&)),
          this, SLOT(onBookmarkTriggered(const QUrl&)));

  //create the find toolbar
  m_findToolBar = new QToolBar(this);
  setupFindToolBar();

  //add the widgets
  addToolBar(Qt::TopToolBarArea, m_toolBar);
  addToolBarBreak(Qt::TopToolBarArea);
  addToolBar(Qt::TopToolBarArea, m_bookmarksToolBar);
  addToolBar(Qt::BottomToolBarArea, m_findToolBar);
  setCentralWidget(m_tabWidget);

  //create and set up the menubar
  m_menuBar = new MenuBar(this);
  setMenuBar(m_menuBar);

  //set the window title and restore the state
  setWindowTitle(MainApplication::APPLICATION_NAME);
  restoreWindowState();

  //add a new tab to begin
  if (!url.toString().isEmpty())
    m_tabWidget->addNewTab(url);
  else
    m_tabWidget->addNewTab();

  connect(m_tabWidget, SIGNAL(tabChanged(WebPanel*)),
          this, SLOT(onTabChanged(WebPanel*)));

  show();
}

MainWindow::~MainWindow()
{
  MainApplication::application()->unregisterWindow(this);
}

WebPanel* MainWindow::webPanel()
{
  if (m_tabWidget->currentIndex() == -1)
    return NULL;
  else
    return dynamic_cast<WebPanel*>(m_tabWidget->currentWidget());
}

MenuBar* MainWindow::menuBar()
{
  return m_menuBar;
}

MainToolBar* MainWindow::mainToolBar()
{
  return m_toolBar;
}

TabWidget* MainWindow::tabWidget()
{
  return m_tabWidget;
}

void MainWindow::setupFindToolBar()
{
  m_findToolBar->setObjectName("FindToolBar");
  m_findToolBar->setVisible(false);

  QLabel* findLabel = new QLabel("Find Text: ");
  m_findLineEdit = new QLineEdit();
  m_findLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  connect(m_findLineEdit, SIGNAL(textChanged(const QString&)),
          this, SLOT(setFindText(const QString&)));

  //add a spacer
  QWidget* spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  //set the size of the buttons and the icon based on the height of the line edit
  QSize buttonSize(m_findLineEdit->sizeHint().height()-4, m_findLineEdit->sizeHint().height()-4);
  QSize iconSize(m_findLineEdit->sizeHint().height()-8, m_findLineEdit->sizeHint().height()-8);

  QPushButton* closeButton = new QPushButton(QIcon(QString("icons/stop.png")), "");
  closeButton->setToolTip("Close the find toolbar");
  closeButton->setFlat(true);
  closeButton->setFixedSize(buttonSize);
  closeButton->setIconSize(iconSize);
  connect(closeButton, SIGNAL(released()), this, SLOT(closeFindToolBar()));

  m_findToolBar->addWidget(findLabel);
  m_findToolBar->addWidget(m_findLineEdit);
  m_findToolBar->addWidget(spacer);
  m_findToolBar->addWidget(closeButton);
}

void MainWindow::setLocationBarText(const QString& text)
{
  m_toolBar->locationBar()->setText(text);
}

void MainWindow::saveWindowState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  settings.setValue("MainWindow/position", geometry());
  settings.setValue("MainWindow/state", saveState(1));
}

void MainWindow::restoreWindowState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  if (settings.value("MainWindow/position").isValid())
    setGeometry(settings.value("MainWindow/position").toRect());
  if (settings.value("MainWindow/state").isValid())
    restoreState(settings.value("MainWindow/state").toByteArray());
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
}

void MainWindow::closeEvent(QCloseEvent * event)
{
  saveWindowState();
  QMainWindow::closeEvent(event);
}

void MainWindow::showFindToolBar()
{
  m_findToolBar->setVisible(true);
  m_findLineEdit->setFocus(Qt::OtherFocusReason);
  m_findLineEdit->selectAll();
  setFindText(m_findLineEdit->text());
}

void MainWindow::closeFindToolBar()
{
  m_findToolBar->setVisible(false);
}

void MainWindow::findNext()
{
  setFindText(m_findLineEdit->text());
}

void MainWindow::setFindText(const QString& findString)
{
  if (!webPanel())
    return;

  webPanel()->page()->findText(findString, QWebPage::FindWrapsAroundDocument);
}

void MainWindow::onBookmarkTriggered(const QUrl& url)
{
  if (!webPanel())
    return;

  webPanel()->setUrl(url);
}

void MainWindow::onTabChanged(WebPanel* webPanel)
{
  mainToolBar()->progressBarAction()->setVisible(false);

  if (!webPanel)
  {
    setLocationBarText(QString(""));
  }
  else
  {
    if (webPanel->currentProgress() != 0)
    {
      mainToolBar()->progressBarAction()->setVisible(true);
      mainToolBar()->progressBar()->setValue(webPanel->currentProgress());
    }
  }


  mainToolBar()->progressBarAction()->setVisible(false);
}

#include "MainWindow.moc"

