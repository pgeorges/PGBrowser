#ifndef __LOCATIONBAR__
#define __LOCATIONBAR__

#include <QtCore/QUrl>
#include <QtGui/QLineEdit>
#include <QtGui/QKeyEvent>

class LocationBar : public QLineEdit
{
  Q_OBJECT
  
public:
  LocationBar(QWidget *parent = 0);
  ~LocationBar();
  
private:
  void keyPressEvent(QKeyEvent *event);
};
#endif
