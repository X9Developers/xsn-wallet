#include <QtGlobal>
#include <QDebug>
#include <QStringList>
#include "HttpRange.hpp"

HttpRange::HttpRange(qint64 start, qint64 end)
    : _start(start)
    , _end(end)
{
    Q_ASSERT(start <= end);
}

qint64 HttpRange::start() const {
    return _start;
}

qint64 HttpRange::end() const {
    return _end;
}

bool HttpRange::isEmpty() const {
    return _start == 0 && _end == 0;
}

QString HttpRange::toString() const
{
    return QString("bytes=%1-%2").arg(_start).arg(_end);
}

// example: "bytes=0-1023"
bool HttpRange::tryParse(const QString& str, HttpRange& range)
{
    QStringList parts = str.trimmed().split('=');
    if (parts.length() == 2) {
        parts = parts[1].split('-');
        if (parts.length() == 2) {
            QString startStr = parts[0].trimmed();
            QString endStr = parts[1].trimmed();
            bool ok1 = false;
            bool ok2 = false;

            range._start = startStr.toLongLong(&ok1, 10);
            range._end = endStr.toLongLong(&ok2, 10);

            if (ok1 && ok2) {
                return true;
            }
        }
    }

    qWarning() << "HttpRange::tryParse() failed:" << str;
    return false;
}

QByteArray HttpRange::header() {
    return "Range";
}
