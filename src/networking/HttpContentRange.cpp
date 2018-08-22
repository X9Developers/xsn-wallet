#include <QtGlobal>
#include <QDebug>
#include <QStringList>
#include "HttpContentRange.hpp"

HttpContentRange::HttpContentRange(qint64 start, qint64 end, qint64 length)
    : _start(start)
    , _end(end)
    , _length(length)
{
    Q_ASSERT(start <= end);
    Q_ASSERT(end <= length);
}

qint64 HttpContentRange::start() const {
    return _start;
}

qint64 HttpContentRange::end() const {
    return _end;
}

qint64 HttpContentRange::length() const {
    return _length;
}

bool HttpContentRange::isEmpty() const {
    return _start == 0 && _end == 0 && _length == 0;
}

QString HttpContentRange::toString() const
{
    return QString("bytes %1-%2/%3").arg(_start).arg(_end).arg(_length);
}

// example: "bytes 0-1023/146515"
bool HttpContentRange::tryParse(const QString& str, HttpContentRange& range)
{
    QString val = str.trimmed();
    if (val.startsWith("bytes")) {
        QStringList parts = str.trimmed().split('/');
        if (parts.length() == 2) {
            bool ok = false;
            range._length = parts[1].toLongLong(&ok, 10);
            if (ok) {
                parts = parts[0].mid(5).split('-');
                if (parts.length() == 2) {
                    range._end = parts[1].toLongLong(&ok, 10);
                    if (ok) {
                        parts = parts[0].split(' ');
                        if (parts.length() >= 2) {
                            range._start = parts.last().toLongLong(&ok, 10);
                            if (ok) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    qWarning() << "HttpContentRange::tryParse() failed:" << str;
    return false;
}

QByteArray HttpContentRange::header() {
    return "Content-Range";
}
