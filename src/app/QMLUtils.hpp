#ifndef QMLUTILS_HPP
#define QMLUTILS_HPP


struct QMLUtils
{
public:
    static void RegisterQMLTypes();

private:
    static void RegisterViewModels(const char *uri, int versionMinor, int versionMajor);
    static void RegisterModels(const char *uri, int versionMinor, int versionMajor);

};

#endif // QMLUTILS_HPP
