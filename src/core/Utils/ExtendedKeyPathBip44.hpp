#ifndef EXTENDEDKEYPATHBIP44_HPP
#define EXTENDEDKEYPATHBIP44_HPP

#include <vector>
#include <QString>

class ExtendedKeyPathBip44
{
public:
    using Container = std::vector<unsigned>;
    ExtendedKeyPathBip44(unsigned coinTypeIndex, unsigned accountIndex = 0, bool isChange = false);

    ExtendedKeyPathBip44 addChild(unsigned index);
    unsigned operator[](unsigned index) const;

    typename Container::const_iterator begin() const;
    typename Container::const_iterator end() const;

    QString toString(bool hex = false) const;

private:
    Container _items;
};

#endif // EXTENDEDKEYPATHBIP44_HPP
