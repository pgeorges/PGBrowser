#include "MainApplication.h"
#include "widgets/MainWindow.h"
#include <QtCore/QLibraryInfo>

int main(int argc, char **argv)
{
  MainApplication* application = MainApplication::application();
  if (application->isRunning())
  {
    if (argc >= 2)
      application->sendMessage(argv[1]);
    else
      application->sendMessage("");
    return 0;
  }

  qDebug() << QLibraryInfo::location(QLibraryInfo::PrefixPath);
  qDebug() << QLibraryInfo::location(QLibraryInfo::PluginsPath);

  MainWindow *window;

  if (argc >= 2)
    window = new MainWindow(QUrl(argv[1]));
  else
    window = new MainWindow();

  int execResult = application->exec();
  delete window;
  delete application;

  return execResult;
}

