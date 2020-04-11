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
    QTest::newRow("testDate3") << "bcd"
                               << "txt"
                               << "[N][M]-[E][Y-D]"
                               << "bcd%M%-txt%Y%-%D%";
    QTest::newRow("testDate4") << "file"
                               << "txt"
                               << "abc[Y,M,D]-[D;M;Y]"
                               << "abc%Y%,%M%,%D%-%D%;%M%;%Y%";
    QTest::newRow("testTime1") << "text"
                               << "txt"
                               << "[hms]-[h-m-s]"
                               << "%h%%m%%s%-%h%-%m%-%s%";
    QTest::newRow("testTime2") << "abs"
                               << "text"
                               << "[N]-[h];[m;h;s]-[YMD]"
                               << "abs-%h%;%m%;%h%;%s%-%Y%%M%%D%";
    QTest::newRow("testTime3") << "nbd"
                               << "txt"
                               << "[ms;h]-[s;hm]"
                               << "%m%%s%;%h%-%s%;%h%%m%";
    QTest::newRow("testIter") << "text"
                              << "txt"
                              << "[C]"
                              << "%C0%";
    QTest::newRow("testIter2") << "text"
                               << "txt"
                               << "[C2,1][C]"
                               << "%C0%%C1%";
    QTest::newRow("testIter3") << "text"
                               << "txt"
                               << "[C2,1]-[YMD][N];[C10]"
                               << "%C0%-%Y%%M%%D%text;%C1%";
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

void ReadMask_Test::test_step_and_value_data()
{
    QTest::addColumn<QString>("mask");
    QTest::addColumn<QVector<uint>>("resultValue");

    QTest::newRow("test1") << "[C1,2]" << QVector<uint>{1, 3, 5, 7};
    QTest::newRow("test2") << "[C5,5]" << QVector<uint>{5, 10, 15, 20};
    QTest::newRow("test3") << "[C]" << QVector<uint>{1, 2, 3, 4, 5};
}

void ReadMask_Test::test_step_and_value()
{
    QFETCH(QString, mask);
    QFETCH(QVector<uint>, resultValue);

    Mask a("text", "txt", mask);
    for (int i = 0; i < resultValue.size(); i++) {
        QCOMPARE(a.getValue_C(0), resultValue[i]);
    }
}

QTEST_APPLESS_MAIN(ReadMask_Test)
