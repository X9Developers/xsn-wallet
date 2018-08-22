#ifndef HTTPCONTENTRANGE_HPP
#define HTTPCONTENTRANGE_HPP

#include <QByteArray>

class HttpContentRange
{
public:
    HttpContentRange(qint64 start = 0, qint64 end = 0, qint64 length = 0);

    qint64 start() const;
    qint64 end() const;
    qint64 length() const;
    bool isEmpty() const;
    QString toString() const;

public:
    static bool tryParse(const QString& str, HttpContentRange& range);
    static QByteArray header();

private:
    qint64 _start;
    qint64 _end;
    qint64 _length;
};

#endif // HTTPCONTENTRANGE_HPP
