#include "QMLUtils.hpp"
#include <Models/WalletTransactionsListModel.hpp>
#include <Models/WalletAssetsListModel.hpp>
#include <ViewModels/WalletAssetViewModel.hpp>
#include <ViewModels/ApplicationViewModel.hpp>
#include <ViewModels/EmulatorViewModel.hpp>

#include <QQmlEngine>

#define QML_REGISTER_TYPE_HELPER(Class) qmlRegisterType<Class>(uri, versionMajor, versionMinor, #Class)

//==============================================================================

void QMLUtils::RegisterQMLTypes()
{
    RegisterModels("com.xsn.models", 0, 1);
    RegisterViewModels("com.xsn.viewmodels", 0, 1);
}

//==============================================================================

void QMLUtils::setContextProperties(QQmlContext *context)
{
    QMLUtils::Sizes sizes;
    std::array<std::pair<QString, QVariant>, 16> sizeValues = {
        {
            {"menuWidthSmallMode", sizes.menuWidthSmallMode},
            {"menuWidthLargeMode", sizes.menuWidthLargeMode},

            {"windowWidthSmallMode", sizes.windowWidthSmallMode},
            {"windowWidthLargeMode", sizes.windowWidthLargeMode},

            {"assetsViewWidthSmallMode", sizes.assetsViewWidthSmallMode},
            {"assetsViewWidthLargeMode", sizes.assetsViewWidthLargeMode},

            {"headerViewHeightSmallMode", sizes.headerViewHeightSmallMode},
            {"headerViewHeightMediumMode", sizes.headerViewHeightMediumMode},
            {"headerViewHeightLargeMode", sizes.headerViewHeightLargeMode},

            {"coinsSizeSmallMode", sizes.coinsSizeSmallMode},
            {"coinsSizeMediumMode", sizes.coinsSizeMediumMode},
            {"coinsSizeLargeMode", sizes.coinsSizeLargeMode},

            {"menuItemHeightSmallMode", sizes.menuItemHeightSmallMode},
            {"menuItemHeightLargeMode", sizes.menuItemHeightLargeMode},

            {"closedTransactionHeight", sizes.closedTransactionHeight},
            {"openedTransactionHeight", sizes.openedTransactionHeight},
        }
    };

    for(auto property : sizeValues)
        context->setContextProperty(property.first, property.second);
}

//==============================================================================

void QMLUtils::RegisterViewModels(const char *uri, int versionMinor, int versionMajor)
{
    QML_REGISTER_TYPE_HELPER(WalletAssetViewModel);
    QML_REGISTER_TYPE_HELPER(EmulatorViewModel);

    qmlRegisterSingletonType<ApplicationViewModel>("com.xsn.viewmodels", 1, 0, "ApplicationViewModel",
                                                   [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        engine->setObjectOwnership(ApplicationViewModel::Instance(), QQmlEngine::CppOwnership);
        return ApplicationViewModel::Instance();
    });

}

//==============================================================================

void QMLUtils::RegisterModels(const char *uri, int versionMinor, int versionMajor)
{
    QML_REGISTER_TYPE_HELPER(WalletAssetsListModel);
}

//==============================================================================
