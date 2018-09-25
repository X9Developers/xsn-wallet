#include "ExtendedKeyPathBip44.hpp"

#include <QStringList>

static const unsigned int BIP32_HARDENED_KEY_LIMIT = 0x80000000;
static const unsigned int BIP43_PURPOSE_CONSTANT = 44;

ExtendedKeyPathBip44::ExtendedKeyPathBip44(unsigned coinType, unsigned accountIndex, bool isChange)
{
    auto buildHardenedIndex = [](unsigned childIndex) {
        return BIP32_HARDENED_KEY_LIMIT + childIndex;
    };

    _items = {
        buildHardenedIndex(BIP43_PURPOSE_CONSTANT),
        buildHardenedIndex(coinType),
        buildHardenedIndex(accountIndex),
        (isChange ? 1u : 0u)
    };
}

ExtendedKeyPathBip44 ExtendedKeyPathBip44::addChild(unsigned index)
{
    _items.push_back(index);
    return *this;
}

unsigned ExtendedKeyPathBip44::operator[](unsigned index) const
{
    return _items.at(index);
}

auto ExtendedKeyPathBip44::begin() const -> Container::const_iterator
{
    return _items.cbegin();
}

auto ExtendedKeyPathBip44::end() const -> Container::const_iterator
{
    return _items.cend();
}

QString ExtendedKeyPathBip44::toString(bool hex) const
{
    QStringList list("m");
    if(hex)
    {
        for(auto &&item : _items)
        {
            list << "0x" + QString::number(item, 16);
        }
    }
    else
    {
        for(size_t i = 0; i < _items.size(); ++i)
        {
            unsigned value = _items[i];
            bool isHardened = i < 3;
            list << QString::number(value - (isHardened ? BIP32_HARDENED_KEY_LIMIT : 0u)) +
                    (isHardened ? "'" : "");
        }
    }

    return list.join('/');
}
