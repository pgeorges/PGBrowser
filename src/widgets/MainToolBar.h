#ifndef __MAINTOOLBAR__
#define __MAINTOOLBAR__

#include "LocationBar.h"
#include "WebPanel.h"
#include <QtGui/QToolBar>
#include <QtGui/QPushButton>
#include <QtGui/QProgressBar>
#include <QtGui/QAction>

class TabWidget;

class MainToolBar : public QToolBar
{
  Q_OBJECT
  
public:
  MainToolBar(TabWidget* tabWidget, QWidget* parent);
  virtual ~MainToolBar();
  
  LocationBar* locationBar();
  QProgressBar* progressBar();
  QAction* progressBarAction();
  void setStopButtonDisabled(bool disabled);
  void setNavigationButtonStates(WebPanel* webPanel);
  void setPluginButtonState(WebPanel* webPanel);

private:
  WebPanel* webPanel();

private slots:
  void backButtonReleased();
  void forwardButtonReleased();
  void reloadButtonReleased();
  void stopButtonReleased();
  void locationBarActivated();
  void pluginButtonToggled();
  void onTabChanged(WebPanel* webPanel);

private:
  TabWidget* m_tabWidget;
  LocationBar* m_locationBar;
  QPushButton* m_backButton;
  QPushButton* m_forwardButton;
  QPushButton* m_reloadButton;
  QPushButton* m_stopButton;
  QPushButton* m_pluginButton;
  QProgressBar* m_progressBar;
  QAction* m_progressBarAction;
};
#endif
