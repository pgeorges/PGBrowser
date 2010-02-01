#include "MainWindow.h"
#include "TabWidget.h"
#include "TabBar.h"
#include "WebPanel.h"
#include <QtGui/QPushButton>
#include <iostream>

TabWidget::TabWidget(MainWindow* window, QWidget* parent)
: QTabWidget(parent)
{
  TabBar* tabBar = new TabBar();
  setTabBar(tabBar);
  m_window = window;
  setDocumentMode(true);
  setTabsClosable(true);
  setMovable(true);
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));
  connect(this, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(createContextMenu(const QPoint&)));
}

TabWidget::~TabWidget()
{
}

void TabWidget::setTabTitle(QWidget* widget, QString& title)
{
  int index = indexOf(widget);
  setTabText(index, elideTitle(title));
}

void TabWidget::setTabIcon(QWidget* widget, const QIcon& icon)
{
  int index = indexOf(widget);
  QTabWidget::setTabIcon(index, icon);
}

void TabWidget::setTabToolTip(QWidget* widget, const QString& tooltip)
{
  int index = indexOf(widget);
  QTabWidget::setTabToolTip(index, tooltip);
}

bool TabWidget::isSelectedWidget(QWidget* widget)
{
  return currentIndex() == indexOf(widget);
}

WebPanel* TabWidget::addNewTab(bool switchToTab)
{
  WebPanel* webPanel = new WebPanel(m_window, this);
  addTab(webPanel, QString("Untitled"));

  if (switchToTab)
    setCurrentWidget(webPanel);

  return webPanel;
}

WebPanel* TabWidget::addNewTab(const QUrl& url, bool switchToTab)
{
  WebPanel* webPanel = new WebPanel(m_window, this, url);
  addTab(webPanel, elideTitle(url.toString()));

  if (switchToTab)
    setCurrentWidget(webPanel);

  return webPanel;
}

void TabWidget::closeTab(QWidget* widget)
{
  int index = indexOf(widget);
  closeTab(index);
}

void TabWidget::closeTab(int index)
{
  WebPanel* webPanel = dynamic_cast<WebPanel*>(widget(index));
  removeTab(index);
  delete webPanel;
}

QString TabWidget::elideTitle(QString title)
{
  //limit the length of the title 
  if (title.length() > 20)
  {
    title = title.mid(0, 20) + QString("...");
  }

  return title;
}

void TabWidget::tabChanged(int index)
{
  if (index == -1)
    emit tabChanged(0);
  else
    emit tabChanged(dynamic_cast<WebPanel*>(widget(index)));
  /*
  if (index == -1)
  {
    m_window->setLocationBarText(QString(""));
  }
  else
  {
    WebPanel* webPanel = dynamic_cast<WebPanel*>(widget(index));
    m_window->setLocationBarText(webPanel->url().toString());
  }

  m_window->mainToolBar()->setNavigationButtonStates();
  m_window->mainToolBar()->progressBarAction()->setVisible(false);*/
}

void TabWidget::createContextMenu(const QPoint& pos)
{
}


