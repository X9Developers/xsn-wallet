#ifndef LOCALBALANCE_HPP
#define LOCALBALANCE_HPP

#include <QObject>

class LocalCurrency : public QObject
{
public:
    using Currency = std::vector<std::pair<QString, QString>>;
    LocalCurrency();

    const Currency currencies () const;

public slots:

private:
    void init();
    void addCurrency(QString symbol, QString name);

private:
    std::map<QString, QString> _currencies;
};

#endif // LOCALBALANCE_HPP
