#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class CoreTests : public QObject
{
    Q_OBJECT

public:
    CoreTests();
    ~CoreTests();

private slots:
    void test_case1();

};

CoreTests::CoreTests()
{

}

CoreTests::~CoreTests()
{

}

void CoreTests::test_case1()
{

}

QTEST_MAIN(CoreTests)

#include "tst_coretests.moc"
