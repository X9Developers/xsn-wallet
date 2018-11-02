#include "LocalCurrency.hpp"

//==============================================================================

LocalCurrency::LocalCurrency()
{
    init();
}

//==============================================================================

const LocalCurrency::Currency LocalCurrency::currencies() const
{
    Currency result;
    for(auto currency : _currencies)
        result.push_back(currency);

    return result;
}

//==============================================================================

void LocalCurrency::init()
{
    _currencies.insert({"JPY", "Japanese Yen"});
    _currencies.insert({"MXN", "Mexican peso"});
    _currencies.insert({"NZD", "New Zealand dollar"});
    _currencies.insert({"TRY", "Turkish lira"});
    _currencies.insert({"USD", "United States dollar"});
    _currencies.insert({"UAH", "Ukraine hryvnia"});
}

//==============================================================================

void LocalCurrency::addCurrency(QString symbol, QString name)
{
    _currencies.emplace(symbol, name);
}

//==============================================================================
