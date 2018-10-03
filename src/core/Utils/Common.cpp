#include "Common.hpp"
#include <QMetaType>

void RegisterCommonQtTypes()
{
    qRegisterMetaType<AssetID>("AssetID");
}
