#include "LocationBar.h"
#include <QtCore/QString>

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
        if (!url.contains("http://", Qt::CaseInsensitive) &&
            !url.contains("https://", Qt::CaseInsensitive) &&
            !url.contains("ftp://", Qt::CaseInsensitive) &&
            !url.contains("file://", Qt::CaseInsensitive))
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

