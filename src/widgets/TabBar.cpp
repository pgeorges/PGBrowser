#include "TabBar.h"

TabBar::TabBar()
: QTabBar()
{
}

TabBar::~TabBar()
{
}

QSize TabBar::tabSizeHint(int index)
{
  QSize baseSize = QTabBar::tabSizeHint(index);
  return QSize(baseSize.width() + 50, baseSize.height());
}

#include "TabBar.moc"

