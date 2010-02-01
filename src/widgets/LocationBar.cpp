#include "LocationBar.h"

// LocationBar
LocationBar::LocationBar(QWidget *parent)
 : QLineEdit(parent)
{
}

LocationBar::~LocationBar()
{
}

void LocationBar::keyPressEvent(QKeyEvent *event)
{
    QString url = text().trimmed();

    if (event->key() == Qt::Key_Return)
    {
        if (url.toLower().indexOf("http://") != 0 ||
            url.toLower().indexOf("https://") != 0 ||
            url.toLower().indexOf("ftp://") != 0 ||
            url.toLower().indexOf("file://") != 0)
        {
            url = "http://" + url;
        }

        if (event->modifiers() & Qt::ControlModifier)
        {
            if (url.length() > 0)
            {
                if (url.toLower().indexOf("www.") != 7)
                {
                    url.insert(7, "www.");
                }

                int ind = url.indexOf('.', 12);
                if (ind == -1)
                {
                    url += ".com/";
                }
                else
                {
                    if (ind == url.length() - 1)
                        url += "com/";
                }
            }
        }

        setText(url);
    }

    QLineEdit::keyPressEvent(event);
}

