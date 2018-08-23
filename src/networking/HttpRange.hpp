#ifndef HTTPRANGE_HPP
#define HTTPRANGE_HPP

#include <QByteArray>

class HttpRange
{
public:
    HttpRange(qint64 start = 0, qint64 end = 0);

    qint64 start() const;
    qint64 end() const;
    bool isEmpty() const;
    QString toString() const;

public:
    static bool tryParse(const QString& str, HttpRange& range);
    static QByteArray header();

private:
    qint64 _start;
    qint64 _end;
};

#endif // HTTPRANGE_HPP
