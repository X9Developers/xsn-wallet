#ifndef CURRENCYMODEL_HPP
#define CURRENCYMODEL_HPP

#include <QAbstractListModel>
#include "Data/LocalCurrency.hpp"

class CurrencyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        SymbolRole,
        NameRole,
    };
    explicit CurrencyModel(QObject *parent = nullptr);
    virtual ~CurrencyModel() override;

    virtual int rowCount(const QModelIndex &parent) const override final;
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;

private:
    LocalCurrency::Currency _currencies;
};
#endif // CURRENCYMODEL_HPP
