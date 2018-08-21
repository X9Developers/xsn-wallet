#include "QMLUtils.hpp"
#include <Models/WalletTransactionsListModel.hpp>
#include <ViewModels/WalletAssetViewModel.hpp>

#include <QQmlEngine>

#define QML_REGISTER_TYPE_HELPER(Class) qmlRegisterType<Class>(uri, versionMajor, versionMinor, #Class)

//==============================================================================

void QMLUtils::RegisterQMLTypes()
{
    RegisterModels("com.xsn.models", 0, 1);
    RegisterViewModels("com.xsn.viewmodels", 0, 1);
}

//==============================================================================

void QMLUtils::RegisterViewModels(const char *uri, int versionMinor, int versionMajor)
{
    QML_REGISTER_TYPE_HELPER(WalletAssetViewModel);
}

//==============================================================================

void QMLUtils::RegisterModels(const char *uri, int versionMinor, int versionMajor)
{
    QML_REGISTER_TYPE_HELPER(WalletAssetViewModel);
}

//==============================================================================
