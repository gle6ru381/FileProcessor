#ifndef RENAME_TEST_H
#define RENAME_TEST_H
#include <QtTest>

class renameTest : public QObject {
    Q_OBJECT

public:
    renameTest();
    ~renameTest();

private slots:
    void test_case1();
};

#endif // RENAME_TEST_H
