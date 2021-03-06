#ifndef QMLUTILS_HPP
#define QMLUTILS_HPP

#include <QQmlContext>

struct QMLUtils
{
public:
    static void RegisterQMLTypes();
    static void setContextProperties(QQmlContext *context);

    struct Sizes {
        int menuWidthSmallMode = 90;
        int menuWidthLargeMode = 200;

        int windowWidthSmallMode = 1180;
        int windowWidthLargeMode = 1250;

        int assetsViewWidthSmallMode = 130;
        int assetsViewWidthLargeMode = 150;

        int headerViewHeightSmallMode = 240;
        int headerViewHeightMediumMode = 300;
        int headerViewHeightLargeMode = 350;

        int coinsSizeSmallMode = 60;
        int coinsSizeMediumMode = 75;
        int coinsSizeLargeMode = 100;

        int menuItemHeightSmallMode = 70;
        int menuItemHeightLargeMode = 60;

        int closedTransactionHeight = 55;
        int openedTransactionHeight = 100;
    };

private:
    static void RegisterViewModels(const char *uri, int versionMinor, int versionMajor);
    static void RegisterModels(const char *uri, int versionMinor, int versionMajor);
    static void RegisterFonts();

};

#endif // QMLUTILS_HPP
