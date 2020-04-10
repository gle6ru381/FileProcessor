#include "readmask_test.h"
#include "../src/mask.cpp"

ReadMask_Test::ReadMask_Test() : QObject()
{
}

ReadMask_Test::~ReadMask_Test()
{
}

void ReadMask_Test::test_case1_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("expand");
    QTest::addColumn<QString>("mask");
    QTest::addColumn<QString>("result");

    QTest::newRow("1") << "file"
                       << "txt"
                       << "[N]"
                       << "file";
    QTest::newRow("2") << "text"
                       << "txt"
                       << "[N1]-[N]"
                       << "t-text";
    QTest::newRow("3") << "text"
                       << "txt"
                       << "[E1-3][N]"
                       << "txttext";
    QTest::newRow("4") << "abcd"
                       << "projct"
                       << "[N2-4][N3,2]-[E].[E1-3]"
                       << "bcdcd-projct.pro";
    QTest::newRow("testDate") << "abcd"
                              << "txt"
                              << "[Y-M-D]"
                              << "%Y%-%M%-%D%";
    QTest::newRow("testDate2") << "text"
                               << "txt"
                               << "[D:Y:M]"
                               << "%D%:%Y%:%M%";
}

void ReadMask_Test::test_case1()
{
    QFETCH(QString, name);
    QFETCH(QString, expand);
    QFETCH(QString, mask);
    QFETCH(QString, result);
    Mask a(name, expand, mask);
    QCOMPARE(a.getTotalName(), result);
}

QTEST_APPLESS_MAIN(ReadMask_Test)
