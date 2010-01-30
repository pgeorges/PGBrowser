#ifndef __PERSISTENTCOOKIEJAR__
#define __PERSISTENTCOOKIEJAR__

#include <QtNetwork/QNetworkCookieJar>

class PersistentCookieJar : public QNetworkCookieJar
{
  Q_OBJECT

public:
  PersistentCookieJar(QObject *parent);
  virtual ~PersistentCookieJar();

private:
  void saveState();
  void loadState();
};
#endif

