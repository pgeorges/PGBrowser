#include "PersistentCookieJar.h"
#include "../MainApplication.h"
#include <QtNetwork/QNetworkCookie>

PersistentCookieJar::PersistentCookieJar(QObject *parent) : QNetworkCookieJar(parent)
{
  loadState();
}

PersistentCookieJar::~PersistentCookieJar()
{
  saveState();
}

void PersistentCookieJar::saveState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  QByteArray cookieData;
  foreach (QNetworkCookie cookie, allCookies())
  {
    if (!cookie.isSessionCookie())
    {
      cookieData.append(cookie.toRawForm());
      cookieData.append("\n");
    }
  }
  settings.setValue("Application/Cookies", cookieData);
}

void PersistentCookieJar::loadState()
{
  QSettings settings(MainApplication::ORGANISATION_NAME, MainApplication::APPLICATION_NAME);
  QByteArray cookieData = settings.value("Application/Cookies").toByteArray();
  setAllCookies(QNetworkCookie::parseCookies(cookieData));
}


